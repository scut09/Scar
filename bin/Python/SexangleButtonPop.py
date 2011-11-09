# 文件名： SexangleButtonPop
# 作者：   屠文翔
# 描述：   游戏主菜单、多人菜单及单人菜单中使用的六边形菜单按钮

from UILoader import *

# 保存这个按钮的动画
NodeAnimatorDict = dict()


# 添加按钮默认样式容器
def BtnDefault():
    uiManager = GetUIManager()
    n = uiManager.AddUIImage( None, 0, 0, 0 )
    #Save( n )
    #n.SetVisible( False )
    return n

# 添加按钮鼠标悬停样式容器
def BtnOver():
    uiManager = GetUIManager()
    n = uiManager.AddUIImage( None, 0, 0, 1 )
    #Save( n )
    #n.SetVisible( False )
    n.SetAlpha( 0 )
    return n

# 按钮里面的字
BtnTitle =  {
                "单人":"../media/UIResource/Menu/t_1.png",
                "多人":"../media/UIResource/Menu/t_2.png",
                "设定":"../media/UIResource/Menu/t_3.png",
                "退出":"../media/UIResource/Menu/t_4.png"
            }

#######################################
# 六边形菜单按钮
#######################################
duration = 400

def OnMenuButtonMouseMoveIn( node ):
    global duration

    # 删除所有动画
    DeleteNodeAnimators( node ) # 通知节点在C++中将它们的动画列表清空
  
  uiManager = GetUIManager()
    aniList = []
    
    alphaUp = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        duration,
        0,
        255 )
    aniList.append( alphaUp )
    alphaDown = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        duration,
        255,
        0 )
    aniList.append( alphaDown )
    move1 = uiManager.CreateAnimatorTranslation(
        Timer().GetRealTime(),
        duration,
        vector2d( 260, 0 ) )
    aniList.append( move1 )
    move2 = move1.Clone()    
    ##Save( move2 )
    squareAlpha = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        duration,
        0,
        255 )
    aniList.append( squareAlpha )
    squareScale = uiManager.CreateAnimatorScale(
        Timer().GetRealTime(),
        duration,
        vector2df( 1.9, 1 ) )
    aniList.append( squareScale )
    
    squareTrans = uiManager.CreateAnimatorTranslation(
        Timer().GetRealTime(),
        duration,
        vector2d( 100, 0 ) )
    aniList.append( squareTrans )

    #SaveAnimators( node, aniList )  # 保存一个节点下的所有动画，以便后期删除
    
    node.GetChildren()[1].GetChildren()[0].SetScale( vector2df( 0.1, 1 ) )
    node.GetChildren()[1].GetChildren()[0].SetPosition( vector2df( 100, 0 ) )
    node.GetChildren()[0].GetChildren()[0].SetPosition( vector2df( 66, -15 ) )
    node.GetChildren()[1].GetChildren()[1].SetPosition( vector2df( 66, -15 ) )    
    
    node.GetChildren()[0].AddAnimator( alphaDown )
    alphaDown.drop()
    node.GetChildren()[1].AddAnimator( alphaUp )
    alphaUp.drop()
    node.GetChildren()[0].GetChildren()[0].AddAnimator( move1 )
    move1.drop()
    node.GetChildren()[1].GetChildren()[1].AddAnimator( move2 )
    move2.drop()
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareAlpha )
    squareAlpha.drop()
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareScale )
    squareScale.drop()
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareTrans )
    squareTrans.drop()
    #node.GetAnimators().clear()


    
