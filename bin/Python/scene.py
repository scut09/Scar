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
def LoadMultiplayerModel():
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


# 提供类似C++的enum
def enum(module, str_enum, sep=None):
    """把用特定分隔符隔开的 str_enum 字符串实现为 module 的枚举值.
    @param module 宿主对象, 可以是 module, class, ...
    eg1: enum(test, "A B C") => test.A,test.B,test.C == 0,1,2
    eg2: enum(CTest, 'one=1,two,three,ten=0x0A,eleven', sep=',') =>
        CTest.one,CTest.two,CTest.ten, CTest.eleven == 1,2,10,11
    """
    idx = 0
    for name in str_enum.split(sep):
        if '=' in name:
            name, val = name.rsplit('=', 1)
            if val.isalnum():
                idx = eval(val)
        setattr(module, name.strip(), idx)
        idx += 1

class s:pass
# 场景状态
enum( s, '''
    start=0
    menu
    multiplayer
    end
    ''')
# 当前场景
cur = s.start

# GotoScene
# scene_id 当前id
# 返回下一个场景的id
def GotoScene(scene_id):
    # 这里基于状态机
    if scene_id == s.start:
        pass
    elif scene_id == s.menu:
        pass
    elif scene_id == s.multiplayer:
        LoadMultiplayerModel()
        
        cur = s.end

