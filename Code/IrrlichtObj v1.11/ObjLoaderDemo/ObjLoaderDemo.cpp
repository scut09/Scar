#include "../../include/irrlicht.h"
#include "WaterFloatingAnimator.h"



using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


#define WAVE_HEIGHT 1.0f
#define WAVE_SPEED 500.0f
#define WAVE_LENGTH 10.0f


int main()
{
	// Initialisation
	IrrlichtDevice * pDevice = createDevice( EDT_OPENGL );
	IVideoDriver * pVideo = pDevice->getVideoDriver();
	ISceneManager * pSM = pDevice->getSceneManager();

	// Water
	IAnimatedMesh * pWaterMesh = pSM->getMesh( "water.obj" );
	ISceneNode * pWaterNode = pSM->addWaterSurfaceSceneNode( pWaterMesh->getMesh( 0 ),
		WAVE_HEIGHT, WAVE_SPEED, WAVE_LENGTH );

	// Bottle
	IAnimatedMesh * pBottleMesh = pSM->getMesh( "1234.obj" );
	ISceneNode * pBottleNode = pSM->addAnimatedMeshSceneNode( pBottleMesh );
	// Add animator to make it look like its floating on water
	//ISceneNodeAnimator * pWaterFloatAnim =
	//	new WaterFloatingAnimator( 0.0f, WAVE_HEIGHT, WAVE_SPEED, WAVE_LENGTH );
	//pBottleNode->addAnimator( pWaterFloatAnim );
	//pWaterFloatAnim->drop();
	// Add animator to make it move forward
	//ISceneNodeAnimator * pMoveStraightAnim =
	//	pSM->createFlyStraightAnimator( vector3df(50,0,0), vector3df(-100, 0, 0), 60000 );
	//pBottleNode->addAnimator( pMoveStraightAnim );
	//pMoveStraightAnim->drop();

	// Lights
	SLight light;
	light.AmbientColor = SColor( 0, 255, 255, 255 );
	light.DiffuseColor = SColor( 0, 128, 128, 128 );
	light.SpecularColor = SColor( 0, 128, 128, 128 );
	ILightSceneNode * pLight = pSM->addLightSceneNode( 0, vector3df( -10, 200.0f, -100 ) );
	pLight->getLightData() = light;

	// Camera
	ICameraSceneNode * pCamera = pSM->addCameraSceneNodeFPS( 0, 100, 200 );
	pCamera->setPosition( vector3df( 40, 60, -60) );
	pCamera->setTarget( vector3df( 0, 0, 0 ) );

	// Main Loop
	while ( pDevice->run() )
	{
		pVideo->beginScene( true, true, SColor( 0, 64, 128, 255 ) );
		pSM->drawAll();
		pVideo->endScene();
	}
	pDevice->drop();

	return 0;
}