﻿# 加载C++中的模块
from UI import *
from Engine import *

ScenesDict = dict() 

def CreateGameScenes():
    '由C++调用来初始化场景结构'
    menu = MenuScene()
    SaveScenes( "menu", menu )
    
    start = StartScene()
    SaveScenes( "start", start )
    
    multi = MultiplayerScene()
    SaveScenes( "m", multi )
    
    start.Scenes[ 0 ] = multi
    
    ChangeGameScene( menu )

def GetScene( name ):
    '输入一个场景的名字，返回一个场景对象'
    global ScenesDict
    return ScenesDict[ name ]

def DeleteScenes():
    '回收场景资源'
    global ScenesDict
    ScenesDict = dict()

def SaveScenes( name, scene ):
    '''
    保存整个场景跳转状态图
    这里保存一个场景的名字和它的实例的映射
    '''
    global ScenesDict
    ScenesDict[ name ] = scene