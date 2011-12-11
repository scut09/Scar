#ifndef ShipFactory_h__
#define ShipFactory_h__

#include "IShip.h"
#include "Frigate.h"
#include "irrlicht.h"
#include "MyIrrlichtEngine.h"
#include "SceneNodeShader.h"
#include "GeneralCallBack.h"
#include "BulletNode.h"
#include "IWeapon.h"
//#include "MissleNode.h"
#include "SpriteFlame.h"
#include <string>

/********************************************************************
	创建日期:	2011/12/11
	文件名: 	C:\Users\Administrator\Desktop\工作\SCAR项目组\opengl-scut\Code\Scar\Scar\ShipFactory.h
	作者:		屠文翔
	
	描述:		输入舰船名字，输出一部装配好的飞船
*********************************************************************/

class ShipFactory
{
public:
	ShipFactory()
	{

	}

	IShip* CreateShip( std::wstring shipName, const std::wstring& gunName = L"railgun", const std::wstring& missleName = L"autotrack" )
	{
		IShip* ship;
		ship = AssambleFrigate( shipName );
		AssambleMainGun( gunName, ship );
		AssambleMissle( missleName, ship );
		AssambleFlame( ship );

		return ship;
	}

	IShip* AssambleFrigate( const std::wstring& shipName )
	{
		IShip* ship;
		MyIrrlichtEngine* pEngine = MyIrrlichtEngine::GetEngine();

		if ( shipName == L"cf1" )
			ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf1.obj" );
		else if ( shipName == L"cf2" )
			ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/cf2.obj" );
		else if ( shipName == L"gf1" )
			ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/gf1.obj" );
		else if ( shipName == L"gf2" )
			ship = pEngine->GetMySceneManager()->addFrigateSceneNode( L"../model/ship/gf2.obj" );

		// Apply shader to ship
		SceneNodeShader shader;
		GeneralCallBack* cb = new GeneralCallBack( ship );
		shader.ApplyShaderToSceneNode( ship, cb, "Shader/cf_1V.vert", "Shader/cf_1F.frag" );
		cb->drop();
		ship->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
		//ship->setVisible( false );
		ship->SetMaxSpeed( 5 );

		return ship;
	}
	
	void AssambleMainGun( const std::wstring& gunName, IShip* ship )
	{
		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
		BulletNode* bullet = new BulletNode( smgr, smgr->getRootSceneNode() );

		if ( gunName == L"railgun" )
		{
			// 磁轨炮
			bullet->setID( 4003 );
			bullet->setMaterialTexture( 0, MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getTexture( "../media/Weapon/bullet.png" ) );
			bullet->SetVelocity( 1600 );
			bullet->SetInterval( 60 );
		}

		ship->AddGun( bullet );
		bullet->drop();
	}

	void AssambleMissle( const std::wstring& missleName, IShip* ship )
	{
		MissleNode* missle;
		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
		// 创建导弹
		if ( missleName == L"autotrack")
		{
			IMesh* missleMesh = smgr->getMesh( _T("../media/Weapon/missle.3ds") );
			missle = new MissleNode( missleMesh, 0, smgr, -1 );
		}

		ship->AddMissles( missle );
	}

	void AssambleFlame( IShip* ship )
	{
		auto smgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
		//飞船尾焰
		SpriteFlame spf;
		spf.SetOffset( vector3df( -6, 0, -22 ) );
		spf.AddFlameToShip( ship, smgr );
		spf.SetOffset( vector3df( 6, 0, -22 ) );
		spf.AddFlameToShip( ship, smgr );
	}
};

#endif // ShipFactory_h__
