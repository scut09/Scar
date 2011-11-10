from Engine import *
from PythonSceneMgr import *

def LoadMap():
    smgr = GetMySceneManager()
    
    ship = smgr.addFrigateSceneNode( u"../model/ship/cf1.obj" )

    ship.setPosition( vector3df( 100, 100, 100 ) )

    
