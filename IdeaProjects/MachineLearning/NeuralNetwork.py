# -*- encoding: utf-8 -*-
"""
@author: miko
"""
import numpy as np
def sigmoid(x):
    return 1 / (1 + np.exp(-x))
# derivative of sigmoid
# sigmoid(y) * (1.0 - sigmoid(y))
# the way we use this y is already sigmoided
def dsigmoid(y):
    return y * (1.0 - y)

class Network(object):
    def __init__(self,sizes):
        self.num_layers =len(sizes)
        self.sizes = sizes
        self.biases = [np.random.randn(y,1) for  y in  sizes[1:]]
        self.weights = [np.random.randn(y,x) for x,y in zip(sizes[:-1],sizes[1:])]
    def feedfward(self, a):
        for b,w in zip(self.biases, self.weights):
            a= sigmoid(np.dot(w,a)+b)
        return a

# sizes =[2,3,1]
# print(sizes[1:])
# bias =[np.random.randn(y,1) for  y in  sizes[1:]]
# print(bias)
#
# print(sizes[:-1])
# print(sizes[1:])
# for x,y in zip(sizes[:-1],sizes[1:]):
#     print(x,y)
# weights = [np.random.randn(y,x) for x,y in zip(sizes[:-1],sizes[1:])]
# print(weights)
net = Network([2,3,1])
print(net.biases)
print(net.weights)

