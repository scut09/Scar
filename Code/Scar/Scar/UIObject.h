#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "def.h"
#include <math.h>
#include "IUIObject.h"

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class UIObject;
class UIAnima;

//////////////////////////////////////////////////////////////////
//名称：UIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class UIObject : public IUIObject
{
	
	public:
	vector2d<f32> DstQuar[4];					//显示区域矩形
	vector2d<f32> Center;						//矩形的中心点
	ITexture * Image;							//应用于UI上的图片
	IVideoDriver * Driver;						//Driver指针
	int Alpha;									//元件透明度
	
public:
	UIObject();
	UIObject( IVideoDriver * driver, const vector2d<f32>& pos, int width, int height );
	virtual ~UIObject() {}

	//shared_ptr<UIAnima> Animations;				//动画变换

	//加载UI图片
	void SetImage( char * );
	//以中心点为基准设置元件位置
	void SetCenter( const vector2d<f32>& pos );
	//获取元件中心点位置
	const vector2d<f32>& GetCenter() const;
		
	
};


//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：静态图片或动画,继承UIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class UIImage : public UIObject
{
public:
	UIImage( IVideoDriver * driver, const vector2d<f32>& pos, int width, int height ) 
		: UIObject( driver, pos, width, height )
	{}
	void Draw();
};

#endif