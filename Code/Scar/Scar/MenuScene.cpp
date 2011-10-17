#include "MenuScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"

void MenuScene::Run()
{
	//std::cout<< "fuck" << std::endl;
}

void MenuScene::Init()
{
	uiManager = new UIManager(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer());

	try
	{
		using namespace boost::python;

		object UILoader = import( "MainMenuIni" );
		object GetRoot = UILoader.attr( "GetRoot" );
		object root = GetRoot();

		IUIObject* r = extract<IUIObject*>( root ); 
		uiManager->SetRoot( r );
		//r->drop();	// 使用Python对象不用内存管理
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void MenuScene::Release()
{
	delete uiManager;

	// 清除掉自己注册的回调函数，否则会因为引用销毁的东西而导致崩溃
	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		return 0;
	} );

	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
		object DeleteTree = UILoader.attr( "DeleteTree" );
		DeleteTree();
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void MenuScene::Draw()
{
	uiManager->RunTree();
}
