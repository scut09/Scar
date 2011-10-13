#include "StartScene.h"
#include "def.h"
#include "UIAnimators.h"

void StartScene::Run() 
{
	u.OnAnimate( MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime() );

	if ( count++ > 200 )
	{
		count = 0;
		u.RemoveAnimators();
	}
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
//	u.Animations->Run();
	u.Draw();
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();

	u.SetImage("pic1.jpg");
	auto timer = pEngine->GetDevice()->getTimer();
	auto ani = new RotateUIAnimator( 
		timer->getTime(),
		1000, 
		90,
		u.GetCenter()
		);
	u.AddAnimator(ani);
	ani->drop();
	//u.Animations->SetUIAnima(1500, 1, UIAnima::STAY, 30);
	//u.Animations->AddRotate(60,u.GetCenter());
}

void StartScene::Release() 
{


}


