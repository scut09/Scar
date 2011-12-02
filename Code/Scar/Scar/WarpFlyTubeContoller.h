//×÷Õß£º ÑîÐñè¤
#include "ISceneNode.h"
#include "MyIrrlichtEngine.h"
#include "WarpFlyAnimator.h"
#include "GeneralCallBack.h"

class WarpFlyTubeController
{
public:
	WarpFlyTubeController()
	{
		m_pSmgr = MyIrrlichtEngine::GetEngine()->GetSceneManager();
		m_pDriver = MyIrrlichtEngine::GetEngine()->GetVideoDriver();
		m_pNode = m_pSmgr->addMeshSceneNode( m_pSmgr->getMesh( "../media/UnitModel/cylinder.3ds" ) );
		m_pNode->setMaterialFlag( EMF_LIGHTING, false );
		m_pNode->setMaterialFlag( EMF_BACK_FACE_CULLING, false );
		m_pNode->setMaterialType( EMT_TRANSPARENT_ADD_COLOR );
		m_pNode->setMaterialTexture( 0, m_pDriver->getTexture( "../media/Space/shieldhardening.png" ) );
		m_pNode->setScale( vector3df( 10, 10, 300 ) );
		
		m_pCB= new WarpTubeCallBack();
		
		shader.ApplyShaderToSceneNode( m_pNode, m_pCB, "", "Shader/WarpTube.frag", EMT_TRANSPARENT_ADD_COLOR );
		m_pCB->drop();

		m_pNode->setRotation(vector3df(0.0f, 90.0f, 0.0f));
		WarpFlyAnimator* pwfani = new WarpFlyAnimator();
		m_pNode->addAnimator(pwfani);
		pwfani->drop();

		
	}
	IMeshSceneNode* GetMeshSceneNode(){ return m_pNode; }

	void BeginFadeIn(){ m_pCB->SetState(0); }

	void BeginFadeOut(){ m_pCB->SetState(2); }


	~WarpFlyTubeController(){ }


private:
	IMeshSceneNode* m_pNode;
	ISceneManager* m_pSmgr;
	irr::video::IVideoDriver* m_pDriver;
	WarpTubeCallBack* m_pCB;
	SceneNodeShader shader;
};