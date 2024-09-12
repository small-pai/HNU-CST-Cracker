#!/usr/bin/env python
# coding: utf-8

# In[45]:


# 如果使用天池平台，请增加以下代码
# !conda install nltk # don't install here, using terminal to install it
# !pip install seaborn
# !pip install --user -U nltk
# !apt-get install fastjar
# !jar xvf /mnt/workspace/downloads/179283/flickr8k.zip


# In[10]:


import numpy as np
import pandas as pd
import os
from tqdm import tqdm
import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import os
from torch.utils.data import DataLoader
import warnings
import matplotlib.pyplot as plt
import seaborn as sns
from textwrap import wrap
import string
import re
import cv2
import nltk
from nltk.translate.bleu_score import corpus_bleu,SmoothingFunction
from torchsummary import summary
from torch import randperm
# pls uncomment the below two statements if you use google CoLab
# from google.colab import drive
# drive.mount('/content/drive')
# 导入所需库，包括深度学习框架、数据处理、图像处理等库


plt.rcParams['font.size'] = 12
sns.set_style("dark")
warnings.filterwarnings('ignore')


# ## Image Captioning
# 
# **What is Image Captioning ?**
# - Image Captioning is the process of generating textual description of an image. It uses both Natural Language Processing and Computer Vision to generate the captions.
# - This task lies at the intersection of computer vision and natural language processing. Most image captioning systems use an encoder-decoder framework, where an input image is encoded into an intermediate representation of the information in the image, and then decoded into a descriptive text sequence.
# 
# **CNNs + RNNs (LSTMs)**
# - To perform Image Captioning we will require two deep learning models combined into one for the training purpose
# - CNNs extract the features from the image of some vector size aka the vector embeddings. The size of these embeddings depend on the type of pretrained network being used for the feature extraction
# - LSTMs are used for the text generation process. The image embeddings are concatenated with the word embeddings and passed to the LSTM to generate the next word
# - For a more illustrative explanation of this architecture check the Modelling section for a picture representation

# <img src="imcaption.png">

# ## Preprocessing the text captions of the dataset

# In[11]:

# 数据预处理
image_path = './Images'
# pls uncomment the below statement if you use google CoLab
# image_path = './drive/MyDrive/ColabNotebooks/Images'


# In[12]:


data = pd.read_csv("./captions.txt")#代码从一个CSV文件中读取图像的路径和对应的文字描述。
# pls uncomment the below statement if you use google CoLab
# data = pd.read_csv("./drive/MyDrive/ColabNotebooks/captions.txt")
data.head()
data["length"] = data["caption"].apply(lambda row: len(row.strip().split()))
sns.displot(data=data, x='length', palette='mako', kind='kde', fill=True,aspect=2)


# **Preprocess raw text to:**
# - lower case
# - remove punctuation

# In[13]:

# 清洗文本数据，转换为小写并去除标点符号
regex = re.compile('[%s]' % re.escape(string.punctuation))
def clean_text(row):
    row = str(row).strip()
    row = row.lower()
    return regex.sub("", row)


# In[14]:


data.columns = [col.strip() for col in data.columns]
data["caption"] = data["caption"].apply(clean_text)
data.head()
len(data)


# **Observing that, almost sentence length is <= 30. So I think 30 is good choice as max_length**

# In[15]:


captions = data["caption"].tolist()
captions[:10]


# **Do some statistic to count the occurence frequency of words in our captions**

# In[16]:


word_freq = {}
for caption in captions:
    caption = caption.strip()
    for word in caption.split():
        if word not in word_freq:
            word_freq[word] = 0
        word_freq[word] += 1


# **See the top 30 words appear the most and the least**

# In[17]:


dict(sorted(word_freq.items(), key=lambda item: item[1])[:30])
dict(sorted(word_freq.items(), key=lambda item: item[1], reverse=True)[:30])


# ## Tokenization and Encoded Representation
# **By having preprocessed captions, we start to build vocabulary in our dataset and convert string to token**
# - The words in a sentence are separated/tokenized and encoded in a one hot representation
# - These encodings are then passed to the embeddings layer to generate word embeddings
# 
# <img src='tocken.gif'>
# 

