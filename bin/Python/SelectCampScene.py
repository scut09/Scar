#encoding:utf-8
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

    #创建阵营1的星球
'''	Sun = smgr->addSphereSceneNode( 100, 100 )

	if ( Sun ):
		# 设置名称
		Sun->setName( "planet1" )
		# 加载纹理
		Sun->setMaterialTexture( 0, pEngine.GetVideoDriver()->getTexture( u"../media/Planets/planet5.jpg" ) )
		Sun->setMaterialTexture( 1, pEngine.GetVideoDriver()->getTexture( u"../media/Planets/night0.jpg" ) )
		Sun->setMaterialTexture( 2, pEngine.GetVideoDriver()->getTexture( u"../media/Planets/a.tga" ) )

		# Shader
		cb = new GeneralCallBack( Sun )
		shader->ApplyShaderToSceneNode( Sun, cb, u"Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" )
		cb->drop()'''
	
    
