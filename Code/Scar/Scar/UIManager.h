#ifndef UIManager_h__
#define UIManager_h__

#include <irrlicht.h>
#include "UIObject.h"

using namespace irr;

class UIManager
{
public:
	UIManager( ITimer* timer ) : Timer(timer), Root(NULL), Focus(NULL), Over(NULL)
	{
		
	}
	bool SetRoot( UIObject* root )
	{
		Root = root;
		return true;
	}
	//��ȡUI�����ڵ�
	UIObject* GetRoot()
	{
		return Root;
	}
	//��UI���в���ڵ�
	bool AddUINode( UIObject* node, const vector2d<s32>& pos, const vector2d<f32>& scalefactor,
					UIObject* parent, s32 order = 0 );
	//��UI����ɾ���ڵ�,Ҳ��ɾ���ýڵ�����к���ڵ�
	bool RemoveUINode( UIObject* node );
	//��ȡ����ǰ�������е�UIԪ��
	UIObject* GetHitUIByPos(s32 x, s32 y);
	//����UI��
	void RunTree()
	{
		Root->OnAnimate(Timer->getRealTime());
		Root->DrawTree();
	}
	//��Ϣ����
	void OnEvent( const SEvent& event );

private:
	UIObject* Root;				//UI�����ڵ�
	UIObject* Focus;			//�������UI�ڵ�
	UIObject* Over;				//��ǰ��껬���ڵ�
	ITimer* Timer;				//Timer




};
#endif // UIManager_h__
