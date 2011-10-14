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

}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	ITimer* timer = pEngine->GetDevice()->getTimer();

	u->SetImage("pic1.jpg");
	v->SetImage("pic1.jpg");

	/*AlphaChangeUIAnimator* ani = new AlphaChangeUIAnimator( 
		timer->getRealTime(),
		5000,
		u->GetAlpha(),
		0);
	u->AddAnimator(ani);
	ani->drop();*/

	RotateUIAnimator* rotani = new RotateUIAnimator(
	timer->getRealTime(),
	3000,
	360,
	v->DstQuar[0],
	v->GetCenter(),
	false);
	v->AddAnimator(rotani);
	rotani->drop();

	TranslateUIAnimator* traani = new TranslateUIAnimator(
		timer->getRealTime(),
		3000,
		vector2d<s32>(1500,0));
	v->AddAnimator(traani);
	traani->drop();

	uiManager->SetRoot(v);	
	//uiManager->AddUINode(v,u);

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{


}


