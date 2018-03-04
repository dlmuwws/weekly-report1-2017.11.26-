#决策树算法

from sklearn.feature_extraction import DictVectorizer  #导入数据，并将输入输出数据转换为标准形式
from sklearn import tree
from sklearn import preprocessing
from sklearn.externals.six import StringIO
import csv

# Read data set (using list and dict)
Info = open(r'C:\Users\wws199633\Desktop\dtdata.csv', 'r+')  
reader = csv.reader(Info)
headers = next(reader)   #第一行，feature的名称
print(headers)
#建立两个列表储存
featureList = []
labelList = []

for row in reader:
    labelList.append(row[len(row)-1])
    rowDict = {}
    for i in range(1, len(row)-1):
        rowDict[headers[i]] = row[i]   #headers[i]是键，row[i]是对应的值
    featureList.append(rowDict)

print(featureList)



#对数据集的数据转化为决策树包识别的类型
vec = DictVectorizer()
trans_feature = vec.fit_transform(featureList) .toarray()#变成数组
print("trans_feature: ",trans_feature)
print(vec.get_feature_names())
print("labelList: ",labelList)

#把labelist进行转化
trans_label = preprocessing.LabelBinarizer().fit_transform(labelList)
print("trans_label: ",trans_label)

# Using decision tree for classification,调用包来建立决策树
clf = tree.DecisionTreeClassifier(criterion='entropy') #分类器，ID3准则
result = clf.fit(trans_feature,trans_label)  #建模
print("result: " ,result)


#最后输出.dot文件结果，并用Graphviz输出决策树的图形
# Visualize model
with open("allElectronicInformationGainOri.dot", 'w') as f:
    f = tree.export_graphviz(clf, feature_names=vec.get_feature_names(), out_file=f)

test_feature = trans_feature[0, :]
test_feature[0] = 1
test_feature[2] = 0
print("test_feature: ",test_feature)
#
#对已有的决策树对象，进行测试
predicted = clf.predict(test_feature.reshape(1,-1))#行数是1,列数不固定，reshape(行，列)
print("predict result: " ,predicted)

print('finish')
Info.close()
