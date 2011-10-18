# 加载C++中的模块
from UI import *
from Engine import *
# 加载其他Python模块，尽量不使用from ... import *，除非是通用的工具函数，
# 否则使用import
from ScenesCreator import *

ObjectDeletionList = []     # 一个场景内部的所有资源，在场景调用Release时，这里面的东西会被删除
AnimatorsTime = dict()
NodeChildren = dict()

def SaveNodeChilren( node, Children ):
    '保存一个节点的孩子,输入一个list，以便于可以一次性删除节点及子节点的动画'
    global NodeChilren
    NodeChildren[ node ] = Children

def GetNodeChildren( node ):
    '获取一个节点的所有孩子'
    global NodeChildren
    return NodeChildren[ node ]

def DeleteNodeAnimators( node ):
    '通知节点在C++中将它们的动画列表清空'
    global NodeChildren
    node.RemoveAnimators()
    for child in NodeChildren[ node ]:
        child.RemoveAnimators()

def SaveNodeAnimatorTime( node, time ):
    global AnimatorsTime
    AnimatorsTime[ node ] = time
    
# 保存一个场景内部的资源
def Save( obj ):
    global ObjectDeletionList, AnimatorsTime
    ObjectDeletionList.append( obj )
   # AnimatorsTime[ obj ] = Timer().GetRealTime()
    
# 删除一个场景内部的资源
def DeleteTree():
    global ObjectDeletionList, NodeChildren, AnimatorsTime
    ObjectDeletionList = []
    AnimatorsTime = dict()
    NodeChildren = dict()
    

def GetAnimatorTime( node ):
    global AnimatorsTime
    return AnimatorsTime[ node ]


count = 0
def StartSceneRun():
    global count
    global ScenesDict
    if ( count > 1000 ):
        ChangeGameScene( ScenesDict[ 'm' ] )    # 跳转到多人游戏
        count = 0
    count += 1

