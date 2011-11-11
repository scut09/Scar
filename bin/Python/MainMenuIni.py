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
    print RatioX, RatioY

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
    menuPosX = 94
    menuPosY = 245
    menu = CreateMenu()
    menu.SetScale( vector2df( RatioY, RatioY ) )
    menu.SetPosition( vector2df( menuPosX * RatioX, menuPosY * RatioY ) )
    # 背景
    bgPosX = 340 + 470
    bgPosY = 0 + 512
    bg = CreateBg()
    bg.SetVisible( False );
    bg.SetScale( vector2df( RatioX, RatioY ) )
    bg.SetPosition( vector2df( bgPosX * RatioX, bgPosY * RatioY ) )

    root.AddChild( bg )
    root.AddChild( menu )
    root.AddChild( logo )

    root.SetName( "Root" )
    
    return root

######################################################
# 组装左上角Logo
######################################################
def CreateLogo():
    uiManager = GetUIManager()
    logo = uiManager.AddUIImage( None, 350, 92 )
    #Save( logo )
    logo.LoadImage( "../media/UIResource/Menu/logo_1.png" )
    logo.SetAntiAliasing()
    return logo

######################################################
# 组装背景
######################################################
def CreateBg():
    uiManager = GetUIManager()
    bg = uiManager.AddUIImage( None, 940, 1024, -1 )
    #Save( bg )
    '''bg.LoadImage( "../media/UIResource/Menu/bg_1.jpg" )
    bg.SetAlpha( 0 )'''
    return bg

######################################################
# 组装菜单项
######################################################    
def CreateMenu():
    uiManager = GetUIManager()
    # 设置第一个按钮的位置，其他按钮相对这个按钮设置位置
    posX = 200
    posY = 100
    # 组装四个按钮
    menu = uiManager.AddUIImage( None, 0, 0 )
    #Save( menu )
    btn1 = SexangleButton.MainMenuBtnPop( "单人" )
    btn1.SetPosition( vector2df( posX, posY ) )
    #Save( btn1 )
    btn2 = SexangleButton.MainMenuBtnPop( "多人" )
    btn2.SetPosition( vector2df( posX + 54, posY + 200 ) )
    #Save( btn2 )
    btn3 = SexangleButton.MainMenuBtnPop( "设定" )
    btn3.SetPosition( vector2df( posX + 108, posY + 400 ) )
    btn4 = SexangleButton.MainMenuBtn( "退出" )
    #Save( btn3 )
    #Save( btn4 )
    btn4.SetPosition( vector2df( posX - 90, posY + 340 ) )
    menu.AddChild( btn1 )
    menu.AddChild( btn2 )
    menu.AddChild( btn3 )
    menu.AddChild( btn4 )
    btn1.SetAlpha( 0 )
    btn1.SetScale( vector2df( 0.1, 0.1 ) )
    btn2.SetAlpha( 0 )
    btn2.SetScale( vector2df( 0.1, 0.1 ) )
    btn3.SetAlpha( 0 )
    btn3.SetScale( vector2df( 0.1, 0.1 ) )
    btn4.SetAlpha( 0 )
    btn4.SetScale( vector2df( 0.1, 0.1 ) )

    btn2.AddFunc( "OnMouseLeftButtonDown", "OnBtn2Click", "MainMenuIni" )

    return menu

######################################################
# 场景装载时动画
######################################################  
def LoadStartAnimation( root ):
    uiManager = GetUIManager()
    root = uiManager.GetUIObjectByName( "Root" )
    
    dua = 400
    #bg = root.GetChildren()[0]
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
    rot1.drop()
    btn1.AddAnimator( alp1 )
    alp1.drop()
    btn1.AddAnimator( sca1 )
    sca1.drop()
    btn2.AddAnimator( rot2 )
    rot2.drop()
    btn2.AddAnimator( alp2 )
    alp2.drop()
    btn2.AddAnimator( sca2 )
    sca2.drop()
    btn3.AddAnimator( rot3 )
    rot3.drop()
    btn3.AddAnimator( alp3 )
    alp3.drop()
    btn3.AddAnimator( sca3 )
    sca3.drop()
    btn4.AddAnimator( rot4 )
    rot4.drop()
    btn4.AddAnimator( alp4 )
    alp4.drop()
    btn4.AddAnimator( sca4 )
    sca4.drop()
    AniList.append( rot1 )
    AniList.append( alp1 )
    AniList.append( sca1 )

    #背景显示动画
    '''alphaUp = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime() + 400,
        1000,
        0,
        255 )
    AniList.append( alphaUp )
    bg.AddAnimator( alphaUp )'''

    return root