# In[19]:


# Some special tokens for RNN model...
UNK = "#UNK"
PAD = "#PAD"
START = "#START"
END = "#END"


# In[20]:

# 创建词汇表并对文本进行编码
def build_vocab(captions, word_freq, count_threshold=5):
    """
    This function builds `vocab` dictionary from list of text captions.
    Also, add constant PAD, UNK, START, END to `vocab`.
    Add a word to vocab if its occurence frequency is larger than `count_threshold`

    Parameters
    ----------
    captions: a list of preprocessed text captions above.
    word_freq: a dictionary of word occurence frequency.
    count_threshold: a int to use when building vocab.

    Returns
    -------
    vocab: an dictionary vocabulary of key-value pair which is:
        -> key: string text
        -> value:  token index
    inv_vocab: an inverse dictionary vocabulary of key-value pair which is:
        -> key: token index
        -> value: string text

    E.g: vocab = {"two": 4, "young": 5, "guys": 6, ...}
         inv_vocab = {4: "two", 5: "young", 6: "guys", ...}
    """
    vocab = {
        PAD: 0,
        UNK: 1,
        START: 2,
        END: 3
    }
    index = 4

    for caption in captions:
        caption = caption.strip().split(" ")
        for word in caption:
            if word and word_freq[word] >= count_threshold and word not in vocab:
                vocab[word] = index
                index += 1

    inv_vocab = {v: k for k, v in vocab.items()}
    return vocab, inv_vocab

vocab, inv_vocab = build_vocab(captions, word_freq)


# In[21]:


def convert_captions(captions, vocab, max_length=30):
    """
    Convert text captions to index token based on `vocab`.
    If a word not in vocab, replace it by the token index of `UNK` constant.
    Also, add `START` constant to the beginning of the sentence and
            `END` constant to the end of the sentence.
    After add `START` and `END` constant, if the length is still < 30,
        use `PAD` constant to fill remaining positions.

    Parameters
    ----------
    captions: a list of preprocessed text captions above.
    vocab: a dictionary vocabulary of key-value pair which is:
        -> key: string text
        -> value: token index
    max_length: an int denotes fixed maximum length to the captions.

    Returns
    -------
    tokens: a list of tokens get from `vocab`
    """
    tokens = [[vocab[PAD]]*max_length for _ in range(len(captions))]
    for i, caption in enumerate(captions):
        caption = caption.strip().split()
        tokens[i][0] = vocab[START]
        j = 1
        for word in caption[:max_length-2]:
            if word not in vocab:
                tokens[i][j] = vocab[UNK]
            else:
                tokens[i][j] = vocab[word]
            j += 1
        tokens[i][j] = vocab[END]
    return tokens


# In[22]:


tokens = convert_captions(captions, vocab)
img_paths = list(data["image"])


# ## Data Preparation (Image preprocessing and caption tockens preparing)
# - Since Image Caption model training like any other neural network training is a highly resource utillizing process, we cannot load the data into the main memory all at once, and hence we need to generate the data in the required format batch wise
# - The outputs will be the proprocessed images (cropped or resized) and their corresonding caption text tockens for the training process

# In[23]:

# 定义数据集处理类
class ImageCaptioningDataset(torch.utils.data.Dataset):

    def __init__(self, img_paths, tokens):
        """
        img_paths: a list of image path we get from dataframe
        tokens: a list of tokens that we converted from text captions
        """
        self.img_paths = [os.path.join(image_path, p) for p in img_paths]
        self.tokens = tokens
        assert len(self.img_paths) == len(self.tokens), "Make sure len(img_paths) == len(tokens)."

    def __getitem__(self, index):
        """
        Get image path and token. Then load image path to numpy array image. Convert to pytorch tensor if it's necessary.
        """
        img_path = self.img_paths[index]
        token = self.tokens[index]
        img = cv2.imread(img_path)
        img = self._resize_img(img, shape=(300, 300))
        img = torchvision.transforms.ToTensor()(img)
        token = torch.as_tensor(token)
        return img, token

    def __len__(self):
        return len(self.img_paths)

    def _resize_img(self, img, shape=(300, 300)):
        h, w = img.shape[0], img.shape[1]
        pad_left = 0
        pad_right = 0
        pad_top = 0
        pad_bottom = 0
        if h > w:
            diff = h - w
            pad_top = diff - diff // 2
            pad_bottom = diff // 2
        else:
            diff = w - h
            pad_left = diff - diff // 2
            pad_right = diff // 2
        cropped_img = img[pad_top:h-pad_bottom, pad_left:w-pad_right, :]
        cropped_img = cv2.resize(cropped_img, shape)
        return cropped_img


