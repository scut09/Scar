from UILoader import *
import SexangleButtonPop

def GetRoot():
    timer = Timer()

    root = UIImage( None, 0, 0 )
    Save( root )

    btn1 = SexangleButtonPop.MainMenuBtn( "单人" )
    btn1.SetPosition( vector2df( 100, 100 ) )
    
    btn2 = SexangleButtonPop.MainMenuBtn( "多人" )
    btn2.SetPosition( vector2df( 200, 200 ) )

    btn3 = SexangleButtonPop.MainMenuBtn( "设定" )
    btn3.SetPosition( vector2df( 300, 300 ) )

    root.AddChild( btn1 )
    root.AddChild( btn2 )
    root.AddChild( btn3 )

    

    #btn.SetVisible( False )

    #btn.GetChildren()[ 1 ].SetVisible( False )

    return root
