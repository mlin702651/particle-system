#include "cuiview.h"

using namespace cocos2d::ui;

USING_NS_CC;

extern cocos2d::Size fSize;

CUIView::CUIView()
{
	_uiRoot = nullptr;
    _stage = nullptr;
    _ParticleControl = nullptr;
    _GravityBMValue = nullptr;
    _SpreadBMValue = nullptr;
    _DirectionBMValue = nullptr;
    _TypeBMValue = nullptr;
    _LifetimeBMValue = nullptr;
    _EmitterSprite = nullptr;
    _emitterSwitchBtn = nullptr;
    _bEmitterOn = false;
    _bEmitterOn01 = false;
}

void CUIView::setModel(CParticleSystem& model)
{
    _ParticleControl = &model;
    _ParticleControl->init(*_stage);
    _ParticleControl->_emitterPt = _EmitterSprite->getLoc();

    _ParticleControl->_emitterPt01 = _EmitterSprite01->getLoc();
    _ParticleControl->_emitterPt02 = _EmitterSprite02->getLoc();
    _ParticleControl->_emitterPt03 = _EmitterSprite03->getLoc();

    _ParticleControl->_fDir = 90.0;
    _ParticleControl->_iNumParticles = 100;
    _ParticleControl->_iGenParticles = 0;
    _ParticleControl->_fSpread = 180.0f;
    _ParticleControl->_fVelocity = 2.5;	 // 分子的離開速度 用Speed控制
    _ParticleControl->_fLifeTime = 3.5f;	 // 分子的存活時間
    _ParticleControl->_fSpin = 0;
    _ParticleControl->_fGravity = 0;
    _ParticleControl->_fElpasedTime = 0;
    _ParticleControl->setType(STAY_FOR_TWOSECONDS); // 分子運動的型態，預設為 0
    _ParticleControl->_windDir = Point(0, 0); // 本範例沒有實作此項功能
}

void CUIView::setProperty(std::string uicsbname, cocos2d::Size vsize, cocos2d::Scene& stage)
{
	_uiRoot = CSLoader::createNode(uicsbname);
	stage.addChild(_uiRoot);
	_uiRoot->setPosition(Vec2(0,0));
    _stage = &stage;
    _size = vsize;
    init();
}

