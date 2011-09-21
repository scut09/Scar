#include "InitUI.h"

ITexture* CInitUI::m_image = NULL;

IrrlichtDevice*		IMyUIScene::m_device = NULL;
IGUIEnvironment*	IMyUIScene::m_guienv = NULL;	// 设备对象
IVideoDriver*		IMyUIScene::m_driver = NULL;	
ISceneManager*		IMyUIScene::m_smgr = NULL;
CMyEventReceiver*	IMyUIScene::m_event = NULL;
IMyUIScene**		IMyUIScene::m_CurrentUI = NULL;

GameLogic::IClient*		IMyUIScene::m_client = NULL;
GameLogic::IServer*		IMyUIScene::m_server = NULL;

std::string	IMyUIScene::m_Myname = "";	//玩家名字
std::string	IMyUIScene::m_carPath = "";	//玩家选择的车子的路径


#define BTN_OK		2
#define BTN_CANCEL	3

CInitUI::CInitUI(void)
{
	m_CarmeraY = 20;
	m_rotY = 0;	
	m_currentCount = 0;
}

CInitUI::~CInitUI(void)
{
}

void CInitUI::Release()
{	
	m_guienv->clear();
}

void CInitUI::DoInput()
{	
	int id = m_event->GetBtnDownID();
	if (id != -1)
	{
		switch(id)
		{		
		case BTN_OK:
			{
				char* buffer = CHelper::wchar_to_char(m_tbName->getText());
				IMyUIScene::m_Myname = buffer;				
				delete[] buffer;

				this->Release();
				m_next->InitUI();				
				*m_CurrentUI = m_next;
				break;
			}
		case BTN_CANCEL:
			{
				ExitProcess(0);		//退出游戏
				break;
			}
		}
	}
}

void CInitUI::Updata()
{
	DoInput();
}

void CInitUI::InitUI()
{
	m_guienv->addImage(m_driver->getTexture("image\\box.jpg"), core::position2d<s32>(0,0));
	/*m_guienv->addStaticText(
		L"Explain: \nmouse: right button to move.\n           left button to select.\n1,2,3,4 to discharge skill",
		core::rect<s32>(30,30,550,120), false, true, 0, -1);

	m_guienv->addStaticText(
		L"A:attack\nZ:move\nS:stop",
		core::rect<s32>(30,120,550,690), false, true, 0, -1);*/
	
	m_guienv->addStaticText(
		L"Input your name:",
		core::rect<s32>(320,607,450,630), false, true, 0, -1);
	m_tbName = m_guienv->addEditBox(L"Name", core::rect<s32>(460,610,600,630));	
	m_tbName->setMax(20);

	AddBtn(350,700,L"OK",BTN_OK);
	AddBtn(550,700,L"Canel",BTN_CANCEL);



}