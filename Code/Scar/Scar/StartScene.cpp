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

	u->SetImage("pic1.jpg");
	v->SetImage("pic1.jpg");

	TranslateUIAnimator* traani = new TranslateUIAnimator(
		timer->getRealTime(),
		2000,
		vector2d<s32>(300,0)); 
	u->AddAnimator(traani);
	traani->drop();

	/*BlinkUIAnimator* in1 = new BlinkUIAnimator( vector2d<f32>(-250, -375));
	u->AddAnimator(in1);
	in1->drop();*/

	/*BlinkUIAnimator* in2 = new BlinkUIAnimator( vector2d<f32>(-50,-75));
	v->AddAnimator(in2);
	in2->drop();*/

	RotateUIAnimator* rotani = new RotateUIAnimator(
	timer->getRealTime(),
	3000,
	360,
	v->GetCenter(),
	true);
	v->AddAnimator(rotani);
	rotani->drop();

	/*BlinkUIAnimator* out2 = new BlinkUIAnimator( vector2d<f32>(50,75));
	v->AddAnimator(out2);
	out2->drop();*/

	/*RotateUIAnimator* rotani2 = new RotateUIAnimator(
	timer->getRealTime(),
	3000,
	360,
	u->GetCenter(),
	true);
	u->AddAnimator(rotani2);
	rotani2->drop();*/
	
	/*BlinkUIAnimator* out1 = new BlinkUIAnimator( vector2d<f32>(250, 375));
	u->AddAnimator(out1);
	out1->drop();*/

	

	
	
	

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
		//uiManager->OnEvent( event );
		return 0;
	} );
}

void StartScene::Release() 
{


}


