# encoding: utf-8

import  pandas as pd
import  numpy as np

# 三、 一维数据 Series
#
# Series 是 Pandas 中最基本的 1 维数据形式。其可以储存整数、浮点数、字符串等形式的数据。Series 的新建方法如下：
#
# s = pandas.Series(data, index=index)
# 其中，data 可以是字典、numpy 里的 ndarray 对象等。index 是数据索引，索引是 pandas 数据结构中的一大特性，它主要的功能是帮助我们更快速地定位数据，这一点后面会谈到。
#
# 3.1 字典 -> Series
#
# 下面，我们将把不同类型的数据转换为为 Series。首先是字典类型
d31 = {'a' : 10, 'b' : 20, 'c' : 30}

s1 = pd.Series(d31, index=['b', 'c', 'd', 'a'])
print s1
# 你会发现，pandas 会自动匹配人为设定的索引值和字典转换过来的索引值。而当索引无对应值时，会显示为 NaN 缺失值。
#
# 3.2 ndarray -> Series
#
# ndarray 是著名数值计算包 numpy 中的多维数组。我们也可以将 ndarray 直接转换为 Series。
data = np.random.randn(5)
index=['a','b','c','d','e']
s=pd.Series(data,index)
print  s

print 2*s

# 上面的两个例子中，我们都指定了 index 的值。而当我们非人为指定索引值时，Pandas 会默认从 0 开始设置索引值。

s = pd.Series(data)
print s

# 当我们需要从一维数据 Series 中返回某一个值时，可以直接通过索引完成。
print s1['a']
print s[1]

# 四、二维数据 DataFrame
#
# DataFrame 是 Pandas 中最为常见、最重要且使用频率最高的数据结构。你可以想到它箱型为电子表格或 SQL 表具有的结构。DataFrame 可以被看成是以 Series 组成的字典。它和 Series 的区别在于，不但具有行索引，且具有列索引。
#
# DataFrame 可以用于储存多种类型的输入：
#
# 一维数组、列表、字典或者 Series 字典。
# 二维 numpy.ndarray。
# 结构化的 ndarray。
# 一个 Series。
# 另一个 DataFrame。

# 4.1 Series 字典 -> DataFrame
d={'one':pd.Series([1,2,3,4,1],index),
   'two':pd.Series([5,4,3,2,1],index)}
df=pd.DataFrame(d)
print  df

# 4.2 ndarrays 或 lists 字典 -> DataFrame
# 列表构成的字典
d2 = {'one' : [1, 2, 3, 4], 'two' : [4, 3, 2, 1]}

df1 = pd.DataFrame(d2) # 未指定索引
df2 = pd.DataFrame(d2, index=['a', 'b', 'c', 'd']) # 指定索引

print df1
print df2

# 4.3 带字典的列表 -> DataFrame
import pandas as pd

# 带字典的列表
d3 = [{'a': 1, 'b': 2}, {'a': 5, 'b': 10, 'c': 20}]

df3 = pd.DataFrame(d3)

print df3

# 4.4 DataFrame.from_ 方法
#
# pandas 的 DataFrame 下面还有 4 个以 from_ 开头的方法，这也可以用来创建 Dataframe。

d4 = [('A', [1, 2, 3]), ('B', [4, 5, 6])]
c4 = ['one', 'two', 'three']

df4 = pd.DataFrame.from_items(d4, orient='index', columns=c4)

print df4

# 4.5 列选择，添加，删除
#
# 接下来，我们延续上面的 4.4 里面的数据来演示。
#
# 在一维数据结构 Series 中，我们用 df['标签'] 来选择行。而到了二维数据 DataFrame 中，df['标签'] 表示选择列了。例如：
print df4['one']

# 删除列的方法为 df.pop('列索引名')，例如：
df4.pop('one')
print df4

# 添加列的方法未 df.insert(添加列位置索引序号, '添加列名', 数值)，例如：
df4.insert(2, 'four', [10, 20])
print df4


