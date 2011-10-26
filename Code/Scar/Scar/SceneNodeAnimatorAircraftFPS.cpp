/********************************************************************
创建时间: 2011-10-18   11:42
文件名:   CSceneNodeAnimatorAircraftFPS.h
作者:     杨旭瑜 Herrmann
说明:	  飞行器摄像机单人射击运动

*********************************************************************/
#include "SceneNodeAnimatorAircraftFPS.h"
#include "MyIrrlichtEngine.h"
#include <iostream>


//! constructor
CSceneNodeAnimatorAircraftFPS::CSceneNodeAnimatorAircraftFPS(gui::ICursorControl* cursorControl,
	IShip* ship,
	f32 rotateSpeed, f32 moveSpeed, f32 jumpSpeed,
	SKeyMap* keyMapArray, u32 keyMapSize, bool noVerticalMovement, bool invertY)
	: CursorControl(cursorControl), Ship(ship), MaxVerticalAngle(88.0f),
	MoveSpeed(moveSpeed), RotateSpeed(rotateSpeed), JumpSpeed(jumpSpeed),
	MouseYDirection(invertY ? -1.0f : 1.0f),
	LastAnimationTime(0), firstUpdate(true), NoVerticalMovement(noVerticalMovement)
{


	if (CursorControl)
		CursorControl->grab();

	allKeysUp();

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

		//// 获得屏幕中心点位置
		//dimension2d<u32> screenSize = MyIrrlichtEngine::GetEngine()->GetVideoDriver()->getScreenSize();
		//CenterPos.X = (s32)screenSize.Width / 2;
		//CenterPos.Y = (s32)screenSize.Height / 2;
		
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

	//// update position
	//core::vector3df pos = camera->getPosition();

	//// Update rotation
	//core::vector3df target = (camera->getTarget() - camera->getAbsolutePosition());
	//core::vector3df relativeRotation = target.getHorizontalAngle();

	if (CursorControl)
	{
		/*std::cout << std::endl;
		std::cout<< CursorPos.X << "," << CursorPos.Y << std::endl;
		std::cout<< CenterPos.X << "," << CenterPos.Y << std::endl;*/

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
		
		vector3df relateRot = camera->getRotation();
		vector3df currentRot = relateRot + vector3df(0, 0.05f, 0 );
		//f32 zDeg = currentRot.Z;
		//vector3df upVector = vector3df( 0, 1, 0 );
		//upVector.rotateXYBy( zDeg );
		camera->setRotation( currentRot );
		camera->setTarget( camera->getTarget() + currentRot.rotationToDirection() );
		//camera->setUpVector( upVector );
		//camera->setPosition( camera->getPosition() + vector3df(-5, 0, 0) );
		

		//if (CursorPos != CenterCursor)
		//{
		//	relativeRotation.Y -= (0.5f - CursorPos.X) * RotateSpeed;
		//	relativeRotation.X -= (0.5f - CursorPos.Y) * RotateSpeed * MouseYDirection;

		//	// X < MaxVerticalAngle or X > 360-MaxVerticalAngle

		//	if (relativeRotation.X > MaxVerticalAngle*2 &&
		//		relativeRotation.X < 360.0f-MaxVerticalAngle)
		//	{
		//		relativeRotation.X = 360.0f-MaxVerticalAngle;
		//	}
		//	else
		//		if (relativeRotation.X > MaxVerticalAngle &&
		//			relativeRotation.X < 360.0f-MaxVerticalAngle)
		//		{
		//			relativeRotation.X = MaxVerticalAngle;
		//		}

		//		// Do the fix as normal, special case below
		//		// reset cursor position to the centre of the window.
		//		//CursorControl->setPosition(0.5f, 0.5f);
		//		CenterCursor = CursorControl->getRelativePosition();

		//		// needed to avoid problems when the event receiver is disabled
		//		CursorPos = CenterCursor;
		//}

		//// Special case, mouse is whipped outside of window before it can update.
		//video::IVideoDriver* driver = smgr->getVideoDriver();
		//core::vector2d<u32> mousepos(u32(CursorControl->getPosition().X), u32(CursorControl->getPosition().Y));
		//core::rect<u32> screenRect(0, 0, driver->getScreenSize().Width, driver->getScreenSize().Height);

		//// Only if we are moving outside quickly.
		//bool reset = !screenRect.isPointInside(mousepos);

		//if(reset)
		//{
		//	// Force a reset.
		//	CursorControl->setPosition(0.5f, 0.5f);
		//	CenterCursor = CursorControl->getRelativePosition();
		//	CursorPos = CenterCursor;
		//}
	}

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

	// set target

	/*target.set(0,0, core::max_(1.f, pos.getLength()));
	core::vector3df movedir = target;

	core::matrix4 mat;
	mat.setRotationDegrees(core::vector3df(relativeRotation.X, relativeRotation.Y, 0));
	mat.transformVect(target);

	if (NoVerticalMovement)
	{
		mat.setRotationDegrees(core::vector3df(0, relativeRotation.Y, 0));
		mat.transformVect(movedir);
	}
	else
	{
		movedir = target;
	}

	movedir.normalize();

	if (CursorKeys[EKA_MOVE_FORWARD])
		pos += movedir * timeDiff * MoveSpeed;

	if (CursorKeys[EKA_MOVE_BACKWARD])
		pos -= movedir * timeDiff * MoveSpeed;*/

	// strafing

	/*core::vector3df strafevect = target;
	strafevect = strafevect.crossProduct(camera->getUpVector());

	if (NoVerticalMovement)
		strafevect.Y = 0.0f;

	strafevect.normalize();

	if (CursorKeys[EKA_STRAFE_LEFT])
		pos += strafevect * timeDiff * MoveSpeed;

	if (CursorKeys[EKA_STRAFE_RIGHT])
		pos -= strafevect * timeDiff * MoveSpeed;*/

	// For jumping, we find the collision response animator attached to our camera
	// and if it's not falling, we tell it to jump.
	/*if (CursorKeys[EKA_JUMP_UP])
	{
		const ISceneNodeAnimatorList& animators = camera->getAnimators();
		ISceneNodeAnimatorList::ConstIterator it = animators.begin();
		while(it != animators.end())
		{
			if(ESNAT_COLLISION_RESPONSE == (*it)->getType())
			{
				ISceneNodeAnimatorCollisionResponse * collisionResponse =
					static_cast<ISceneNodeAnimatorCollisionResponse *>(*it);

				if(!collisionResponse->isFalling())
					collisionResponse->jump(JumpSpeed);
			}

			it++;
		}
	}*/

	// write translation
	//camera->setPosition(pos);

	// write right target
	//target += pos;
	//camera->setTarget(target);
}


