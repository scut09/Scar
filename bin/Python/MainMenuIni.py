from UILoader import *
import SexangleButton

def GetRoot():
    # 设置第一个按钮的位置，其他按钮相对这个按钮设置位置
    posX = 200
    posY = 100

    # 场景根节点
    root = UIImage( None, 0, 0 )
    Save( root )

    # 组装四个按钮
    btn1 = SexangleButton.MainMenuBtnPop( "单人" )
    btn1.SetPosition( vector2df( posX, posY ) )
    btn2 = SexangleButton.MainMenuBtnPop( "多人" )
    btn2.SetPosition( vector2df( posX + 54, posY + 200 ) )
    btn3 = SexangleButton.MainMenuBtnPop( "设定" )
    btn3.SetPosition( vector2df( posX + 108, posY + 400 ) )
    btn4 = SexangleButton.MainMenuBtn( "退出" )
    btn4.SetPosition( vector2df( posX - 90, posY + 340 ) )
    root.AddChild( btn1 )
    root.AddChild( btn2 )
    root.AddChild( btn3 )
    root.AddChild( btn4 )
    btn1.SetRotation( -90 )
    btn1.SetAlpha( 0 )
    btn1.SetScale( vector2df( 0.1, 0.1 ) )

    # 旋转、缩放、Alpha改变动画
    dua = 400 #动画持续时间
    AniList = [] #用以保存动画
    rot1 = RotateUIAnimator(
        Timer().GetRealTime(),
        dua,
        90 )
    sca1 = ScaleUIAnimator(
        Timer().GetRealTime(),
        dua,
        vector2df( 1.9, 1.9 ) )
    alp1 = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        dua,
        0,
        255 )
    

    btn1.AddAnimator( rot1 )
    btn1.AddAnimator( alp1 )
    btn1.AddAnimator( sca1 )
    AniList.append( rot1 )
    #Save( rot1 )
    AniList.append( alp1 )
    #Save( alp1 )
    AniList.append( sca1 )

    Save( AniList )

    #btn.SetVisible( False )

    #btn.GetChildren()[ 1 ].SetVisible( False )

    return root