# In[24]:


dataset = ImageCaptioningDataset(img_paths, tokens)


# ## Model architecture

# In this architecture, the encoder is CNN which outputs a feature vector. Then, the decoder RNN (LSTM) uses this feature vector as initial hidden states.
# 
# **Modelling**
# - The image embedding representations are concatenated with the first word of sentence ie. starseq and passed to the LSTM network
# - The LSTM network starts generating words after each input thus forming a sentence at the end
# 
# <img src="./model.png">
# 

# In[25]:


MAX_LENGTH = 30
NUM_VOCAB = len(vocab)
BATCH_SIZE = 128 #128
BATCH_SIZE_TEST = 128
EPOCH = 10
if torch.cuda.is_available():
    DEVICE = "cuda"
elif torch.backends.mps.is_available():
    DEVICE = torch.device("mps")
else:
    DEVICE = "cpu"
print(DEVICE)


# **Image Feature Extraction**
# - The best practice is to use pretrained models from ImageNet: VGG, Resnet, Alexnet, Googlenet,... We can call those pretrained models are the backbones.
# - We'll use ResNet34 (or ResNet18) as the image feature extraction (encoder).
# - Since the final layer of the ResNet34 model for the feature extraction is 1000, our image embeddings will be a vector of size 1000
# 
# <img src="./resnet.png">

# In[26]:

# 模型构建，包括编码器和解码器
class CNNEncoder(nn.Module):

    def __init__(self) -> None:
        super().__init__()
        
        # online download
        # self.cnn = torchvision.models.resnet18(pretrained=True) 
        
        # offline # 使用 ResNet34 作为底层模型
        self.cnn = torchvision.models.resnet34(pretrained=False) 
        # pre = torch.load('resnet18-f37072fd.pth')
        pre = torch.load('resnet34-333f7ec4.pth')
        self.cnn.load_state_dict(pre)

    def forward(self, img):
        return self.cnn(img)# 返回经过 CNN 处理的图像特征


# **Define LSTM decoder:**
# 
# In this class, you should have to define nn.Embedding, nn.LSTM, nn.Linear,... to appropriate training model.
# <div><img width = '600', src="LSTM_Cell.png"></div>

# In[27]:

