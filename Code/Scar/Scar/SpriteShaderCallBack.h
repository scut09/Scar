#ifndef SpriteShaderCallBack_h__
#define SpriteShaderCallBack_h__

/********************************************************************
	����ʱ��:	2011/12/04
	�ļ�����: 	SpriteShaderCallBack
	����:		������ - Kid
	
	����:		����֡ͼƬ���ϳ�һ��ͼƬʱ��ʹ�øûص��������Ƶ�ǰ���Ƶ��к��к�
				ר��Ƭ��ѡ������
				ʹ��SpriteControlAnimatorl������
*********************************************************************/

#include "SceneNodeShader.h"

//�к��еĽṹ��
struct SpriteRowCol
{
	f32 col;	//��
	f32 row;	//��
};

class SpriteShaderCallBack : public irr::video::IShaderConstantSetCallBack
{
	SpriteRowCol* RowCol;
	f32 TotalCol;
	f32 TotalRow;

public:
	SpriteShaderCallBack( SpriteRowCol* rowCol, f32 totalCol, f32 totalRow )
	{
		TotalCol = totalCol;
		TotalRow = totalRow;
		RowCol = rowCol;
	}

private:
	virtual void OnSetConstants( IMaterialRendererServices* services, s32 userData ) 
	{
		//IVideoDriver* driver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		//ISceneManager* smgr = MyIrrlichtEngine::GetEngine()->GetDevice()->getSceneManager();

		//����, ���֧����������
		int d[]   = {0, 1, 2, 3};      //Sampler2d IDs
		services->setPixelShaderConstant("TextureL0",(float*)&d[0],1);
		/*services->setPixelShaderConstant("TextureL1",(float*)&d[1],1);
		services->setPixelShaderConstant("TextureL2",(float*)&d[2],1);
		services->setPixelShaderConstant("TextureL3",(float*)&d[3],1);*/

		//����
		services->setVertexShaderConstant( "Col", (f32*)&RowCol->col, 1);
		services->setVertexShaderConstant( "Row", (f32*)&RowCol->row, 1);
		services->setVertexShaderConstant( "TotalCol", (f32*)&TotalCol, 1);
		services->setVertexShaderConstant( "TotalRow", (f32*)&TotalRow, 1);

		//ʱ��
		/*f32 timeMs = (f32)MyIrrlichtEngine::GetEngine()->GetDevice()->getTimer()->getTime();
		services->setVertexShaderConstant( "TimeMs", (f32*)&timeMs, 1);*/
	}
};

#endif // SpriteShaderCallBack_h__
