/********************************************************************
����ʱ��: 2011-10-18   11:42
�ļ���:   CSceneNodeAnimatorAircraftFPS.h
����:     ����� Herrmann
˵��:	  �������������������˶�

*********************************************************************/
#include "SceneNodeAnimatorAircraftFPS.h"
#include "MyIrrlichtEngine.h"
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/math/quaternion.hpp>
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

	// ������������ʼ������
	if (firstUpdate)
	{
		// ���λ�ó�ʼΪ��Ļ����
		camera->updateAbsolutePosition();
		if (CursorControl && camera)
		{
			CursorControl->setPosition(0.5f, 0.5f);
			CursorPos = CenterPos = CursorControl->getPosition();
		}
		// ������ƶ��ķ�Χ�Ǵ�ȦȦ�ķ�Χ
		MoveRadius = 586 / 2;

		LastAnimationTime = timeMs;

		// ����Ҫ����ת��target
		camera->bindTargetAndRotation( false );
		
		// ��ʼ�����
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

	// ��֡��ͷ��Ϣ
	vector3df relateRot = camera->getRotation();
	vector3df lastUpVector = camera->getUpVector();
	vector3df lastDirection = ( camera->getTarget() - camera->getPosition() ).normalize();
	// һЩ��ʼ������
	matrix4 irrMat;
	ub::matrix<f32> bosMat(4,4);
	ub::vector<f32> t(4);

	// ������
	// ȡ�õ�ǰ�������Ļ�ϵ�λ���Լ������ĵ��λ����
	vector2d<s32> CursorOffset = CursorPos - CenterPos;
	s32 OffsetLength = CursorOffset.getLength();
	// ������ɳ���ȦȦ
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
	// ��ȡ��ǰ����ת�����ת��
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
	// ��任����
	f32 rotAng = (f32)CursorOffset.getLength() / (f32)MoveRadius * -2.0f /*ϵ�����*/;
	rotAxisQuat = rotAxisQuat.fromAngleAxis( rotAng * DEGTORAD, rotAxis ); // �ɸղ���õ���ת����ת�ض��Ƕ�
	irrMat = rotAxisQuat.getMatrix();		
	for ( int i=0; i<4; i++ )
	{
		for( int j=0; j<4; j++ )
		{
			bosMat(j,i) = irrMat[ 4*i + j ];
		}
	}
	//rotAxisQuat.toEuler( RotChange );
	// ���µ���ǰ����
	t(0) = lastDirection.X; t(1) = lastDirection.Y; t(2) = lastDirection.Z; t(3) = 0;
	t = prod( t, bosMat );
	vector3df newDirection = vector3df( t(0), t(1), t(2) ).normalize();
	// ���µ���������
	t(0) = lastUpVector.X; t(1) = lastUpVector.Y; t(2) = lastUpVector.Z; t(3) = 0;
	t = prod( t, bosMat );
	vector3df newUpVector = vector3df( t(0), t(1), t(2) );
	// ���µ���ת��
	vector3df newRotation;
	rotAxisQuat = rotAxisQuat.rotationFromTo( vector3df(0,0,1), newDirection );
	rotAxisQuat.toEuler( newRotation );
	newRotation *= RADTODEG;
	//newRotation += camera->getRotation();
	// �����ٶ��ƶ��ɴ�
	vector3df movement = newDirection * Ship->GetVelocity() /* �ٳ���ʱ��*/;
	// ���������״̬
	camera->setPosition( camera->getPosition() + movement );
	camera->setTarget( camera->getPosition() + newDirection );
	camera->setUpVector( newUpVector );
	camera->setRotation( newRotation );
	//std::cout<<std::endl;
	//std::cout<<tAng<<std::endl;
	//std::cout<< rotAxis.X << ","<< rotAxis.Y << ","<< rotAxis.Z << std::endl;

	// ���̿���
	// ��W������ʱ���٣���W������ʱ�ٶȻ�������
	if ( CursorKeys[EKA_MOVE_FORWARD] )
	{
		if ( Ship->GetVelocity() < Ship->GetMaxSpeed() )
		{
			f32 current = ( Ship->GetMaxSpeed() - Ship->GetVelocity() ) / 100.0f/*���������*/ + Ship->GetVelocity();
			Ship->SetVelocity( current );
		}
		// ��ֹ����
		if ( Ship->GetVelocity() > Ship->GetMaxSpeed() )
			Ship->SetVelocity( Ship->GetMaxSpeed() );
	}
	else if ( Ship->GetVelocity() > 0 )
	{
		Ship->SetVelocity( Ship->GetVelocity() - 0.005f/*���������*/ );
		// ��ֹ����
		if ( Ship->GetVelocity() < 0 )
			Ship->SetVelocity( 0 );
	}
	// ��S������ʱ����
	if ( CursorKeys[EKA_MOVE_BACKWARD] )
	{
		if ( Ship->GetVelocity() > 0 )
			Ship->SetVelocity( Ship->GetVelocity() - 0.01f/*���������*/ );
		// ��ֹ����
		if ( Ship->GetVelocity() < 0 )
			Ship->SetVelocity( 0 );
	}
	// ��A������ʱ��෭
	if ( CursorKeys[EKA_STRAFE_LEFT] )
	{
		/*if ( ! flag )
			flag = true;*/
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
		new CSceneNodeAnimatorAircraftFPS(CursorControl, Ship, 0, 0);
	newAnimator->setKeyMap(KeyMap);
	return newAnimator;
}

void CSceneNodeAnimatorAircraftFPS::setKeyMap(const core::array<SCamKeyMap>& keymap)
{
	KeyMap=keymap;
}

// ���µ���Щ��������Ҫʵ��

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


