#include "MenuScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"

void MenuScene::Run()
{
	//std::cout<< "fuck" << std::endl;
	if ( IsFirstRun )
	{
		IsFirstRun = false;

		try
		{
			using namespace boost::python;

			object UILoader = import( SceneName.c_str() );
			object LoadStartAnimation = UILoader.attr( "LoadStartAnimation" );
			IUIObject* root = uiManager->GetRoot();
			LoadStartAnimation( boost::ref( root ) );

			//r->drop();	// 使用Python对象不用内存管理
		}
		catch ( ... )
		{
			PyErr_Print();
		}

	}
}

void MenuScene::Init()
{
	std::cout << "===> " << this->SceneName << " construction" << std::endl;

	uiManager = new UIManager(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer());

	try
	{
		using namespace boost::python;

		object UILoader = import( SceneName.c_str() );
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

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		uiManager->OnEvent( event );
		return 0;
	} );
}

void MenuScene::Release()
{
	std::cout << "===> " << this->SceneName << " destruction" << std::endl;

	delete uiManager;
	//uiManager = NULL;

	//try
	//{
	//	using namespace boost::python;

	//	object UILoader = import( "UILoader" );
	//	object DeleteTree = UILoader.attr( "DeleteTree" );
	//	DeleteTree();
	//}
	//catch ( ... )
	//{
	//	PyErr_Print();
	//}
}

void MenuScene::Draw()
{
	if ( uiManager )
		uiManager->RunTree();
}
