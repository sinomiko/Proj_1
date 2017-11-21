# encoding: utf-8
import numpy as np

# 四、Numpy 数值类型
# 安装完毕之后，我们先来了解 Numpy 支持的数据类型。为了更加方便地学习和演示，以下代码在为特别注明的情况下，均在 ipython 交互式终端运行，你可以通过在线环境左下角系统应用菜单>附件打开。
# Python 本身支持的数值类型有 int（整型，python2 中存在 long 长整型）、float（浮点型）、bool（布尔型） 和 complex（复数型）。
# 而 Numpy 支持比 Python 本身更为丰富的数值类型，细分如下：
# 1. bool：布尔类型，1 个字节，值为 True 或 False。
# 2. int：整数类型，通常为 int64 或 int32 。
# 3. intc：与 C 里的 int 相同，通常为 int32 或 int64。
# 4. intp：用于索引，通常为 int32 或 int64。
# 5. int8：字节（从 -128 到 127）
# 6. int16：整数（从 -32768 到 32767）
# 7. int32：整数（从 -2147483648 到 2147483647）
# 8. int64：整数（从 -9223372036854775808 到 9223372036854775807）
# 9. uint8：无符号整数（从 0 到 255）
# 10. uint16：无符号整数（从 0 到 65535）
# 11. uint32：无符号整数（从 0 到 4294967295）
# 12. uint64：无符号整数（从 0 到 18446744073709551615）
# 13. float：float64 的简写。
# 14. float16：半精度浮点，5 位指数，10 位尾数
# 15. float32：单精度浮点，8 位指数，23 位尾数
# 16. float64：双精度浮点，11 位指数，52 位尾数
# 17. complex：complex128 的简写。
# 18. complex64：复数，由两个 32 位浮点表示。
# 19. complex128：复数，由两个 64 位浮点表示。
# 在 Numpy 中，上面提到的这些数值类型都被归于 dtype（data-type） 对象的实例。
# 我们可以用 numpy.dtype(object, align, copy) 来指定数值类型。而在数组里面，可以用 dtype= 参数。


# ndarray 介绍
# 在 python 内建对象中，数组有三种形式：
# 4. list 列表：[1, 2, 3]
# 5. Tuple 元组：(1, 2, 3, 4, 5)
# 6. Dict 字典：{A:1, B:2}
# 其中，元组与列表相似，不同之处在于元组的元素不能修改。而字典由键和值构成。
# python 标准类针对数组的处理局限于 1 维，并仅提供少量的功能。
# 而 Numpy 最核心且最重要的一个特性就是 ndarray 多维数组对象，它区别于 python 的标准类，拥有对高维数组的处理能力，这也是数值计算过程中缺一不可的重要特性。
# Numpy 中，ndarray 类具有六个参数，它们分别为：
# 7. shape：数组的形状。
# 8. dtype：数据类型。
# 9. buffer：对象暴露缓冲区接口。
# 10. offset：数组数据的偏移量。
# 11. strides：数据步长。
# 12. order：{'C'，'F'}，以行或列为主排列顺序。
# 下面，我们来了解创建 ndarray 的一些方法。在 numpy 中，我们主要通过以下 5 种途径创建数组，它们分别是：
# 6. 从 Python 数组结构列表，元组等转换。
# 7. 使用 np.arange、np.ones、np.zeros 等 numpy 原生方法。
# 8. 从存储空间读取数组。
# 9. 通过使用字符串或缓冲区从原始字节创建数组。
# 10. 使用特殊函数，如 random。



# 在 numpy 中，我们使用 numpy.array 将列表或元组转换为 ndarray 数组。其方法为：
# numpy.array(object, dtype=None, copy=True, order=None, subok=False, ndmin=0)
#
# 其中，参数：
# ● object：列表、元组等。
# ● dtype：数据类型。如果未给出，则类型为被保存对象所需的最小类型。
# ● copy：布尔来写，默认 True，表示复制对象。
# ● order：顺序。
# ● subok：布尔类型，表示子类是否被传递。
# ● ndmin：生成的数组应具有的最小维数。

ai = np.array([[1.1, 2.2, 3.3], [1.1, 2.2, 3.3], [1.1, 2.2, 3.3], [1.1, 2.2, 3.3]], dtype = np.float64)
print ai
# 你可以使用 .astype() 方法在不同的数值类型之间相互转换。
print ai.astype(int)
# 你可以使用 .dtype 来查看 dtype 属性。
print ai.dtype

a222 = np.array([(1.1, 2.2, 3.3), (1.1, 2.2, 3.3), (1.1, 2.2, 3.3), (1.1, 2.2, 3.3)], dtype = np.float64)
print a222
print a222.astype(int)
print a222.dtype

# numpy.arange(start, stop, step, dtype=None)
# 你需要先设置值所在的区间，这里为 `[开始， 停止），
# 你应该能发现这是一个半开半闭区间。然后，在设置 step 步长用于设置值之间的间隔。最后的可选参数 dtype可以设置返回ndarray 的值类型。
a223=np.arange(3,7,0.5, dtype=np.float64)
print a223


# linspace 用于在指定的区间内返回间隔均匀的值。其方法如下：
# numpy.linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
#
# ● start：序列的起始值。
# ● stop：序列的结束值。
# ● num：生成的样本数。默认值为50。
# ● endpoint：布尔值，如果为真，则最后一个样本包含在序列内。
# ● retstep：布尔值，如果为真，返回间距。
# ● dtype：数组的类型。