#该类定义了一个长短期记忆网络解码器，用于基于图像特征生成文字描述。
class RNNDecoder(nn.Module):

    def __init__(self, num_vocab) -> None:
        super().__init__()
        # 特征降维
        self.bottleneck = nn.Sequential(
            nn.Linear(1000, 512), # nn.Linear(1000, 512),
            nn.ReLU(),
            nn.Linear(512, 256), # nn.Linear(512, 256),
            nn.ReLU()
        )
        self.num_vocab = num_vocab
        self.embedding = nn.Embedding(num_embeddings=num_vocab, embedding_dim=256, padding_idx=0)
        self.num_layers = 1
        self.bidirectional = False
        self.rnn = nn.LSTM(input_size=256, hidden_size=256, num_layers=self.num_layers, batch_first=True, bidirectional=self.bidirectional)
        self.classifier = nn.Sequential(
            nn.Linear(256, 512), # nn.Linear(256, 512),
            nn.ReLU(),
            nn.Linear(512, 1024), # nn.Linear(512, 1024),
            # nn.ReLU(),
            # nn.Linear(1024, 2048), #nn.Linear(1024, 2048),
            # nn.ReLU(),
            nn.Linear(1024, num_vocab) # nn.Linear(2048, num_vocab)
  
        )
        self.softmax = nn.Softmax(dim=-1)

    def forward(self, input, img_embeded, prediction=False,test_ce=False):
        img_embeded = self.bottleneck(img_embeded)
        img_embeded = torch.stack([img_embeded]*(self.num_layers), dim=0)
        if prediction:
            output = []
            hidden = (img_embeded, img_embeded)
            out = input
            for i in range(MAX_LENGTH):
            # while out != vocab[END] and len(output) <= MAX_LENGTH:
                if test_ce:
                    if i == 0:
                        # import pdb
                        # pdb.set_trace()
                        out = torch.tensor([[out]*img_embeded.size(1)]).to(DEVICE)
                    else:
                        out = torch.tensor(out).transpose(0,1).to(DEVICE)
                    # import pdb
                    # pdb.set_trace()
                    out = self.embedding(out)
                    out = out.permute(1,0,2)
                    out, hidden = self.rnn(out, hidden)
                    out = self.classifier(out)
                    output.append(out)
                    out = self.softmax(out)
                    out = torch.argmax(out, dim=-1)
                    # import pdb
                    # pdb.set_trace()
                    out = out.cpu().numpy().tolist()
                else:
                    out = torch.tensor([[out]]).to(DEVICE)
                    out = self.embedding(out)
                    out, hidden = self.rnn(out, hidden)
                    out = self.classifier(out)
                    out = self.softmax(out)
                    out = torch.argmax(out, dim=-1)
                    out = out.squeeze().item()
                    if out == vocab[PAD]:
                        continue
                    if out == vocab[END]:
                        break
                    output.append(out)
        else:
            input = self.embedding(input)
            output, (h, c) = self.rnn(input, (img_embeded, img_embeded))
            output = self.classifier(output)
        return output


# ## Train Model
# 
# **Define the image caption model by combinning the encoder and decoder.**
# - In this part, you should combine what you defined to train model (Dataset, Encoder, Decoder,...)
# - In the predict method, it is used to generate the captions of input images at the inference time, where the images are passed along with the first word, followed by which the text embedding of each new word is passed to generate the next word.
# - In the train method, it is used to train the model with batch SGD, where the images are passed along with all words in the caption to use teaching-forced method to train the model.
# - In the test method, it is juse used to test the model with batch style on test set.

# In[28]:

#整合之前定义的编码器和解码器，提供预测、测试和训练模型的方法
class ImageCaptioningModel:

    def __init__(self, encoder : CNNEncoder, decoder : RNNDecoder, train_dataset : ImageCaptioningDataset,test_dataset : ImageCaptioningDataset):
        self.device = DEVICE
        self.encoder = encoder.to(self.device)
        self.encoder.eval()
        self.decoder = decoder.to(self.device)
        self.train_dataloader = DataLoader(train_dataset, batch_size=BATCH_SIZE, shuffle=True)
        self.test_dataloader = DataLoader(test_dataset, batch_size=BATCH_SIZE_TEST)
        self.optimizer = optim.Adam(decoder.parameters())
        self.loss = nn.CrossEntropyLoss()

    def predict(self, img,test_ce=False):
        with torch.no_grad():
            img_embed = self.encoder(img)
            caption = vocab[START]
            caption = self.decoder(caption, img_embed, prediction=True,test_ce=test_ce)
            
        if test_ce:
            return caption
        else:
            text = [inv_vocab[t] for t in caption]
            text = " ".join(text)
            return text

    def test(self):
        bleu_metric = 0
        pbar = tqdm(self.test_dataloader, total=len(self.test_dataloader),desc="iterate the testing dataset")
        test_loss = 0
        for i,(img, caption_true) in enumerate(pbar):
            img = img.to(self.device)
            caption_true = caption_true.to(DEVICE)
            output = self.predict(img,test_ce = True)
            
            # cross-entropy metric
            # import pdb
            # pdb.set_trace()
            # output = [vocab[t] for t in caption]
            out = output[0]
            for i in range(1,len(output)):
               out = torch.cat([out,output[i]],dim=1)
            out = out.permute(0, 2, 1)
            loss = self.loss(out[:,:,:-1], caption_true[:,1:])
            # loss = self.loss(out, caption_true)
            test_loss += loss.tolist()
            
            # bleu_metric
        #     text = [inv_vocab[t] for t in caption_true[-1].tolist()]
        #     text_true = " ".join(text)
        #     bleu_metric =+ corpus_bleu([text_true.split()], [caption.split()],smoothing_function=SmoothingFunction().method4)
        
        # return bleu_metric
        return test_loss/len(pbar)

    def train(self):
        train_loss = []
        test_loss = []
        for e in range(EPOCH):
            pbar = tqdm(self.train_dataloader, total=len(self.train_dataloader), desc="Epoch: {}".format(e+1))
            epoch_loss = 0
            for i, (img, caption) in enumerate(pbar):
                img = img.to(self.device)
                caption = caption.to(self.device)
                img_embed = self.encoder(img)
                output = self.decoder(caption[:, :-1], img_embed)
                output = output.permute(0, 2, 1)
                loss = self.loss(output, caption[:, 1:])
                epoch_loss += loss

                self.optimizer.zero_grad()
                loss.backward()
                self.optimizer.step()

                # pbar.set_description(desc="Epoch " + str(e+1) + " - Loss: %.5f" % (loss.item()))
                # loss = loss/len(pbar)
                # train_loss.append(f'{train_loss:.2f}')
                # print(f"the test performance is {self.test()}")

                if ((i+1)%100) == 0:
                    plt.imshow(img[-1].cpu().detach().numpy().transpose((1, 2, 0)))
                    output = self.predict(img[-1].unsqueeze(0))
                    plt.title(output)
                    plt.show()
            # compute the total loss of each epoch
            pbar.set_description(desc="Epoch " + str(e+1) + " - Loss: %.5f" % (loss.item()))
            # import pdb
            # pdb.set_trace()
            train_loss.append(f'{epoch_loss.tolist()/len(pbar):.2f}')
            test_loss.append(self.test())
            print(f"the test loss is {self.test()}")
        return train_loss,test_loss


