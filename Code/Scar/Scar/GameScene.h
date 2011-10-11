/********************************************************************
    ����ʱ��: 2011-10-8   15:51
    �ļ���:   GameScene.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ��������

*********************************************************************/

#ifndef GameScene_h__
#define GameScene_h__


class GameScene
{
public:
	virtual ~GameScene() {}

	virtual void Run() = 0;
	virtual void Init() = 0;
	virtual void Release() = 0;
	
};


#endif // GameScene_h__
