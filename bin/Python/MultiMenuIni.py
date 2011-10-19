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

    return root
