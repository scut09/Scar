from UILoader import *
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
    scMenu.SetVisible( False )
    # 菜单按钮，加达里
    selectC = uiManager.AddUIButton( scMenu, 360, 460 )
    selectC.SetPosition( vector2df( -194, 25 ) )
    coverC = uiManager.AddUIImage( selectC, 360, 460 )
    coverC.LoadImage("../media/UIResource/Game/sc_mask.png")
    coverC.SetVisible( False )
    selectC.AddFunc( "OnMouseMoveIn", "GeneralCoverOver", "MultiPlayCallBacks" )
    selectC.AddFunc( "OnMouseMoveOut", "GeneralCoverDefault", "MultiPlayCallBacks" )
    selectC.AddFunc( "OnMouseLeftButtonDown", "SelectCClick", "MultiPlayCallBacks" )
    # 菜单按钮，盖伦特
    selectG = uiManager.AddUIButton( scMenu, 360, 460 )
    selectG.SetPosition( vector2df( 194, 25 ) )
    coverG = uiManager.AddUIImage( selectG, 360, 460 )
    coverG.LoadImage("../media/UIResource/Game/sc_mask.png")
    coverG.SetVisible( False )
    selectG.AddFunc( "OnMouseMoveIn", "GeneralCoverOver", "MultiPlayCallBacks" )
    selectG.AddFunc( "OnMouseMoveOut", "GeneralCoverDefault", "MultiPlayCallBacks" )
    selectG.AddFunc( "OnMouseLeftButtonDown", "SelectGClick", "MultiPlayCallBacks" )

    # 选择舰船
    # 加达里
    # 菜单背景
    ssMenu = uiManager.AddUIImage( root, 800, 550 )
    ssMenu.SetPosition( vector2df( cenX, cenY ) )
    ssMenu.LoadImage("../media/UIResource/Game/ss_bg.png")
    ssMenu.SetName( "ssMenuC" )
    ssMenu.SetVisible( False )
    # 舰船列表菜单
    # 蜻蜓
    cf1b = uiManager.AddUIButton( ssMenu, 120, 40 )
    cf1b.SetPosition( vector2df( -314, -195 ) )
    default = uiManager.AddUIImage( cf1b, 120, 40 )
    default.LoadImage("../media/UIResource/Game/cf1b_d.png")
    default.SetVisible( False )
    over = uiManager.AddUIImage( cf1b, 120, 40 )
    over.LoadImage("../media/UIResource/Game/cf1b_o.png")
    cf1b.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    cf1b.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    cf1b.AddFunc( "OnMouseLeftButtonDown", "SelectCf1", "MultiPlayCallBacks" )
    #over.SetVisible( False )
    # 小鹰
    cf2b = uiManager.AddUIButton( ssMenu, 120, 40 )
    cf2b.SetPosition( vector2df( -314, -145 ) )
    default = uiManager.AddUIImage( cf2b, 120, 40 )
    default.LoadImage("../media/UIResource/Game/cf2b_d.png")
    #default.SetVisible( False )
    over = uiManager.AddUIImage( cf2b, 120, 40 )
    over.LoadImage("../media/UIResource/Game/cf2b_o.png")
    over.SetVisible( False )
    cf2b.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    cf2b.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    cf2b.AddFunc( "OnMouseLeftButtonDown", "SelectCf2", "MultiPlayCallBacks" )
    # 蜻蜓信息窗口
    cf1Info = uiManager.AddUIImage( ssMenu, 0, 0 )
    cf1Info.SetName( "cf1Info" )
    #cf1Info.SetVisible( False )
    cf1Pic = uiManager.AddUIImage( cf1Info, 410, 290 )
    cf1Pic.LoadImage("../media/UIResource/Game/cf1.jpg")
    cf1Pic.SetPosition( vector2df( 130, -50 ) )
    cf1Att = uiManager.AddUIImage( cf1Info, 78, 119 )
    cf1Att.LoadImage("../media/UIResource/Game/attribute.png")
    cf1Att.SetPosition( vector2df( -158, -112 ) )
    cf1Des = uiManager.AddUIImage( cf1Info, 229, 14 )
    cf1Des.LoadImage("../media/UIResource/Game/describtion.png")
    cf1Des.SetPosition( vector2df( 46, 115 ) )
    # 小鹰信息窗口
    cf2Info = uiManager.AddUIImage( ssMenu, 0, 0 )
    cf2Info.SetName( "cf2Info" )
    cf2Info.SetVisible( False )
    cf2Pic = uiManager.AddUIImage( cf2Info, 410, 290 )
    cf2Pic.LoadImage("../media/UIResource/Game/cf2.jpg")
    cf2Pic.SetPosition( vector2df( 130, -50 ) )
    cf2Att = uiManager.AddUIImage( cf2Info, 78, 119 )
    cf2Att.LoadImage("../media/UIResource/Game/attribute.png")
    cf2Att.SetPosition( vector2df( -158, -112 ) )
    cf2Des = uiManager.AddUIImage( cf2Info, 229, 14 )
    cf2Des.LoadImage("../media/UIResource/Game/describtion.png")
    cf2Des.SetPosition( vector2df( 46, 115 ) )
    # 确认按钮
    confirm = uiManager.AddUIButton( ssMenu, 150, 50 )
    confirm.SetPosition( vector2df( 291, 233 ) )
    default = uiManager.AddUIImage( confirm, 150, 50 )
    default.LoadImage("../media/UIResource/Game/confirm_d.png")
    over = uiManager.AddUIImage( confirm, 150, 50 )
    over.LoadImage("../media/UIResource/Game/confirm_o.png")
    over.SetVisible( False )
    confirm.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    confirm.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    confirm.AddFunc( "OnMouseLeftButtonDown", "ConfirmClick", "MultiPlayCallBacks" )
    # 盖伦特
    # 菜单背景
    ssMenu = uiManager.AddUIImage( root, 800, 550 )
    ssMenu.SetPosition( vector2df( cenX, cenY ) )
    ssMenu.LoadImage("../media/UIResource/Game/ss_bg.png")
    ssMenu.SetName( "ssMenuG" )
    ssMenu.SetVisible( False )
    # 舰船列表菜单
    # 投矛手
    gf1b = uiManager.AddUIButton( ssMenu, 120, 40 )
    gf1b.SetPosition( vector2df( -314, -195 ) )
    default = uiManager.AddUIImage( gf1b, 120, 40 )
    default.LoadImage("../media/UIResource/Game/gf1b_d.png")
    default.SetVisible( False )
    over = uiManager.AddUIImage( gf1b, 120, 40 )
    over.LoadImage("../media/UIResource/Game/gf1b_o.png")
    gf1b.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    gf1b.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    gf1b.AddFunc( "OnMouseLeftButtonDown", "SelectGf1", "MultiPlayCallBacks" )
    #over.SetVisible( False )
    # 纳维达斯
    gf2b = uiManager.AddUIButton( ssMenu, 120, 40 )
    gf2b.SetPosition( vector2df( -314, -145 ) )
    default = uiManager.AddUIImage( gf2b, 120, 40 )
    default.LoadImage("../media/UIResource/Game/gf2b_d.png")
    #default.SetVisible( False )
    over = uiManager.AddUIImage( gf2b, 120, 40 )
    over.LoadImage("../media/UIResource/Game/gf2b_o.png")
    over.SetVisible( False )
    gf2b.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    gf2b.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    gf2b.AddFunc( "OnMouseLeftButtonDown", "SelectGf2", "MultiPlayCallBacks" )
    # 投矛手信息窗口
    gf1Info = uiManager.AddUIImage( ssMenu, 0, 0 )
    gf1Info.SetName( "gf1Info" )
    #gf1Info.SetVisible( False )
    gf1Pic = uiManager.AddUIImage( gf1Info, 410, 290 )
    gf1Pic.LoadImage("../media/UIResource/Game/gf1.jpg")
    gf1Pic.SetPosition( vector2df( 130, -50 ) )
    gf1Att = uiManager.AddUIImage( gf1Info, 78, 119 )
    gf1Att.LoadImage("../media/UIResource/Game/attribute.png")
    gf1Att.SetPosition( vector2df( -158, -112 ) )
    gf1Des = uiManager.AddUIImage( gf1Info, 229, 14 )
    gf1Des.LoadImage("../media/UIResource/Game/describtion.png")
    gf1Des.SetPosition( vector2df( 46, 115 ) )
    # 纳维达斯信息窗口
    gf2Info = uiManager.AddUIImage( ssMenu, 0, 0 )
    gf2Info.SetName( "gf2Info" )
    gf2Info.SetVisible( False )
    gf2Pic = uiManager.AddUIImage( gf2Info, 410, 290 )
    gf2Pic.LoadImage("../media/UIResource/Game/gf2.jpg")
    gf2Pic.SetPosition( vector2df( 130, -50 ) )
    gf2Att = uiManager.AddUIImage( gf2Info, 78, 119 )
    gf2Att.LoadImage("../media/UIResource/Game/attribute.png")
    gf2Att.SetPosition( vector2df( -158, -112 ) )
    gf2Des = uiManager.AddUIImage( gf2Info, 229, 14 )
    gf2Des.LoadImage("../media/UIResource/Game/describtion.png")
    gf2Des.SetPosition( vector2df( 46, 115 ) )
    # 确认按钮
    confirm = uiManager.AddUIButton( ssMenu, 150, 50 )
    confirm.SetPosition( vector2df( 291, 233 ) )
    default = uiManager.AddUIImage( confirm, 150, 50 )
    default.LoadImage("../media/UIResource/Game/confirm_d.png")
    over = uiManager.AddUIImage( confirm, 150, 50 )
    over.LoadImage("../media/UIResource/Game/confirm_o.png")
    over.SetVisible( False )
    confirm.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    confirm.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    confirm.AddFunc( "OnMouseLeftButtonDown", "ConfirmClick", "MultiPlayCallBacks" )

    # 购买武器装备
    seMenu = uiManager.AddUIButton( root, 800, 550 )
    seMenu = uiManager.AddUIImage( root, 800, 550 )
    seMenu.SetPosition( vector2df( cenX, cenY ) )
    seMenu.LoadImage("../media/UIResource/Game/se_bg.png")
    seMenu.SetName( "seMenu" )
    seMenu.SetVisible( False )
    # 购买导航栏
    # 主炮
    navGun = uiManager.AddUIButton( seMenu, 60, 40 )
    #navGun.SetName( "navGun" )
    navGun.SetPosition( vector2df( -102, -205 ) )
    default = uiManager.AddUIImage( navGun, 60, 40 )
    default.LoadImage("../media/UIResource/Game/gunb_d.png")
    default.SetVisible( False )
    over = uiManager.AddUIImage( navGun, 60, 40 )
    over.LoadImage("../media/UIResource/Game/gunb_o.png")
    #over.SetVisible( False )
    navGun.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    navGun.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    navGun.AddFunc( "OnMouseLeftButtonDown", "NavGunClick", "MultiPlayCallBacks" )
    # 导弹
    navMissle = uiManager.AddUIButton( seMenu, 60, 40 )
    #navMissle.SetName( "navMissle" )
    navMissle.SetPosition( vector2df( -102, -155 ) )
    default = uiManager.AddUIImage( navMissle, 60, 40 )
    default.LoadImage("../media/UIResource/Game/missleb_d.png")
    over = uiManager.AddUIImage( navMissle, 60, 40 )
    over.LoadImage("../media/UIResource/Game/missleb_o.png")
    over.SetVisible( False )
    navMissle.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    navMissle.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    navMissle.AddFunc( "OnMouseLeftButtonDown", "NavMissleClick", "MultiPlayCallBacks" )
    # 购买列表
    # 主炮
    Gun = uiManager.AddUIImage( seMenu, 0, 0 )
    Gun.SetName( "buyListGun" )
    #Gun.SetVisible( False )
    # 磁轨炮
    Gun1 = uiManager.AddUIButton( Gun, 370, 64 )
    Gun1.SetPosition( vector2df( 145, -153 ) )
    default = uiManager.AddUIImage( Gun1, 370, 64 )
    default.LoadImage("../media/UIResource/Game/gun1_d.png")
    over = uiManager.AddUIImage( Gun1, 370, 64 )
    over.LoadImage("../media/UIResource/Game/gun1_o.png")
    over.SetVisible( False )
    Gun1.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    Gun1.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    Gun1.AddFunc( "OnMouseLeftButtonDown", "Gun1Click", "MultiPlayCallBacks" )
    # 集束激光
    Gun2 = uiManager.AddUIButton( Gun, 370, 64 )
    Gun2.SetPosition( vector2df( 145, -89 ) )
    default = uiManager.AddUIImage( Gun2, 370, 64 )
    default.LoadImage("../media/UIResource/Game/gun2_d.png")
    over = uiManager.AddUIImage( Gun2, 370, 64 )
    over.LoadImage("../media/UIResource/Game/gun2_o.png")
    over.SetVisible( False )
    Gun2.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    Gun2.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    Gun2.AddFunc( "OnMouseLeftButtonDown", "Gun2Click", "MultiPlayCallBacks" )
    # 导弹
    Missle = uiManager.AddUIImage( seMenu, 0, 0 )
    Missle.SetName( "buyListMissle" )
    Missle.SetVisible( False )
    # 热导飞弹
    Missle1 = uiManager.AddUIButton( Missle, 370, 64 )
    Missle1.SetPosition( vector2df( 145, -153 ) )
    default = uiManager.AddUIImage( Missle1, 370, 64 )
    default.LoadImage("../media/UIResource/Game/missle1_d.png")
    over = uiManager.AddUIImage( Missle1, 370, 64 )
    over.LoadImage("../media/UIResource/Game/missle1_o.png")
    over.SetVisible( False )
    Missle1.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    Missle1.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    Missle1.AddFunc( "OnMouseLeftButtonDown", "Missle1Click", "MultiPlayCallBacks" )
    # 确认按钮
    confirm = uiManager.AddUIButton( seMenu, 150, 50 )
    confirm.SetPosition( vector2df( 291, 233 ) )
    default = uiManager.AddUIImage( confirm, 150, 50 )
    default.LoadImage("../media/UIResource/Game/confirm_d.png")
    over = uiManager.AddUIImage( confirm, 150, 50 )
    over.LoadImage("../media/UIResource/Game/confirm_o.png")
    over.SetVisible( False )
    confirm.AddFunc( "OnMouseMoveIn", "GeneralOver", "MultiPlayCallBacks" )
    confirm.AddFunc( "OnMouseMoveOut", "GeneralDefault", "MultiPlayCallBacks" )
    confirm.AddFunc( "OnMouseLeftButtonDown", "ConfirmClick", "MultiPlayCallBacks" )

    
    # 以下这些为战斗时候用的UI
    # 活动范围圈
    ring1 = uiManager.AddUIImage( root, 586, 586, 0, 1, vector2df( cenX, cenY ) )
    ring1.LoadImage("../media/UIResource/Game/cr_1.png")
    ring1.SetName( "ring" )
    ring1.SetVisible( False )

    # 水平圈
    ring2 = uiManager.AddUIImage( root, 636, 436, 0, 1, vector2df( cenX, cenY ) )
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
    speedBar1 = uiManager.AddUIImage( root, 92, 394, 0, 0, vector2df( cenX + 242, cenY ) )
    speedBar1.LoadImage("../media/UIResource/Game/speed_1.png")
    speedBar1.SetName( "speed1" )
    speedBar1.SetVisible( False )
    # 速度槽空
    speedBar2 = uiManager.AddUIImage( root, 92, 394, 0, 0, vector2df( cenX + 242, cenY ) )
    speedBar2.LoadImage("../media/UIResource/Game/speed_2.png")
    speedBar2.SetName( "speed2" )
    speedBar2.SetVisible( False )
    # 速度显示文字
    speedText = uiManager.AddUIStaticText( root, 100, 20, u"速度:", SColor(255,255,255,255) )
    speedText.SetName( "speedText" )
    speedText.SetPosition( vector2df( cenX + 160, cenY + 210 ) )
    speedText.SetVisible( False )

    # 能量槽满
    energy1 = uiManager.AddUIImage( root, 89, 369, 0, 0, vector2df( cenX + 226, cenY ) )
    energy1.LoadImage("../media/UIResource/Game/energy_1.png")
    energy1.SetName( "energy1" )
    energy1.SetVisible( False )
    # 能量槽空
    energy2 = uiManager.AddUIImage( root, 89, 369, 0, 0, vector2df( cenX + 226, cenY ) )
    energy2.LoadImage("../media/UIResource/Game/energy_2.png")
    energy2.SetName( "energy2" )
    energy2.SetVisible( False )
    # 能量显示文字
    energyText = uiManager.AddUIStaticText( root, 100, 20, u"能量:", SColor(255,255,255,255) )
    energyText.SetName( "energyText" )
    energyText.SetPosition( vector2df( cenX + 145, cenY + 190 ) )
    energyText.SetVisible( False )

    # 护盾槽满
    shield1 = uiManager.AddUIImage( root, 89, 369, 0, 0, vector2df( cenX - 226, cenY ) )
    shield1.LoadImage("../media/UIResource/Game/shield_1.png")
    shield1.SetName( "shield1" )
    shield1.SetVisible( False )
    # 护盾槽空
    shield2 = uiManager.AddUIImage( root, 89, 369, 0, 0, vector2df( cenX - 226, cenY ) )
    shield2.LoadImage("../media/UIResource/Game/shield_2.png")
    shield2.SetName( "shield2" )
    shield2.SetVisible( False )
    # 护盾显示文字
    shieldText = uiManager.AddUIStaticText( root, 100, 20, u"护盾:", SColor(255,255,255,255) )
    shieldText.SetName( "shieldText" )
    shieldText.SetPosition( vector2df( cenX - 115, cenY + 190 ) )
    shieldText.SetVisible( False )

    # 护甲槽满
    armor1 = uiManager.AddUIImage( root, 92, 394, 0, 0, vector2df( cenX - 242, cenY ) )
    armor1.LoadImage("../media/UIResource/Game/armor_1.png")
    armor1.SetName( "armor1" )
    armor1.SetVisible( False )
    # 护甲槽满
    armor2 = uiManager.AddUIImage( root, 92, 394, 0, 0, vector2df( cenX - 242, cenY ) )
    armor2.LoadImage("../media/UIResource/Game/armor_2.png")
    armor2.SetName( "armor2" )
    armor2.SetVisible( False )
    # 护甲显示文字
    armorText = uiManager.AddUIStaticText( root, 100, 20, u"护甲:", SColor(255,255,255,255) )
    armorText.SetName( "armorText" )
    armorText.SetPosition( vector2df( cenX - 130, cenY + 210 ) )
    armorText.SetVisible( False )

    # 雷达
    #radarBox = uiManager.AddUIImage( root, 0, 0, 0, 0, vector2df( cenX - 430, cenY + 260 ) )
    radarBox = uiManager.AddUIImage( root, 0, 0, 0, 0, vector2df( cenX, cenY + 260 ) )
    radarBox.SetScale( vector2df( 1, 0.25 ) )
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

