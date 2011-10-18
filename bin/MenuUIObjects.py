# 文件名： MenuUIObjects
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

#######################################
# 六边形菜单按钮
#######################################
duration = 400

def OnMenuButtonMouseMoveIn( node ):
    global duration

    # 删除所有动画
    childrenList = GetNodeChildren( node )
    node.RemoveAnimators()
    for child in  childrenList:
        child.RemoveAnimators()
    
    SaveNodeAnimatorTime( node, Timer().GetRealTime() )   
    alphaUp = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        duration,
        0,
        255 )
    Save( alphaUp )
    alphaDown = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        duration,
        255,
        0 )
    Save( alphaDown )
    move1 = TranslateUIAnimator(
        Timer().GetRealTime(),
        duration,
        vector2d( 260, 0 ) )
    Save( move1 )
    move2 = move1.Clone()
    Save( move2 )
    squareAlpha = AlphaChangeUIAnimator(
        Timer().GetRealTime(),
        duration,
        0,
        255 )
    Save( squareAlpha )
    squareScale = ScaleUIAnimator(
        Timer().GetRealTime(),
        duration,
        vector2df( 1.9, 1 ) )
    Save( squareScale )
    node.GetChildren()[1].GetChildren()[0].SetScale( vector2df( 0.1, 1 ) )
    
    squareTrans = TranslateUIAnimator(
        Timer().GetRealTime(),
        duration,
        vector2d( 100, 0 ) )
    Save( squareTrans )
    
    node.GetChildren()[0].AddAnimator( alphaDown )
    node.GetChildren()[1].AddAnimator( alphaUp )
    node.GetChildren()[0].GetChildren()[0].AddAnimator( move1 )
    node.GetChildren()[1].GetChildren()[1].AddAnimator( move2 )
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareAlpha )
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareScale )
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareTrans )
    #node.GetAnimators().clear()



    
def OnMenuButtonMouseMoveOut( node ):
    global duration
    
    # 删除所有动画
    childrenList = GetNodeChildren( node )
    node.RemoveAnimators()
    for child in  childrenList:
        child.RemoveAnimators()
    
    addTime = 0
    #runTime = Timer().GetRealTime() - GetAnimatorTime( node )
    #addTime = duration - runTime   
    SaveNodeAnimatorTime( node, Timer().GetRealTime() )
    
    alphaUp = AlphaChangeUIAnimator(
        Timer().GetRealTime() + addTime,
        duration,
        0,
        255 )
    Save( alphaUp )
    alphaDown = AlphaChangeUIAnimator(
        Timer().GetRealTime() + addTime,
        duration,
        255,
        0 )
    Save( alphaDown )
    
    move1 = TranslateUIAnimator(
        Timer().GetRealTime() + addTime,
        duration,
        vector2d( 66 - Float2Int( node.GetChildren()[0].GetChildren()[0].GetPosition().X ), 0 ) )
    Save( move1 )
    move2 = move1.Clone()
    Save( move2 )
    squareAlpha = AlphaChangeUIAnimator(
        Timer().GetRealTime() + addTime,
        duration,
        255,
        0 )
    Save( squareAlpha )
    squareScale = ScaleUIAnimator(
        Timer().GetRealTime() + addTime,
        duration,
        vector2df( 0.1, 1 ) )
    Save( squareScale )
    squareTrans = TranslateUIAnimator(
        Timer().GetRealTime() + addTime,
        duration,
        vector2d( 66 - Float2Int( node.GetChildren()[1].GetChildren()[0].GetPosition().X ), 0 ) )
    Save( squareTrans )
    
    node.GetChildren()[0].AddAnimator( alphaUp )
    node.GetChildren()[1].AddAnimator( alphaDown )
    node.GetChildren()[0].GetChildren()[0].AddAnimator( move1 )
    node.GetChildren()[1].GetChildren()[1].AddAnimator( move2 )
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareAlpha )
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareScale )
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareTrans )

def OnMenuLeftButtonUp( node ):
    m = MultiplayerScene()
    SaveScenes( "fuck", m )
    DeleteTree()
    ChangeGameScene( m )
    
    
    

# 组装主菜单六边形按钮
def MainMenuBtn( titleIndex ):
    btn = UIButton(
        None,
        210, 210,
        0,
        1
        )
    Save( btn )

    # btn children list
    btnChildren = []
    
    default = BtnDefault()    
    over = BtnOver()
    
    btnChildren.append( over )
    btnChildren.append( default )
    
    btn.AddChild( default )
    btn.AddChild( over )

    default1 = UIImage( None, 210, 210, 0 )
    Save( default1 )    
    default1.LoadImage( "../media/UIResource/Menu/b_1_b.png" )
    default.AddChild( default1 )
    btnChildren.append( default1 )

    default2 = UIImage( None, 105, 187, -1, 0, vector2df( 66, -15 ) )
    Save( default2 )
    default2.LoadImage( "../media/UIResource/Menu/b_2_b.png" )
    default.AddChild( default2 )
    btnChildren.append( default2 )

    defaultTitle = UIImage( None, 96, 60, 1 )
    Save( defaultTitle )
    defaultTitle.LoadImage( BtnTitle[ titleIndex ] )
    default.AddChild( defaultTitle )
    btnChildren.append( defaultTitle )
    
    over1 = UIImage( None, 210, 210, 0 )
    Save( over1 )
    over1.LoadImage( "../media/UIResource/Menu/b_1_y.png" )
    over.AddChild( over1 )
    btnChildren.append( over1 )

    over2 = UIImage( None, 105, 187, -1, 0, vector2df( 66, -15 ) )
    Save( over2 )
    over2.LoadImage( "../media/UIResource/Menu/b_2_y.png" )
    over.AddChild( over2 )
    btnChildren.append( over2 )

    over3 = UIImage( None, 291, 83, -2, 0, vector2df( 200, 20 ) )
    Save( over3 )
    over3.LoadImage( "../media/UIResource/Menu/b_3.png" )
    over3.SetAlpha( 0 )
    over3.SetScale( vector2df( 0.1, 1 ) )
    over3.SetPosition( vector2df( 100, 0 ) )
    over.AddChild( over3 )
    btnChildren.append( over3 )

    overTitle = UIImage( None, 96, 60, 1 )
    Save( overTitle )
    overTitle.LoadImage( BtnTitle[ titleIndex ] )
    over.AddChild( overTitle )
    btnChildren.append( overTitle )

    btn.AddFunc( "OnMouseMoveIn", "OnMenuButtonMouseMoveIn", "MenuUIObjects" )
    btn.AddFunc( "OnMouseMoveOut", "OnMenuButtonMouseMoveOut", "MenuUIObjects" )
    btn.AddFunc( "OnMouseLeftButtonUp", "OnMenuLeftButtonUp", "MenuUIObjects" )

    SaveNodeChilren( btn, btnChildren )
    
    return btn

#######################################
# 六边形菜单按钮
#######################################
