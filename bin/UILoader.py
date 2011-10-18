from UI import *
from Engine import *

ObjectDeletionList = []     # 一个场景内部的所有资源，在场景调用Release时，这里面的东西会被删除
ScenesDict = dict()     # 场景寿命长
AnimatorsTime = dict()
NodeChildren = dict()


def SaveNodeChilren( node, Children ):
    global NodeChilren
    NodeChildren[ node ] = Children

def GetNodeChildren( node ):
    global NodeChildren
    return NodeChildren[ node ]

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
    global ObjectDeletionList
    ObjectDeletionList = dict()

def GetAnimatorTime( node ):
    global AnimatorsTime
    return AnimatorsTime[ node ]

# 保存整个场景跳转状态图
def SaveScenes( name, scene ):
    global ScenesDict
    ScenesDict[ name ] = scene
# 删除整个场景
def DeleteScenes():
    global ScenesDict
    ScenesDict = []

count = 0
def StartSceneRun():
    global count
    global ScenesDict
    if ( count > 1000 ):
        ChangeGameScene( ScenesDict[ 'm' ] )    # 跳转到多人游戏
        count = 0
    count += 1

def CreateGameScenes():
    menu = MenuScene()
    SaveScenes( "menu", menu )
    
    start = StartScene()
    SaveScenes( "start", start )
    
    multi = MultiplayerScene()
    SaveScenes( "m", multi )
    
    start.Scenes[ 0 ] = multi
    
    ChangeGameScene( menu )


