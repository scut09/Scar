#####################################################
#
# 描述： 
# 维护者：
#
#####################################################
#encoding:utf-8
from Engine import *
from PythonSceneMgr import *
from Shader import * 

def LoadMap():
    # 一些需要用到的变量
    smgr = GetMySceneManager()
    shader = ShaderManager()
    camera = smgr.getActiveCamera()
    
    # 全局的场景，不仅仅只有该状态用到
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
    shader.ApplyShaderGeneralCallback( skybox, "Shader/universeV.txt", "Shader/universeF.txt" )
    
    # 恒星
    Sun = smgr.addSphereSceneNode( )
    Sun.setName( "Sun" )
    Sun.setPosition( vector3df( 0, 0, 18e5 ) )
    
    # 阵营1
    # 阵营1行星
    Planet1 = smgr.addSphereSceneNode( 1e5, 64 )
    Planet1.setName( "planet1" )
    #Planet1.setPosition( vector3df(-5e5,0,8e5) )
    Planet1.setPosition( vector3df(1e5,0.5e5,3e5) )
    Planet1.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/neptune.jpg" ) )
    Planet1.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/Earth.jpg" ) )
    Planet1.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Planet1, "Shader/Earth.vert", "Shader/Earth.frag" )




    
