#include "StartScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"

void StartScene::Run() 
{

	/*if ( count++ > 200 )
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
	//u->OnAnimate(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime());
	/*v->OnAnimate(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime());
	v->DrawTree();*/
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	ITimer* timer = pEngine->GetDevice()->getTimer();

	u->LoadImage("pic1.jpg");
	v->LoadImage("pic1.jpg");

	/*TranslateUIAnimator* traani = new TranslateUIAnimator(
		timer->getRealTime(),
		3000,
		vector2d<s32>(300,0)); 
	u->AddAnimator(traani);
	traani->drop();*/

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

	AlphaChangeUIAnimator* alpani = new AlphaChangeUIAnimator(
		timer->getRealTime(),
		3000,
		u->GetAlpha(),
		0);
	u->AddAnimator(alpani);
	alpani->drop();

	uiManager->SetRoot(u);	
	uiManager->AddUINode(v,u);

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		//uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{

}

StartScene::StartScene() : count( 0 )
{
	u = new UIImage( NULL, MyIrrlichtEngine::GetEngine()->GetVideoDriver(), 500, 750, 0, vector2d<f32>(250, 375) );
	v = new UIImage( NULL, MyIrrlichtEngine::GetEngine()->GetVideoDriver(), 100, 150, 0, vector2d<f32>(-200, -300) ); 
	uiManager = new UIManager(MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer());
}


