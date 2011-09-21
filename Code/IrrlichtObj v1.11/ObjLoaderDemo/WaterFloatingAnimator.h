#ifndef WATER_FLOATING_ANIMATOR_H
#define WATER_FLOATING_ANIMATOR_H


#include "../../include/irrlicht.h"


using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


#define RAD2DEG (f32) 57.29578


class WaterFloatingAnimator : public ISceneNodeAnimator
{
private:
	f32 sceneNodeHeight_, waveHeight_, waveSpeed_, oneOverWaveLength_;

public:
	WaterFloatingAnimator( f32 sceneNodeHeight, f32 waveHeight, f32 waveSpeed, f32 waveLength ) :
		sceneNodeHeight_( sceneNodeHeight ), waveHeight_( waveHeight ),
		waveSpeed_( waveSpeed ), oneOverWaveLength_( 1.0f / waveLength ) {}

	virtual void animateNode( ISceneNode * pSceneNode, u32 timeMs )
	{
		f32 cyclePhase = timeMs / waveSpeed_;
		vector3df nodePos = pSceneNode->getPosition();

		// rotation
		vector3df rotation = vector3df( 0, 0, 0 );
		// partial derivative of scene node animator's equation with respect to X axis
		rotation.X = (f32)  cos( nodePos.X * oneOverWaveLength_ + cyclePhase ) * oneOverWaveLength_ * RAD2DEG;
		// partial derivative of scene node animator's equation with respect to Z axis
		rotation.Z = (f32) -sin( nodePos.Z * oneOverWaveLength_ + cyclePhase ) * oneOverWaveLength_ * RAD2DEG;
		// Note: no rotation about Y axis
		pSceneNode->setRotation( rotation );

		// displacement (only along Y axis to simulate up-down motion)
		nodePos.Y = sceneNodeHeight_ +
			( (f32) sin( ( ( nodePos.X * oneOverWaveLength_ ) + cyclePhase ) ) * waveHeight_ ) + 
			( (f32) cos( ( ( nodePos.Z * oneOverWaveLength_ ) + cyclePhase ) ) * waveHeight_ );
		pSceneNode->setPosition( nodePos );
	}
};


#endif