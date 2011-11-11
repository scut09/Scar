from Engine import *
from PythonSceneMgr import *

def LoadMap():
    smgr = GetMySceneManager()
    
    ship = smgr.addFrigateSceneNode( u"../model/ship/cf1.obj" )
        
    ani = smgr.createFlyStraightAnimator(
        vector3df( 0, 0, 0 ),
        vector3df( 0, 0, 1000 ),
        5000, True, True )

    ship.addAnimator( ani )
    ani.drop()

    ship = smgr.addFrigateSceneNode( u"../model/ship/cf1.obj" )
        
    ani = smgr.createFlyStraightAnimator(
        vector3df( 100, 0, 0 ),
        vector3df( -100, 0, 1000 ),
        5000, True, True )

    ship.addAnimator( ani )
    ani.drop()
