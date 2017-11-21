# -*- encoding: utf-8 -*-
"""
@author: miko
"""
from numpy import *

class cluster_node:
    def __init__(self,vec,left=None,right=None,distance=0.0,id=None):
        self.left=left
        self.right=right
        self.vec=vec
        self.id=id
        self.distance=distance

def L2dist(v1,v2):
    return sqrt(sum(v1-v2)**2)
def L1dist(v1,v2):
    return sum(abs(v1-v2))

def hcluster(features,distance=L2dist):
    distances={}
    currentClusterId=-1
    clust=[cluster_node(array(features),id=i) for i in range(len(features))]

    while(len(clust)>1):
        lowesPair=(0,1)
        closest=distance(clust[0].vec,clust[1].vec)
        for i in range(len(clust)):
            for j in range(i+1,len(clust)):
                if((clust[i].id,clust[j].id) not in distances):
                    distances[(clust[i].id,clust[j].id)]=distance(clust[i].vec,clust[j].vec)
                    d=distances[(clust[i].id,clust[j].id)]
                    if d<closest:
                        closest=d
                        lowesPair=(i,j)

        mergevec=(clust[lowesPair[0]].vec-clust[lowesPair[1].vec])/2.0
        newcluster=cluster_node(array(mergevec),left=clust[lowesPair[0]],right=clust[lowesPair[1]],distance=closest,id=currentClusterId)
        currentClusterId-=1
        del clust[lowesPair[0]]
        del clust[lowesPair[1]]
        clust.append(newcluster)
    return clust[0]

def extract_cluster(clust,dist):
    cluster={}
    if clust.distance<dist:
        return [clust]
    else:
        cl=[]
        cr=[]
        if clust.left!=None:
            cl=extract_cluster(clust.left, dist)
        if clust.right!=None:
            cr=extract_cluster(clust.right, dist)
        return cl+cr