#################################################
#                                               #
#   该文件储存MultiPlayScene中需要用到的回调函数      #
#                                               #
#################################################

    # 按钮通用
def GeneralDefault( node ):
    node.GetChildren()[0].SetVisible( True )
    node.GetChildren()[1].SetVisible( False )
def GeneralOver( node ):
    node.GetChildren()[0].SetVisible( False )
    node.GetChildren()[1].SetVisible( True )

    # 覆盖式按钮通用
def GeneralCoverDefault( node ):
    node.GetChildren()[0].SetVisible( False )
def GeneralCoverOver( node ):
    node.GetChildren()[0].SetVisible( True )
    
    '''# 选择阵营菜单  加达里盖伦特通用
def SelectCGDefault( node ):
    node.GetChildren()[0].SetVisible( False )
def SelectCGOver( node ):
    node.GetChildren()[0].SetVisible( True )'''

    # 选择阵营菜单  选择加达里
def SelectCClick( node ):
    pass
    # 选择阵营菜单  选择盖伦特
def SelectGClick( node ):
    pass

    '''# 选择舰船菜单 通用
def ShipMenuButtonDefault( node ):
    node.GetChildren()[0].SetVisible( True )
    node.GetChildren()[1].SetVisible( False )
def ShipMenuButtonOver( node ):
    node.GetChildren()[0].SetVisible( False )
    node.GetChildren()[1].SetVisible( True )'''
