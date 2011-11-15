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

	// ��ʼ���޷���
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

	// ������������ʼ������
	if (firstUpdate)
	{
		// ���λ�ó�ʼΪ��Ļ����
		if (CursorControl && ship)
		{
			CursorControl->setPosition(0.5f, 0.5f);
			CursorPos = CenterPos = CursorControl->getPosition();
		}
		// ������ƶ��ķ�Χ�Ǵ�ȦȦ�ķ�Χ
		MoveRadius = 586 / 2;

		LastAnimationTime = timeMs;
		
		// ��ʼ�����
		firstUpdate = false;
	}

	scene::ISceneManager * smgr = ship->getSceneManager();

	// ����ʱ���
	f32 timeDiff = (f32)( timeMs - LastAnimationTime ) / 20.f;
	LastAnimationTime = timeMs;

	// ��֡��ͷ��Ϣ
	vector3df relateRot = ship->getRotation();
	vector3df lastUpVector = ship->getUpVector();
	vector3df lastDirection = ( ship->getTarget() - ship->getPosition() ).normalize();
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
		if ( CursorControl )
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
	// ���Ӱ��ת��
	f32 rotAng = (f32)CursorOffset.getLength() / (f32)MoveRadius * -2.0f * timeDiff/*ϵ�����*/;
	// ��任����
	rotAxisQuat = rotAxisQuat.fromAngleAxis( rotAng * DEGTORAD, rotAxis ); // �ɸղ���õ���ת����ת�ض��Ƕ�
	irrMat = rotAxisQuat.getMatrix();		
	for ( int i=0; i<4; i++ )
	{
		for( int j=0; j<4; j++ )
		{
			bosMat(j,i) = irrMat[ 4*i + j ];
		}
	}
	// ���µ���ǰ����
	t(0) = lastDirection.X; t(1) = lastDirection.Y; t(2) = lastDirection.Z; t(3) = 0;
	t = prod( t, bosMat );
	vector3df newDirection = vector3df( t(0), t(1), t(2) ).normalize();
	// ���µ���������
	t(0) = lastUpVector.X; t(1) = lastUpVector.Y; t(2) = lastUpVector.Z; t(3) = 0;
	t = prod( t, bosMat );
	vector3df newUpVector = vector3df( t(0), t(1), t(2) );
	
	// �����ٶ��ƶ��ɴ�
	vector3df movement = newDirection * ship->GetVelocity() * timeDiff /* �ٳ���ʱ��*/;


	// ��������
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
	
	// ���������״̬
	ship->setPosition( ship->getPosition() + movement );
	ship->setTarget( ship->getPosition() + newDirection );
	ship->setUpVector( newUpVector );

	// �������������ת����
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
	mat.makeInverse();	// ��Ϊ�����

	// �������������ת��
	ship->setRotation( mat.getRotationDegrees() );

	// ���̿���
	// ��W������ʱ���٣���W������ʱ�ٶȻ�������
	if ( CursorKeys[EKA_MOVE_FORWARD] )
	{
		if ( ship->GetVelocity() < ship->GetMaxSpeed() )
		{
			f32 current = ( ship->GetMaxSpeed() - ship->GetVelocity() ) / 100.0f/*���������*/ + ship->GetVelocity();
			ship->SetVelocity( current );
		}
		// ��ֹ����
		if ( ship->GetVelocity() > ship->GetMaxSpeed() )
			ship->SetVelocity( ship->GetMaxSpeed() );
	}
	else if ( ship->GetVelocity() > 0 )
	{
		ship->SetVelocity( ship->GetVelocity() - 0.005f/*���������*/ );
		// ��ֹ����
		if ( ship->GetVelocity() < 0 )
			ship->SetVelocity( 0 );
	}
	// ��S������ʱ����
	if ( CursorKeys[EKA_MOVE_BACKWARD] )
	{
		if ( ship->GetVelocity() > 0 )
			ship->SetVelocity( ship->GetVelocity() - 0.01f/*���������*/ );
		// ��ֹ����
		if ( ship->GetVelocity() < 0 )
			ship->SetVelocity( 0 );
	}
	// ��A������ʱ��෭
	if ( CursorKeys[EKA_STRAFE_LEFT] )
	{
		if ( RollAng < 4.5f )
			RollAng += 0.15f;
	}
	// ������D��ʱ�Ҳ෭
	if ( CursorKeys[EKA_STRAFE_RIGHT] )
	{
		if ( RollAng > -4.5f )
			RollAng -= 0.15f;
	}
	// �����м�����ʱ�ָ�
	if ( !CursorKeys[EKA_STRAFE_LEFT] && !CursorKeys[EKA_STRAFE_RIGHT] )
	{
		if ( RollAng > 0 )
		{
			RollAng -= 0.15f;
			// ��ֹ����
			if ( RollAng < 0 )
				RollAng = 0;
		}	
		else if ( RollAng < 0 )
		{
			RollAng += 0.15f;
			// ��ֹ����
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


