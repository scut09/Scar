from Engine import *

# 为引擎添加模型
def Load():
    # 创建和引擎通讯的模型代理
    man = ModelMan()

    # 下面以 "MeshID" "Mesh文件名" "Mesh的贴图名"为引擎添加Mesh
    man.AddMesh( "1", "../module/1234.obj", "" )
    man.AddMesh( "2", "../media/sydney.md2", "../media/sydney.bmp" )
    

    

