#####################################################
#
# 描述： 战场地图1
# 维护者： 屠文翔
#
#####################################################

from Engine import *
from PythonSceneMgr import *
from Shader import *

def LoadMap():
    # 一些需要用到的变量
    smgr = GetMySceneManager()
    shader = ShaderManager()
    camera = smgr.getActiveCamera()

    # 战场根节点
    battleField = smgr.addSphereSceneNode( )
    battleField.setName( "battleField" )
    battleField.setVisible( False )
    print "-!"*40

    # 星球背景地球
    earth = smgr.addSphereSceneNode( 1e5, 64, battleField )
    earth.setName( "bfEarth" )
    earth.setPosition( vector3df(3e5,0,0.5e5) )
    earth.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/l.tga" ) )
    earth.setMaterialTexture( 1, smgr.getTexture( "../media/Planets/seraphius.jpg" ) )
    earth.setMaterialTexture( 2, smgr.getTexture( "../media/Planets/f.tga" ) )
    earth.setMaterialTexture( 3, smgr.getTexture( "../media/Planets/citylights2.png" ) )
    shader.ApplyShaderGeneralCallback( earth, "Shader/Earth.vert", "Shader/Earth.frag" )
    ani = smgr.createRotationAnimator( vector3df( 0, 0.005, 0 ) )
    earth.addAnimator( ani )
    ani.drop()
    earth.setVisible( False )
    
    # 大气圈
    atmos = smgr.addSphereSceneNode( 1.05e5, 64, earth )
    atmos.setMaterialFlag( EMF_BACK_FACE_CULLING, False )
    atmos.setMaterialFlag( EMF_FRONT_FACE_CULLING, True )
    shader.ApplyShaderGeneralCallback( atmos, "Shader/PlanetAtmosV.vert", "Shader/PlanetAtmosF.frag", EMT_TRANSPARENT_ADD_COLOR )

    # 星球背景月球
    moon = smgr.addSphereSceneNode( 1e4, 64, battleField )
    moon.setName( "bfMoon" )
    moon.setPosition( earth.getPosition() + vector3df(-2.3e5,0,-0.7e5) )
    moon.setMaterialTexture( 0, smgr.getTexture( "../media/Planets/planet1.jpg" ) )
    shader.ApplyShaderGeneralCallback( moon, "Shader/Satellite.vert", "Shader/Satellite.frag" )
    ani = smgr.createRotationAnimator( vector3df( 0, 0.005, 0 ) )
    moon.addAnimator( ani )
    ani.drop()
    moon.setVisible( False )

    # 星门
    gate = smgr.addMeshSceneNode( smgr.getMesh ("../model/jumpgate/jumpgate.obj"), battleField )
    gate.setName( "bfGate" )
    #gate.setVisible( False )
    #gate.setPosition(vector3df( -1e5, -0.8e5, 1.5e5 ) )
    #gate.setRotation( vector3df( 0, 90, 0 ) );
    #gate.setScale(vector3df(0.01))
    shader.ApplyShaderGeneralCallback( gate, "Shader/cs_1V.vert", "Shader/cs_1F.frag" )
    gate.setVisible( False )

    
