from UILoader import *

def GetRoot():
    timer = Timer()

    btn = UIImage(
        None,
        210, 210 )

    btn.LoadImage( "../media/UIResource/Menu/b_1_y.png" )

    Save( btn )

    return btn
