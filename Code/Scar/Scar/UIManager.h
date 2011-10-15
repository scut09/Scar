#ifndef UIManager_h__
#define UIManager_h__

#include <irrlicht.h>
#include "IUIObject.h"

using namespace irr;

class UIManager
{
public:
	UIManager( ITimer* timer ) : Timer(timer), Root(NULL), Focus(NULL), Over(NULL)
	{
		
	}
	bool SetRoot( IUIObject* root )
	{
		Root = root;
		return true;
	}
	//��ȡUI�����ڵ�
	IUIObject* GetRoot();
	//��UI���в���ڵ�
	bool AddUINode( IUIObject* node, IUIObject* parent )
	{
		parent->AddChild(node);
		//for( auto iter = parent->GetChildren().begin(); iter != parent->GetChildren().end(); ++iter )
		//{
		//	
		//}
		//for( auto iter = parent->GetAnimators().begin(); iter != parent->GetAnimators().end(); ++iter )
		//{
		//	node->AddAnimator( (*iter)->Clone() );		
		//}
		return true;
	}
	//��UI����ɾ���ڵ�,Ҳ��ɾ���ýڵ�����к���ڵ�
	bool RemoveUINode( IUIObject* node );
	//��ȡ����ǰ�������е�UIԪ��
	IUIObject* GetHitUIByPos(s32 x, s32 y);
	//����UI��
	void RunTree();
	//��Ϣ����
	void OnEvent( const SEvent& event );

	// ���м��
	IUIObject* HistTest( s32 x, s32 y );

private:
	IUIObject* Root;				//UI�����ڵ�
	IUIObject* Focus;			//�������UI�ڵ�
	IUIObject* Over;				//��ǰ��껬���ڵ�
	ITimer* Timer;				//Timer




};
#endif // UIManager_h__
