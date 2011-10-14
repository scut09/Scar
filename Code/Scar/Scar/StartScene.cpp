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
	//u->AddChild( v );
	
	/*AlphaChangeUIAnimator* ani = new AlphaChangeUIAnimator( 
		timer->getRealTime(),
		5000,
		u->GetAlpha(),
		0);
	u->AddAnimator(ani);
	ani->drop();*/

	TranslateUIAnimator* traani = new TranslateUIAnimator(
		timer->getRealTime(),
		2000,
		vector2d<s32>(300,0));
	u->AddAnimator(traani);
	traani->drop();

	uiManager->SetRoot(u);	

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{


}


