﻿# 文件名： MenuUIObjects
# 作者：   屠文翔
# 描述：   组装UI元件资源

from UILoader import *


# 添加按钮默认样式容器
def BtnDefault():
    n = UIImage( None, 0, 0, 0 )
    Save( n )
    #n.SetVisible( False )
    return n

# 添加按钮鼠标悬停样式容器
def BtnOver():
    n = UIImage( None, 0, 0, 1 )
    Save( n )
    #n.SetVisible( False )
    n.SetAlpha( 0 )
    return n

# 按钮里面的字
BtnTitle =  {
                "单人":"../media/UIResource/Menu/t_1.png",
                "多人":"../media/UIResource/Menu/t_2.png",
                "选项":"../media/UIResource/Menu/t_3.png",
                "退出":"../media/UIResource/Menu/t_4.png"
            }

"""def Test1( node ):
    ani = RotateUIAnimator(
        Timer().GetRealTime(),
        3000,
        360,
        True
        )
    Save( ani )
    node.AddAnimator( ani )"""

def OnMenuButtonMouseMoveIn( node ):
    alphaUp = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        400,
        0,
        255 )
    Save( alphaUp )
    alphaDown = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        400,
        255,
        0 )
    Save( alphaDown )
    node.GetChildren()[0].AddAnimator( alphaDown )
    node.GetChildren()[1].AddAnimator( alphaUp )

    
def OnMenuButtonMouseMoveOut( node ):
    pass
    

# 组装主菜单六边形按钮
def MainMenuBtn( titleIndex ):
    btn = UIButton(
        None,
        210, 210,
        )
    Save( btn )
    
    default = BtnDefault()
    over = BtnOver()
    
    btn.AddChild( default )
    btn.AddChild( over )

    default1 = UIImage( None, 210, 210, 0 )
    Save( default1 )
    default1.LoadImage( "../media/UIResource/Menu/b_1_b.png" )
    default.AddChild( default1 )

    default2 = UIImage( None, 105, 187, -1, 0, vector2df( 66, -15 ) )
    Save( default2 )
    default2.LoadImage( "../media/UIResource/Menu/b_2_b.png" )
    default.AddChild( default2 )

    defaultTitle = UIImage( None, 96, 60, 1 )
    Save( defaultTitle )
    defaultTitle.LoadImage( BtnTitle[ titleIndex ] )
    default.AddChild( defaultTitle )

    over1 = UIImage( None, 210, 210, 0 )
    Save( over1 )
    over1.LoadImage( "../media/UIResource/Menu/b_1_y.png" )
    over.AddChild( over1 )

    over2 = UIImage( None, 105, 187, -1, 0, vector2df( 66, -15 ) )
    Save( over2 )
    over2.LoadImage( "../media/UIResource/Menu/b_2_y.png" )
    over.AddChild( over2 )

    over3 = UIImage( None, 291, 83 )
    Save( over3 )
    over3.LoadImage( "../media/UIResource/Menu/b_3.png" )
    over3.SetVisible( False )
    over.AddChild( over3 )

    overTitle = UIImage( None, 96, 60, 1 )
    Save( overTitle )
    overTitle.LoadImage( BtnTitle[ titleIndex ] )
    over.AddChild( overTitle )

    btn.AddFunc( "OnMouseMoveIn", "OnMenuButtonMouseMoveIn", "MenuUIObjects" )

    return btn