# encoding: utf-8
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
#matplotlib inline
# 4.1. 一维数据集
#
# 在下面的所有例子中，我们将按照存储在 NumPy ndarray 对象中的数据绘制图表。当然，matplotlib 也能够按照以不同的 Python 格式存储的数据（如列表对象）绘制图表。首先，我们需要用于绘制图表的数据。为此，我们生成20个标准正态分布（伪）随机数，保存在一个NumPy ndarray中：
np.random.seed(1000)
y = np.random.standard_normal(20)

# pyplot 子库中的 plot 函数是最基础的绘图函数，但是也相当强大。原则上，它需要两组数值。
#
# x 值：包含 x 坐标（横坐标）的列表或者数组
# y 值：包含 y 坐标（纵坐标）的列表或者数组
# 当然，x 和 y 值的 数量 必须相等，考虑下面两行代码，其输出如图所示
x = range(len(y))
plt.plot(x, y)
plt.show()

plt.figure(1) # 创建图表1
plt.figure(2) # 创建图表2
ax1 = plt.subplot(211) # 在图表2中创建子图1
ax2 = plt.subplot(212) # 在图表2中创建子图2
x = np.linspace(0, 3, 100)
for i in range(5):
    plt.figure(1)  #❶ # 选择图表1
    plt.plot(x, np.exp(i*x/3))
    plt.sca(ax1)   #❷ # 选择图表2的子图1
    plt.plot(x, np.sin(i*x))
    plt.sca(ax2)  # 选择图表2的子图2
    plt.plot(x, np.cos(i*x))
plt.show()

X1 = range(0, 50)
Y1 = [num**2 for num in X1] # y = x^2
X2 = [0, 1]
Y2 = [0, 1]  # y = x
Fig = plt.figure(figsize=(8,4))                      # Create a `figure' instance
Ax = Fig.add_subplot(111)               # Create a `axes' instance in the figure
Ax.plot(X1, Y1, X2, Y2)                 # Create a Line2D instance in the axes
Fig.show()
Fig.savefig("test.pdf")



# plt 会注意到何时传递了 ndarray 对象。在这种情况下，没有必要提供 x 值的 “额外” 信息。如果你只提供 y 值，plot 以索引值作为对应的 x 值。因此，下面一行代码会生成完全一样的输出，如下图
# plt.plot(y)
#
#
# 可以简单地向 matplotlib 函数传递 Numpy ndarray 对象。函数能够解释数据结构以简化绘图工作。但是要注意，不要传递太大或者太复杂的数组。
#
# 由于大部分 ndarray 方法返回的仍然是一个 ndarray 对象，也可以附加一个方法（有些时候甚至可以附加多个方法）传递对象。我们用样板数据调用 ndarray 对象上的 cumsum 方法，可以获得这些数据的总和，并且和预想的一样得到不同的输出，如下图
y = np.random.standard_normal(20)
plt.plot(y.cumsum())
# 此处输入图片的描述

# 一般来说，默认绘图样式不能满足报表、出版等的典型要求。例如，你可能希望自定义所使用的字体（例如，为了 LaTeX 字体兼容）、在坐标轴上有标签或者为了更好的可辨认性而绘制网格。因此，matplotlib 提供了大量函数以自定义绘图样式。有些函数容易理解，其他的则需要更深入一步研究。例如，操纵坐标轴和增加网格及标签的函数很容易理解，如下图：
plt.plot(y.cumsum())
plt.grid(True)           # 添加网格线
plt.axis('tight')        # 紧凑坐标轴


# 下图列出了 plt.axis 的其它选项，大部分都以字符串对象的形式传递
#
#
# 此外，可以使用 plt.xlim 和 plt.ylim 设置每个坐标轴的最小值和最大值。下面的代码提供了一个示例，输出如图
plt.plot(y.cumsum())
plt.grid(True)
plt.xlim(-1,20)
plt.ylim(np.min(y.cumsum()) - 1,
         np.max(y.cumsum()) + 1)


