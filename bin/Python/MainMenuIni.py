from UILoader import *
import SexangleButton
import ScenesCreator

RatioX = 0.78125
RatioY = 0.625
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
    menuPosX = 94
    menuPosY = 245
    menu = CreateMenu()
    menu.SetScale( vector2df( RatioY, RatioY ) )
    menu.SetPosition( vector2df( menuPosX * RatioX, menuPosY * RatioY ) )
    # 背景
    bgPosX = 340 + 470
    bgPosY = 0 + 512
    bg = CreateBg()
    bg.SetScale( vector2df( RatioX, RatioY ) )
    bg.SetPosition( vector2df( bgPosX * RatioX, bgPosY * RatioY ) )

    root.AddChild( bg )
    root.AddChild( menu )
    root.AddChild( logo )

    return root

######################################################
# 组装左上角Logo
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
    bg.SetAlpha( 0 )
    alphaUp = AlphaChangeUIAnimator(
        Timer().GetRealTime() + 400,
        1000,
        0,
        255 )
    AniList.append( alphaUp )
    bg.AddAnimator( alphaUp )
    return bg

######################################################
# 组装菜单项
######################################################    
def CreateMenu():
    
    # 设置第一个按钮的位置，其他按钮相对这个按钮设置位置
    posX = 200
    posY = 100
    # 组装四个按钮
    menu = UIImage( None, 0, 0 )
    Save( menu )
    btn1 = SexangleButton.MainMenuBtnPop( "单人" )
    btn1.SetPosition( vector2df( posX, posY ) )
    Save( btn1 )
    btn2 = SexangleButton.MainMenuBtnPop( "多人" )
    btn2.SetPosition( vector2df( posX + 54, posY + 200 ) )
    Save( btn2 )
    btn3 = SexangleButton.MainMenuBtnPop( "设定" )
    btn3.SetPosition( vector2df( posX + 108, posY + 400 ) )
    btn4 = SexangleButton.MainMenuBtn( "退出" )
    Save( btn3 )
    Save( btn4 )
    btn4.SetPosition( vector2df( posX - 90, posY + 340 ) )
    menu.AddChild( btn1 )
    menu.AddChild( btn2 )
    menu.AddChild( btn3 )
    menu.AddChild( btn4 )
    btn1.SetRotation( -90 )
    btn1.SetAlpha( 0 )
    btn1.SetScale( vector2df( 0.1, 0.1 ) )
    btn2.SetRotation( -90 )
    btn2.SetAlpha( 0 )
    btn2.SetScale( vector2df( 0.1, 0.1 ) )
    btn3.SetRotation( -90 )
    btn3.SetAlpha( 0 )
    btn3.SetScale( vector2df( 0.1, 0.1 ) )
    btn4.SetRotation( -90 )
    btn4.SetAlpha( 0 )
    btn4.SetScale( vector2df( 0.1, 0.1 ) )
  
    # 旋转、缩放、Alpha改变动画
    dua = 400 #动画持续时间
    #AniList = [] #用以保存动画
    global AniList
    rot1 = RotateUIAnimator(
        Timer().GetRealTime(),
        dua,
        450 )
    sca1 = ScaleUIAnimator(
        Timer().GetRealTime(),
        dua,
        vector2df( 1.9, 1.9 ) )
    alp1 = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        dua,
        0,
        255 )
    rot2 = rot1.Clone()
    rot3 = rot1.Clone()
    rot4 = rot1.Clone()
    sca2 = sca1.Clone()
    sca3 = sca1.Clone()
    sca4 = sca1.Clone()
    alp2 = alp1.Clone()
    alp3 = alp1.Clone()
    alp4 = alp1.Clone()
    btn1.AddAnimator( rot1 )
    btn1.AddAnimator( alp1 )
    btn1.AddAnimator( sca1 )
    btn2.AddAnimator( rot2 )
    btn2.AddAnimator( alp2 )
    btn2.AddAnimator( sca2 )
    btn3.AddAnimator( rot3 )
    btn3.AddAnimator( alp3 )
    btn3.AddAnimator( sca3 )
    btn4.AddAnimator( rot4 )
    btn4.AddAnimator( alp4 )
    btn4.AddAnimator( sca4 )
    rot2.drop()
    rot3.drop()
    rot4.drop()
    sca2.drop()
    sca3.drop()
    sca4.drop()
    alp2.drop()
    alp3.drop()
    alp4.drop()
    AniList.append( rot1 )
    AniList.append( alp1 )
    AniList.append( sca1 )

    #Save( AniList )

    btn2.AddFunc( "OnMouseLeftButtonDown", "OnBtn2Click", "MainMenuIni" )

    return menu

######################################################
# 点击多人游戏后切换场景
###################################################### 
def OnBtn2Click( node ):
    '''menu = node.Parent
    btn1 = node.GetChildren()[0]
    btn2 = node.GetChildren()[1]
    btn3 = node.GetChildren()[2]
    btn4 = node.GetChildren()[3]'''
    #创建菜单过场动画
    sca1 = ScaleUIAnimator(
        Timer().GetRealTime(),
        400,
        vector2df( 0.1, 0.1 ) )
    alp1 = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        400,
        255,
        0 )    
    #global ScenesDict
    ChangeGameScene( GetScene( 'm' ) )
