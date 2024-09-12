import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split, cross_val_score, GridSearchCV
from sklearn.metrics import classification_report,confusion_matrix,accuracy_score
from sklearn.tree import DecisionTreeClassifier, plot_tree
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn.preprocessing import LabelEncoder

# Load the dataset加载数据集
url = "https://archive.ics.uci.edu/ml/machine-learning-databases/adult/adult.data"
columns = ['age', 'workclass', 'fnlwgt', 'education', 'education_num', 'marital_status', 'occupation',
           'relationship', 'race', 'sex', 'capital_gain', 'capital_loss', 'hours_per_week', 'native_country', 'income']
# data = pd.read_csv('./adult/adult.data', names=columns, na_values=' ?')
data = pd.read_csv(url, names=columns, na_values=' ?')
# data overview
# load top 5 rows values from adult dataset展示数据前5行
data.head(5)
print ("Rows     : " ,data.shape[0])#打印数据集的行数和列数
print ("Columns  : " ,data.shape[1])
print ("\nFeatures : \n" ,data.columns.tolist())#打印数据集的列名
print ("\nMissing values :  ", data.isnull().sum().values.sum())# 打印数据集中的缺失值数量
print ("\nUnique values :  \n",data.nunique())
# Let's understand the type of values present in each column of our adult dataframe 'data'
# The info() method : Used to get a quick description of the data, in particular the total number of rows,columns and each attribute's type and number of non-null values...etc
data.info()
data.describe()

# checking "NaN" total values present in particular 'workclass' feature检查特定“工作类”功能中存在的“NaN”总值
df_check_missing_workclass = (pd.isnull(data['workclass'])).sum()
df_check_missing_workclass
# checking "NaN" total values present in particular 'occupation' feature检查特定“职业”特征中存在的“NaN”总值
df_check_missing_occupation = (pd.isnull(data['occupation'])).sum()
df_check_missing_occupation
# checking "NaN" values, how many are there in the whole dataset
df_missing = pd.isnull(data).sum()
df_missing
# find out percentage of "NaN" value present across the dataset
percent_missing = pd.isnull(data).sum() * 100/len(data)
percent_missing
# Let's find total number of rows which doesn't contain any missing value as '?'
data.apply(lambda x: pd.notnull(x),axis=1).sum()

# Drop rows with missing values删除包含缺失值的行
# write your code here -------
data_clean = data.dropna()#用于删除数据集中包含缺失值的行，并将结果保存到data_clean中

# Preprocessing: Convert categorical variables to numerical using one-hot encoding使用独热编码转换分类变量为数值型
data = pd.get_dummies(data, columns=['workclass', 'education', 'marital_status', 'occupation', 'relationship', 'race', 'sex', 'native_country'])
# Separate fatures and target variable分离特征和目标变量
# write your code here -------
X = data.drop('income', axis=1)  # 特征数据
y = data['income']               # 目标变量

# or encode categorical variables using label Encoder或使用标签编码器编码分类变量
# select all categorical variables选择所有分类变量
data_categorical = data.select_dtypes(include=['object'])
data_categorical.head()
# Apply label encoder to df_categorical应用标签编码器
# write your code here -------
label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)  # 对目标变量应用标签编码
# Next, Concatenate df_categorical dataframe with original df (dataframe
# first, Drop earlier duplicate columns which had categorical values丢弃早先duplicate的分类列
# write your code here --------
data.drop(data_categorical.columns, axis=1, inplace=True)#从data数据集中删除了所有的分类数据列。
#参数axis=1表示按列操作，inplace=True表示在原数据集上进行修改，而不是返回一个新的数据集。
data.head()
data.info()

# Next, Since here we have income as target/predicted variable we can see it's showing integer though we need to figure out labelled as <=50𝐾 𝑎𝑛𝑑 >50K and >50K as categorical.
# Separate features and target variable
# write your code here --------

# Split data into train and test sets using method of train_test_split()将数据分割为训练集和测试集
# write your code here --------
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
#test_size=0.3：指定测试集的大小为30%。这意味着70%的数据将用于训练，30%的数据将用于测试。
#random_state=42：用来设置随机种子，这样每次运行划分数据集的操作时都能得到相同的训练集和测试集，有助于结果的可重现性。
#X_train：训练集的特征数据,X_test：测试集的特征数据,y_train：训练集的目标数据,y_test：测试集的目标数据
# Build a decision tree classifier创建决策树分类器实例
# write your code here --------
dt_classifier = DecisionTreeClassifier()
# Define hyperparameters for tuning
params = {
    'max_depth': [3, 5, 7, 10],
    'min_samples_split': [2, 5, 10],
    'min_samples_leaf': [1, 2, 4]
}
# params = {
#     'max_depth': [6, 6.5, 7, 7.5, 8],
#     'min_samples_split': [9, 10, 11],
#     'min_samples_leaf': [3, 4, 5],
# }#改进的参数尝试

# Hyperparameter tuning using GridSearchCV
grid_search = GridSearchCV(dt_classifier, params, cv=5)#5折交叉验证
grid_search.fit(X_train, y_train)

# Get the best hyperparameters
best_params = grid_search.best_params_
print("Best Hyperparameters:", best_params)

# Train the decision tree classifier with the best parameters使用最佳超参数训练决策树分类器
best_dt_classifier = DecisionTreeClassifier(**best_params)
# write your code here --------
best_dt_classifier.fit(X_train, y_train)

# Evaluate the model with accuracy
train_accuracy = best_dt_classifier.score(X_train, y_train)
test_accuracy = best_dt_classifier.score(X_test, y_test)
print("Train Accuracy:", train_accuracy)
print("Test Accuracy:", test_accuracy)

# Evaluate the model with more metrics
y_pred = best_dt_classifier.predict(X_test)
print(classification_report(y_test,y_pred))
# Printing confusion matrix and accuracy
print(confusion_matrix(y_test,y_pred))
print(accuracy_score(y_test,y_pred))

# Visualize the decision tree
plt.figure(figsize=(20,10),dpi=600)
plot_tree(best_dt_classifier, feature_names=X.columns, class_names=["<=50K", ">50K"], filled=True)
plt.show()
