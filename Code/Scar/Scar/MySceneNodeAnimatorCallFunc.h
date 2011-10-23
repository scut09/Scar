#ifndef MySceneNodeAnimatorCallFunc_h__
#define MySceneNodeAnimatorCallFunc_h__

/********************************************************************
	��������:	2011/10/23
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\MySceneNodeAnimatorCallFunc.h
	����:		������
	
	����:		�趨�ӳ�һ��ʱ��֮�������һ������
				ʹ��SetCallBack�����ûص�����
				�÷�Ϊ
				funcAni->SetCallback( []()
				{
					//�˴�д������
				});
*********************************************************************/

#include "ISceneNode.h"
#include <functional>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

class MySceneNodeAnimatorCallFunc : public ISceneNodeAnimator
{
	typedef std::function< void() >	FuncCallbackType;

	u32 Begin;
	u32 Delay;
	u32 Duration;	

	FuncCallbackType	Func;

public:
	MySceneNodeAnimatorCallFunc( u32 delay, u32 duration );

	virtual void animateNode( ISceneNode* node, u32 timeMs );

	virtual ISceneNodeAnimator* createClone( ISceneNode* node, ISceneManager* newManager=0 );

	void SetCallback( FuncCallbackType func )
	{
		Func = func;
	}

};

#endif // MySceneNodeAnimatorCallFunc_h__