void CSceneNodeAnimatorAircraftFPS::allKeysUp()
{
	for (u32 i=0; i<6; ++i)
		CursorKeys[i] = false;
}


//! Sets the rotation speed
void CSceneNodeAnimatorAircraftFPS::setRotateSpeed(f32 speed)
{
	RotateSpeed = speed;
}


//! Sets the movement speed
void CSceneNodeAnimatorAircraftFPS::setMoveSpeed(f32 speed)
{
	MoveSpeed = speed;
}


//! Gets the rotation speed
f32 CSceneNodeAnimatorAircraftFPS::getRotateSpeed() const
{
	return RotateSpeed;
}


// Gets the movement speed
f32 CSceneNodeAnimatorAircraftFPS::getMoveSpeed() const
{
	return MoveSpeed;
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


//! Sets whether vertical movement should be allowed.
void CSceneNodeAnimatorAircraftFPS::setVerticalMovement(bool allow)
{
	NoVerticalMovement = !allow;
}


//! Sets whether the Y axis of the mouse should be inverted.
void CSceneNodeAnimatorAircraftFPS::setInvertMouse(bool invert)
{
	if (invert)
		MouseYDirection = -1.0f;
	else
		MouseYDirection = 1.0f;
}


ISceneNodeAnimator* CSceneNodeAnimatorAircraftFPS::createClone(ISceneNode* node, ISceneManager* newManager)
{
	CSceneNodeAnimatorAircraftFPS * newAnimator =
		new CSceneNodeAnimatorAircraftFPS(CursorControl, Ship, RotateSpeed, MoveSpeed, JumpSpeed,
		0, 0, NoVerticalMovement);
	newAnimator->setKeyMap(KeyMap);
	return newAnimator;
}


void CSceneNodeAnimatorAircraftFPS::setKeyMap(const core::array<SCamKeyMap>& keymap)
{
	KeyMap=keymap;
}