void CUIView::init() 
{
    // For Emitter
    _EmitterSprite = CDraggableSprite::create();
    _EmitterSprite->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _EmitterSprite->setVisible(false);
    _bEmitterOn = false;
    _stage->addChild(_EmitterSprite, 5);

    auto emiterpos = dynamic_cast<Sprite*>(_uiRoot->getChildByName("emitterpos"));
    Point loc = emiterpos->getPosition();
    emiterpos->setVisible(false);
    _emitterSwitchBtn = CSwitchButton::create();
    _emitterSwitchBtn->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc);
    _stage->addChild(_emitterSwitchBtn, 2);
    //01
    _EmitterSprite01 = CDraggableSprite::create();
    _EmitterSprite01->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _EmitterSprite01->setVisible(false);
    _bEmitterOn01 = false;
    _stage->addChild(_EmitterSprite01, 5);

    auto emiterpos01 = dynamic_cast<Sprite*>(_uiRoot->getChildByName("emitterpos01"));
    Point loc01 = emiterpos01->getPosition();
    emiterpos01->setVisible(false);
    _emitterSwitchBtn01 = CSwitchButton::create();
    _emitterSwitchBtn01->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc01);
    _stage->addChild(_emitterSwitchBtn01, 2);

    //02
    _EmitterSprite02 = CDraggableSprite::create();
    _EmitterSprite02->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _EmitterSprite02->setVisible(false);
    _bEmitterOn02 = false;
    _stage->addChild(_EmitterSprite02, 5);

    auto emiterpos02 = dynamic_cast<Sprite*>(_uiRoot->getChildByName("emitterpos02"));
    Point loc02 = emiterpos02->getPosition();
    emiterpos02->setVisible(false);
    _emitterSwitchBtn02 = CSwitchButton::create();
    _emitterSwitchBtn02->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc02);
    _stage->addChild(_emitterSwitchBtn02, 2);

    //03
    _EmitterSprite03 = CDraggableSprite::create();
    _EmitterSprite03->setSpriteInfo("emittericon.png", Point(-125.0f + _size.width / 2.0f, _size.height / 2.0f));
    _EmitterSprite03->setVisible(false);
    _bEmitterOn03 = false;
    _stage->addChild(_EmitterSprite03, 5);

    auto emiterpos03 = dynamic_cast<Sprite*>(_uiRoot->getChildByName("emitterpos03"));
    Point loc03 = emiterpos03->getPosition();
    emiterpos03->setVisible(false);
    _emitterSwitchBtn03 = CSwitchButton::create();
    _emitterSwitchBtn03->setButtonInfo("emitteroff.png", "emitteron.png", "emittertd.png", loc03);
    _stage->addChild(_emitterSwitchBtn03, 2);

    // 分子的可調整參數的捲動軸
    auto* GravitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Gravity"));
    GravitySlider->addEventListener(CC_CALLBACK_2(CUIView::GravityEvent, this));
    GravitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 -10 到 10 之間
    _GravityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GravityBMFont"));

    // Slider of Spread
    auto* SpreadSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spread"));
    SpreadSlider->addEventListener(CC_CALLBACK_2(CUIView::SpreadEvent, this));
    SpreadSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 180 之間
    _SpreadBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpreadBMFont"));

    // Slider of Direction
    auto* DirectionSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Direction"));
    DirectionSlider->addEventListener(CC_CALLBACK_2(CUIView::DirectionEvent, this));
    DirectionSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _DirectionBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("DirectionBMFont"));

    // Slider of Type
    auto* TypeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Type"));
    TypeSlider->addEventListener(CC_CALLBACK_2(CUIView::TypeEvent, this));
    TypeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _TypeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("TypeBMFont"));

    // Slider of speed
    auto* SpeedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Speed"));
    SpeedSlider->addEventListener(CC_CALLBACK_2(CUIView::SpeedEvent, this));
    SpeedSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _SpeedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpeedBMFont"));

    // Slider of Lifetime
    auto* LifetimeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Lifetime"));
    LifetimeSlider->addEventListener(CC_CALLBACK_2(CUIView::LifetimeEvent, this));
    LifetimeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _LifetimeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("LifetimeBMFont"));
    // Slider of color Red
    auto* RedSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Red"));
    RedSlider->addEventListener(CC_CALLBACK_2(CUIView::RedEvent, this));
    RedSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _RedBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("RedBMFont"));
    // Slider of color Blue
    auto* BlueSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Blue"));
    BlueSlider->addEventListener(CC_CALLBACK_2(CUIView::BlueEvent, this));
    BlueSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _BlueBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("BlueBMFont"));
    // Slider of color Green
    auto* GreenSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Green"));
    GreenSlider->addEventListener(CC_CALLBACK_2(CUIView::GreenEvent, this));
    GreenSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _GreenBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("GreenBMFont"));
    // Slider of Opacity
    auto* OpacitySlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Opacity"));
    OpacitySlider->addEventListener(CC_CALLBACK_2(CUIView::OpacityEvent, this));
    OpacitySlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _OpacityBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("OpacityBMFont"));
    // Slider of Particles
    auto* ParticlesSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Particles"));
    ParticlesSlider->addEventListener(CC_CALLBACK_2(CUIView::ParticlesEvent, this));
    ParticlesSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _ParticlesBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("ParticlesBMFont"));
    // Slider of Spin
    auto* SpinSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Spin"));
    SpinSlider->addEventListener(CC_CALLBACK_2(CUIView::SpinEvent, this));
    SpinSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _SpinBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SpinBMFont"));
    // Slider of Wind
    auto* WindSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Wind"));
    WindSlider->addEventListener(CC_CALLBACK_2(CUIView::WindEvent, this));
    WindSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _WindBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("WindBMFont"));
    // Slider of Size
    auto* SizeSlider = dynamic_cast<cocos2d::ui::Slider*>(_uiRoot->getChildByName("Slider_Size"));
    SizeSlider->addEventListener(CC_CALLBACK_2(CUIView::SizeEvent, this));
    SizeSlider->setMaxPercent(100); 	// 將 0 到 100 對應到 0 到 360 之間
    _SizeBMValue = dynamic_cast<cocos2d::ui::TextBMFont*>(_uiRoot->getChildByName("SizeBMFont"));

    //Button of Texture
    _btn_cloud = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_cloud"));
    _btn_cloud->addTouchEventListener(CC_CALLBACK_2(CUIView::TextureEvent_cloud, this));
    _btn_flare = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_flare"));
    _btn_flare->addTouchEventListener(CC_CALLBACK_2(CUIView::TextureEvent_flare, this));
    _btn_bubble = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_bubble"));
    _btn_bubble->addTouchEventListener(CC_CALLBACK_2(CUIView::TextureEvent_bubble, this));
    _btn_circle = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_circle"));
    _btn_circle->addTouchEventListener(CC_CALLBACK_2(CUIView::TextureEvent_circle, this));
    _btn_comet = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_comet"));
    _btn_comet->addTouchEventListener(CC_CALLBACK_2(CUIView::TextureEvent_comet, this));
    _btn_raindrop = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_raindrop"));
    _btn_raindrop->addTouchEventListener(CC_CALLBACK_2(CUIView::TextureEvent_raindrop, this));

    _btn_rotateSwitch = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_rotate"));
    _btn_rotateSwitch->addTouchEventListener(CC_CALLBACK_2(CUIView::RotateEvent, this));
   
    _btn_textureSwitch = dynamic_cast<cocos2d::ui::Button*>(_uiRoot->getChildByName("Button_texture"));
    _btn_textureSwitch->addTouchEventListener(CC_CALLBACK_2(CUIView::RandomTextureEvent, this));
}


