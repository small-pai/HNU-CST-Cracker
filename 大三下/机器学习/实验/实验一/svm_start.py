import random
import matplotlib.pyplot as plt

def loadData(b_n,e_n):
    path = 'breast-cancer_scale.txt'
    f = open(path,'r')
    line = f.readline()
    y = []
    phi =[]
    while line:
        line = line.rstrip().split(' ')
        feat = []# 存放当前行的特征
        if int(line[0]) == 2:
            y.append(1.0)# 癌症类标签
        else:
            y.append(-1.0)# 非癌症类标签
        for d in line[1:]:
            feat.append(float(d.split(':')[1]))# 提取特征
        phi.append(feat)
        line = f.readline() # 读取下一行
    f.close()
    return(y[b_n:e_n],phi[b_n:e_n])

# 点积函数，用于计算两个向量的点积
def dp(x1,x2):
    ele_wis_prod = [x1[i]*x2[i] for i in range(len(x1))]
    return sum(ele_wis_prod)

# 计算梯度的函数
def accumGrad(gradw,gradb,w,phi,y,b,c_o_n):
    # write your code here to compute the gradients of w and b
    n = len(y)
    for i in range(n):
        if y[i] * (dp(w, phi[i]) + b) < 1:
            # 对于每个特征进行梯度累加
            for j in range(len(w)):
                gradw[j] -= y[i] * phi[i][j]
            # 偏置的梯度
            gradb -= y[i]
    # 包括权重衰减
    for j in range(len(w)):
        gradw[j] += 2 * c_o_n * w[j]

    
# 计算hinge损失函数
def hingeloss(w, b, phi, y,c_o_n):
    # write your code here to compute the value of the loss function
    loss = 0
    n = len(y)
    for i in range(n):
        loss += max(0, 1 - y[i] * (dp(w, phi[i]) + b))
    # L2范数正则化项
    regularization_loss = 0.5 * c_o_n * sum(wi**2 for wi in w)
    # 平均损失加正则化
    total_loss = loss / n + regularization_loss
    return total_loss
        
def main():
    b_n = 0 # the beginning index of training data训练数据开始索引
    e_n = 400 # the end index of training data训练数据结束索引
    y,phi=loadData(b_n,e_n)# 加载训练数据

    # The number of features in phi 
    m = len(phi[0]) #特征数量
    # The number of Samples in training dataset
    n = len(y)# 样本数量
    loss_history= []# 存储每次迭代的损失
    lrate = 0.11     # 学习率
    epochs = 100    # 迭代次数
    C = 1.0 
    c_o_n = C / n #coefficent for regularization term   # 正则化系数
    # c_o_n = 0.1
    # creating an array of random values to initialize the weights
    w = [random.random() for k in range(m)] # 随机初始化权重
    b = 0   # 初始化偏置

     # 文件打开用于写入最终模型参数
    mf = open('svm.txt','w')
    for i in range(epochs):
        print('iteration {}'.format(i).center(30,'-'))
        # calculate gradients
        gradw = [.0 for k in range(m)]
        gradb = 0
        # write your code here
        accumGrad(gradw, gradb, w, phi, y, b, c_o_n)  # 梯度计算
        # update the weights of w and b
        for k in range(m):
            w[k] = w[k] - gradw[k] * lrate# 更新权重
        b = b - gradb * lrate # 更新偏置
        # output loss of the objective funtion
        obj_loss = hingeloss(w,b,phi,y,c_o_n) # 计算损失
        print('the objective value is: {:.4f}'.format(obj_loss))
        loss_history.append(obj_loss) 
    for j in range(len(w)+1):
        if j == len(w):
            mf.write(str(b)+'')
        else:
            mf.write(str(w[j])+' ')
    mf.close()
    # 绘制损失曲线
    plt.plot(range(epochs),loss_history)
    plt.show()

    ## test part ###
    b_n = 400 # the beginning index of training data# 测试数据开始索引
    e_n = 638 # the end index of training data # 测试数据结束索引
    lbl, feat = loadData(b_n,e_n)
    # load trained models from svm.txt# 打开模型文件
    mf = open('svm.txt','r')
    if mf:
        w_str = mf.readline().rstrip().split()

        # get float model parameters
        wei = [float(w_str[i]) for i in range(len(w_str)-1)]
        bia = float(w_str[len(w_str)-1])
        
        n_correct = 0
        for f, l in zip(feat, lbl):
            # predict cancer or not for one instance
            score = dp(f, wei)+bia# 计算每个测试样本的得分
            y_pred = -1. # 初始化预测为非癌症
            if score > 0:
                y_pred = 1.0 # 得分大于0预测为癌症
            if y_pred == l:
                n_correct += 1 # 正确预测次数
            print('groundtruth: {}, prediction: {}'.format(l, y_pred))
        
        # report accuracy
        print('accuracy: {}'.format(n_correct/len(lbl)))# 输出准确率

    mf.close()# 关闭文件

if __name__ == '__main__':
    main()        
