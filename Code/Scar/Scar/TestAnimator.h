/********************************************************************
创建时间: 2011-10-12   17:27
文件名:   TestAnimator.h
作者:     华亮 Cedric Porter [ Stupid ET ]	
说明:     测试Animator

*********************************************************************/

#ifndef TestAnimator_h__
#define TestAnimator_h__

#include <irrlicht.h>

class TestAnimator : public ISceneNodeAnimator
{
public:

	//! constructor
	CSceneNodeAnimatorDelete(ISceneManager* manager, u32 when);

	//! animates a scene node
	virtual void animateNode(ISceneNode* node, u32 timeMs);

	//! Returns type of the scene node animator
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const
	{
		return ESNAT_DELETION;
	}

	//! Creates a clone of this animator.
	/** Please note that you will have to drop
	(IReferenceCounted::drop()) the returned pointer after calling
	this. */
	virtual ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager=0);

private:

	ISceneManager* SceneManager;
};


#endif // TestAnimator_h__