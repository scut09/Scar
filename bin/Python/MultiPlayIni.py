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
    Save( post1 )

    # 鼠标准心
    post2 = UIImage( root, 56, 56, 0, 1, vector2df( cenX, cenY ) )
    post2.LoadImage("../media/UIResource/Game/post_2.png")
    Save( post2 )

    return root

