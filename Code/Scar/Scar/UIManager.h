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
		//root->grab();
		//if ( Root )
		//	Root->drop();
		Root = root;
		return true;
	}
	//��ȡUI�����ڵ�
	IUIObject* GetRoot();
	//��UI���в���ڵ�
	bool AddUINode( IUIObject* node, IUIObject* parent );
	//��UI����ɾ���ڵ�,Ҳ��ɾ���ýڵ�����к���ڵ�
	bool RemoveUINode( IUIObject* node )
	{
		return NULL;
	}

	//��ȡ����ǰ�������е�UIԪ��
	IUIObject* GetHitUIByPos(s32 x, s32 y)
	{
		return NULL;
	}

	//����UI��
	void RunTree();
	//��Ϣ����
	void OnEvent( const SEvent& event );
	//�����ϻ�ȡ�ض����ֵĽڵ�
	IUIObject* GetObjectByName( const std::string& name, IUIObject* node = 0 );

	// ���м��
	IUIObject* HistTest( s32 x, s32 y )
	{
		return NULL;
	}

private:
	IUIObject*	Root;				//UI�����ڵ�
	IUIObject*	Focus;				//�������UI�ڵ�
	IUIObject*	Over;				//��ǰ��껬���ڵ�
	ITimer*		Timer;				//Timer




};
#endif // UIManager_h__
