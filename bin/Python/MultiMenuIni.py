from UILoader import *
import SexangleButton
import ScenesCreator

RatioX = 0.78125
RatioY = 0.625
AniList = [] #���Ա��涯��
Save( AniList )

def GetRoot():
    global RatioX
    global RatioY

    # �������ڵ�
    root = UIImage( None, 0, 0 )
    Save( root )

    return root
