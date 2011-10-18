from Engine import *

def btn1_OnMouseMove( node ):
   # Save( node )
    print "a",
    node.SetVisible( False )
    print node.GetVisible()
    node.SetPosition( vector2df( 10, 10 ) )
    node.SetVisible( False )