def OnMenuButtonMouseMoveOut( node ):
    global duration
    
    # 删除所有动画
    DeleteNodeAnimators( node )    
    uiManager = GetUIManager()
    aniList = []
    
    alphaUp = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        duration,
        0,
        255 )
    aniList.append( alphaUp )
    alphaDown = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        duration,
        255,
        0 )
    aniList.append( alphaDown )
    
    move1 = uiManager.CreateAnimatorTranslation(
        Timer().GetRealTime(),
        duration,
        vector2d(
            66 - Float2Int( node.GetChildren()[0].GetChildren()[0].GetPosition().X ),
            0 ) )
    aniList.append( move1 )
    # 对于所有的由C++创建出来的对象，在AddAnimator后都要调用drop()，否则会内存泄露
    move2 = move1.Clone()       
    squareAlpha = uiManager.CreateAnimatorAlphaChange(
        Timer().GetRealTime(),
        duration,
        255,
        0 )
    aniList.append( squareAlpha )
    squareScale = uiManager.CreateAnimatorScale(
        Timer().GetRealTime(),
        duration,
        vector2df( 0.1, 1 ) )
    aniList.append( squareScale )
    squareTrans = uiManager.CreateAnimatorTranslation(
        Timer().GetRealTime(),
        duration,
        vector2d(
            100 - Float2Int( node.GetChildren()[1].GetChildren()[0].GetPosition().X ),
            0 ) )
    aniList.append( squareTrans )

    #SaveAnimators( node, aniList )  # 保存一个节点下的所有动画，以便后期删除    
    
    node.GetChildren()[0].AddAnimator( alphaUp )
    alphaUp.drop()
    node.GetChildren()[1].AddAnimator( alphaDown )
    alphaDown.drop()
    node.GetChildren()[0].GetChildren()[0].AddAnimator( move1 )
    move1.drop()
    node.GetChildren()[1].GetChildren()[1].AddAnimator( move2 )
    move2.drop()
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareAlpha )
    squareAlpha.drop()
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareScale )
    squareScale.drop()
    node.GetChildren()[1].GetChildren()[0].AddAnimator( squareTrans )
    squareTrans.drop()

    


    
def OnMenuLeftButtonUp( node ):
    global ScenesDict
    ChangeGameScene( ScenesDict[ 'm' ] )
    
    
    

# 组装主菜单六边形按钮
def MainMenuBtn( titleIndex ):
    uiManager  = GetUIManager()
    btn = uiManager.AddUIButton(
        None,
        210, 210,
        0,
        1
        )
    #Save( btn )

    # btn children list
    btnChildren = []
    
    default = BtnDefault()    
    over = BtnOver()
    
    btnChildren.append( over )
    btnChildren.append( default )
    
    btn.AddChild( default )
    btn.AddChild( over )

    default1 = uiManager.AddUIImage( None, 210, 210, 0 )
    #Save( default1 )    
    default1.LoadImage( "../media/UIResource/Menu/b_1_b.png" )
    default.AddChild( default1 )
    btnChildren.append( default1 )

    default2 = uiManager.AddUIImage( None, 105, 187, -1, 0, vector2df( 66, -15 ) )
    #Save( default2 )
    default2.LoadImage( "../media/UIResource/Menu/b_2_b.png" )
    default.AddChild( default2 )
    btnChildren.append( default2 )

    defaultTitle = uiManager.AddUIImage( None, 96, 60, 1 )
    #Save( defaultTitle )
    defaultTitle.LoadImage( BtnTitle[ titleIndex ] )
    default.AddChild( defaultTitle )
    btnChildren.append( defaultTitle )
    
    over1 = uiManager.AddUIImage( None, 210, 210, 0 )
    #Save( over1 )
    over1.LoadImage( "../media/UIResource/Menu/b_1_y.png" )
    over.AddChild( over1 )
    btnChildren.append( over1 )

    over2 = uiManager.AddUIImage( None, 105, 187, -1, 0, vector2df( 66, -15 ) )
    #Save( over2 )
    over2.LoadImage( "../media/UIResource/Menu/b_2_y.png" )
    over.AddChild( over2 )
    btnChildren.append( over2 )

    over3 = uiManager.AddUIImage( None, 291, 83, -2, 0, vector2df( 200, 20 ) )
    #Save( over3 )
    over3.LoadImage( "../media/UIResource/Menu/b_3.png" )
    over3.SetAlpha( 0 )
    over3.SetScale( vector2df( 0.1, 1 ) )
    over3.SetPosition( vector2df( 100, 0 ) )
    over.AddChild( over3 )
    btnChildren.append( over3 )

    overTitle = uiManager.AddUIImage( None, 96, 60, 1 )
    #Save( overTitle )
    overTitle.LoadImage( BtnTitle[ titleIndex ] )
    over.AddChild( overTitle )
    btnChildren.append( overTitle )

    btn.AddFunc( "OnMouseMoveIn", "OnMenuButtonMouseMoveIn", "SexangleButtonPop" )
    btn.AddFunc( "OnMouseMoveOut", "OnMenuButtonMouseMoveOut", "SexangleButtonPop" )
    btn.AddFunc( "OnMouseLeftButtonUp", "OnMenuLeftButtonUp", "SexangleButtonPop" )

    # 保存一个节点的所有孩子，以便于删除一个节点和它的所有孩子的动画
    #SaveNodeChilren( btn, btnChildren )
    
    return btn

#######################################
# 六边形菜单按钮
#######################################
