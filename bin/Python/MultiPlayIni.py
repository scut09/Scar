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
    post1 = UIImage( root, 86, 86, 0, 1, vector2df( cenX, cenY ) )
    post1.LoadImage("../media/UIResource/Game/post_1.png")
    post1.SetAntiAliasing()
    rotAni = RotateUIAnimator( 0, 2000, 360, True )
    Save( rotAni )
    post1.AddAnimator( rotAni )
    Save( post1 )

    # 鼠标准心
    post2 = UIImage( root, 56, 56, 0, 1, vector2df( cenX, cenY ) )
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
    return root

