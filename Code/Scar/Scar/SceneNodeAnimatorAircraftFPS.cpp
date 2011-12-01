/********************************************************************
创建时间: 2011-10-18   11:42
文件名:   CSceneNodeAnimatorAircraftFPS.h
作者:     杨旭瑜 Herrmann
说明:	  飞行器摄像机单人射击运动

*********************************************************************/
#include "SceneNodeAnimatorAircraftFPS.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/math/quaternion.hpp>

#define PRINT_POS( pos ) std::cout << #pos ## " " << pos.X << ' ' << pos.Y << ' ' << pos.Z << std::endl;

namespace ub = boost::numeric::ublas;
using core::vector3df;

//! constructor
CSceneNodeAnimatorAircraftFPS::CSceneNodeAnimatorAircraftFPS(gui::ICursorControl* cursorControl,
	SKeyMap* keyMapArray, u32 keyMapSize)
	: CursorControl(cursorControl), 
	LastAnimationTime(0), firstUpdate(true)
{


	if (CursorControl)
		CursorControl->grab();

	allKeysUp();

	// 初始化无翻滚
	RollFlag = 0;
	RollAng = 0;

	// create key map
	if (!keyMapArray || !keyMapSize)
	{
		// create default key map
		KeyMap.push_back(SCamKeyMap(EKA_MOVE_FORWARD, irr::KEY_KEY_W ));
		KeyMap.push_back(SCamKeyMap(EKA_MOVE_BACKWARD, irr::KEY_KEY_S));
		KeyMap.push_back(SCamKeyMap(EKA_STRAFE_LEFT, irr::KEY_KEY_A));
		KeyMap.push_back(SCamKeyMap(EKA_STRAFE_RIGHT, irr::KEY_KEY_D));
		KeyMap.push_back(SCamKeyMap(EKA_JUMP_UP, irr::KEY_KEY_J));
	}
	else
	{
		// create custom key map
		setKeyMap(keyMapArray, keyMapSize);
	}
}


//! destructor
CSceneNodeAnimatorAircraftFPS::~CSceneNodeAnimatorAircraftFPS()
{
	if (CursorControl)
		CursorControl->drop();
}


//! It is possible to send mouse and key events to the camera. Most cameras
//! may ignore this input, but camera scene nodes which are created for
//! example with scene::ISceneManager::addMayaCameraSceneNode or
//! scene::ISceneManager::addFPSCameraSceneNode, may want to get this input
//! for changing their position, look at target or whatever.
bool CSceneNodeAnimatorAircraftFPS::OnEvent(const SEvent& evt)
{
	switch(evt.EventType)
	{
	case EET_KEY_INPUT_EVENT:
		for (u32 i=0; i<KeyMap.size(); ++i)
		{
			if (KeyMap[i].keycode == evt.KeyInput.Key)
			{
				CursorKeys[KeyMap[i].action] = evt.KeyInput.PressedDown;
				return true;
			}
		}
		break;

	case EET_MOUSE_INPUT_EVENT:
		if (evt.MouseInput.Event == EMIE_MOUSE_MOVED)
		{
			CursorPos = CursorControl->getPosition();
			return true;
		}
		break;

	default:
		break;
	}

	return false;
}


