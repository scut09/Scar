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
    rotAni2 = RotateUIAnimator( 0, 2000, -360, True )
    Save( rotAni2 )
    post2.AddAnimator( rotAni2 )
    Save( post2 )

    # 速度槽满
    speedBar1 = UIImage( root, 98, 389, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    speedBar1.LoadImage("../media/UIResource/Game/speed_1.png")
    #speedBar1.SetSourceRect( vector2df( 0, 150 ), vector2df( 98, 389 ) );
    Save( speedBar1 )
    # 速度槽空
    speedBar2 = UIImage( root, 98, 389, 0, 0, vector2df( cenX + 232, cenY - 10 ) )
    speedBar2.LoadImage("../media/UIResource/Game/speed_2.png")
    #speedBar2.SetSourceRect( vector2df( 0, 0 ), vector2df( 98, 150 ) );
    Save( speedBar2 )

    return root