# 为了得到更好的易理解性，图表通常包含一些标签——例如描述x和y值性质的标题和标签。这些标签分别通过 plt.title, plt.xlabe 和 plt.ylabel 添加。默认情况下，即使提供的数据点是离散的，plot也绘制连续线条。离散点的绘制通过选择不同的样式选项实现。下图覆盖（红色）点和线宽为1.5个点的（蓝色）线条：
plt.figure(figsize=(7, 4))
# the figsize parameter defines the size of the figure in(width, height)

plt.plot(y.cumsum(), 'b', lw=1.5)
plt.plot(y.cumsum(), 'ro')
plt.grid(True)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value')
plt.title('A Simple Plot')

# 默认情况下，plt.plot 支持下表中的颜色缩写
#
#
# 对于线和点的样式，plt.plot 支持下表中列出的字符
#

# 任何颜色缩写都可以与任何样式字符组合，这样，你可以确保不同的数据集能够轻松区分。我们将会看到，绘图样式也会反映到图例中
# 4.2 二维数据集
#
# 按照一维数据绘图可以看做一种特例。一般来说，数据集包含多个单独的子集。这种数据的处理遵循matplotlib处理一维数据时的原则。但是，这种情况会出现其他一些问题，例如，两个数据集可能有不同的刻度，无法用相同的y或x轴刻度绘制。另一个问题是，你可能希望以不同的方式可视化两组不同数据，例如，一组数据使用线图，另一组使用柱状图。
#
# 首先，我们生成一个二维样本数据集。下面的代码生成包含标准正态分布（伪）随机数的20×2 NumPy ndarray。在这个数组上调用 cumsum 计算样本数据在0轴（即第一维）上的总和:
np.random.seed(2000)
y = np.random.standard_normal((20,2)).cumsum(axis=0)


# 一般来说，也可以将这样的二维数组传递给 plt.plot。它将自动把包含的数据解释为单独的数据集（沿着1轴，即第二维）。如下图：
plt.figure(figsize=(7, 4))
plt.plot(y, lw=1.5)
plt.plot(y, 'ro')
plt.grid(True)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value')
plt.title('A Simple Plot')


# 在这种情况下，进一步的注释有助于更好地理解图表，可以为每个数据集添加单独的标签并在图例中列出。plt.legend 接受不同的位置参数。0表示“最佳位置”，也就是图例尽可能少地遮盖数据。下图展示了包含两个数据集的图表，这一次带有图例。在生成代码中，我们没有传递整个 ndarray 对象，而是分别访问两个数据子集（y[:, 0]和y[:, 1]），可以为它们附加单独的标签
plt.figure(figsize=(7,4))
plt.plot(y[:, 0], lw=1.5, label='1st')
plt.plot(y[:, 1], lw=1.5, label='2nd')
plt.plot(y, 'ro')
plt.grid(True)
plt.legend(loc=0)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value')
plt.title('A Simple Plot')


# plt.legend 的其它位置选项如下图所示
#
#
# 多个具有类似刻度的数据集（如同一金融风险因素的模拟路径）可以用单一的 y轴绘制。但是，数据集常常有不同的刻度，用单一 y轴刻度绘制这种数据的图表通常会导致可视化信息的显著丢失。为了说明这种效果，我们将两个数据子集中的第一个扩大 100倍，再次绘制该图
y[:, 0] = y[:, 0] * 100
plt.figure(figsize=(7,4))
plt.plot(y[:, 0], lw=1.5, label='1st')
plt.plot(y[:, 1], lw=1.5, label='2nd')
plt.plot(y, 'ro')
plt.grid(True)
plt.legend(loc=0)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value')
plt.title('A Simple Plot')


# 观察上图我们可以知道，第一个数据集仍然是“在视觉上易于辨认的”，而第二个数据集在新的Y轴刻度上看起来像一条直线。在某种程度上，第二个数据集的有关信息现在“在视觉上已经丢失”。解决这个问题有两种基本方法：
#
# 使用 2 个 y 轴（左/右）
# 使用两个子图（上/下，左/右）
# 我们首先在图表中引入第二个 y 轴。下图中有两个不同的y轴，左侧的y轴用于第一个数据集，右侧的y轴用于第二个数据集，因此，有两个图例：

