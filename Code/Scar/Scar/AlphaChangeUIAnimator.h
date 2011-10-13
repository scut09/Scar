#ifndef AlphaChangeUIAnimator_h__
#define AlphaChangeUIAnimator_h__

#include "IUIAnimator.h"
using namespace irr::core;

class AlphaChangeUIAnimator;

//////////////////////////////////////////////////////////////////
//���ƣ�AlphaChangeUIAnimator
//������alphaֵ�޸Ķ���
//���ߣ������裬�����
//////////////////////////////////////////////////////////////////
class AlphaChangeUIAnimator : public IUIAnimator
{
private:
	u32 Begin;
	u32 Duration;
	u32 LastTime;
	unsigned int SrcAlpha;
	unsigned int TarAlpha;
	f32 AlphaFactor;
	bool Loop;

public:
	AlphaChangeUIAnimator( u32 begin, u32 duration, unsigned int srcalpha,
		unsigned int taralpha, bool loop = false );

	virtual bool animateUIObject( IUIObject* node, u32 timeMS );

	virtual AlphaChangeUIAnimator* Clone();
};

#endif // AlphaChangeUIAnimator_h__