from UILoader import *
from MenuUIObjects import *

def GetRoot():
    timer = Timer()

    btn = MainMenuBtn( "多人" )

    btn.SetPosition( vector2df( 300, 300 ) )

    #btn.SetVisible( False )

    #btn.GetChildren()[ 1 ].SetVisible( False )

    return btn
