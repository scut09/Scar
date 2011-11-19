#####################################################
#
# 描述： SelectCamp状态初始化
# 维护者： 杨旭瑜
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


    # 阵营1
    # 阵营1行星
    Planet1 = smgr.addSphereSceneNode( 50, 64 )
    Planet1.setName( "planet1" )
    Planet1.setPosition( vector3df(-700.0, 350.0, -10.0) )
    Planet1.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet5.jpg" ) )
    Planet1.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/night0.jpg" ) )
    Planet1.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Planet1, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" )
    # 阵营1卫星
    Satellite1 = smgr.addSphereSceneNode( 20, 64 )
    Satellite1.setName( "Satellite1" )
    Satellite1.setPosition( Planet1.getPosition() + vector3df(200, -100, -10.0) )
    Satellite1.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet2.jpg" ) )
    Satellite1.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/night0.jpg" ) )
    Satellite1.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Satellite1, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" )
    # 阵营1基地
    station1 = smgr.addMeshSceneNode( smgr.getMesh ("../model/station/cs1.obj") )
    station1.setName( "station1" )
    station1.setPosition(Planet1.getPosition() + vector3df(150, -200, 50))
    station1.setScale(vector3df(0.001, 0.001, 0.001))
    shader.ApplyShaderGeneralCallback( station1, "Shader/gs_1V.vert", "Shader/gs_1F.frag" )
    
    # 阵营2
    # 阵营2行星
    Planet2 = smgr.addSphereSceneNode( 50, 64 )
    Planet2.setName( "planet2" )
    Planet2.setPosition( vector3df(700.0, -350.0, -10.0) ) 
    Planet2.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet6.jpg" ) )
    Planet2.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/night0.jpg" ) )
    Planet2.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Planet2, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" )
    # 阵营2卫星
    Satellite2 = smgr.addSphereSceneNode( 20, 64 )
    Satellite2.setName( "Satellite2" )
    Satellite2.setPosition( Planet2.getPosition() + vector3df(200, -100, -10.0) )
    Satellite2.setMaterialTexture( 0, smgr.getTexture( "../media/neptune.jpg" ) )
    Satellite2.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/night0.jpg" ) )
    Satellite2.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Satellite2, "Shader/PlanetGroundV.txt", "Shader/PlanetGroundF.txt" )
    # 阵营2基地
    station2 = smgr.addMeshSceneNode( smgr.getMesh ("../model/station/gs1.obj") )
    station2.setName( "station2" )
    station2.setPosition(Planet2.getPosition() + vector3df(-150, -200, 50) )
    station2.setScale(vector3df(0.001, 0.001, 0.001))
    shader.ApplyShaderGeneralCallback( station2, "Shader/gs_1V.vert", "Shader/gs_1F.frag" )

    #smgr.addRunWaySceneNode( vector3df(0,0,0), 200, 300, vector3df( 255,255,0 ), vector3df( 0, 255, 0 ) )
    smgr.addSphereSceneNode( 10, 64 )

    
