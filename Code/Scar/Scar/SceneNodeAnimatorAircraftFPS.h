/********************************************************************
创建时间: 2011-10-18   11:42
文件名:   CSceneNodeAnimatorAircraftFPS.h
作者:     杨旭瑜 Herrmann
说明:	  飞行器摄像机单人射击运动

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
		 *	以下的这些函数不需要被实现
		 */
		virtual f32 getMoveSpeed() const;

		virtual void setMoveSpeed( f32 moveSpeed );

		virtual f32 getRotateSpeed() const;

		virtual void setRotateSpeed( f32 rotateSpeed );

		virtual void setVerticalMovement( bool allow );

		virtual void setInvertMouse( bool invert );
		/*
		 *	以上的这些函数不需要被实现
		 */
	private:
		void allKeysUp();

		gui::ICursorControl *CursorControl;

		s32 LastAnimationTime;			// 上一次动画时间

		core::array<SCamKeyMap> KeyMap;	// 键盘按键映射
		bool CursorKeys[6];				// 相应按键是否被按下

		bool firstUpdate;				// 是否初始化完成

		vector2d<s32> CenterPos;		// 屏幕中心位置
		vector2d<s32> CursorPos;		// 鼠标当前位置
		s32 MoveRadius;					// 准心移动半径

		//IShip* Ship;					// 操控的飞船
		s32 RollFlag;					// 翻滚标志位 0无翻滚 1向左 2向右
		f32 RollAng;					// 当前翻滚角度
		s32 Count;						// 计数器
};
#endif
