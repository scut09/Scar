#include "StartScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"

void StartScene::Run() 
{
	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
		object StartSceneRun = UILoader.attr( "StartSceneRun" );
		StartSceneRun();
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

void StartScene::Draw()
{	
	uiManager->RunTree();
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	ITimer* timer = pEngine->GetDevice()->getTimer();

	uiManager = new UIManager(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer());

	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
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


	//u = new UIImage( NULL, 500, 750, 0, vector2d<f32>(250, 375) );
	//v = new UIImage( NULL, 100, 150, 0, vector2d<f32>(-200, -300) ); 
	//bt = new UIButton( NULL, 0, 0 );

	//u->LoadImage("pic1.jpg");
	//v->LoadImage("pic1.jpg");

	//TranslateUIAnimator* traani = new TranslateUIAnimator(
	//	timer->getRealTime(),
	//	3000,
	//	vector2d<s32>(300,0)); 
	//u->AddAnimator(traani);
	//traani->drop();

	//RotateUIAnimator* rotani = new RotateUIAnimator(
	//	timer->getRealTime(),
	//	3000,
	//	360,
	//	true);
	//v->AddAnimator(rotani);
	//rotani->drop();

	//RotateUIAnimator* rotani2 = new RotateUIAnimator(
	//	timer->getRealTime(),
	//	3000,
	//	360,
	//	true);
	//u->AddAnimator(rotani2);
	//rotani2->drop();

	//ScaleUIAnimator* scaani = new ScaleUIAnimator(
	//	timer->getRealTime(),
	//	3000,
	//	vector2d<f32>(.5f,.5f)
	//	);
	//u->AddAnimator(scaani);
	//scaani->drop();

	////AlphaChangeUIAnimator* alpani = new AlphaChangeUIAnimator(
	////	timer->getRealTime(),
	////	3000,
	////	u->GetAlpha(),
	////	0);
	////u->AddAnimator(alpani);
	////alpani->drop();

	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{
	//v->drop();
	//uiManager->GetRoot()->drop();	// 使用Python传回的不用Delete

	delete uiManager;

	// 清除掉自己注册的回调函数，否则会因为引用销毁的东西而导致崩溃
	dynamic_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
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

StartScene::StartScene() : count( 0 )
{
	
}


