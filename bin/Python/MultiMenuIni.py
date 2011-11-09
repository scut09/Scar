from UILoader import *
import SexangleButton
import ScenesCreator

RatioX = ScreenWidth / 1280.0
RatioY = ScreenHeight / 1024.0
AniList = [] #用以保存动画
#Save( AniList )

def GetRoot():
    global RatioX
    global RatioY
    uiManager = GetUIManager()
    # 场景根节点
    root = uiManager.AddUIImage( None, 0, 0 )
    #Save( root )

    # 左上角Logo
    logoPosX = 79 + 175
    logoPosY = 70 + 46
    logo = CreateLogo()
    logo.SetScale( vector2df( RatioY, RatioY ) )
    logo.SetPosition( vector2df( logoPosX * RatioX, logoPosY * RatioY ) )
    # 菜单项
    menuPosX = 100
    menuPosY = 240
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

    root.SetName( "Root" )

    return root
######################################################
# 组装菜单项
######################################################
def CreateMenu():
    uiManager = GetUIManager()
    menu = uiManager.AddUIImage( None, 0, 0 )
    #Save( menu )
    #第一个按钮的位置
    posX = 100
    posY = 240
    img = SexangleButton.MainMenuButtonSelected( "多人" )
    #Save( img )
    btn1 = SexangleButton.MainMenuBtn( "新建" )
    #Save( btn1 )
    btn2 = SexangleButton.MainMenuBtn( "加入" )
    #Save( btn2 )
    btn3 = SexangleButton.MainMenuBtn( "返回" )
    #Save( btn3 )
    menu.AddChild( img )
    menu.AddChild( btn1 )
    menu.AddChild( btn2 )
    menu.AddChild( btn3 )
    img.SetPosition( vector2df( posX, posY ) )
    btn1.SetPosition( vector2df( posX + 140, posY - 144 ) )
    btn2.SetPosition( vector2df( posX + 194, posY + 56 ) )
    btn3.SetPosition( vector2df( posX + 46, posY + 196 ) )
    img.SetAlpha( 0 )
    btn1.SetAlpha( 0 )
    btn2.SetAlpha( 0 )
    btn3.SetAlpha( 0 )
    img.SetScale( vector2df( 0.1, 0.1 ) )
    btn1.SetScale( vector2df( 0.1, 0.1 ) )
    btn2.SetScale( vector2df( 0.1, 0.1 ) )
    btn3.SetScale( vector2df( 0.1, 0.1 ) )
    return menu

######################################################
# 左上角LOGO
######################################################
def CreateLogo():
    uiManager = GetUIManager()
    logo = uiManager.AddUIImage( None, 350, 92 )
    #Save( logo )
    logo.LoadImage( "../media/UIResource/Menu/logo_1.png" )
    return logo

######################################################
# 组装背景
######################################################
def CreateBg():
    uiManager = GetUIManager()
    bg = uiManager.AddUIImage( None, 940, 1024, -1 )
    #Save( bg )
    bg.LoadImage( "../media/UIResource/Menu/bg_1.jpg" )
    return bg

######################################################
# 场景装载时动画
######################################################
def LoadStartAnimation( root ):
    uiManager = GetUIManager()
    root = uiManager.GetUIObjectByName( "Root" )
    
    dua = 400
    menu = root.GetChildren()[1]
    btn1 = menu.GetChildren()[0]
    btn2 = menu.GetChildren()[1]
    btn3 = menu.GetChildren()[2]
    btn4 = menu.GetChildren()[3]

    # 按钮出现动画
    rot1 = uiManager.CreateAnimatorRotation(
        Timer().GetRealTime(),
        dua,
        360 )
    sca1 = uiManager.CreateAnimatorScale(
        Timer().GetRealTime(),
        dua,
        vector2df( 1.9, 1.9 ) )
    alp1 = uiManager.CreateAnimatorAlphaChange(
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
    return root
    
