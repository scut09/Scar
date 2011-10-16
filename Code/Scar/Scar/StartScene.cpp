#include "StartScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"

void StartScene::Run() 
{

	/*if ( count++ > 3000 )
	{
		count = 0;
		pEngine->currentScene = multiplayerScene;
		Release();
		pEngine->currentScene->Init();
	}*/
	
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
		root = GetRoot();
		//root.ptr()->ob_refcnt++;		// 增加引用计数

		IUIObject* r = extract<IUIObject*>( root ); 
		uiManager->SetRoot( r );
		//r->drop();	// 使用Python对象不用内存管理
	}
	catch ( ... )
	{
		PyErr_Print();
	}


	u = new UIImage( NULL, 500, 750, 0, vector2d<f32>(250, 375) );
	v = new UIImage( NULL, 100, 150, 0, vector2d<f32>(-200, -300) ); 
	bt = new UIButton( NULL, 0, 0 );

	u->LoadImage("pic1.jpg");
	v->LoadImage("pic1.jpg");

	TranslateUIAnimator* traani = new TranslateUIAnimator(
		timer->getRealTime(),
		3000,
		vector2d<s32>(300,0)); 
	u->AddAnimator(traani);
	traani->drop();

	RotateUIAnimator* rotani = new RotateUIAnimator(
		timer->getRealTime(),
		3000,
		360,
		true);
	v->AddAnimator(rotani);
	rotani->drop();

	RotateUIAnimator* rotani2 = new RotateUIAnimator(
		timer->getRealTime(),
		3000,
		360,
		true);
	u->AddAnimator(rotani2);
	rotani2->drop();

	ScaleUIAnimator* scaani = new ScaleUIAnimator(
		timer->getRealTime(),
		3000,
		vector2d<f32>(.5f,.5f)
		);
	u->AddAnimator(scaani);
	scaani->drop();

	//AlphaChangeUIAnimator* alpani = new AlphaChangeUIAnimator(
	//	timer->getRealTime(),
	//	3000,
	//	u->GetAlpha(),
	//	0);
	//u->AddAnimator(alpani);
	//alpani->drop();

	uiManager->SetRoot( u );	
	uiManager->AddUINode( v, u );
	uiManager->AddUINode( bt, u );

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		//std::cout<< u->GetAbsoluteTransformation() <<std::endl;
		/*std::cout<< event.MouseInput.X << " , " << event.MouseInput.Y <<std::endl;
		std::cout<< u->IsPointIn( event.MouseInput.X, event.MouseInput.Y ) <<std::endl;
		std::cout << std::endl;*/
		uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{
	//v->drop();
	//uiManager->GetRoot()->drop();	// 使用Python传回的不用Delete

	delete uiManager;

	try
	{
		using namespace boost::python;

		object UILoader = import( "UILoader" );
		object DeleteTree = UILoader.attr( "DeleteTree" );
		DeleteTree();
		root = object();
	}
	catch ( ... )
	{
		PyErr_Print();
	}
}

StartScene::StartScene() : count( 0 )
{
	
}


