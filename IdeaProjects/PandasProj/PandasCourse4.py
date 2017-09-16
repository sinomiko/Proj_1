# encoding: utf-8

import  pandas as pd
import  numpy as np

# 1.1 实验内容
#
# Pandas 是非常著名的开源数据处理工具，我们可以通过它对数据集进行快速读取、转换、过滤、分析等一系列操作。除此之外，Pandas 拥有强大的缺失数据处理与数据透视功能，可谓是数据预处理中的必备利器。这是 Pandas 使用教程的第 3 章节，将学会使用 Pandas 对数据进行选择与变换。
#
# 1.2 实验知识点
#
# 缺失值标记
# 缺失值填充
# 缺失值插值
# 二、认识缺失值
#
# 在真实的生产环境中，我们需要处理的数据文件往往没有想象中的那么美好。其中，很大几率会遇到的情况就是缺失值。
#
# 2.1 什么是缺失值？
#
# 缺失值主要是指数据丢失的现象，也就是数据集中的某一块数据不存在。除此之外、存在但明显不正确的数据也被归为缺失值一类。例如，在一个时间序列数据集中，某一段数据突然发生了时间流错乱，那么这一小块数据就是毫无意义的，可以被归为缺失值。
#
# 当然，除了原始数据集就已经存在缺失值以外。当我们用到前面章节中的提到的索引对齐（reindex()）的方法时，也容易人为导致缺失值的产生。举个例子:
#
# 首先，我们生成一个 DataFrame。
df21 = pd.DataFrame(np.random.rand(5, 5), index=list('cafed'),columns=list('ABCDE'))

print df21
# 然后，我们使用 `reindex() 完成索引对齐。

print df21.reindex(list('abcde'))
# 由于原始数据集中，没有索引 b，所以对齐之后，b 后面全部为缺失值，也就造成了数据缺失。
#
# 2.2 检测缺失值
#
# Pandas 为了更方便地检测缺失值，将不同类型数据的缺失均采用 NaN 标记。这里的 NaN 代表 Not a Number，它仅仅是作为一个标记。例外是，在时间序列里，时间戳的丢失采用 NaT 标记。
#
# Pandas 中用于检测缺失值主要用到两个方法，分别是：isnull() 和 notnull()，故名思意就是「是缺失值」和「不是缺失值」。默认会返回布尔值用于判断。
#
# 下面，演示一下这两个方法的作用，我们这里沿用上面进行索引对齐后的数据。

df22 = df21.reindex(list('abcde'))

print  df22.isnull()
print  df22.notnull()

# 然后，我们来看一下对时间序列缺失值的检测，对上面的 df2 数据集进行稍微修改。

# 插入 T 列，并打上时间戳
df22.insert(value=pd.Timestamp('2017-10-1'),loc=0,column='T')

# 将 T 列的 1，3，5 行置为缺失值
df22.loc[['a','c','e'],['T']] = np.nan
# 这里，我们也更清晰看到，时间序列的缺失值用 NaT 标记。我们对 df2 进行缺失值检测。

print df22.isnull()
print df22.notnull()

# 三、填充和清除缺失值
#
# 上面已经对缺省值的产生、检测进行了介绍。那么，我们面对缺失值时，到底有哪些实质性的措施呢？接下来，就来看一看如何完成对缺失值填充和清除。
#
# 填充和清除都是两个极端。如果你感觉有必要保留缺失值所在的列或行，那么就需要对缺失值进行填充。如果没有必要保留，就可以选择清除缺失值。
#
# Pandas 中，填充缺失的方法为 fillna()，清除为 dropna()。
#
# 3.1 填充缺失值 fillna()
#
# 首先，我们看一看 fillna() 的使用方法。重新打开一个 ipython 终端，我们生成和上面相似的数据。

df31 = pd.DataFrame(np.random.rand(9, 5), columns=list('ABCDE'))

# 插入 T 列，并打上时间戳
df31.insert(value=pd.Timestamp('2017-10-1'),loc=0,column='Time')

# 将 1, 3, 5 列的 1，3，5 行置为缺失值
df31.iloc[[1,3,5,7], [0,2,4]] = np.nan

