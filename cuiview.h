#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h" // For Cocos Studio 控制項元件
#include "cocostudio/CocoStudio.h"
#include "Common/CSwitchButton.h"
#include "Common/CDraggableSprite.h"
#include "CParticleSystem.h"

class CUIView
{
private:
	// 建立控制 particle system 所需的操作介面
	cocos2d::Node* _uiRoot;
	cocos2d::Scene* _stage;
	cocos2d::Size _size; //開啟的視窗大小

	// 分子的可提整不同參數的顯示
	cocos2d::ui::TextBMFont* _GravityBMValue;
	cocos2d::ui::TextBMFont* _SpreadBMValue;
	cocos2d::ui::TextBMFont* _DirectionBMValue;
	cocos2d::ui::TextBMFont* _SpeedBMValue;
	cocos2d::ui::TextBMFont* _LifetimeBMValue;
	cocos2d::ui::TextBMFont* _RedBMValue;
	cocos2d::ui::TextBMFont* _BlueBMValue;
	cocos2d::ui::TextBMFont* _GreenBMValue; 
	cocos2d::ui::TextBMFont* _OpacityBMValue;
	cocos2d::ui::TextBMFont* _ParticlesBMValue;
	cocos2d::ui::TextBMFont* _TextureBMValue;
	cocos2d::ui::TextBMFont* _SpinBMValue;
	cocos2d::ui::TextBMFont* _WindBMValue;
	cocos2d::ui::TextBMFont* _SizeBMValue;
	// 選擇不同的分子型態，用在 Emitter 沒有開啟的狀態
	cocos2d::ui::TextBMFont* _TypeBMValue;

	// For Emitter
	CDraggableSprite* _EmitterSprite;
	CSwitchButton* _emitterSwitchBtn;
	bool _bEmitterOn;

	//Emitter 1-3
	CDraggableSprite* _EmitterSprite01;
	CSwitchButton* _emitterSwitchBtn01;
	bool _bEmitterOn01;
	CDraggableSprite* _EmitterSprite02;
	CSwitchButton* _emitterSwitchBtn02;
	bool _bEmitterOn02;
	CDraggableSprite* _EmitterSprite03;
	CSwitchButton* _emitterSwitchBtn03;
	bool _bEmitterOn03;

	// 指向 Particle System 的指標物件
	CParticleSystem* _ParticleControl;
	//
	cocos2d::ui::Button* _btn_cloud;
	cocos2d::ui::Button* _btn_flare;
	cocos2d::ui::Button* _btn_bubble;
	cocos2d::ui::Button* _btn_circle;
	cocos2d::ui::Button* _btn_comet;
	cocos2d::ui::Button* _btn_raindrop;
	//
	cocos2d::ui::Button* _btn_rotateSwitch;
	//
	cocos2d::ui::Button* _btn_textureSwitch;
	//
	cocos2d::ui::Button* _btn_emitter01;
	cocos2d::ui::Button* _btn_emitter02;
	cocos2d::ui::Button* _btn_emitter03;

	int countRotate = 0;
	int countRandomTexture = 0;
public:
	CUIView();

	void setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage);
	void setModel(CParticleSystem &model);
	void init();

	// 定義 Callback function
	void GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void SizeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	void BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	
	void TextureEvent_cloud(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void TextureEvent_flare(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void TextureEvent_bubble(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void TextureEvent_circle(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void TextureEvent_comet(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void TextureEvent_raindrop(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void RotateEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void RandomTextureEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	void TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
	//
	/*void Emitter01(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);*/

	// touch 事件
	void onTouchBegan(const cocos2d::Point& tPoint);
	void onTouchMoved(const cocos2d::Point& tPoint); //觸碰移動事件
	void onTouchEnded(const cocos2d::Point& tPoint); //觸碰結束事件 

};