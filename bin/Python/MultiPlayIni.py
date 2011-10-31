from UILoader import *
import ScenesCreator

cenX = ScreenWidth / 2.0
cenY = ScreenHeight / 2.0

def GetRoot():
    global cenX, cenY
    # 场景根节点
    root = UIImage( None, 0, 0 )
    Save( root )

    # 活动范围圈
    ring1 = UIImage( root, 586, 586, 0, 1, vector2df( cenX, cenY ) )
    ring1.LoadImage("../media/UIResource/Game/cr_1.png")
    Save( ring1 )

    # 水平圈
    ring2 = UIImage( root, 635, 438, 0, 1, vector2df( cenX, cenY ) )
    ring2.LoadImage("../media/UIResource/Game/cr_2.png")
    ring2.SetName( "gradienter" )
    ring2.SetAntiAliasing()
    Save( ring2 )

    # 中心准心
    post1 = UIImage( root, 74, 74, 0, 1, vector2df( cenX, cenY ) )
    post1.LoadImage("../media/UIResource/Game/post_1.png")
    post1.SetAntiAliasing()
    rotAni = RotateUIAnimator( 0, 2000, 360, True )
    Save( rotAni )
    post1.AddAnimator( rotAni )
    Save( post1 )

    # 鼠标准心
    post2 = UIImage( root, 46, 46, 0, 1, vector2df( cenX, cenY ) )
    post2.LoadImage("../media/UIResource/Game/post_2.png")
    post2.SetAntiAliasing()
    post2.SetName( "cursor" )
    rotAni2 = RotateUIAnimator( 0, 2000, -360, True )
    Save( rotAni2 )
    post2.AddAnimator( rotAni2 )
    Save( post2 )

    # 速度槽满
    speedBar1 = UIImage( root, 98, 389, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    speedBar1.LoadImage("../media/UIResource/Game/speed_1.png")
    speedBar1.SetName( "speed1" )
    Save( speedBar1 )
    # 速度槽空
    speedBar2 = UIImage( root, 98, 389, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    speedBar2.LoadImage("../media/UIResource/Game/speed_2.png")
    speedBar2.SetName( "speed2" )
    Save( speedBar2 )
    # 速度显示文字
    '''speedText = UIStaticText( root, 100, 20, "我了个大区", SColor(255,255,255) )
    speedText.SetName( "speedText" )
    Save( speedText )'''

    # 能量槽满
    energy1 = UIImage( root, 94, 363, 0, 0, vector2df( cenX + 214, cenY - 10 ) )
    energy1.LoadImage("../media/UIResource/Game/energy_1.png")
    energy1.SetName( "energy1" )
    Save( energy1 )
    # 能量槽空
    '''energy2 = UIImage( root, 94, 363, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    energy2.LoadImage("../media/UIResource/Game/energy_2.png")
    energy2.SetName( "energy2" )
    Save( energy2 )'''

    # 护盾槽满
    shield1 = UIImage( root, 100, 389, 0, 0, vector2df( cenX - 232, cenY + 10 ) )
    shield1.LoadImage("../media/UIResource/Game/shield_1.png")
    shield1.SetName( "shield1" )
    Save( shield1 )
    # 护盾槽空
    shield2 = UIImage( root, 100, 389, 0, 0, vector2df( cenX - 232, cenY + 10 ) )
    shield2.LoadImage("../media/UIResource/Game/shield_2.png")
    shield2.SetName( "shield2" )
    Save( shield2 )

    # 护甲槽满
    armor1 = UIImage( root, 93, 360, 0, 0, vector2df( cenX - 214, cenY + 10 ) )
    armor1.LoadImage("../media/UIResource/Game/armor_1.png")
    armor1.SetName( "armor1" )
    Save( armor1 )
    # 护甲槽满
    armor2 = UIImage( root, 93, 360, 0, 0, vector2df( cenX - 214, cenY + 10 ) )
    armor2.LoadImage("../media/UIResource/Game/armor_2.png")
    armor2.SetName( "armor2" )
    Save( armor2 )


    #以下的这些不会在一开始就出现在屏幕上，供复制用

    #目标圈——敌军
    target1 = UIImage( root, 60, 60, 0, 1, vector2df( 100, 100 ) )
    target1.LoadImage( "../media/UIResource/Game/target_1.png" )
    target1.SetName( "target1" )
    target1.SetAntiAliasing()
    Save( target1 )
    #目标圈——友军
    '''target2 = UIImage( root, 60, 60, 0, 1, vector2df( 100, 100 ) )
    target2.LoadImage( "../media/UIResource/Game/target_2.png" )
    target2.SetName( "target2" )
    Save( target2 )'''

    #锁定框——已锁定
    lock1 = UIImage( root, 100, 100, 0, 1, vector2df( cenX, cenY ) )
    lock1.LoadImage( "../media/UIResource/Game/lock_1.png" )
    lock1.SetName( "lock1" )
    lock1.SetAntiAliasing()
    rotAni3 = RotateUIAnimator( 0, 1000, -360, True )
    Save( rotAni3 )
    lock1.AddAnimator( rotAni3 )
    Save( lock1 )

    #敌人指示器
    indicator1 = UIImage( root, 0, 0, 0, 1, vector2df( cenX, cenY ) )
    indicator1.SetName( "indicator1" )
    Save( indicator1 )
    tip = UIImage( indicator1, 31, 28, 0, 0, vector2df( 0, -302 ) )
    tip.LoadImage( "../media/UIResource/Game/indicator_1.png" )
    Save( tip )
    
    return root

