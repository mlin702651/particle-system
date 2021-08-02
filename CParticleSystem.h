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
	int _iFree;	// �i�Ϊ�  Particle �Ӽ�
	int _iInUsed;  // ���b�ϥΪ� Particle �Ӽ�
	int _iType;  // �ثe������l�B�ʼҦ��O���@�ث��A

	bool _bEmitterOn; // Emitter �O�_���
	bool _bEmitterOn01;
	bool _bEmitterOn02;
	bool _bEmitterOn03;

	float fireworkTimer;
	cocos2d::Point _fireworkPt;
	cocos2d::Point _fireworkExploPt;
public:
	// Emitter �]�w�������Ѽ�
	cocos2d::Point _emitterPt;// Emitter ����m	
	cocos2d::Point _emitterPt01;
	cocos2d::Point _emitterPt02;
	cocos2d::Point _emitterPt03;
	float    _fDir; // Emitter ���Q�g��V�A0 �� 360�סA�f�ɰw��V����
	int		_iNumParticles;	// �C�������ͪ����l�Ӽ�
	int     _iGenParticles; // ��ثe����Ҳ��ͪ����l�Ӽ�(�H�C�����)
	float	_fSpread;	 // 0 �� 180 �סA�w�]�� 180 
	float   _fVelocity;	 // ���l�����}�t��
	float   _fLifeTime;	 // ���l���s���ɶ�
	float	_fSpin;		// ���l������q degree/sec
	float   _fGravity;
	float   _fElpasedTime;	// �g�L�h�֮ɶ��A�H�����A�@�����ͤ��l���p��̾�
	int _iRed, _iBlue, _iGreen;//color
	float _fOpacity;
	int _iParticlesType;//�K�Ϻ���
	int _iRotate;
	cocos2d::Point _windDir;  // ������V�A���d�ҨS����@
	float	_fWind;
	float _fSize;
	bool _bRandomTexture;//�H���K��
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