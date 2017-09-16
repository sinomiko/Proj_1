# encoding: utf-8

import  pandas as pd
import  numpy as np

# 二、Pandas 常见的基本方法
#
# 2.1 数据读取与存储
#
# Pandas 支持大部分常见数据文件读取与存储。一般清楚下，读取文件的方法以 pd.read_ 开头，而写入文件的方法以 pd.to_ 开头。详细的表格如下。
#
# 此处输入图片的描述
#
# 拿刚刚下载好的数据文件举例，如果没有下载，请看 1.5 小节。
df = pd.read_csv("los_census.csv") #读取 csv 文件
print df

# 可以看到，文件已经读取出来了。由于列数太多，所以分段显示了。输出的最下方会有一个行数和列数的统计。这里是 319 行 X 7 列。

# 我们可以发现，由 pandas 读取的文件就已经是 DataFrame 结构了。上面演示了 csv 文件的读取，其余格式的文件也很相似。
#
# 不过，很多时候我们拿到手的数据是像 los_census.txt 文件样式的数据，如下图所示

df2 = pd.read_table("los_census.txt") #读取 txt 文件
print df2

# 其实 los_census.txt 也就是 los_census.csv 文件，因为 csv 文件又叫逗号分隔符文件，数据之间采用逗号分割。
#
# 那么，我们怎样将这种文件转换为 DataFrame 结构的数据呢？这里就要使用到读取方法中提供的一些参数了，例如 sep[] 分隔符参数。


df3 = pd.read_table("los_census.txt", sep=',') #读取 txt 文件
print df3

# 除了 sep，读取文件时常用的参数还有：
#
# header=，用来选择将第几行作为列索引名称。
# names=[]，自定义列索引名称。

df4 = pd.read_csv("los_census.csv", header=1 ) #将第二行作为列索引名称。
print df4

df5 = pd.read_csv("los_census.csv", names=['A', 'B', 'C', 'D', 'E', 'F', 'G']) #自定义列索引名称。
print df5

# 好了，说了这么久的读取文件，再说一说存储文件。存储文件的方法也很简单。比如我们将 los_census.csv 文件，存储为 json 格式的文件。
df6 = pd.read_csv("los_census.csv")  #读取 csv 文件

df6.to_json("1.json") # 将其存储为 json 格式文件

# 当然，你也可以通过 to_excel("1.xlsx") 储存为 Excel 默认支持的 .xlsx 格式。只是，需要注意在线环境会报错。这时候需要再补充安装 openpyxl 包就好了：
#
# sudo pip install openpyxl

# 2.2 Head & Tail
#
# 有些时候，我们读取的文件很大。如果全部输出预览这些文件，既不美观，又很耗时。还好，Pandas 提供了 head() 和 tail() 方法，它可以帮助我们只预览一小块数据。
#
# 顾名思义，head() 方法就是从数据集开头预览，不带参数默认显示头部的 5 条数据，你也可以自定义显示条数。


df21 = pd.read_csv("los_census.csv")  #读取 csv 文件

print df21.head() # 默认显示前 5 条
print df21.head(7) # 显示前 7 条

# tail() 方法就是从数据集尾部开始显示了，同样默认 5 条，可自定义。
print df21.tail() # 默认显示后 5 条
print df21.tail(7) # 显示后 7 条

# 2.3 统计方法
#
# Pandas 提供了几个统计和描述性方法，方便你从宏观的角度去了解数据集。
#
# 1. describe()
#
# describe() 相当于对数据集进行概览，会输出该数据集的计数、最大值、最小值等。
print df21.describe()

# 例如上面，针对一个 DataFrame 会对每一列的数据单独统计。

# 2. idxmin() & idxmax()
#
# idxmin() 和 idxmax() 会计算最小、最大值对应的索引标签。
print df21.idxmin()
print df21.idxmax()

# 3. count()
#
# count() 用于统计非空数据的数量。
print df21.count()

# 4.value_counts()
#
# value_counts() 仅仅针对 Series，它会计算每一个值对应的数量统计。
s = pd.Series(np.random.randint(0, 9, size=100)) # 生成一个 Series，并在 0-9 之间生成 100 个随机值。

print s
print s.value_counts()

# 2.4 计算方法
#
# 除了统计类的方法，Pandas 还提供了很多计算类的方法。
#
# 1. sum()
#
# sum() 用于计算数值数据的总和。
print df21.sum()

# 2. mean()
#
# mean() 用于计算数值数据的平均值。
print df21.mean()

# 3. median()
#
# median() 用于计算数值数据的算术中值。
print df21.median()

# 2.5 标签对齐
#
# 索引标签是 Pandas 中非常重要的特性，有些时候，由于数据的缺失等各种因素导致标签错位的现象，或者想匹配新的标签。于是 Pandas 提供了索引标签对齐的方法 reindex()。
#
# reindex() 主要有三个作用：
#
# 重新排序现有数据以匹配新的一组标签。
# 在没有标签对应数据的位置插入缺失值（NaN）标记。
# 特殊情形下，使用逻辑填充缺少标签的数据（与时间序列数据高度相关）。

s25 = pd.Series(data=[1, 2, 3, 4, 5], index=['a', 'b', 'c', 'd', 'e'])

print s25
print s25.reindex(['e', 'b', 'f', 'd'])

# 我们可以看到，重新排列的数据中，原有索引对应的数据能自动匹配，而新索引缺失的数据通过 NaN 补全。
#
# 当然，对于 DataFrame 类型的数据也是一样的。
df26 = pd.DataFrame(data={'one': [1, 2, 3], 'two': [4, 5, 6], 'three': [7, 8, 9]}, index=['a', 'b', 'c'])
print df26
print df26.reindex(index=['b', 'c', 'a'], columns=['three', 'two', 'one'])
# 你甚至还可以将上面 Series 的数据按照下面的 DataFrame 的索引序列对齐。
print s25.reindex(df26.index)

# 2.6 排序
#
# 既然是数据处理，就少不了排序这一常用的操作。在 Pandas 中，排序拥有很多「姿势」，下面就一起来看一看。
#
# 1. 按索引排序
#
# 首先是按照索引排序，其方法为Series.sort_index()或者是DataFrame.sort_index()。
df261 = pd.DataFrame(data={'one': [1, 2, 3], 'two': [4, 5, 6], 'three': [7, 8, 9], 'four': [10, 11, 12]}, index=['a', 'c', 'b'])

print df261
# 下面按索引对行重新排序：
print df261.sort_index()
# 或者添加参数，进行倒序排列：
print df261.sort_index(ascending=False)

# 1. 按数值排序
#
# 第二种是按照数值排序，其方法为Series.sort_values()或者是DataFrame.sort_values()。举个例子：
# 将第三列按照从小到大排序：
print df261.sort_values(by='three')
# 也可以同时按照两列
print df261[['one', 'two', 'three', 'four']].sort_values(by=['one','two'])