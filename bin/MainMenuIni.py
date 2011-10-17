from UILoader import *
from MenuUIObjects import *

def GetRoot():
    timer = Timer()

    btn = MainMenuBtn( "多人" )

    btn.SetPosition( vector2df( 200, 200 ) )

    #btn.SetVisible( False )

    #btn.GetChildren()[ 1 ].SetVisible( False )

    return btn