void CSceneNodeAnimatorAircraftFPS::animateNode(ISceneNode* node, u32 timeMs)
{
	

	IShip* ship = static_cast<IShip*>( node );

	// 在这里面做初始化工作
	if (firstUpdate)
	{
		// 鼠标位置初始为屏幕中心
		if (CursorControl && ship)
		{
			CursorControl->setPosition(0.5f, 0.5f);
			CursorPos = CenterPos = CursorControl->getPosition();
		}
		// 鼠标能移动的范围是大圈圈的范围
		MoveRadius = 586 / 2;

		LastAnimationTime = timeMs;
		
		// 初始化完成
		firstUpdate = false;
	}

	scene::ISceneManager * smgr = ship->getSceneManager();

	// 计算时间差
	f32 timeDiff = (f32)( timeMs - LastAnimationTime ) / 20.f;
	LastAnimationTime = timeMs;

	// 上帧镜头信息
	vector3df relateRot = ship->getRotation();
	vector3df lastUpVector = ship->getUpVector();
	vector3df lastDirection = ( ship->getTarget() - ship->getPosition() ).normalize();
	// 一些初始化变量
	matrix4 irrMat;
	ub::matrix<f32> bosMat(4,4);
	ub::vector<f32> t(4);

	// 鼠标控制
	// 取得当前鼠标在屏幕上的位置以及离中心点的位移量
	vector2d<s32> CursorOffset = CursorPos - CenterPos;
	s32 OffsetLength = CursorOffset.getLength();
	// 如果鼠标飞出大圈圈
	if ( OffsetLength > MoveRadius )
	{
		vector2d<s32> newPos;
		f32 factor = MoveRadius / (f32)OffsetLength;
		CursorOffset.X  = (s32)( CursorOffset.X * factor );
		CursorOffset.Y  = (s32)( CursorOffset.Y * factor );
		newPos = CursorOffset + CenterPos;
		CursorPos = newPos;
		if ( CursorControl )
			CursorControl->setPosition( newPos.X, newPos.Y );
	}
	// 获取当前的旋转轴和旋转角
	f32 tAng = (f32)CursorOffset.getAngle() - 90;
	if ( tAng < 0 )
		tAng += 360;

	quaternion rotAxisQuat;
	rotAxisQuat = rotAxisQuat.fromAngleAxis( tAng * DEGTORAD, lastDirection );
	vector3df rotAxis = lastUpVector.crossProduct( lastDirection );
	t(0) = rotAxis.X;  t(1) = rotAxis.Y;  t(2) = rotAxis.Z;  t(3) = 0;
	irrMat = rotAxisQuat.getMatrix();
	for ( int i=0; i<4; i++ )
	{
		for( int j=0; j<4; j++ )
		{
			bosMat(j,i) = irrMat[ 4*i + j ];
		}
	}
	t = prod( t, bosMat );
	rotAxis = vector3df( t(0), t(1), t(2) );
	// 鼠标影响转动
	f32 rotAng = (f32)CursorOffset.getLength() / (f32)MoveRadius * -2.0f * timeDiff/*系数相关*/;
	// 求变换矩阵
	rotAxisQuat = rotAxisQuat.fromAngleAxis( rotAng * DEGTORAD, rotAxis ); // 由刚才求得的旋转轴旋转特定角度
	irrMat = rotAxisQuat.getMatrix();		
	for ( int i=0; i<4; i++ )
	{
		for( int j=0; j<4; j++ )
		{
			bosMat(j,i) = irrMat[ 4*i + j ];
		}
	}
	// 求新的向前向量
	t(0) = lastDirection.X; t(1) = lastDirection.Y; t(2) = lastDirection.Z; t(3) = 0;
	t = prod( t, bosMat );
	vector3df newDirection = vector3df( t(0), t(1), t(2) ).normalize();
	// 求新的向上向量
	t(0) = lastUpVector.X; t(1) = lastUpVector.Y; t(2) = lastUpVector.Z; t(3) = 0;
	t = prod( t, bosMat );
	vector3df newUpVector = vector3df( t(0), t(1), t(2) );
	
	// 根据速度移动飞船
	vector3df movement = newDirection * ship->GetVelocity() * timeDiff /* 再乘以时间*/;


	// 翻滚动作
	if ( RollAng != 0 )
	{
		rotAxisQuat = rotAxisQuat.fromAngleAxis( RollAng * DEGTORAD * timeDiff, newDirection );
		irrMat = rotAxisQuat.getMatrix();
		for ( int i=0; i<4; i++ )
		{
			for( int j=0; j<4; j++ )
			{
				bosMat(j,i) = irrMat[ 4*i + j ];
			}
		}
		t(0)=newUpVector.X; t(1)=newUpVector.Y; t(2)=newUpVector.Z; t(3)=0;
		t = prod( t, bosMat );
		newUpVector = vector3df( t(0), t(1), t(2) );
	}
	
	// 更新照相机状态
	ship->setPosition( ship->getPosition() + movement );
	ship->setTarget( ship->getPosition() + newDirection );
	ship->setUpVector( newUpVector );

	// 计算摄像机的旋转矩阵
	vector3df up = ship->getUpVector();
	vector3df dir = ship->getTarget() - ship->getPosition();
	vector3df x = up.crossProduct( dir );
	up.normalize();	dir.normalize();	x.normalize();

	core::matrix4 mat;
	f32 m[ 16 ];
	m[ 0 ] = x.X;	m[ 1 ] = up.X;		m[ 2 ] = dir.X;		m[ 3 ] = 0;	
	m[ 4 ] = x.Y;	m[ 5 ] = up.Y;		m[ 6 ] = dir.Y;		m[ 7 ] = 0;
	m[ 8 ] = x.Z;	m[ 9 ] = up.Z;		m[ 10 ] = dir.Z;	m[ 11 ] = 0;
	m[ 12 ] = 0;	m[ 13 ] = 0;	m[ 14 ] = 0;		m[ 15 ] = 1;
	mat.setM( m );
	mat.makeInverse();	// 变为逆矩阵

	// 设置摄像机的旋转角
	ship->setRotation( mat.getRotationDegrees() );

	// 键盘控制
	// 当W键按下时加速，当W键弹起时速度缓慢回落
	if ( CursorKeys[EKA_MOVE_FORWARD] )
	{
		if ( ship->GetVelocity() < ship->GetMaxSpeed() )
		{
			f32 current = ( ship->GetMaxSpeed() - ship->GetVelocity() ) / 100.0f/*灵敏度相关*/ + ship->GetVelocity();
			ship->SetVelocity( current );
		}
		// 防止上溢
		if ( ship->GetVelocity() > ship->GetMaxSpeed() )
			ship->SetVelocity( ship->GetMaxSpeed() );
	}
	else if ( ship->GetVelocity() > 0 )
	{
		ship->SetVelocity( ship->GetVelocity() - 0.005f/*灵敏度相关*/ );
		// 防止下溢
		if ( ship->GetVelocity() < 0 )
			ship->SetVelocity( 0 );
	}
	// 当S键按下时减速
	if ( CursorKeys[EKA_MOVE_BACKWARD] )
	{
		if ( ship->GetVelocity() > 0 )
			ship->SetVelocity( ship->GetVelocity() - 0.01f/*灵敏度相关*/ );
		// 防止下溢
		if ( ship->GetVelocity() < 0 )
			ship->SetVelocity( 0 );
	}
	// 当A键按下时左侧翻
	if ( CursorKeys[EKA_STRAFE_LEFT] )
	{
		if ( RollAng < 4.5f )
			RollAng += 0.15f;
	}
	// 当按下D键时右侧翻
	if ( CursorKeys[EKA_STRAFE_RIGHT] )
	{
		if ( RollAng > -4.5f )
			RollAng -= 0.15f;
	}
	// 当所有键弹起时恢复
	if ( !CursorKeys[EKA_STRAFE_LEFT] && !CursorKeys[EKA_STRAFE_RIGHT] )
	{
		if ( RollAng > 0 )
		{
			RollAng -= 0.15f;
			// 防止下溢
			if ( RollAng < 0 )
				RollAng = 0;
		}	
		else if ( RollAng < 0 )
		{
			RollAng += 0.15f;
			// 防止上溢
			if ( RollAng > 0 )
				RollAng = 0;
		}	
	}
}


