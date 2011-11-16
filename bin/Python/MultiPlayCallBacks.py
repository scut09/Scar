#################################################
#                                               #
#   该文件储存MultiPlayScene中需要用到的回调函数      #
#                                               #
#################################################

    # 选择阵营菜单  加达里盖伦特通用
def SelectCGDefault( node ):
    node.GetChildren()[0].SetVisible( False )
def SelectCGOver( node ):
    node.GetChildren()[0].SetVisible( True )

