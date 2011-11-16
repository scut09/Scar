﻿from UILoader import *
import ScenesCreator

cenX = ScreenWidth / 2.0
cenY = ScreenHeight / 2.0

def GetRoot():
    global cenX, cenY
    uiManager = GetUIManager()
    
    # 场景根节点
    root = uiManager.AddUIImage( uiManager.GetRootUIObject(), 0, 0 )
    #Save( root )

    # 以下为菜单
    # 选择阵营
    # 菜单背景
    scMenu = uiManager.AddUIImage( root, 800, 550 )
    scMenu.SetPosition( vector2df( cenX, cenY ) )
    scMenu.LoadImage("../media/UIResource/Game/sc_bg.png")
    scMenu.SetName( "scMenu" )
    # 菜单按钮，加达里
    selectC = uiManager.AddUIButton( scMenu, 360, 460 )
    selectC.SetPosition( vector2df( -194, 25 ) )
    coverC = uiManager.AddUIImage( selectC, 360, 460 )
    coverC.LoadImage("../media/UIResource/Game/sc_mask.png")
    coverC.SetVisible( False )
    selectC.AddFunc( "OnMouseMoveIn", "SelectCGOver", "MultiPlayCallBacks" )
    selectC.AddFunc( "OnMouseMoveOut", "SelectCGDefault", "MultiPlayCallBacks" )
    # 菜单按钮，盖伦特
    selectG = uiManager.AddUIButton( scMenu, 360, 460 )
    selectG.SetPosition( vector2df( 194, 25 ) )
    coverG = uiManager.AddUIImage( selectG, 360, 460 )
    coverG.LoadImage("../media/UIResource/Game/sc_mask.png")
    coverG.SetVisible( False )
    selectG.AddFunc( "OnMouseMoveIn", "SelectCGOver", "MultiPlayCallBacks" )
    selectG.AddFunc( "OnMouseMoveOut", "SelectCGDefault", "MultiPlayCallBacks" )



    
    # 以下这些为战斗时候用的UI
    # 活动范围圈
    ring1 = uiManager.AddUIImage( root, 586, 586, 0, 1, vector2df( cenX, cenY ) )
    ring1.LoadImage("../media/UIResource/Game/cr_1.png")
    ring1.SetName( "ring" )
    ring1.SetVisible( False )

    # 水平圈
    ring2 = uiManager.AddUIImage( root, 635, 438, 0, 1, vector2df( cenX, cenY ) )
    ring2.LoadImage("../media/UIResource/Game/cr_2.png")
    ring2.SetName( "gradienter" )
    ring2.SetAntiAliasing()
    ring2.SetVisible( False )

    # 中心准心
    post1 = uiManager.AddUIImage( root, 74, 74, 0, 1, vector2df( cenX, cenY ) )
    post1.LoadImage("../media/UIResource/Game/post_1.png")
    post1.SetAntiAliasing()
    post1.SetName( "centerCursor" )
    post1.SetVisible( False )
    rotAni = uiManager.CreateAnimatorRotation( 0, 2000, 360, True )
    post1.AddAnimator( rotAni )
    rotAni.drop()

    # 鼠标准心
    post2 = uiManager.AddUIImage( root, 46, 46, 0, 1, vector2df( cenX, cenY ) )
    post2.LoadImage("../media/UIResource/Game/post_2.png")
    post2.SetAntiAliasing()
    post2.SetVisible( False )
    post2.SetName( "cursor" )
    rotAni2 = uiManager.CreateAnimatorRotation( 0, 2000, -360, True )
    post2.AddAnimator( rotAni2 )
    rotAni2.drop()

    # 速度槽满
    speedBar1 = uiManager.AddUIImage( root, 98, 389, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    speedBar1.LoadImage("../media/UIResource/Game/speed_1.png")
    speedBar1.SetName( "speed1" )
    speedBar1.SetVisible( False )
    # 速度槽空
    speedBar2 = uiManager.AddUIImage( root, 98, 389, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    speedBar2.LoadImage("../media/UIResource/Game/speed_2.png")
    speedBar2.SetName( "speed2" )
    speedBar2.SetVisible( False )
    # 速度显示文字
    speedText = uiManager.AddUIStaticText( root, 100, 20, u"速度:", SColor(220,220,220,220) )
    speedText.SetName( "speedText" )
    speedText.SetPosition( vector2df( cenX + 160, cenY + 200 ) )
    speedText.SetVisible( False )

    # 能量槽满
    energy1 = uiManager.AddUIImage( root, 94, 363, 0, 0, vector2df( cenX + 214, cenY - 10 ) )
    energy1.LoadImage("../media/UIResource/Game/energy_1.png")
    energy1.SetName( "energy1" )
    energy1.SetVisible( False )
    # 能量槽空
    energy2 = uiManager.AddUIImage( root, 94, 363, 0, 0, vector2df( cenX + 214, cenY - 10 ) )
    energy2.LoadImage("../media/UIResource/Game/energy_2.png")
    energy2.SetName( "energy2" )
    energy2.SetVisible( False )
    # 能量显示文字
    energyText = uiManager.AddUIStaticText( root, 100, 20, u"能量:", SColor(220,220,220,220) )
    energyText.SetName( "energyText" )
    energyText.SetPosition( vector2df( cenX + 145, cenY + 180 ) )
    energyText.SetVisible( False )

    # 护盾槽满
    shield1 = uiManager.AddUIImage( root, 100, 389, 0, 0, vector2df( cenX - 232, cenY + 10 ) )
    shield1.LoadImage("../media/UIResource/Game/shield_1.png")
    shield1.SetName( "shield1" )
    shield1.SetVisible( False )
    # 护盾槽空
    shield2 = uiManager.AddUIImage( root, 100, 389, 0, 0, vector2df( cenX - 232, cenY + 10 ) )
    shield2.LoadImage("../media/UIResource/Game/shield_2.png")
    shield2.SetName( "shield2" )
    shield2.SetVisible( False )
    # 护盾显示文字
    shieldText = uiManager.AddUIStaticText( root, 100, 20, u"护盾:", SColor(220,220,220,220) )
    shieldText.SetName( "shieldText" )
    shieldText.SetPosition( vector2df( cenX - 115, cenY + 190 ) )
    shieldText.SetVisible( False )

    # 护甲槽满
    armor1 = uiManager.AddUIImage( root, 93, 360, 0, 0, vector2df( cenX - 214, cenY + 10 ) )
    armor1.LoadImage("../media/UIResource/Game/armor_1.png")
    armor1.SetName( "armor1" )
    armor1.SetVisible( False )
    # 护甲槽满
    armor2 = uiManager.AddUIImage( root, 93, 360, 0, 0, vector2df( cenX - 214, cenY + 10 ) )
    armor2.LoadImage("../media/UIResource/Game/armor_2.png")
    armor2.SetName( "armor2" )
    armor2.SetVisible( False )
    # 护甲显示文字
    armorText = uiManager.AddUIStaticText( root, 100, 20, u"护甲:", SColor(220,220,220,220) )
    armorText.SetName( "armorText" )
    armorText.SetPosition( vector2df( cenX - 130, cenY + 210 ) )
    armorText.SetVisible( False )

    # 雷达
    radarBox = uiManager.AddUIImage( root, 0, 0, 0, 0, vector2df( cenX - 430, cenY + 260 ) )
    radarBox.SetScale( vector2df( 1, 0.4 ) )
    radarBox.SetName( "radarBox" )
    radarBox.SetVisible( False )
    radar = uiManager.AddUIImage( radarBox, 402, 402 )
    radar.LoadImage("../media/UIResource/Game/radar.png")
    radar.SetName( "radar" )
    radar.SetAntiAliasing()
    # 自己
    mes = uiManager.AddUIImage( radarBox, 48, 66 )
    mes.LoadImage("../media/UIResource/Game/radar_me_s.png")
    me = uiManager.AddUIImage( radarBox, 48, 66 )
    me.LoadImage("../media/UIResource/Game/radar_me.png")
    me.SetPosition( vector2df( 0, -20 ) )
    
    
    '''rotAni = uiManager.CreateAnimatorRotation( 0, 4000, 360, True )
    radar.AddAnimator( rotAni )
    rotAni.drop()'''


    #以下的这些不会在一开始就出现在屏幕上，供复制用

    # 雷达上的敌人
    rEnemy = uiManager.AddUIImage( radar, 36, 36 )
    rEnemy.LoadImage("../media/UIResource/Game/radar_e.png")
    rEnemy.SetName( "rEnemy" )
    rEnemy.SetVisible( False )
    # 雷达上的友军
    rFriend = uiManager.AddUIImage( radar, 36, 36 )
    rFriend.LoadImage("../media/UIResource/Game/radar_f.png")
    rFriend.SetName( "rFriend" )
    rFriend.SetVisible( False )

    #目标圈——敌军
    target1 = uiManager.AddUIImage( root, 60, 60, 0, 1, vector2df( 100, 100 ) )
    target1.LoadImage( "../media/UIResource/Game/target_1.png" )
    target1.SetName( "target1" )
    target1.SetAntiAliasing()
    target1.SetVisible( False )
    #Save( target1 )
    #目标圈——友军
    '''target2 = uiManager.AddUIImage( root, 60, 60, 0, 1, vector2df( 100, 100 ) )
    target2.LoadImage( "../media/UIResource/Game/target_2.png" )
    target2.SetName( "target2" )
    #Save( target2 )'''

    #锁定框——已锁定
    lock1 = uiManager.AddUIImage( root, 100, 100, 0, 1, vector2df( cenX, cenY ) )
    lock1.LoadImage( "../media/UIResource/Game/lock_1.png" )
    lock1.SetName( "lock1" )
    lock1.SetAntiAliasing()
    lock1.SetVisible( False )
    rotAni3 = uiManager.CreateAnimatorRotation( 0, 1000, -360, True )
    #Save( rotAni3 )
    lock1.AddAnimator( rotAni3 )
    rotAni3.drop()
    ##Save( lock1 )

    #敌人指示器
    indicator1 = uiManager.AddUIImage( root, 0, 0, 0, 1, vector2df( cenX, cenY ) )
    indicator1.SetName( "indicator1" )
    indicator1.SetVisible( False )
    #Save( indicator1 )
    tip = uiManager.AddUIImage( indicator1, 31, 28, 0, 0, vector2df( 0, -302 ) )
    tip.LoadImage( "../media/UIResource/Game/indicator_1.png" )
    #Save( tip )
    
    return root