# **Split the dataset into training and testing datasets**

# In[29]:


num_samples = len(dataset) # num_samples = 40455

num_train = round(num_samples*0.8)
num_test = num_samples-num_train
train_data,test_data= torch.utils.data.random_split(dataset,[num_train,num_test])
print(len(train_data),len(test_data))

# use only a fractional data to train and test the model
# lenth = randperm(num_samples).tolist()
# indices = range(int(round(num_samples*0.5)))# use half of the dataset
# sub_dataset = torch.utils.data.Subset(dataset, indices)
# num_samples = len(sub_dataset)
# num_train = round(num_samples*0.8)
# num_test = num_samples-num_train
# train_data,test_data= torch.utils.data.random_split(sub_dataset,[num_train,num_test])
# print(len(train_data),len(test_data))


# **Start the training**

# In[ ]:


print(DEVICE)
cnn = CNNEncoder()
rnn = RNNDecoder(num_vocab=NUM_VOCAB)
model = ImageCaptioningModel(encoder=cnn, decoder=rnn, train_dataset=train_data,test_dataset=test_data)
train_loss,test_loss = model.train()
# test_loss = model.test()


# ## Inference
# - Learning Curve (Loss Curve)
# - Assessment of Generated Captions (by checking the relevance of the caption with respect to the image, BLEU Score will not be used in this version)

# **Learning Curve**
# <!-- - The model has clearly overfit, possibly due to less amount of data
# - We can tackle this problem in two ways
#     1. Train the model on a larger dataset Flickr40k
#     2. Attention Models -->

# In[22]:


# Force the type conversion of the data stored in the list (you can choose the type of conversion, here is float)
# import pdb# 将训练和测试损失列表中的所有元素转换为浮点数
# pdb.set_trace()
for i in range(len(train_loss)):
    train_loss[i] = float(train_loss[i])
for i in range(len(test_loss)):
    test_loss[i] = float(test_loss[i])