# 五、三维数据 Panel
#
# Panel 是 Pandas 中使用频率较低的一种数据结构，但它是三维数据的重要容器。
#
# 5.1 面板数据
#
# Panel data 又称面板数据，它是计量经济学中派生出来的一个概念。在计量经济学中，数据大致可分为三类：截面数据，时间序列数据，以及面板数据.
# 而面板数据即是截面数据与时间序列数据综合起来的一种数据类型。
#
# 简单来讲，截面数据指在某一时间点收集的不同对象的数据。而时间序列数据是指同一对象在不同时间点所对应的数据集合。
#
# 这里引用一个城市和 GDP 关系的示例来解释上面的三个概念（面板数据）：
#
# 截面数据：
#
# 例如城市：北京、上海、重庆、天津在某一年的 GDP 分别为10、11、9、8（单位亿元）。
# 时间序列数据:
#
# 例如：2000、2001、2002、2003、2004 各年的北京市 GDP 分别为8、9、10、11、12（单位亿元）。
# 面板数据：
#
# 2000、2001、2002、2003、2004 各年中国所有直辖市的 GDP 分别为（单位亿元）： 北京市分别为 8、9、10、11、12； 上海市分别为 9、10、11、12、13； 天津市分别为 5、6、7、8、9； 重庆市分别为 7、8、9、10、11。

# 5.2 Panel 构成
#
# 在 Pandas 中，Panel 主要由三个要素构成：
#
# items: 每个项目（item）对应于内部包含的 DataFrame。
# major_axis: 每个 DataFrame 的索引（行）。
# minor_axis: 每个 DataFrame 的索引列。
# 简而言之，在 Pandas 中，一个 Panel 由多个 DataFrame 组成。下面就生成一个 Panel。
wp = pd.Panel(np.random.randn(2, 5, 4), items=['Item1', 'Item2'], major_axis=pd.date_range('1/1/2000', periods=5), minor_axis=['A', 'B', 'C', 'D'])

print wp
#
# 我们可以看到，wp 由 2 个项目、5 个主要轴和 4 个次要轴组成。其中，主要轴由 2000-01-01 到 2000-01-05 这 5 天组成的时间序列，次轴从 A 到 D。
#
# 你可以输出 Item1 看一看。

print wp['Item1']
print wp['Item2']

# 可以看到，这两个 Dataframe 的行索引及列索引是一致的。由于数据是随机生成的，所以不一致。
#
# 5.2 Panel 的未来
#
# 由于 Panel 在 Pandas 中的使用频率远低于 Series 和 DataFrame，所以 Pandas 决定在未来的版本中将 Panel 移除，转而使用 MultiIndex DataFrame 来表示多维数据结构。
#
# 这里，可以用到 Panel.to_frame() 输出多维数据结构。就拿上面的例子继续：
print wp.to_frame()
#################### random funtion note#############################
# numpy.random.randn(d0, d1, …, dn)
#
# 其中d0, d1, …, dn)为整数型，输出标准正太分布的矩阵。
#
# 生产的分布，则sigma * np.random.randn(…) + mu，如下：
#
# 若我们要生成满足正太分布为N(3，2.5^2)，2行4列的array
#
# 2.5 * np.random.randn(2, 4) + 3
# 输出：
#
# array([
#     [-4.49401501,  4.00950034, -1.81814867,  7.29718677],
#     [ 0.39924804,  4.68456316,  4.99394529,  4.84057254]
# ])

# numpy.random.randint(low, high=None, size=None)
#
# 生产一定范围内的元素为整数的array。
#
# low为下限，size为生成的array大小，如果high为none则生成0~low的均匀分布随机数，若指定了high，那么生产low~high的均匀分布随机数。如生产2×4的在（0，4）的array，则：
#
# np.random.randint(5, size=(2, 4))
# 输出：
#
# array([
#     [4, 0, 2, 1],
#     [3, 2, 2, 0]
# ])
######################################################

