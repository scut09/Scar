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
	UIObject* GetRoot();
	//��UI���в���ڵ�
	bool AddUINode( UIObject* node, UIObject* parent, s32 order = 0 )
	{
		parent->AddChild(node);
		//for( auto iter = parent->GetChildren())
		for( auto iter = parent->GetAnimators().begin(); iter != parent->GetAnimators().end(); ++iter )
		{
			node->AddAnimator( (*iter)->Clone() );		
		}
		/*vector2d<f32> offset = pos - node->Center;
		for(int i=0; i<4; i++)
		node->DstQuar[i] += offset;*/
		return true;
	}
	//��UI����ɾ���ڵ�,Ҳ��ɾ���ýڵ�����к���ڵ�
	bool RemoveUINode( UIObject* node );
	//��ȡ����ǰ�������е�UIԪ��
	UIObject* GetHitUIByPos(s32 x, s32 y);
	//����UI��
	void RunTree();
	//��Ϣ����
	void OnEvent( const SEvent& event );

private:
	UIObject* Root;				//UI�����ڵ�
	UIObject* Focus;			//�������UI�ڵ�
	UIObject* Over;				//��ǰ��껬���ڵ�
	ITimer* Timer;				//Timer




};
#endif // UIManager_h__