# x axis# x 轴数据，表示训练周期
x1 = range (0, len(train_loss))
y1 = train_loss
x2 = range (0, len(test_loss))
y2 = test_loss
# loss figure# 配置绘图环境，设置图像大小
plt.figure(figsize=(20,8))
# 绘制训练损失和验证损失的折线图
plt. plot(x1, y1, '.-')# 训练损失折线图
plt. plot(x2, y2, '.-')# 验证损失折线图
# 设置图表标题和坐标轴标签
plt. xlabel( 'epoch')
plt. ylabel('loss')
plt.title('model loss')
# 图例显示，指明不同折线图的含义
plt.legend(['train', 'val'], loc='upper left')
# 设置 y 轴的刻度范围，方便查看损失值的变化
my_yTicks2 = np. arange (0, 10, 1)
plt.yticks(my_yTicks2)
# 保存绘制的图形到本地文件
plt.savefig("loss.jpg")
plt.show()# 显示图形
# plt.figure(figsize=(20,8))
# plt.plot(history.history['loss'])
# plt.plot(history.history['val_loss'])
# plt.title('model loss')
# plt.ylabel('loss')
# plt.xlabel('epoch')
# plt.legend(['train', 'val'], loc='upper left')
# plt.show()


# **Caption generation of Samples**
# - Use the predict function to generate the captions of input images at the inference time.
# - Here the images are passed along with the first word, followed by which the text embedding of each new word is passed to generate the next word
# - Please be **NOTED** that **The visualized image with captions, where "the #START....#END" is the true caption, while the true caption is immediately followed by the predicted caption.** 

# **Taking 15 Random Samples for Caption Prediction and Visualization**

# In[23]:


# def display_images(img):
#     plt.figure(figsize = (20 , 20))
#     n = 0
#     for i in range(15):
#         n+=1
#         plt.subplot(5 , 5, n)
#         plt.subplots_adjust(hspace = 0.7, wspace = 0.3)
#         # image = readImage(f"../input/flickr8k/Images/{temp_df.image[i]}")
#         plt.imshow(img[-1].cpu().detach().numpy().transpose((1, 2, 0)))
#         # plt.imshow(image)
#         plt.title("\n".join(wrap(caption, 20)))
#         plt.axis("off")
        
#         plt.imshow(img[-1].cpu().detach().numpy().transpose((1, 2, 0)))
#         output = self.predict(img[-1].unsqueeze(0))
#         plt.title(output)
#         plt.show()
        
num_samples = 15
plt.figure(figsize = (20 , 20))
n = 0
sampler = torch.utils.data.RandomSampler(test_data,replacement=False, num_samples=num_samples)
# import pdb
# pdb.set_trace()
random_test_dataloader = DataLoader(test_data, batch_size=1, shuffle=False, sampler=sampler)
for i, (img,caption) in enumerate(random_test_dataloader):
    n+=1
    plt.subplot(5, 5, n)
    plt.subplots_adjust(hspace = 0.7, wspace = 0.3)
    img = img.to(DEVICE)
    text_img = model.predict(img[-1].unsqueeze(0))
    plt.imshow(img[-1].cpu().detach().numpy().transpose((1, 2, 0)))
    # plt.title("\n".join(wrap(text_img, 20)))
    
    # show the ground truth caption on images also
    text = [inv_vocab[t] for t in caption[-1].tolist()]
    text_true = []
    # import pdb
    # pdb.set_trace()
    for t in text:
        if t == END:
            text_true.append(t)
            break
        else:
            text_true.append(t)
    # import pdb
    # pdb.set_trace()
    text_true = " ".join(text_true)
    plt.title("\n".join(wrap(text_true, 20))+"\n"+"\n".join(wrap(text_img, 20)))
    plt.axis("off")


# ## Results
# - As we can clearly see there is some redundant caption generation e.g. Dog running through the water, overusage of blue shirt for any other coloured cloth
# - The model performance can be further improved by training on more data and using attention mechanism so that our model can focus on relevant areas during the text generation
# - We can also leverage the interprettability of the attention mechanism to understand which areas of the image leads to the generation of which word

# <p style='font-size: 18px'><strong>Conclusion: </strong>This may not be the best performing model, but the objective of this kernel is to give a gist of how Image Captioning problems can be approached. In the future work of this kernel <strong>Attention model</strong> training and <strong>BLEU Score</strong> assessment will be performed.</p>

# In[ ]:




