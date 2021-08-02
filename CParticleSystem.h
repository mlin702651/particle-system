#ifndef __CPARTICLE_SYSTEM_H__
#define __CPARTICLE_SYSTEM_H__

#include "cocos2d.h"
#include "CParticle.h"
#include <list>

using namespace std;


class CParticleSystem
{
private:
	CParticle* _pParticles;
	list<CParticle*> _FreeList;
	list<CParticle*> _InUsedList;
	int _iFree;	// 可用的  Particle 個數
	int _iInUsed;  // 正在使用的 Particle 個數
	int _iType;  // 目前控制的分子運動模式是哪一種型態

	bool _bEmitterOn; // Emitter 是否顯示
	bool _bEmitterOn01;
	bool _bEmitterOn02;
	bool _bEmitterOn03;

	float fireworkTimer;
	cocos2d::Point _fireworkPt;
	cocos2d::Point _fireworkExploPt;
public:
	// Emitter 設定的相關參數
	cocos2d::Point _emitterPt;// Emitter 的位置	
	cocos2d::Point _emitterPt01;
	cocos2d::Point _emitterPt02;
	cocos2d::Point _emitterPt03;
	float    _fDir; // Emitter 的噴射方向，0 到 360度，逆時針方向為正
	int		_iNumParticles;	// 每秒鐘產生的分子個數
	int     _iGenParticles; // 到目前為止所產生的分子個數(以每秒為單位)
	float	_fSpread;	 // 0 到 180 度，預設為 180 
	float   _fVelocity;	 // 分子的離開速度
	float   _fLifeTime;	 // 分子的存活時間
	float	_fSpin;		// 分子的旋轉量 degree/sec
	float   _fGravity;
	float   _fElpasedTime;	// 經過多少時間，以秒為單位，作為成生分子的計算依據
	int _iRed, _iBlue, _iGreen;//color
	float _fOpacity;
	int _iParticlesType;//貼圖種類
	int _iRotate;
	cocos2d::Point _windDir;  // 風的方向，本範例沒有實作
	float	_fWind;
	float _fSize;
	bool _bRandomTexture;//隨機貼圖
	int _textureType;
	cocos2d::Point saveTouchPoint;
	bool fireworkOn=false;
	CParticleSystem();
	~CParticleSystem();
	void init(cocos2d::Scene &stage);
	void update(float dt);
	void setEmitter(bool bEm);
	void setType(int type) { _iType = type; }

 //   void onTouchesEnded(const cocos2d::CCPoint &touchPoint);
    void onTouchesBegan(const cocos2d::Point &touchPoint);
    void onTouchesMoved(const cocos2d::Point &touchPoint);
	void onTouchesEnded(const cocos2d::Point& touchPoint);

	void setGravity(float fGravity);
	void setSpeed(float fSpeed);

	void setOpacity(float fOpacity);
	void setRed(int iRed);
	void setGreen(int iGreen);
	void setBlue(int iBlue);
	void setLifeTime(float fLifeTime);
	void setParticles(int iParticles);
	void setTexture(int iParticlesType);
	void setSpin(float fSpin);
	void setWind(float fWind);
	void setSize(float fSize);
	void setBtnEmitter(int buttonType ,const cocos2d::Point& touchPoint);

	void setRotate(int iRotate);
	void setRandomTexture(int iRandomTexture);
	//emitter01
	void setEmitter01(bool bEm);
	void setEmitter02(bool bEm);
	void setEmitter03(bool bEm);
};

#endif