a224 = np.linspace(0,10,10,True,True,np.float64)
print a224

# numpy.ones 用于快速创建数值全部为 1 的多维数组。其方法如下：
# numpy.ones(shape, dtype=None, order='C')
#
# 其中：
# ● shape：用于指定数组形状，例如（1， 2）或 3。
# ● dtype：数据类型。
# ● order：{'C'，'F'}，按行或列方式储存数组。

a225 = np.ones((2,3),np.float64)
print a225

# zeros 方法和上面的 ones 方法非常相似，不同的地方在于，这里全部填充为 0。zeros 方法和 ones 是一致的。
# numpy.zeros(shape, dtype=None, order='C')
#
# 其中：
# ● shape：用于指定数组形状，例如（1， 2）或3。
# ● dtype：数据类型。
# ● order：{'C'，'F'}，按行或列方式储存数组。

a226 = np.zeros((2,3),np.float64)
print a226

# numpy.eye 用于创建一个二维数组，其特点是k 对角线上的值为 1，其余值全部为0。方法如下：
# numpy.eye(N, M=None, k=0, dtype=<type 'float'>)
#
# 其中：
# ● N：输出数组的行数。
# ● M：输出数组的列数。
# ● k：对角线索引：0（默认）是指主对角线，正值是指上对角线，负值是指下对角线。

a2271 = np.eye(5,4,1,np.float64)
print a2271
a2272 = np.eye(5,4,-1,np.float64)
print a2272

# 2.8 从已知数据创建
# 我们还可以从已知数据文件、函数中创建 ndarray。numpy 提供了下面 5 个方法：
# 6. frombuffer（buffer）：将缓冲区转换为 1 维数组。
# 7. fromfile（file，dtype，count，sep）：从文本或二进制文件中构建多维数组。
# 8. fromfunction（function，shape）：通过函数返回值来创建多维数组。
# 9. fromiter（iterable，dtype，count）：从可迭代对象创建 1 维数组。
# 10. fromstring（string，dtype，count，sep）：从字符串中创建 1 维数组。
a228 =np.fromfunction(lambda a, b: a + b, (5, 4))
print a228

# 三、ndarray 数组属性
# 首先，我们创建一个 ndarray 数组，这里还是沿用本章节开头的例子。

a31 = np.array([[1,2,3],[4,5,6],[7,8,9]])

# 3.1 ndarray.T
#
# ndarray.T用于数组的转置，与 .transpose() 相同。
print a31.T
# 3.2 ndarray.dtype
#
# ndarray.dtype 用来输出数组包含元素的数据类型。
print a31.dtype

# 3.3ndarray.imag
#
# ndarray.imag 用来输出数组包含元素的虚部。
print a31.imag

# 3.4ndarray.real
#
# ndarray.real用来输出数组包含元素的实部。
print a31.real

# 3.5 ndarray.size
#
# ndarray.size用来输出数组中的总包含元素数。
print a31.size

# 3.6ndarray.itemsize
#
# ndarray.itemsize输出一个数组元素的字节数。
print a31.itemsize

# 3.7 ndarray.nbytes
#
# ndarray.nbytes用来输出数组的元素总字节数。
print a31.nbytes

# 3.8 ndarray.ndim
#
# ndarray.ndim用来输出数组尺寸(维度)。
#
# import numpy as np
#
print  a31.ndim

# 3.9 ndarray.shape
#
# ndarray.shape用来输出数组维数组.

print a31.shape

# 3.10 ndarray.strides
#
# ndarray.strides用来遍历数组时，输出每个维度中步进的字节数组。
print a31.strides

# 第3节 Numpy 数组操作及随机抽样
# 二、Numpy 数组的基本操作
# 上一个章节，我们了解了如何利用 numpy 创建各式各样的 ndarray。本章节，我们将利用学会针对 ndarray 的各种花式操作技巧。
# 2.1 重设形状
# reshape 可以在不改变数组数据的同时，改变数组的形状。其中，numpy.reshape() 等效于 ndarray.reshape()。reshape 方法非常简单：
# numpy.reshape(a, newshape)
# 其中，a 表示原数组，newshape 用于指定新的形状(整数或者元组)。
a31=np.arange(10).reshape((5, 2))
print a31

# 2.2 数组展开
# ravel 的目的是将任意形状的数组扁平化，变为 1 维数组。ravel 方法如下：
# numpy.ravel(a, order='C')
# 其中，a 表示需要处理的数组。order 表示变换时的读取顺序，默认是按照行依次读取，当 order='F' 时，可以按列依次读取排序。
# 示例：
#

print np.ravel(a31, order='F')

# 2.3 轴移动
# moveaxis 可以将数组的轴移动到新的位置。其方法如下：
# numpy.moveaxis(a, source, destination)
# 其中：
# a：数组。
# source：要移动的轴的原始位置。
# destination：要移动的轴的目标位置。
a323 = np.eye(3, 4, 1)
print a323
print np.moveaxis(a323, 0, -1)

# 2.4 轴交换
# 和 moveaxis 不同的是，swapaxes 可以用来交换数组的轴。其方法如下：
# numpy.swapaxes(a, axis1, axis2)
# 其中：
# a：数组。
# axis1：需要交换的轴 1 位置。
# axis2：需要与轴 1 交换位置的轴 1 位置。
a324 = np.ones((1,4,3))
print "a324"
print a324
print np.swapaxes(a324, 0, 2)