fig, ax1 = plt.subplots()
plt.plot(y[:, 0], 'b', lw=1.5, label='1st')
plt.plot(y[:, 0], 'ro')
plt.grid(True)
plt.legend(loc=8)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value 1st')
plt.title('A Simple Plot')

ax2 = ax1.twinx()
plt.plot(y[:, 1], 'g', lw=1.5, label='2nd')
plt.plot(y[:, 1], 'ro')
plt.legend(loc=0)
plt.ylabel('value 2nd')

# 在上图中，管理坐标轴的代码行是关键，通过使用 plt.subplots 函数，可以直接访问底层绘图对象（图、子图等）。例如，可以用它生成和第一个子图共享x轴的第二个子图。上图中有两个相互重叠的子图。
#
# 接下来，考虑两个单独子图的情况。这个选项提供了处理两个数据集的更大自由度，如下图所示：

plt.figure(figsize=(7,5))

plt.subplot(211)
plt.plot(y[:, 0], lw=1.5, label='1st')
plt.plot(y[:, 0], 'ro')
plt.grid(True)
plt.legend(loc=0)
plt.axis('tight')
plt.ylabel('value')

plt.title('A Simple Plot')

plt.subplot(212)
plt.plot(y[:, 1], 'g', lw=1.5, label='2nd')
plt.plot(y[:, 1], 'ro')
plt.grid(True)
plt.legend(loc=0)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value')


# matplotlib figure对象中子图的定位通过使用一种特殊的坐标系来实现。plt.subplot 有3个整数参数，即 numrows 、numcols 和 fignum （可能由逗号分隔，也可能没有）。numrows 指定行数，numcols 指定列数，fignum 指定子图编号（从1到numrows×numcols）。例如，有9个大小相同子图的图表有numrows=3，numcols=3，fignum=1，2，…，9。左下角的子图“坐标”如下：plt.subplot(3,3,9) 。
#
# 有时候，选择两个不同的图表类型来可视化数据可能是必要的或者是理想的。利用子图方法，就可以自由地组合matplotlib提供的任意图表类型，下图组合了线图/点图和柱状图：

plt.figure(figsize=(9, 4))

plt.subplot(121)
plt.plot(y[:, 0], lw=1.5, label='1st')
plt.plot(y[:, 0], 'ro')
plt.grid(True)
plt.legend(loc=0)
plt.axis('tight')
plt.xlabel('index')
plt.ylabel('value')
plt.title('1st Data Set')

plt.subplot(122)
plt.bar(np.arange(len(y)), y[:, 1], width=0.5, color='g', label='2nd')
plt.grid(True)
plt.legend(loc=0)
plt.axis('tight')
plt.xlabel('index')
plt.title('2nd Data Set')

一、其它绘图样式

对于二维绘图，线图和点图可能是金融学中最重要的；这是因为许多数据集用于表示时间序列数据，此类数据通常可以由这些图表进行可视化。

1.1 散点图

我们要介绍的第一种图表是散点图，这种图表中一个数据集的值作为其他数据集的x值。下图展示了一个这种图表。例如，这种图表类型可用于绘制一个金融时间序列的收益和另一个时间序列收益的对比。在下面的例子中，我们将使用二维数据集和其他一些数据：

y = np.random.standard_normal((1000, 2))

plt.figure(figsize=(7, 5))
plt.plot(y[:, 0], y[:, 1], 'ro')
plt.grid(True)
plt.xlabel('1st')
plt.ylabel('2nd')
plt.title('Scatter Plot')
此处输入图片的描述

matplotlib 还提供了生成散点图的一个特殊函数。它的工作方式本质上相同，但是提供了一些额外的功能。这次使用的是 scatter 函数：
plt.figure(figsize=(7, 5))
plt.scatter(y[:, 0], y[:, 1], marker='o')
plt.grid(True)
plt.xlabel('1st')
plt.ylabel('2nd')
plt.title('Scatter Plot')
此处输入图片的描述