void CUIView::onTouchBegan(const cocos2d::Point& tPoint)
{ 
    
    //顯示 Emitter 時，可拖曳該圖式
    if (_bEmitterOn) { _EmitterSprite->touchesBegan(tPoint); log("E00 touchesBegan"); }
    if (_bEmitterOn01) { 
        _EmitterSprite01->touchesBegan(tPoint);     
    }
    if (_bEmitterOn02) {
        _EmitterSprite02->touchesBegan(tPoint);
    }
    if (_bEmitterOn03) {
        _EmitterSprite03->touchesBegan(tPoint);
    }
   if (!_emitterSwitchBtn01->touchesBegan(tPoint) && !_bEmitterOn01&&!_emitterSwitchBtn02->touchesBegan(tPoint) && !_bEmitterOn02&&!_emitterSwitchBtn->touchesBegan(tPoint) && !_bEmitterOn&&!_emitterSwitchBtn03->touchesBegan(tPoint) && !_bEmitterOn03) _ParticleControl->onTouchesBegan(tPoint);
}

void CUIView::onTouchMoved(const cocos2d::Point& tPoint)
{
    if (_bEmitterOn) {
        if (_EmitterSprite->touchesMoved(tPoint)) { // 移動並更新 Emitter 的位置
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
    if (_bEmitterOn01) {
        if (_EmitterSprite01->touchesMoved(tPoint)) { // 移動並更新 Emitter 的位置
            _ParticleControl->_emitterPt01 = _EmitterSprite01->getLoc();
        }
    }
    if (_bEmitterOn02) {
        if (_EmitterSprite02->touchesMoved(tPoint)) { // 移動並更新 Emitter 的位置
            _ParticleControl->_emitterPt02 = _EmitterSprite02->getLoc();
        }
    }
    if (_bEmitterOn03) {
        if (_EmitterSprite03->touchesMoved(tPoint)) { // 移動並更新 Emitter 的位置
            _ParticleControl->_emitterPt03 = _EmitterSprite03->getLoc();
        }
    }
   
    if (!_emitterSwitchBtn01->touchesBegan(tPoint) && !_bEmitterOn01 && !_emitterSwitchBtn02->touchesBegan(tPoint) && !_bEmitterOn02 && !_emitterSwitchBtn->touchesBegan(tPoint) && !_bEmitterOn && !_emitterSwitchBtn03->touchesBegan(tPoint) && !_bEmitterOn03) _ParticleControl->onTouchesBegan(tPoint);
}

void CUIView::onTouchEnded(const cocos2d::Point& tPoint)
{
    
    if (_bEmitterOn) {   
        if (_EmitterSprite->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt = _EmitterSprite->getLoc();
        }
    }
     // 點在 Emitter 切換的圖示上，進行必要的狀態改變
    if (_emitterSwitchBtn->touchesEnded(tPoint))
    {
       
        _bEmitterOn = _emitterSwitchBtn->getStatus();
        if (_bEmitterOn) { // 顯示 Emitter 圖示
            _EmitterSprite->setVisible(true);
        }
        else { // 關閉 Emitter 圖示
            _EmitterSprite->setVisible(false);
        }
        _ParticleControl->setEmitter(_bEmitterOn); // 更新控制系統中的 Emitter 狀態
    }
    //01
    if (_bEmitterOn01) {
        if (_EmitterSprite01->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt01 = _EmitterSprite01->getLoc();
        }
    }
    if (_emitterSwitchBtn01->touchesEnded(tPoint))
    {
        _bEmitterOn01 = _emitterSwitchBtn01->getStatus();
        
        //if (_bEmitterOn01) { // 顯示 Emitter 圖示
        //    _EmitterSprite01->setVisible(true);
        //}
        //else { // 關閉 Emitter 圖示
        //    _EmitterSprite01->setVisible(false);
        //}
        _ParticleControl->setEmitter01(_bEmitterOn01); // 更新控制系統中的 Emitter 狀態
    }
    //02 
    if (_bEmitterOn02) {
        if (_EmitterSprite02->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt02 = _EmitterSprite02->getLoc();
        }
    }
    if (_emitterSwitchBtn02->touchesEnded(tPoint))
    {
        _bEmitterOn02 = _emitterSwitchBtn02->getStatus();

        //if (_bEmitterOn02) { // 顯示 Emitter 圖示
        //    _EmitterSprite02->setVisible(true);
        //}
        //else { // 關閉 Emitter 圖示
        //    _EmitterSprite02->setVisible(false);
        //}
        _ParticleControl->setEmitter02(_bEmitterOn02); // 更新控制系統中的 Emitter 狀態
    }
    //03 
    if (_bEmitterOn03) {
        if (_EmitterSprite03->touchesEnded(tPoint)) {
            _ParticleControl->_emitterPt03 = _EmitterSprite03->getLoc();
        }
    }
    if (_emitterSwitchBtn03->touchesEnded(tPoint))
    {
        _bEmitterOn03 = _emitterSwitchBtn03->getStatus();

        //if (_bEmitterOn03) { // 顯示 Emitter 圖示
        //    _EmitterSprite03->setVisible(true);
        //}
        //else { // 關閉 Emitter 圖示
        //    _EmitterSprite03->setVisible(false);
        //}
        _ParticleControl->setEmitter03(_bEmitterOn03); // 更新控制系統中的 Emitter 狀態
    }
  
}

void CUIView::GravityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        float fGravity = (-50.0f + percent) / 5.0f; // 將 0 到 100 對應到 -10 到 10 之間
        _GravityBMValue->setString(StringUtils::format("%2.1f", fGravity)); // 透過 _GravityBMValue 顯示在畫面上
        _ParticleControl->setGravity(fGravity);
    }
}

