#include "StartScene.h"
#include "def.h"
#include "UIAnimators.h"

void StartScene::Run() 
{
	u.OnAnimate( MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime() );
	//v.OnAnimate( MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getRealTime() );
	/*if ( count++ > 200 )
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
	}*/

	//u.SetCenter( vector2d<s32>( count, count ) );

}

void StartScene::Draw()
{	
//	u.Animations->Run();
	u.DrawTree();
}

void StartScene::Init() 
{
	pEngine = MyIrrlichtEngine::GetEngine();
	driver = pEngine->GetVideoDriver();
	ITimer* timer = pEngine->GetDevice()->getTimer();

	u.SetImage("pic1.jpg");
	v.SetImage("pic1.jpg");
	u.AddChild(&v);
	
	RotateUIAnimator* ani = new RotateUIAnimator( 
		timer->getRealTime(),
		1000, 
		90,
		u.GetCenter()
		);
	u.AddAnimator(ani);
	ani->drop();

	
}

void StartScene::Release() 
{


}