void CSceneNodeAnimatorAircraftFPS::allKeysUp()
{
	for (u32 i=0; i<6; ++i)
		CursorKeys[i] = false;
}

//! Sets the keyboard mapping for this animator
void CSceneNodeAnimatorAircraftFPS::setKeyMap(SKeyMap *map, u32 count)
{
	// clear the keymap
	KeyMap.clear();

	// add actions
	for (u32 i=0; i<count; ++i)
	{
		switch(map[i].Action)
		{
		case EKA_MOVE_FORWARD: KeyMap.push_back(SCamKeyMap(EKA_MOVE_FORWARD, map[i].KeyCode));
			break;
		case EKA_MOVE_BACKWARD: KeyMap.push_back(SCamKeyMap(EKA_MOVE_BACKWARD, map[i].KeyCode));
			break;
		case EKA_STRAFE_LEFT: KeyMap.push_back(SCamKeyMap(EKA_STRAFE_LEFT, map[i].KeyCode));
			break;
		case EKA_STRAFE_RIGHT: KeyMap.push_back(SCamKeyMap(EKA_STRAFE_RIGHT, map[i].KeyCode));
			break;
		case EKA_JUMP_UP: KeyMap.push_back(SCamKeyMap(EKA_JUMP_UP, map[i].KeyCode));
			break;
		default:
			break;
		}
	}
}

ISceneNodeAnimator* CSceneNodeAnimatorAircraftFPS::createClone(ISceneNode* node, ISceneManager* newManager)
{
	CSceneNodeAnimatorAircraftFPS * newAnimator =
		new CSceneNodeAnimatorAircraftFPS(CursorControl, 0, 0);
	newAnimator->setKeyMap(KeyMap);
	return newAnimator;
}

void CSceneNodeAnimatorAircraftFPS::setKeyMap(const core::array<SCamKeyMap>& keymap)
{
	KeyMap=keymap;
}

// 以下的这些方法不需要实现

irr::f32 CSceneNodeAnimatorAircraftFPS::getMoveSpeed() const
{
	throw std::exception("The method or operation is not implemented.");
}

void CSceneNodeAnimatorAircraftFPS::setMoveSpeed( f32 moveSpeed )
{
	throw std::exception("The method or operation is not implemented.");
}

irr::f32 CSceneNodeAnimatorAircraftFPS::getRotateSpeed() const
{
	throw std::exception("The method or operation is not implemented.");
}

void CSceneNodeAnimatorAircraftFPS::setRotateSpeed( f32 rotateSpeed )
{
	throw std::exception("The method or operation is not implemented.");
}

void CSceneNodeAnimatorAircraftFPS::setVerticalMovement( bool allow )
{
	throw std::exception("The method or operation is not implemented.");
}

void CSceneNodeAnimatorAircraftFPS::setInvertMouse( bool invert )
{
	throw std::exception("The method or operation is not implemented.");
}


