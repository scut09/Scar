/********************************************************************
    ����ʱ��: 2011-10-8   15:51
    �ļ���:   GameScene.h
    ����:     ���� Cedric Porter [ Stupid ET ]	
    ˵��:     ��������

*********************************************************************/

#ifndef GameScene_h__
#define GameScene_h__

#include <vector>
#include <string>

/*
** ���֣�GameScene
** ˵����������Ϸ�����ĳ������
**		 ����Ϸ�������ѭ���У�
**
*/
class GameScene
{
public:
	GameScene() : Scenes( 20, 0 ) {}

	virtual ~GameScene() {}

	std::vector<GameScene*> Scenes;

	std::string	Name;

	const std::string& GetName() const
	{
		return Name;
	}

	void SetName( const std::string& name )
	{
		Name = name;
	}

	//************************************
	// ������:  GameScene::Run
	// ����ֵ:  void
	// ��������:
	// ������   ����Ϸ��ѭ���У�ÿ�ζ��ᱻ���õ�
	//************************************
	virtual void Run() = 0;

	//************************************
	// ������:  GameScene::Init
	// ����ֵ:  void
	// ��������:
	// ������   ��ʼ�������������������Դ
	//************************************
	virtual void Init() = 0;

	//************************************
	// ������:  GameScene::Release
	// ����ֵ:  void
	// ��������:
	// ������   �ͷ�������������ص���Դ
	//************************************
	virtual void Release() = 0;

	virtual void Draw() {}
	
};


#endif // GameScene_h__
