# -*- coding: utf-8 -*-
"""
@author: miko
"""


from sklearn.feature_extraction import DictVectorizer
import csv
from sklearn import tree
from sklearn import preprocessing
from sklearn.externals.six import StringIO


import numpy as np
np.set_printoptions(threshold = 1e6)#设置打印数量的阈值


# Read in the csv file and put features into list of dict and list of class label
allElectronicsData = open(r'D:\development\DailyImprove\July机器学习与深度学习\(Part One)深度学习基础\代码与素材\代码与素材(1)\01DTree\AllElectronics.csv', 'r')
reader = csv.reader(allElectronicsData)
#headers = reader.next()
headers = next(reader)


print(headers)
print("~"*10+"headers end"+"~"*10)


featureList = []
labelList = []


for row in reader:  # 遍历每一列
    labelList.append(row[len(row)-1])   # 标签列表
    rowDict = {}                        # 每一行的所有特征放入一个字典
    for i in range(1, len(row)-1):      # 左闭右开 遍历从age到credit_rating
        rowDict[headers[i]] = row[i]    # 字典的赋值
    featureList.append(rowDict)         #将每一行的特征字典装入特征列表内


print(featureList)
print("~"*10+"featureList end"+"~"*10)


# Vetorize features
vec = DictVectorizer() # Vectorizer 矢量化
dummyX = vec.fit_transform(featureList).toarray()


print("dummyX: " + str(dummyX))
print(vec.get_feature_names())
print("~"*10+"dummyX end"+"~"*10)


print("labelList: " + str(labelList))
print("~"*10+"labelList end"+"~"*10)


# vectorize class labels
lb = preprocessing.LabelBinarizer()
dummyY = lb.fit_transform(labelList)
print("dummyY: " + str(dummyY))
print("~"*10+"dummyY end"+"~"*10)


# Using decision tree for classification
# clf = tree.DecisionTreeClassifier()
clf = tree.DecisionTreeClassifier(criterion='entropy')  # 标准 熵
clf = clf.fit(dummyX, dummyY)
print("clf: " + str(clf))




# Visualize model
with open("allElectronicInformationGainOri.dot", 'w') as f:
    # 输出到dot文件里，安装 Graphviz软件后，可使用 dot -Tpdf allElectronicInformationGainOri.dot -o outpu.pdf 命令 转化dot文件至pdf可视化决策树
    f = tree.export_graphviz(clf, feature_names=vec.get_feature_names(), out_file=f)




oneRowX = dummyX[0, :]
print("oneRowX: " + str(oneRowX))


newRowX = oneRowX
newRowX[0] = 1
newRowX[2] = 0
print("newRowX: " + str(newRowX))


predictedY = clf.predict(newRowX)
print("predictedY: " + str(predictedY))