void CUIView::SpreadEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fSpread = percent * 1.8f; // 0 到 180 之間
        _SpreadBMValue->setString(StringUtils::format("%2.1f", fSpread));
        _ParticleControl->_fSpread = fSpread;
    }
}

void CUIView::DirectionEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        float fDir = percent * 3.6f; // 0 到 360 之間
        _DirectionBMValue->setString(StringUtils::format("%2.1f", fDir));
        _ParticleControl->_fDir = fDir;
    }
}

void CUIView::TypeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        const Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent();
        int maxPercent = slider->getMaxPercent();
        int iType = percent *0.09; 
        _TypeBMValue->setString(StringUtils::format("%2d", iType));
        _ParticleControl->setType(iType);
    }
}

void CUIView::SpeedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) 
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        // 將 0 到 100 對應到 0 到 40 之間
        float fSpeed = percent / 2.5f;
        // 透過 _SpreadBMValue 顯示在畫面上
        _SpeedBMValue->setString(StringUtils::format("%2.1f", fSpeed));
        _ParticleControl->setSpeed(fSpeed);
    }

}
void CUIView::LifetimeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        // 將 0 到 100 對應到 0 到 10 之間
        float fLifetime = percent / 10.0f;
        _LifetimeBMValue->setString(StringUtils::format("%2.1f", fLifetime));
        _ParticleControl->setLifeTime(fLifetime);
    }
}
void CUIView::OpacityEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        int iOpacity = percent * 2.55f;
        _OpacityBMValue->setString(StringUtils::format("%3d", iOpacity));
        _ParticleControl->setOpacity(iOpacity);
    }
}
void CUIView::ParticlesEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        int iParticles = percent * 3;
        _ParticlesBMValue->setString(StringUtils::format("%3d", iParticles));
        _ParticleControl->setParticles(iParticles);
    }
}
void CUIView::RedEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        int iRed = percent * 2.55f;
        _RedBMValue->setString(StringUtils::format("%3d", iRed));
        _ParticleControl->setRed(iRed);
    }
}
void CUIView::GreenEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        int iGreen = percent * 2.55f;
        _GreenBMValue->setString(StringUtils::format("%3d", iGreen));
        _ParticleControl->setGreen(iGreen);
    }
}
void CUIView::BlueEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type)
{
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        int iBlue = percent * 2.55f;
        _BlueBMValue->setString(StringUtils::format("%3d", iBlue));
        _ParticleControl->setBlue(iBlue);
    }
}
void CUIView::SpinEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        float fSpin = percent * 3.6f;
        _SpinBMValue->setString(StringUtils::format("%3.1f", fSpin));
        _ParticleControl->setSpin(fSpin);
    }
}
void CUIView::WindEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        float fWind = percent * 2 - 100;
        _WindBMValue->setString(StringUtils::format("%3.1f", fWind));
        _ParticleControl->setWind(fWind);
    }
}
void CUIView::SizeEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);
        int percent = slider->getPercent(); // 捲動鈕目前的位置 0 ~ 100
        int maxPercent = slider->getMaxPercent();
        float fSize = percent*0.1  + 0.05;
        _SizeBMValue->setString(StringUtils::format("%2.2f", fSize));
        _ParticleControl->setSize(fSize);
    }
}

