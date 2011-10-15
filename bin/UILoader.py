from UI import *
from Engine import *

def GetTran():
    timer = Timer()
    ani = TranslateUIAnimator(
        timer.GetTime(),
        2000,
        vector2d( 300, 200 )
        )

    return ani
