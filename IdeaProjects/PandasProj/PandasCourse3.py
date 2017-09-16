# encoding: utf-8

import  pandas as pd
import  numpy as np

# 1.1 实验内容
#
# Pandas 是非常著名的开源数据处理工具，我们可以通过它对数据集进行快速读取、转换、过滤、分析等一系列操作。除此之外，Pandas 拥有强大的缺失数据处理与数据透视功能，可谓是数据预处理中的必备利器。这是 Pandas 使用教程的第 3 章节，将学会使用 Pandas 对数据进行选择与变换。
#
# 1.2 实验知识点
#
# 基于索引数字选择
# 基于标签名称选择
# 数据随机取样
# 条件语句选择
# where() 方法选择
# query() 方法选择
# 二、数据选择
#
# 在数据预处理过程中，我们往往会对数据集进行切分，只将需要的某些行、列，或者数据块保留下来，输出到下一个流程中去。这也就是这里所说的数据选择。
#
# 由于 Pandas 的数据结构中存在索引、标签，所以我们可以通过多轴索引完成对数据的选择。
#
# 2.1 基于索引数字选择
#
# 当我们新建一个 DataFrame 之后，如果未自己指定行索引或者列对应的标签，那么 Pandas 会默认从 0 开始以数字的形式作为行索引，并以数据集的第一行作为列对应的标签。其实，这里的「列」也有数字索引，默认也是从 0 开始，只是未显示出来。
#
# 所以，我们首先可以基于数字索引对数据集进行选择。这里用到的 Pandas 中的 .iloc 方法。该方法可以接受的类型有：
#
# 整数。例如：5
# 整数构成的列表或数组。例如：[1, 2, 3]
# 布尔数组。
# 可返回索引值的函数或参数。
# 下面，我们还是用 los_census.csv 数据集演示该方法的使用。如果未下载该数据集，请看 1.5 节。
df = pd.read_csv("los_census.csv")

print df.head()
# 首先，我们可以选择前 3 行数据。这和 python 或者 numpy 里面的切片很相似
print df.iloc[:3]
# 我们还可以选择特定的一行。

print df.iloc[5]
# 那么选择多行是不是 print df.iloc[1, 3, 5] 这样呢？答案是错误的。df.iloc[] 的 [[行]，[列]] 里面可以同时接受行和列的位置，如果你直接键入 df.iloc[1, 3, 5] 就会报错。
#
# 所以，很简单。如果你想要选择 1，3，5 行，可以这样做。

print df.iloc[[1, 3, 5]]
# 选择行学会以后，选择列就应该能想到怎么办了。你可以先暂停浏览下面的内容，自己试一试。
#
# 例如，我们要选择第 2-4 列。

print df.iloc[:, 1:4]

# 这里选择 2-4 列，输入的却是 1:4。这和 python 或者 numpy 里面的切片操作非常相似。
#
# 既然我们能定位行和列，那么只需要组合起来，我们就可以选择数据集中的任何一块数据了。
#
# 2.2 基于标签名称选择
#
# 除了根据数字索引选择，我们还可以直接根据标签对应的名称选择。这里用到的方法和上面的 iloc 很相似，少了个 i 为 df.loc[]。
#
# df.loc[] 可以接受的类型有：
#
# 单个标签。例如：2 或 'a'，这里的 2 指的是标签而不是索引位置。
# 列表或数组包含的标签。例如：['A', 'B', 'C']。
# 切片对象。例如：'A':'E'，注意这里和上面切片的不同支持，首位都包含在内。
# 布尔数组。
# 可返回标签的函数或参数。
# 下面，我们来演示 df.loc[] 的用法。我们先随机生成一个 DataFrame。
df22 = pd.DataFrame(np.random.randn(6,5),index=list('abcdef'),columns=list('ABCDE'))

print df22
# 先选择前 3 行：

print df22.loc['a':'c']
# 再选择 1，3，5 行：

print df22.loc[['a', 'c', 'd']]
# 然后，选择 2-4 列：

print df22.loc[:, 'B':'D']
# 最后，选择 1，3 行和 C 后面的列：

print df22.loc[['a','c'], 'C':]

# 2.3 数据随机取样
#
# 上面，的 .iloc 和 .loc 可用于精准定位数据块。而 Pandas 同样也提供了随机取样的方法，用于满足各种情况。随机取样用 .sample() 完成，下面我们就演示一下它的用法。
#
# 首先，看一看 Series 数据结构。
s23 = pd.Series([0,1,2,3,4,5,6,7,8,9])

print s23.sample()
# 我们可以看到，默认情况下 .sample() 返回了一个数值。注意，前面的 2 是数字索引，后面的 2 才是值。
#
# 我们可以通过 n= 参数，设定返回值的数量。
print s23.sample(n=5)
# 同样也可以用 frac= 参数设定返回数量的比例。

print s23.sample(frac=.6) # 返回 60% 的数值

# 对应 DataFrame 而言，过程也很相似，只是需要选择坐标轴。举个例子：


df24 = pd.DataFrame(np.random.randn(6,5),index=list('abcdef'),columns=list('ABCDE'))

print df24
print df24.sample(n=3)

# 默认会返回行，如果要随机返回 3 列。需要添加 axis= 参数。

print df24.sample(n=3, axis=1)
# 2.4 条件语句选择
#
# 数据选择的时候，我们还可以加入一些条件语句，从而达到对数据筛选的目的。这个过程和 numpy 里面的效果很相似。我们先举一个 Series 的例子：

s24 = pd.Series(range(-5, 5))

print s24
print s24[(s24 < -2) | (s24 > 1)] # 添加 逻辑或 条件

# 对于 DataFrame 也是相似的。


df242 = pd.DataFrame(np.random.randn(6,5),index=list('abcdef'),columns=list('ABCDE'))

print df242
print df242[(df242['B'] > 0) | (df242['D'] < 0)]  # 添加条件

# 2.5 where() 方法选择
#
# 接下来，再介绍一种通过 where() 方法进行数据选择得方法。DataFrame 和 Series 都带有 where()，可以通过一些判断句来选择数据。举个例子：

df25 = pd.DataFrame(np.random.randn(6,5),index=list('abcdef'),columns=list('ABCDE'))

print df25
print df25.where(df25 < 0)  # 添加条件
# .where(df < 0) 会返回所有负值，而非负值就会被置为空值 NaN。
# 你也可以对判断条件以外得值重新替代，例如这里将非负值全部变号为负值。

print df25.where(df25 < 0, -df25)  # 筛选负值并将正值变号

# 故，where() 实际上期待了匹配和替换得效果。我们可以借助该方法实现对数据的自由设定。
#
# 2.6 query() 方法选择
#
# 针对数据变换和筛选的方法还很多，除了上面的提到的，Pandas 0.13 之后的版本中增加了 query() 实验性方法，该方法也可以被用来选择数据。
#
# query() 是 DataFrame 具有的方法，你可以通过一个比较语句对满足行列条件的值进行选择，举个例子：
df26 = pd.DataFrame(np.random.rand(10, 5), columns=list('abcde'))

print df26
print df26.query('(a < b) & (b < c)')  # 添加 逻辑与 条件
# 上面的判断语句应该很容易看明白，也就是满足 a 列的值需小于 b 列，且 b 列的值小于 c 列所在的行。
# 当然，在没有 query() 之前，我们也是可以通过前面提到的条件语句选择。

print df26[(df26.a < df26.b) & (df26.b < df26.c)]

# 结果虽然一致，但是 query() 语句的确要简洁和自然很多。query() 包含很多内容，非常强大。你可以通过官方文档了解，这里就不再赘述了。