例如，scatter 绘图函数可以加入第三维，通过不同的颜色进行可视化，并使用彩条加以描述。为此，我们用随机数据生成第三个数据集，这次使用的是 0和10 之间的整数:
c = np.random.randint(0, 10, len(y))
下图展示的散点图有不同颜色小点表示的第三维，还有作为颜色图例的彩条
plt.figure(figsize=(7, 5))
plt.scatter(y[:, 0], y[:, 1], c=c, marker='o')
plt.colorbar()
plt.grid(True)
plt.xlabel('1st')
plt.ylabel('2nd')
plt.title('Scatter Plot')
此处输入图片的描述

1.2 直方图

下图在同一个图表中放置两个数据集的频率值
plt.figure(figsize=(7, 4))
plt.hist(y, label=['1st', '2nd'], bins=25)
plt.grid(True)
plt.legend(loc=0)
plt.xlabel('value')
plt.ylabel('frequency')
plt.title('Histogram')
此处输入图片的描述

此处输入图片的描述

由于直方图是金融应用中的重要图表类型，我们要更认真地观察 plt.hist 的使用方法。下面的例子说明了所支持的参数：
plt.hist(x, bins=10, range=None, normed=False, weights=None, cumulative=False, bottom=None, histtype='bar', align='mid', orientation='vertical', rwidth=None, log=False, color=None, label=None, stacked=False, hold=None, **kwargs)
plt.hist 主要参数的描述如下
此处输入图片的描述

如下图，两个数据集的数据在直方图中堆叠
y = np.random.standard_normal((1000, 2))

plt.figure(figsize=(7, 4))
plt.hist(y, label=['1st', '2nd'], color=['b', 'g'], stacked=True, bins=20)
plt.grid(True)
plt.legend(loc=0)
plt.xlabel('value')
plt.ylabel('frequency')
plt.title('Histogram')
此处输入图片的描述

1.3 箱形图

另一种实用的图表类型是箱形图。和直方图类似，箱形图可以简洁地概述数据集的特性，很容易比较多个数据集。下图展示了按照我们的数据集绘制的这类图表：

fig, ax = plt.subplots(figsize=(7,4))
plt.boxplot(y)
plt.grid(True)
plt.setp(ax, xticklabels=['1st', '2nd'])
plt.xlabel('data set')
plt.ylabel('value')
plt.title('Boxplot')
此处输入图片的描述

1.4 数学示例

在本节的最后一个例证中，我们考虑一个受到数学启迪的图表，这个例子也可以在 matplotlib 的“展厅”中找到:http://www/matplotlib.org/gallery.html 。它绘制一个函数的图像，并以图形的方式说明了某个下限和上限之间函数图像下方区域的面积——换言之，从下限到上限之间的函数积分值。下图展示了结果图表，说明 matplotlib 能够无缝地处理 LaTeX 字体设置，在图表中加入数学公式：

from matplotlib.patches import Polygon

def func(x):
    return 0.5 * np.exp(x) + 1

a, b = 0.5, 1.5
x = np.linspace(0, 2)
y = func(x)

fig, ax = plt.subplots(figsize=(7, 5))
plt.plot(x, y, 'b', linewidth=2)
plt.ylim(ymin=0)

Ix = np.linspace(a, b)
Iy = func(Ix)
verts = [(a, 0)] + list(zip(Ix, Iy)) + [(b, 0)]
poly = Polygon(verts, facecolor='0.7', edgecolor='0.5')
ax.add_patch(poly)

plt.text(0.5 * (a + b), 1, r"$\int_a^b fx\mathrm{d}x$", horizontalalignment='center', fontsize=20)
plt.figtext(0.9, 0.075, '$x$')
plt.figtext(0.075, 0.9, '$f(x)$')

ax.set_xticks((a, b))
ax.set_xticklabels(('$a$', '$b$'))
ax.set_yticks([func(a), func(b)])
ax.set_yticklabels(('$f(a)$', '$f(b)$'))
plt.grid(True)
此处输入图片的描述

