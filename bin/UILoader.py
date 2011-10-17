from UI import *
from Engine import *

ObjectDeletionList = []     # 一个场景内部的所有资源，在场景调用Release时，这里面的东西会被删除
ScenesDict = dict()     # 场景寿命长

# 保存一个场景内部的资源
def Save( obj ):
    global ObjectDeletionList
    ObjectDeletionList.append( obj )
# 删除一个场景内部的资源
def DeleteTree():
    global ObjectDeletionList
    ObjectDeletionList = dict()

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
    menu.Scenes[ 0 ] = menu
    
    start = StartScene()
    SaveScenes( "start", start )
    multi = MultiplayerScene()
    SaveScenes( "m", multi )
    
    start.Scenes[ 0 ] = multi
    ChangeGameScene( start )

def GetRoot():   
    timer = Timer()     # 
    
    img = UIImage(
        None,
        500, 750 )

    img.LoadImage( "pic1.jpg" )

    Save( img )    

    tranni = TranslateUIAnimator(
        timer.GetRealTime(),
        3000,
        vector2d( 300, 200 )
        )
    img.AddAnimator( tranni )
    Save( tranni )              # 对于所有创建出来的对象都要使用Save，不用使用drop

    rotani = RotateUIAnimator(
        timer.GetRealTime(),
        3000,
        360,
        True
        )
    img.AddAnimator( rotani )
    Save( rotani )

    return img


