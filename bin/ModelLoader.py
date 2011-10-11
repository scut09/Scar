from Engine import *
import random

def Color( alpha, red, green, blue ):
    color = SColor()
    color.alpha = alpha
    color.red = red
    color.green = green
    color.blue = blue
    return color

# 为引擎添加模型
def MultiplayerLoad():
    # 创建和引擎通讯的模型代理
    man = ModelMan()

    # 下面以 "MeshID" "Mesh文件名" "Mesh的贴图名"为引擎添加Mesh
    man.AddMesh( "1", "../module/1234.obj", "" )
    man.AddMesh( "2", "../media/sydney.md2", "../media/sydney.bmp" )
    man.AddMesh( "bottle", "../module/mayabottle.obj", "" )

    # 设置光源
    light = SLight()
    light.AmbientColor = Color( 0, 10, 255, 255 )
    light.DiffuseColor = Color( 0, 128, 128, 128 )
    light.SpecularColor = Color( 0, 128, 128, 128 )
    man.AddLight( light, 1000.0, 200.0, 100.0 )

    for i in range( 2 ):
        node = man.AddSceneNodeByMeshID( "1", False )
        node.SetPosition( random.randint(-1000, 1000),
                          random.randint(-1000, 1000),
                          random.randint(-1000, 1000) )
    