######################################################
# 点击多人游戏后切换场景
###################################################### 
def OnBtn2Click( node ):
    uiManager = GetUIManager()
    #ChangeGameScene( GetScene( 'multiMenu' ) )
    menu = node.GetParent()
    btn1 = menu.GetChildren()[0]
    btn2 = menu.GetChildren()[1]
    btn3 = menu.GetChildren()[2]
    btn4 = menu.GetChildren()[3]
    #取消响应函数
    btn1.RemoveFunc( "OnMenuButtonMouseMoveIn" )
    btn1.RemoveFunc( "OnMenuButtonMouseMoveOut" )
    btn2.RemoveFunc( "OnMenuButtonMouseMoveIn" )
    btn2.RemoveFunc( "OnMenuButtonMouseMoveOut" )
    btn3.RemoveFunc( "OnMenuButtonMouseMoveIn" )
    btn3.RemoveFunc( "OnMenuButtonMouseMoveOut" )
    btn4.RemoveFunc( "OnNoPopMouseMoveIn" )
    btn4.RemoveFunc( "OnNoPopMouseMoveOut" )
    #创建菜单过场动画
    sca1 = uiManager.CreateAnimatorScale(
        Timer().GetRealTime(),
        400,
        vector2df( 0.6, 0.6 ) )
    alp1 = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        400,
        255,
        0 )
    rot1 = uiManager.CreateAnimatorRotation(
        Timer().GetRealTime(),
        400,
        -360 )
    rot2 = rot1.Clone()
    rot3 = rot1.Clone()
    sca2 = sca1.Clone()
    sca3 = sca1.Clone()
    alp2 = alp1.Clone()
    alp3 = alp1.Clone()
    AniList.append( sca1 )
    AniList.append( sca2 )
    AniList.append( sca3 )
    AniList.append( alp1 )
    AniList.append( alp2 )
    AniList.append( alp3 )
    AniList.append( rot1 )
    AniList.append( rot2 )
    AniList.append( rot3 )
    btn1.AddAnimator( sca1 )
    sca1.drop()
    btn1.AddAnimator( alp1 )
    alp1.drop()
    btn1.AddAnimator( rot1 )
    rot1.drop()
    btn4.AddAnimator( sca2 )
    sca2.drop()
    btn4.AddAnimator( alp2 )
    alp2.drop()
    btn4.AddAnimator( rot2 )
    rot2.drop()
    btn3.AddAnimator( sca3 )
    sca3.drop()
    btn3.AddAnimator( alp3 )
    alp3.drop()
    btn3.AddAnimator( rot3 )
    rot3.drop()
    rot4 = rot1.Clone()
    sca4 = sca1.Clone()
    alp4 = alp1.Clone()
    AniList.append( rot4 )
    AniList.append( sca4 )
    AniList.append( alp4 )
    btn2.AddAnimator( rot4 )
    rot4.drop()
    btn2.AddAnimator( sca4 )
    sca4.drop()
    btn2.AddAnimator( alp4 )
    alp4.drop()
    btn2.GetChildren()[1].GetChildren()[0].SetVisible( False )
    btn2.GetChildren()[1].GetChildren()[1].SetVisible( False )
    #动画播放完后跳转场景
    tim1 = uiManager.CreateAnimatorTimelag(
        Timer().GetRealTime(),
        400,
        "MainMenuIni",
        "JumpToMultiMenu" )
    AniList.append( tim1 )
    btn2.AddAnimator( tim1 )
    tim1.drop()

def JumpToMultiMenu():
    sceneMgr = GetGameSceneManager()
    ChangeGameScene( sceneMgr.GetSceneByName( 'MultiMenuIni' ) )
