#################################################
#                                               #
#   该文件储存MultiPlayScene中需要用到的回调函数      #
#                                               #
#################################################
import PythonSceneMgr
import Engine
#from Engine import *

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

    # 确认菜单通用
def ConfirmClick( node ):
    player = Engine.GetCurrentPlayer()
    player.SetConfirm( True )
    

    # 选择阵营菜单  选择加达里
def SelectCClick( node ):
    player = Engine.GetCurrentPlayer()
    player.SetTeam( 1 )
    # 选择阵营菜单  选择盖伦特
def SelectGClick( node ):
    player = Engine.GetCurrentPlayer()
    player.SetTeam( 2 )

    # 选择飞船  加达里
def SelectCf1( node ):
    player = Engine.GetCurrentPlayer()
    player.SetShipName( "cf1" )
    uiManager = Engine.GetUIManager()
    uiManager.GetUIObjectByName( "ssMenuC" ).GetChildren()[1].GetChildren()[0].SetVisible( True )
    uiManager.GetUIObjectByName( "ssMenuC" ).GetChildren()[1].GetChildren()[1].SetVisible( False )
    uiManager.GetUIObjectByName( "cf1Info" ).SetVisible( True )
    uiManager.GetUIObjectByName( "cf2Info" ).SetVisible( False )
def SelectCf2( node ):
    player = Engine.GetCurrentPlayer()
    player.SetShipName( "cf2" )
    uiManager = Engine.GetUIManager()
    uiManager.GetUIObjectByName( "ssMenuC" ).GetChildren()[0].GetChildren()[0].SetVisible( True )
    uiManager.GetUIObjectByName( "ssMenuC" ).GetChildren()[0].GetChildren()[1].SetVisible( False )
    uiManager.GetUIObjectByName( "cf1Info" ).SetVisible( False )
    uiManager.GetUIObjectByName( "cf2Info" ).SetVisible( True )
    # 选择飞船  盖伦特
def SelectGf1( node ):
    player = Engine.GetCurrentPlayer()
    player.SetShipName( "gf1" )
    uiManager = Engine.GetUIManager()
    uiManager.GetUIObjectByName( "ssMenuG" ).GetChildren()[1].GetChildren()[0].SetVisible( True )
    uiManager.GetUIObjectByName( "ssMenuG" ).GetChildren()[1].GetChildren()[1].SetVisible( False )
    uiManager.GetUIObjectByName( "gf1Info" ).SetVisible( True )
    uiManager.GetUIObjectByName( "gf2Info" ).SetVisible( False )
def SelectGf2( node ):
    player = Engine.GetCurrentPlayer()
    player.SetShipName( "gf2" )
    uiManager = Engine.GetUIManager()
    uiManager.GetUIObjectByName( "ssMenuG" ).GetChildren()[0].GetChildren()[0].SetVisible( True )
    uiManager.GetUIObjectByName( "ssMenuG" ).GetChildren()[0].GetChildren()[1].SetVisible( False )
    uiManager.GetUIObjectByName( "gf1Info" ).SetVisible( False )
    uiManager.GetUIObjectByName( "gf2Info" ).SetVisible( True )

    # 选武器装备 切换导航栏
def NavGunClick( node ):
    uiManager = Engine.GetUIManager()
    uiManager.GetUIObjectByName( "seMenu" ).GetChildren()[1].GetChildren()[0].SetVisible( True )
    uiManager.GetUIObjectByName( "seMenu" ).GetChildren()[1].GetChildren()[1].SetVisible( False )
    uiManager.GetUIObjectByName( "buyListGun" ).SetVisible( True )
    uiManager.GetUIObjectByName( "buyListMissle" ).SetVisible( False )
def NavMissleClick( node ):
    uiManager = Engine.GetUIManager()
    uiManager.GetUIObjectByName( "seMenu" ).GetChildren()[0].GetChildren()[0].SetVisible( True )
    uiManager.GetUIObjectByName( "seMenu" ).GetChildren()[0].GetChildren()[1].SetVisible( False )
    uiManager.GetUIObjectByName( "buyListGun" ).SetVisible( False )
    uiManager.GetUIObjectByName( "buyListMissle" ).SetVisible( True )

    '''# 选择舰船菜单 通用
def ShipMenuButtonDefault( node ):
    node.GetChildren()[0].SetVisible( True )
    node.GetChildren()[1].SetVisible( False )
def ShipMenuButtonOver( node ):
    node.GetChildren()[0].SetVisible( False )
    node.GetChildren()[1].SetVisible( True )'''
