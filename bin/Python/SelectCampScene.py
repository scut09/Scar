﻿#####################################################
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
    # 恒星光晕1
    flare1 = smgr.addBillboardSceneNode( None, dimension2df( 256, 256 ) )
    flare1.setMaterialTexture( 0, smgr.getTexture( "../media/Space/sun.tga" ) )
    flare1.setMaterialFlag( EMF_ZBUFFER, False )
    #flare1.setMaterialFlag( EMF_LIGHTING, False )
    #flare1.setMaterialType( EMT_TRANSPARENT_ADD_COLOR )
    relStay = smgr.createRelateCameraStayAnimator( 0, 1000, camera, vector3df( 0,0,250 ) )
    flare1.addAnimator( relStay )
    relStay.drop()
    shader.ApplyShaderGeneralCallback( flare1, "", "Shader/flare1.frag", EMT_TRANSPARENT_ADD_COLOR )
    # 恒星光晕2
    flare2 = smgr.addBillboardSceneNode( flare1, dimension2df( 256, 256 ) )
    flare2.setMaterialTexture( 0, smgr.getTexture( "../media/Space/flare2.png" ) )
    flare2.setMaterialFlag( EMF_ZBUFFER, False )
    shader.ApplyShaderGeneralCallback( flare2, "Shader/flare2.vert", "Shader/flare2.frag", EMT_TRANSPARENT_ADD_COLOR )
    # 恒星光晕3
    flare3 = smgr.addBillboardSceneNode( flare1, dimension2df( 256, 256 ) )
    flare3.setMaterialTexture( 0, smgr.getTexture( "../media/Space/rainbow.tga" ) )
    flare3.setMaterialFlag( EMF_ZBUFFER, False )
    shader.ApplyShaderGeneralCallback( flare3, "Shader/flare3.vert", "Shader/flare3.frag", EMT_TRANSPARENT_ADD_COLOR )

    # 阵营1
    # 阵营1行星
    Planet1 = smgr.addSphereSceneNode( 1e5, 64 )
    Planet1.setName( "planet1" )
    #Planet1.setPosition( vector3df(1e5,0.5e5,3e5) )
    Planet1.setPosition( vector3df(-5e5,-1e5,8e5) )
    #Planet1.setPosition( vector3df(3e5,0.5e5,-1e5) )
    #camera.setTarget( vector3df(1,0,0) )
    Planet1.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet5.jpg" ) )
    Planet1.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Planet1, "Shader/PlanetGroundV.vert", "Shader/PlanetGroundF.frag" )
    '''relStay = smgr.createRelateCameraStayAnimator( 0, 1000, camera, vector3df( -5e5,-1e5,8e5) )
    Planet1.addAnimator( relStay )
    relStay.drop()'''
    # 阵营1行星星环
    ring = smgr.addMeshSceneNode( smgr.getMesh ("../media/Planets/ring.obj"), Planet1 )
    ring.setScale( vector3df( 1.5e5 ) )
    ring.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/saturnringcolor.jpg" ) )
    ring.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/saturnringcolor.jpg" ) )
    ring.setMaterialFlag( EMF_BACK_FACE_CULLING, False )
    shader.ApplyShaderGeneralCallback( ring, "Shader/PlanetRing.vert", "Shader/PlanetRing.frag", EMT_TRANSPARENT_ALPHA_CHANNEL )
    # 阵营1行星大气
    atmos = smgr.addSphereSceneNode( 1.05e5, 64, Planet1 )
    atmos.setMaterialFlag( EMF_BACK_FACE_CULLING, False )
    atmos.setMaterialFlag( EMF_FRONT_FACE_CULLING, True )
    shader.ApplyShaderGeneralCallback( atmos, "Shader/PlanetAtmosV.vert", "Shader/PlanetAtmosF.frag", EMT_TRANSPARENT_ADD_COLOR )
    # 阵营1卫星
    Satellite1 = smgr.addSphereSceneNode( 0.25e5, 64, Planet1 )
    Satellite1.setName( "Satellite1" )
    Satellite1.setPosition( vector3df( -2e5, -0.9e5, 2e5 ) )
    #Satellite1.setPosition( vector3df(-1e5,-4e4,1e5) )
    Satellite1.setVisible( False )
    #Satellite1.setScale( vector3df( 0.01 ) )
    Satellite1.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet1.jpg" ) )
    shader.ApplyShaderGeneralCallback( Satellite1, "Shader/Satellite.vert", "Shader/Satellite.frag" )
    # 阵营1基地
    station1 = smgr.addMeshSceneNode( smgr.getMesh ("../model/station/cs1.obj"), Planet1 )
    station1.setName( "station1" )
    station1.setVisible( False )
    #station1.setPosition( vector3df( -.5e5, -0.3e5, 2e5 ) )
    station1.setPosition( vector3df( -1e5, -0.8e5, 1.5e5 ) )
    station1.setScale(vector3df(0.01))
    shader.ApplyShaderGeneralCallback( station1, "Shader/gs_1V.vert", "Shader/gs_1F.frag" )
    
    # 阵营2
    # 阵营2行星
    Planet2 = smgr.addSphereSceneNode( 1e5, 64 )
    Planet2.setName( "planet2" )
    Planet2.setVisible( False )
    #Planet2.setPosition( vector3df(5e5,0,8e5) )
    Planet2.setScale( vector3df( 0.4, 0.4, 0.4 ) )
    Planet2.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet6.jpg" ) )
    Planet2.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Planet2, "Shader/PlanetGroundV.vert", "Shader/PlanetGroundF.frag" )
    relStay = smgr.createRelateCameraStayAnimator( 0, 1000, camera, vector3df( 5e5,0,8e5), True )
    Planet2.addAnimator( relStay )
    relStay.drop()
    # 阵营2行星大气
    atmos = smgr.addSphereSceneNode( 1.05e5, 64, Planet2 )
    atmos.setMaterialFlag( EMF_BACK_FACE_CULLING, False )
    atmos.setMaterialFlag( EMF_FRONT_FACE_CULLING, True )
    shader.ApplyShaderGeneralCallback( atmos, "Shader/PlanetAtmosV.vert", "Shader/PlanetAtmosF.frag", EMT_TRANSPARENT_ADD_COLOR )
    # 阵营2卫星
    '''Satellite2 = smgr.addSphereSceneNode( 1e5, 64 )
    Satellite2.setName( "Satellite2" )
    Satellite2.setVisible( False )
    #Satellite2.setPosition( Planet2.getPosition() + vector3df(200, -100, -10.0) )
    Satellite2.setMaterialTexture( 0, smgr.getTexture( "../media/neptune.jpg" ) )
    Satellite2.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/a.tga" ) )
    shader.ApplyShaderGeneralCallback( Satellite2, "Shader/PlanetGroundV.vert", "Shader/PlanetGroundF.frag" )'''
    # 阵营2基地
    station2 = smgr.addMeshSceneNode( smgr.getMesh ("../model/station/gs1.obj") )
    station2.setName( "station2" )
    station2.setVisible( False )
    #station2.setPosition(Planet2.getPosition() + vector3df(-150, -200, 50) )
    #station2.setScale(vector3df(0.001, 0.001, 0.001))
    shader.ApplyShaderGeneralCallback( station2, "Shader/gs_1V.vert", "Shader/gs_1F.frag" )

    #smgr.addRunWaySceneNode( vector3df(0,0,0), 200, 300, vector3df( 255,255,0 ), vector3df( 0, 255, 0 ) )
    #smgr.addSphereSceneNode( 10, 64 )

    
