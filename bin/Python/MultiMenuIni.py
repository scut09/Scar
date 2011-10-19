from UILoader import *
import SexangleButton
import ScenesCreator

RatioX = 1000 / 1280.0
RatioY = 600 / 1024.0
AniList = [] #用以保存动画
Save( AniList )

def GetRoot():
    global RatioX
    global RatioY

    # 场景根节点
    root = UIImage( None, 0, 0 )
    Save( root )

    # 左上角Logo
    logoPosX = 79 + 175
    logoPosY = 70 + 46
    logo = CreateLogo()
    logo.SetScale( vector2df( RatioY, RatioY ) )
    logo.SetPosition( vector2df( logoPosX * RatioX, logoPosY * RatioY ) )
    # 菜单项
    '''menuPosX = 94
    menuPosY = 245
    menu = CreateMenu()
    menu.SetScale( vector2df( RatioY, RatioY ) )
    menu.SetPosition( vector2df( menuPosX * RatioX, menuPosY * RatioY ) )'''
    # 背景
    bgPosX = 340 + 470
    bgPosY = 0 + 512
    bg = CreateBg()
    bg.SetScale( vector2df( RatioX, RatioY ) )
    bg.SetPosition( vector2df( bgPosX * RatioX, bgPosY * RatioY ) )

    root.AddChild( bg )
    #root.AddChild( menu )
    root.AddChild( logo )

    return root

######################################################
# 左上角LOGO
######################################################
def CreateLogo():
    logo = UIImage( None, 350, 92 )
    Save( logo )
    logo.LoadImage( "../media/UIResource/Menu/logo_1.png" )
    return logo

######################################################
# 组装背景
######################################################
def CreateBg():
    bg = UIImage( None, 940, 1024, -1 )
    Save( bg )
    bg.LoadImage( "../media/UIResource/Menu/bg_1.jpg" )
    return bg
