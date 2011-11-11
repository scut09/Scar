# demo版的地图
from Engine import *
from PythonSceneMgr import *
from Shader import * 

def LoadMap():
    smgr = GetMySceneManager()

    shader = ShaderManager()

    # 天空盒
    skybox = smgr.addSkyBoxSceneNode(
        	smgr.getTexture( u"../media/Space/c07_up.jpg" ),
		smgr.getTexture( u"../media/Space/c07_dn.jpg" ),
		smgr.getTexture( u"../media/Space/c07_lt.jpg" ),
		smgr.getTexture( u"../media/Space/c07_rt.jpg" ),
		smgr.getTexture( u"../media/Space/c07_ft.jpg" ),
		smgr.getTexture( u"../media/Space/c07_bk.jpg" ) )

    skybox.setScale( vector3df( 0.1, 0.1, 0.1 ) )

    skybox.setMaterialTexture( 1, smgr.getTexture(u"../media/Space/stars.png") )

    shader.ApplyShaderGeneralCallback(
        skybox,
        "Shader/universeV.txt",
        "Shader/universeF.txt" )

    # 创建飞船
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
