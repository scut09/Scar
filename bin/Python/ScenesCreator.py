# 
# 作者：华亮
# 说明：提供创建场景，切换场景，删除场景的方法
#
from UI import *
from GameSceneModule import *
from Engine import *

ScenesDict = dict() 

def CreateGameScenes():
    '由C++调用来初始化场景结构'
    sceneMgr = GetGameSceneManager()
    mainMenu = sceneMgr.AddMenuScene( "MainMenuIni" )
    mainMenu.SetName( "MainMenuIni" )

    multiMenu = sceneMgr.AddMenuScene( "MultiMenuIni" )
    multiMenu.SetName( "MultiMenuIni" )
   
    multi = sceneMgr.AddMultiplayerScene()    
    
    ChangeGameScene( multi )
