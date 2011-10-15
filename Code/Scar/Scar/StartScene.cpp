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
	/*u->OnAnimate( MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime() );
	u->DrawTree();*/
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	ITimer* timer = pEngine->GetDevice()->getTimer();

	u->SetImage("pic1.jpg");
	v->SetImage("pic1.jpg");

	/*TranslateUIAnimator* traani = new TranslateUIAnimator(
		timer->getRealTime(),
		2000,
		vector2d<s32>(300,0)); 
	u->AddAnimator(traani);
	traani->drop();*/

	RotateUIAnimator* rotani2 = new RotateUIAnimator(
		timer->getRealTime(),
		3000,
		360,
		u->GetCenter(),
		u->GetCenter(),
		false);
	u->AddAnimator(rotani2);
	rotani2->drop();

	RotateUIAnimator* rotani = new RotateUIAnimator(
	timer->getRealTime(),
	3000,
	360,
	v->GetCenter(),
	v->GetCenter(),
	false);
	v->AddAnimator(rotani);
	rotani->drop();

	/*ScaleUIAnimator* scaani = new ScaleUIAnimator(
		timer->getRealTime(),
		3000,
		vector2d<f32>(2,1),
		v->DstQuar[0]-vector2d<f32>( 80,80 ),
		v->GetCenter()
		);
	v->AddAnimator(scaani);
	scaani->drop();*/

	

	uiManager->SetRoot(u);	
	uiManager->AddUINode(v,u);

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{


}


