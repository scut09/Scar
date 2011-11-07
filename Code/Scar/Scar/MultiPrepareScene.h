#ifndef MultiPrepare_h__
#define MultiPrepare_h__

/********************************************************************
	��������:	2011/11/06
	�ļ���: 	C:\Users\Administrator\Desktop\����\SCAR��Ŀ��\opengl-scut\Code\Scar\Scar\MultiPrepare.h
	����:		������
	
	����:		������Ϸ׼������
				ѡ��ɴ���������װ��
*********************************************************************/

#include "GameScene.h"
#include "MyIrrlichtEngine.h"

class MultiPrepareScene : public GameScene
{
	scene::ICameraSceneNode*	m_pCamera;
	scene::ISceneNode*			m_pSkyBox;

public:
	MultiPrepareScene() : m_pCamera( 0 )
	{
	}

	~MultiPrepareScene()
	{
		Release();
	}

	virtual void Run();

	virtual void Init();

	virtual void Release();

	virtual void Draw();

};

#endif // MultiPrepare_h__
