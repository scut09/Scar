#ifndef UIOBJECT_H
#define UIOBJECT_H

#include "def.h"
#include <math.h>
#include <vector>

using std::vector;
using namespace irr;
using namespace irr::core;
using namespace irr::video;

class UIObject;

//////////////////////////////////////////////////////////////////
//名称：UIObject
//描述：UI基类
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class UIObject
{
protected:

	vector2d<s32> DstQuar[4];		//显示区域矩形
	//int Width, Height;			
	//float RotDegree;
	vector2d<s32> RotCenter;		//旋转中心
	vector< shared_ptr<UIObject> > Children;	//子对象
	shared_ptr<UIObject> Parent;				//父对象
	ITexture * Image;					//应用于UI上的图片
	IVideoDriver * Driver;						//Driver指针

public:
	UIObject();
	UIObject( IVideoDriver * driver, vector2d<s32> pos, int width, int height );

	virtual ~UIObject() {}

	//设置UI图片
	void SetImage( char * );
	
	//绘制虚函数
	virtual void Draw() = 0;	
};


//////////////////////////////////////////////////////////////////
//名称：UIImage 
//描述：仅处理静态图片,继承UIObject
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
class UIImage : public UIObject
{
public:
	UIImage( IVideoDriver * driver, vector2d<s32> pos, int width, int height ) 
		: UIObject( driver, pos, width, height )
	{}
	void Draw();
};

#endif