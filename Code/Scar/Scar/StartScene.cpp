#include "StartScene.h"
#include "def.h"
#include "UIAnimators.h"
#include "UIManager.h"
#include "MyIrrlichtEngine.h"
#include "EventListener.h"

void StartScene::Run() 
{
	//v.OnAnimate( MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime() );
	/*if ( count++ > 200 )
	{
		count = 0;
		u.RemoveAnimators();
	}*/


	if ( count++ > 200 )
	{
		count = 0;
		pEngine->currentScene = multiplayerScene;
		Release();
		pEngine->currentScene->Init();
	}

	//u.SetCenter( vector2d<s32>( count, count ) );

}

void StartScene::Draw()
{	
	u->OnAnimate( MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime() );

//	u.Animations->Run();
	u->DrawTree();
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	ITimer* timer = pEngine->GetDevice()->getTimer();

	u->SetImage("pic1.jpg");
	v->SetImage("pic1.jpg");
	u->AddChild( v );
	
	AlphaChangeUIAnimator* ani = new AlphaChangeUIAnimator( 
		timer->getRealTime(),
		5000,
		u->GetAlpha(),
		0);
	u->AddAnimator(ani);
	ani->drop();

	DeletionAnimator* delAni = new DeletionAnimator( timer->getRealTime(), 500 );
	v->AddAnimator( delAni );
	delAni->drop();

	

	static_cast<MyEventReceiver*>( MyIrrlichtEngine::pEventReceiver )->SetEventCallbackFunc( [this]( const SEvent& event )->void*
	{	
		uiManager.OnEvent( event );
		//control.OnEvent( event );
		//pEngine;		// ÒıÇæÖ¸Õë
		//std::cout << "\n" << event.MouseInput.X << ' ' << event.MouseInput.Y << std::endl;
		return 0;
	} );
}

void StartScene::Release() 
{


}


