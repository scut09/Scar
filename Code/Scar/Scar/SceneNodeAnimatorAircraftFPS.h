/********************************************************************
����ʱ��: 2011-10-18   11:42
�ļ���:   CSceneNodeAnimatorAircraftFPS.h
����:     ����� Herrmann
˵��:	  �������������������˶�

*********************************************************************/
#ifndef CSceneNodeAnimatorAircraftFPS_h_
#define CSceneNodeAnimatorAircraftFPS_h_


#include <irrlicht.h>
#include "IShip.h"
using namespace irr;
using namespace irr::core;
using namespace scene;

class CSceneNodeAnimatorAircraftFPS : public ISceneNodeAnimatorCameraFPS
{
public:
	public:

		//! Constructor
		CSceneNodeAnimatorAircraftFPS(gui::ICursorControl* cursorControl,
			SKeyMap* keyMapArray=0, u32 keyMapSize=0 );

		//! Destructor
		virtual ~CSceneNodeAnimatorAircraftFPS();

		//! Animates the scene node, currently only works on cameras
		virtual void animateNode(ISceneNode* node, u32 timeMs);

		//! Event receiver
		virtual bool OnEvent(const SEvent& event);

		//! Sets the keyboard mapping for this animator
		//! \param keymap: an array of keyboard mappings, see SKeyMap
		//! \param count: the size of the keyboard map array
		virtual void setKeyMap(SKeyMap *map, u32 count);

		//! This animator will receive events when attached to the active camera
		virtual bool isEventReceiverEnabled() const
		{
			return true;
		}

		//! Returns the type of this animator
		virtual ESCENE_NODE_ANIMATOR_TYPE getType() const
		{
			return ESNAT_CAMERA_FPS;
		}

		//! Creates a clone of this animator.
		/** Please note that you will have to drop
		(IReferenceCounted::drop()) the returned pointer once you're
		done with it. */
		virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);

		struct SCamKeyMap
		{
			SCamKeyMap() {};
			SCamKeyMap(s32 a, EKEY_CODE k) : action(a), keycode(k) {}

			s32 action;
			EKEY_CODE keycode;
		};

		//! Sets the keyboard mapping for this animator
		/** Helper function for the clone method.
		\param keymap the new keymap array */
		void setKeyMap(const core::array<SCamKeyMap>& keymap);

		/*
		 *	���µ���Щ��������Ҫ��ʵ��
		 */
		virtual f32 getMoveSpeed() const;

		virtual void setMoveSpeed( f32 moveSpeed );

		virtual f32 getRotateSpeed() const;

		virtual void setRotateSpeed( f32 rotateSpeed );

		virtual void setVerticalMovement( bool allow );

		virtual void setInvertMouse( bool invert );
		/*
		 *	���ϵ���Щ��������Ҫ��ʵ��
		 */
	private:
		void allKeysUp();

		gui::ICursorControl *CursorControl;

		s32 LastAnimationTime;			// ��һ�ζ���ʱ��

		core::array<SCamKeyMap> KeyMap;	// ���̰���ӳ��
		bool CursorKeys[6];				// ��Ӧ�����Ƿ񱻰���

		bool firstUpdate;				// �Ƿ��ʼ�����

		vector2d<s32> CenterPos;		// ��Ļ����λ��
		vector2d<s32> CursorPos;		// ��굱ǰλ��
		s32 MoveRadius;					// ׼���ƶ��뾶

		//IShip* Ship;					// �ٿصķɴ�
		s32 RollFlag;					// ������־λ 0�޷��� 1���� 2����
		f32 RollAng;					// ��ǰ�����Ƕ�
		s32 Count;						// ������
};
#endif