下面我们一步步来描述这个图表的生成，第一步是定义需要求取积分的函数：
def func(x):
    return 0.5 * np.exp(x) + 1
第二步是定义积分区间，生成必需的数值
a ,b = 0.5, 1.5

x = np.linspace(0, 2)
y = func(x)
第三步，绘制函数图形
fig, ax = plt.subplots(figsize=(7, 5))
plt.plot(x, y, 'b', linewidth=2)
plt.ylim(ymin=0)
第四步是核心，我们使用 Polygon 函数生成阴影部分（“补丁”），表示积分面积：
Ix = np.linspace(a, b)
Iy = func(Ix)
verts = [(a, 0)] + list(zip(Ix, Iy)) + [(b, 0)]
poly = Polygon(verts, facecolor='0.7', edgecolor='0.5')
ax.add_patch(poly)
第五步是用 plt.text 和 plt.figtext 在图表上添加数学公式和一些坐标轴标签。LaTeX 代码在两个美元符号之间传递（$ … $）。两个函数的前两个参数都是放置对应文本的坐标值：
plt.text(0.5 * (a + b), 1, r"$\int_a^b fx\mathrm{d}x$", horizontalalignment='center', fontsize=20)
plt.figtext(0.9, 0.075, '$x$')
plt.figtext(0.075, 0.9, '$f(x)$')
最后，我们分别设置x和y刻度标签的位置。注意，尽管我们以 LaTeX 渲染变量名称，但是用于定位的是正确的数字值。我们还添加了网格，在这个特殊例子中，只是为了强调选中的刻度：
ax.set_xticks((a, b))
ax.set_xticklabels(('$a$', '$b$'))
ax.set_yticks([func(a), func(b)])
ax.set_yticklabels(('$f(a)$', '$f(b)$'))
plt.grid(True)
二、3D 绘图

金融中从3维可视化中获益的领域不是太多。但是，波动率平面是一个应用领域，它可以同时展示许多到期日和行权价的隐含波动率。在下面的例子中，我们人为生成一个类似波动率平面的图表。为此，我们考虑如下因素：

行权价格在50～150元之间；
到期日在0.5～2.5年之间。
这为我们提供了一个2维坐标系。我们可以使用 NumPy 的 meshgrid函数，根据两个 1 维 ndarray 对象生成这样的坐标系：

strike = np.linspace(50, 150, 24)
ttm = np.linspace(0.5, 2.5, 24)
strike, ttm = np.meshgrid(strike, ttm)
上述代码将两个 1 维数组转换为 2 维数组，在必要时重复原始坐标轴值：
此处输入图片的描述

现在，根据新的 ndarray 对象，我们通过简单的比例调整二次函数生成模拟的隐含波动率：
iv = (strike - 100) ** 2 / (100 * strike) / ttm
通过下面的代码得出一个三维图形
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(9,6))
ax = fig.gca(projection='3d')

surf = ax.plot_surface(strike, ttm, iv, rstride=2, cstride=2, cmap=plt.cm.coolwarm, linewidth=0.5, antialiased=True)

ax.set_xlabel('strike')
ax.set_ylabel('time-to-maturity')
ax.set_zlabel('implied volatility')

fig.colorbar(surf, shrink=0.5, aspect=5)
此处输入图片的描述

下图提供了 plot_surface 函数使用的不同参数的描述
此处输入图片的描述

和2维图表一样，线样式可以由单个点或者下例中的单个三角形表示。下图用相同的数据绘制3D散点图，但是现在用 view_init 函数设置不同的视角：
fig = plt.figure(figsize=(8, 5))
ax = fig.add_subplot(111, projection='3d')
ax.view_init(30, 60)

ax.scatter(strike, ttm, iv, zdir='z', s=25, c='b', marker='^')

ax.set_xlabel('strike')
ax.set_ylabel('time-to-maturity')
ax.set_zlabel('implied volatility')