void CUIView::TextureEvent_cloud(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
   
        switch (type)
        {
        case Widget::TouchEventType::BEGAN:
            _ParticleControl->setTexture(0);
            log("Touch Down"); break;
        case Widget::TouchEventType::MOVED:
            log("Touch Move"); break;
        case Widget::TouchEventType::ENDED:
            log("Touch Up"); break;
        case Widget::TouchEventType::CANCELED:
            log("Touch Cancelled"); break;
        default: break;
        }

}
void CUIView::TextureEvent_flare(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        _ParticleControl->setTexture(1);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}
void CUIView::TextureEvent_bubble(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        _ParticleControl->setTexture(2);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}
void CUIView::TextureEvent_circle(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        _ParticleControl->setTexture(3);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}
void CUIView::TextureEvent_comet(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        _ParticleControl->setTexture(4);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}
void CUIView::TextureEvent_raindrop(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        _ParticleControl->setTexture(5);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}

void CUIView::RotateEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        countRotate += 1;
        log("%d", countRotate % 2);
        _ParticleControl->setRotate(countRotate % 2);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}
void CUIView::RandomTextureEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        countRandomTexture += 1;
        log("%d", countRandomTexture % 2);
        _ParticleControl->setRandomTexture(countRandomTexture % 2);
        log("Touch Down"); break;
    case Widget::TouchEventType::MOVED:
        log("Touch Move"); break;
    case Widget::TouchEventType::ENDED:
        log("Touch Up"); break;
    case Widget::TouchEventType::CANCELED:
        log("Touch Cancelled"); break;
    default: break;
    }
}

