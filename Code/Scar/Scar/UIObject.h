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
//名称：UIAnima
//描述：实现UI的平移，旋转，缩放，Alpah改变等动画
//作者：屠文翔，杨成熙
//////////////////////////////////////////////////////////////////
//class UIAnima
//{
//public:
//	//动画播放结束后的操作
//	enum ANIMA_END_OPTION
//	{
//		STAY ,			//停留
//		DESTROY			//销毁宿主
//	};
//
//private:
//	UIObject* Host;	//宿主
//
//	u32 Interval;		//每两帧动画的间隔，毫秒
//	u32 Duration;		//动画总共的持续时间
//	u32 LastFrameTime;	//绘制上一帧时的时间
//	u32 NumOfFrame;		//总持续帧数
//	u32 CurrentFrame;	//当前帧数
//	u32 Loop;			//总循环次数，0为无限循环。
//	u32 CurrentLoop;	//当前循环次数
//	
//	ANIMA_END_OPTION EndOption;	//动画结束后动作
//
//	bool HasScale;				//是否加入缩放动画
//	bool HasRotate;				//是否加入旋转动画
//	bool HasTranslate;			//是否加入平移动画
//	vector2d<f32> RotCen;		//旋转中心点
//	vector2d<f32> StrCen;		//缩放中心点
//	float StepDeg;				//旋转角度步进值
//	vector2d<f32> StepStr;		//缩放比例步进值
//	vector2d<f32> StepTran;		//平移步进值	
//
//public:
//	UIAnima( UIObject* host, u32 duration = 30, u32 loop = 1,  ANIMA_END_OPTION opflag = STAY, u32 interval=30);
//	//设置动画信息
//	void SetUIAnima( u32 duration, u32 loop = 1, ANIMA_END_OPTION opflag = STAY, u32 interval=30);
//	//添加缩放动画
//	void AddScale( const vector2d<f32>& stretch, const vector2d<f32>& scalePoint );
//	//添加旋转动画
//	void AddRotate( float degree, const vector2d<f32>& rotatePoint );
//	//添加平移动画
//	void AddTranslate( const vector2d<f32>& offset );
//	//步进缩放
//	void Scale( const vector2d<f32>& stepstr, const vector2d<f32>& scalePoint );
//	//步进旋转
//	void Rotate( float stepdeg, const vector2d<f32>& rotatePoint );
//	//步进平移
//	void Translate( const vector2d<f32>& steptran );
//	//运行动画
//	void Run();
//
//};

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
	//vector< shared_ptr<UIObject> > Children;	//子对象
	//shared_ptr<UIObject> Parent;				//父对象
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
	UIImage( IVideoDriver * driver, const vector2d<f32>& pos, int width, int height ) 
		: UIObject( driver, pos, width, height )
	{}
	void Draw();
};

#endif