# 将 2, 4, 6 列的 2，4，6 行置为缺失值
df31.iloc[[2,4,6,8], [1,3,5]] = np.nan

# 我们用相同的标量值替换 NaN，比如用 0。

print df31.fillna(0)

# 注意，这里的填充并不会直接覆盖原数据集，你可以重新输出 df 比较结果。

# 除了直接填充值，我们还可以通过参数，将缺失值前面或者后面的值填充给相应的缺失值。例如使用缺失值前面的值进行填充：

print df31.fillna(method='pad')
# 或者是后面的值：

print df31.fillna(method='bfill')

# 最后一行由于没有对于的后序值，自然继续存在缺失值。
#
# 上面的例子中，我们的缺失值是间隔存在的。那么，如果存在连续的缺失值是怎样的情况呢？试一试。首先，我们将数据集的第 2，4 ，6 列的第 3，5 行也置为缺失值。

df31.iloc[[3,5], [1,3,5]] = np.nan

# 然后来正向填充：

print df31.fillna(method='pad')
# 可以看到，连续缺失值也是按照前序数值进行填充的，并且完全填充。这里，我们可以通过 limit= 参数设置连续填充的限制数量。

print df31.fillna(method='pad', limit=1)

# 除了上面的填充方式，还可以通过 Pandas 自带的求平均值方法等来填充特定列或行。举个例子：
print "fill na"
print df31.fillna(df31.mean()['C':'E'])
# 对 C 列和 E 列用平均值填充。

# 3.2 清除缺失值 dropna()
#
# 上面演示了缺失值填充。但有些时候，缺失值比较少或者是填充无意义时，就可以直接清除了。
#
# 由于填充和清除在赋值之前，均不会影响原有的数据。所以，我们这里依旧延续使用上面的 df。

print "drop na"
print df31.dropna()
# 我们可以看到，dropna() 方法带来的默认效果就是，凡是存在缺失值的行均被直接移除。此时，dropna() 里面有一个默认参数是 axis=0，代表依据行来移除。
#
# 如果我们像将凡是有缺失值的列直接移除，可以将 axis=1，试一试。

print "remove nan clumn"
print df31.dropna(axis=1)
# 由于上面的 df 中，每一列都有缺失值，所以全部被移除了。

# 四、插值 interpolate()
#
# 插值是数值分析中一种方法。简而言之，就是借助于一个函数（线性或非线性），再根据已知数据去求解未知数据的值。插值在数据领域非常常见，它的好处在于，可以尽量去还原数据本身的样子。
#
# Pandas 中的插值，通过 interpolate() 方法完成，默认为线性插值，即 method='linear'。除此之外，还有{‘linear’, ‘time’, ‘index’, ‘values’, ‘nearest’, ‘zero’, ‘slinear’, ‘quadratic’, ‘cubic’, ‘barycentric’, ‘krogh’, ‘polynomial’, ‘spline’, ‘piecewise_polynomial’, ‘from_derivatives’, ‘pchip’, ‘akima’}等插值方法可供选择。
#
# 举个例子：
df41 = pd.DataFrame({'A': [1.1, 2.2, np.nan, 4.5, 5.7, 6.9], 'B': [.21, np.nan, np.nan, 3.1, 11.7, 13.2]})
# 对于上面存在的缺失值，如果通过前后值，或者平均值来填充是不太能反映出趋势的。这时候，插值最好使。我们用默认的线性插值试一试。
print df41
print df41.interpolate()

# 如果你熟悉 Matplotlib，我们可以将数据绘制成图看一看趋势。图中，第 2，3 点的坐标是我们插值的结果。
#
# 此处输入图片的描述
#
# 上面提到了许多插值的方法，也就是 method=。下面给出几条选择的建议：
#
# 如果你的数据增长速率越来越快，可以选择 method='quadratic'二次插值。
# 如果数据集呈现出累计分布的样子，推荐选择 method='pchip'。
# 如果需要填补缺省值，以平滑绘图为目标，推荐选择 method='akima'。
# 当然，最后提到的 method='akima'，需要你的环境中安装了 Scipy 库。除此之外，method='barycentric' 和 method='pchip' 同样也需要 Scipy 才能使用。