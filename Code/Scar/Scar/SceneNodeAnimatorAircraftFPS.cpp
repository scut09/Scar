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
namespace ub = boost::numeric::ublas;

//! constructor
CSceneNodeAnimatorAircraftFPS::CSceneNodeAnimatorAircraftFPS(gui::ICursorControl* cursorControl,
	IShip* ship, SKeyMap* keyMapArray, u32 keyMapSize)
	: CursorControl(cursorControl), Ship(ship),
	LastAnimationTime(0), firstUpdate(true)
{


	if (CursorControl)
		CursorControl->grab();

	allKeysUp();

	/*Vect = vector2d<f32> ( 0.f, 0.f );
	AcceFactor = 10;*/
	//Count = 0;

	//flag = false;

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
	if (!node || node->getType() != ESNT_CAMERA)
		return;

	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);

	// 在这里面做初始化工作
	if (firstUpdate)
	{
		// 鼠标位置初始为屏幕中心
		camera->updateAbsolutePosition();
		if (CursorControl && camera)
		{
			CursorControl->setPosition(0.5f, 0.5f);
			CursorPos = CenterPos = CursorControl->getPosition();
		}
		// 鼠标能移动的范围是大圈圈的范围
		MoveRadius = 586 / 2;

		LastAnimationTime = timeMs;

		// 不需要绑定旋转和target
		camera->bindTargetAndRotation( false );
		
		// 初始化完成
		firstUpdate = false;
	}

	// If the camera isn't the active camera, and receiving input, then don't process it.
	if(!camera->isInputReceiverEnabled())
		return;

	scene::ISceneManager * smgr = camera->getSceneManager();
	if(smgr && smgr->getActiveCamera() != camera)
		return;

	// get time
	f32 timeDiff = (f32) ( timeMs - LastAnimationTime );
	LastAnimationTime = timeMs;

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
		CursorControl->setPosition( newPos.X, newPos.Y );
	}
	// 杨成熙写的鼠标方向控制
	//Count += 1;
	//Count %= 100;
	vector3df RotChange = vector3df(0);
	//if ( ! flag )
	//{
	f32 horizonChange = 1;	// 当镜头上下翻转时鼠标水平操控方向也要翻转
	if ( camera->getUpVector().Y < 0 )
		horizonChange = -1;
	f32 factor = 1.f;
	//vector2d<f32>temvect ( (f32)CursorOffset.X, (f32)CursorOffset.Y );
	//temvect.normalize();
	/*bool vectchange = ( abs( Vect.X - temvect.X ) < 0.05f ) && ( abs( Vect.Y - temvect.Y ) < 0.05f );
	if ( vectchange )
	{
	if ( AcceFactor != 90 )
	AcceFactor += 1;
	RotChange.Y += (f32) horizonChange * ( CursorOffset.X  / (f32)MoveRadius ) / factor * sin( AcceFactor * DEGTORAD );
	RotChange.X += (f32) ( CursorOffset.Y  / (f32)MoveRadius ) / factor * sin( AcceFactor * DEGTORAD );
	if ( Count == 0 )
	LastOffset = CursorOffset;
	}
	else
	{
	if( AcceFactor != 5 )
	{
	RotChange.Y += (f32) horizonChange * ( LastOffset.X  / (f32)MoveRadius ) / factor * sin( AcceFactor * DEGTORAD );
	RotChange.X += (f32) ( LastOffset.Y  / (f32)MoveRadius ) / factor * sin( AcceFactor * DEGTORAD );
	AcceFactor -= 1;
	}
	else
	{
	RotChange.Y += (f32) horizonChange * ( CursorOffset.X  / (f32)MoveRadius ) / factor * sin( AcceFactor * DEGTORAD );
	RotChange.X += (f32) ( CursorOffset.Y  / (f32)MoveRadius ) / factor * sin( AcceFactor * DEGTORAD );
	Vect = temvect;
	}
	}*/
	RotChange.Y += (f32) horizonChange * ( CursorOffset.X  / (f32)MoveRadius ) / factor;
	RotChange.X += (f32) ( CursorOffset.Y  / (f32)MoveRadius ) / factor;
		//}

	// 键盘控制
	// 当W键按下时加速，当W键弹起时速度缓慢回落
	if ( CursorKeys[EKA_MOVE_FORWARD] )
	{
		if ( Ship->GetVelocity() < Ship->GetMaxSpeed() )
		{
			f32 current = ( Ship->GetMaxSpeed() - Ship->GetVelocity() ) / 100.0f/*灵敏度相关*/ + Ship->GetVelocity();
			Ship->SetVelocity( current );
		}
		// 防止上溢
		if ( Ship->GetVelocity() > Ship->GetMaxSpeed() )
			Ship->SetVelocity( Ship->GetMaxSpeed() );
	}
	else if ( Ship->GetVelocity() > 0 )
	{
		Ship->SetVelocity( Ship->GetVelocity() - 0.005f/*灵敏度相关*/ );
		// 防止下溢
		if ( Ship->GetVelocity() < 0 )
			Ship->SetVelocity( 0 );
	}
	// 当S键按下时减速
	if ( CursorKeys[EKA_MOVE_BACKWARD] )
	{
		if ( Ship->GetVelocity() > 0 )
			Ship->SetVelocity( Ship->GetVelocity() - 0.01f/*灵敏度相关*/ );
		// 防止下溢
		if ( Ship->GetVelocity() < 0 )
			Ship->SetVelocity( 0 );
	}
	// 当A键按下时左侧翻
	if ( CursorKeys[EKA_STRAFE_LEFT] )
	{
		/*if ( ! flag )
			flag = true;*/
		RotChange = vector3df( 0, 0, 15 );
	}
	/*if ( flag )
	{
		RotChange = vector3df( 0, 0, -15 );
		Count += 1;
		camera->setPosition( camera->getPosition() + vector3df( -50, 0, 0 ) );
		if ( Count == 24 )
		{
			flag = false;
			Count = 0;
		}
	}*/



	// 设置照相机节点旋转状态
	vector3df relateRot = camera->getRotation();
	vector3df currentRot = relateRot + RotChange/* + 旋转改变量*/;
	camera->setRotation( currentRot );

	// 使用四元数完美解决万向锁，感谢熙狗
	// 从欧拉角构造四元数
	irr::core::quaternion quar( vector3df( currentRot.X * DEGTORAD, currentRot.Y * DEGTORAD, currentRot.Z * DEGTORAD ) );
	// 从四元数构造旋转矩阵
	matrix4 m = quar.getMatrix();
	// 镜头upVector初始为( 0, 1, 0 )
	ub::vector<f32> temp(4);
	temp(0) = 0; temp(1) = 1; temp(2) = 0; temp(3) = 1;
	// 使用boost库进行向量和矩阵相乘
	ub::matrix<f32> m2(4,4);
	for ( int i=0; i<4; i++ )
	{
		for( int j=0; j<4; j++ )
		{
			m2(j,i) = m[ 4*i + j ];
		}
	}
	// 设置镜头upVector
	// 注意：当上下翻转后，鼠标水平操控方向翻转
	temp = ub::prod( temp, m2 );
	camera->setUpVector( vector3df( temp(0), temp(1), temp(2) ) );
	// 设置target的位置（X轴和Y轴）
	temp(0) = 0; temp(1) = 0; temp(2) = 1; temp(3) = 1;
	temp = ub::prod( temp, m2 );
	vector3df direction = vector3df( temp(0), temp(1), temp(2) );
	// 设置照相机节点的位置
	vector3df movement = direction * Ship->GetVelocity()/* 再乘以一个时间系数 */;
	camera->setPosition( camera->getPosition() + movement );
	// 设置target的位置（X轴和Y轴）
	camera->setTarget( camera->getPosition() + direction );

	// 设置照相机节点的位置
	//vector3df direction = currentRot.rotationToDirection();
	//direction.normalize();
	//vector3df movement = direction * Ship->GetVelocity()/* 再乘以一个时间系数 */;
	//camera->setPosition( camera->getPosition() + movement );
	//camera->setPosition( camera->getPosition() + vector3df(0, 0, Ship->GetVelocity()) );

	//// 设置target的位置（X轴和Y轴）
	//direction = vector3df( currentRot.X, currentRot.Y, currentRot.Z );			// 先忽略Z轴旋转
	//direction = direction.rotationToDirection();					// 由角度求出位置向量
	//camera->setTarget( camera->getPosition() + direction );


	

	// 设置镜头旋转（Z轴）y
	//f32 zDeg = currentRot.Z;
	////if ( (s32)currentRot.Y % 360 >= 90 )
	////zDeg *= -1;
	//vector3df upVector = vector3df( 0, 1, 0 );
	//upVector.rotateXYBy( zDeg );
	//camera->setUpVector( upVector );
	/*std::cout<<camera->getUpVector().X<<","<<camera->getUpVector().Y<<","<<camera->getUpVector().Z<<"\t";
	std::cout<<zDeg<<std::endl;*/

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
		new CSceneNodeAnimatorAircraftFPS(CursorControl, Ship, 0, 0);
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


