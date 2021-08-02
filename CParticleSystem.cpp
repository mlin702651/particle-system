#include "CParticleSystem.h"

#define NUMBER_PARTICLES 2000 // �w�]�@�����o 1000 �� Particles

USING_NS_CC;

CParticleSystem::CParticleSystem()
{
	_fGravity = 0;
	_bEmitterOn = false;
	_iRed = 255;
	_iBlue = 255;
	_iGreen = 255;
	_fOpacity = 255;
	_iRotate = 0;
	_bEmitterOn01 = false;
	fireworkTimer = 0;
}

void CParticleSystem::setEmitter(bool bEm)
{
	_bEmitterOn = bEm;
}
void CParticleSystem::setEmitter01(bool bEm)
{
	_bEmitterOn01 = bEm;
}
void CParticleSystem::setEmitter02(bool bEm)
{
	_bEmitterOn02 = bEm;
}
void CParticleSystem::setEmitter03(bool bEm)
{
	_bEmitterOn03 = bEm;
}

void CParticleSystem::init(cocos2d::Scene &stage)
{
	_iFree = NUMBER_PARTICLES;
	_iInUsed = 0;
	_pParticles = new CParticle[NUMBER_PARTICLES]; // ���o�һݭn�� particle �Ŷ�
	 // Ū�J�x�s�h�i�Ϥ��� plist ��
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("particletexture.plist");
	for (int i = 0; i < NUMBER_PARTICLES; i++) {	
		_pParticles[i].setParticle("cloud.png", stage);
		_FreeList.push_front(&_pParticles[i]);
	}
}

void CParticleSystem::update(float dt)
{
	CParticle *get;
	list <CParticle *>::iterator it;	
	if (_bEmitterOn) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {
					get = _FreeList.front();
					if (_bRandomTexture) {
						_iParticlesType = rand() % 6;
						get->setParticleTexture(_iParticlesType);
					}
					else {
						get->setParticleTexture(_iParticlesType);
					}
					get->setBehavior(EMITTER_DEFAULT);
					get->setColor(Color3B(_iRed, _iGreen, _iBlue));
					get->setOpacity(_fOpacity);
					get->setVelocity(_fVelocity);
					get->setLifetime(_fLifeTime);				
					get->setGravity(_fGravity);
					get->setPosition(_emitterPt);
					get->setSize(_fSize);
					get->setSpin(_fSpin);
					get->setRotate(_iRotate);
					get->setWind(_fWind);
					// �ھ� _fSpread �P _vDir ���ͤ�V
					float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
					t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
					t = (_fDir + t )* M_PI / 180.0f;
					Vec2 vdir(cosf(t), sinf(t));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l
			
		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;		
	}
	//
	if (_bEmitterOn01) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		int n = (int)(_fElpasedTime * 80); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setParticleTexture(_iParticlesType);
					get->setBehavior(EMITTER01);
					_emitterPt01.x = rand() % 450 + 550 ;
					_emitterPt01.y = 800;
					get->setPosition(_emitterPt01);
					get->setSize(1.0f);
					//
					get->setWind(rand() % 10);
					float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
					t = 360 - t * 360 * 2; //  ���ͪ����סA�ন����
					t = (30 + t) * M_PI / 180.0f;
					Vec2 vdir(cosf(t)* sinf(t), sinf(t)* sinf(t*2));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= 100) _iGenParticles -= 100;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	//
	if (_bEmitterOn02) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setParticleTexture(_iParticlesType);
					get->setBehavior(EMITTER02);

					get->setPosition(_emitterPt02);
					get->setGravity(_fGravity);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;	
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	//
	if (_bEmitterOn03) { // �ھ� Emitter �]�w�������ѼơA���ͬ۹��������l
		// ���p��b�֥[
		int n = (int)(_fElpasedTime * _iNumParticles); // ��ثe�������Ӳ��ͪ����l�Ӽ�
		if (n > _iGenParticles) {  // ���ͪ����l�ӼƤ����A���ͨ� n �Ӥ��l
			for (int i = 0; i < n - _iGenParticles; i++) {
				// �ھ� Emitter �������ѼơA�]�w�Ҳ��ͤ��l���Ѽ�
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setParticleTexture(_iParticlesType);
					get->setBehavior(EMITTER03);
					get->setPosition(_emitterPt03);
					/*get->setSize(1.0f);*/

					float t = (rand() % 1001) / 1000.0f; // ���ͤ��� 0 �� 1 ������
					t = _fSpread - t * _fSpread * 2; //  ���ͪ����סA�ন����
					t = (_fDir + t) * M_PI / 180.0f;
					Vec2 vdir(cosf(t), sinf(t));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // �ثe�w�g���� n �Ӥ��l

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	//
	if (fireworkOn) {
		fireworkTimer += dt;	

		if (_iFree != 150 && fireworkTimer > 1.0f) {
			fireworkOn = false;
			fireworkTimer = 0;
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(FIREWORK);
				get->setSpin(_fSpin);
				get->setPosition(_fireworkExploPt);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
	}

	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt)) { // ���l�ͩR�g���w�g��F
									 // �N�ثe�o�@�Ӹ`�I�����e��^ _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // �����ثe�o�@��, 

				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}

	
}

//
void CParticleSystem::setGravity(float fGravity)
{
	// �]�w�ثe particle �O�b inused �� gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // �����l�ݭn��s��
		for (it = _InUsedList.begin(); it != _InUsedList.end(); it++) {
			(*it)->setGravity(_fGravity);
		}
	}
}
void CParticleSystem::setSpeed(float fSpeed) {
	_fVelocity = fSpeed;
}
void CParticleSystem::setRed(int iRed) {
	_iRed = iRed;
}
void CParticleSystem::setBlue(int iBlue) {
	_iBlue = iBlue;
}
void CParticleSystem::setGreen(int iGreen) {
	_iGreen = iGreen;
}
void CParticleSystem::setOpacity(float fOpacity) {
	_fOpacity = fOpacity;
}
void CParticleSystem::setLifeTime(float fLifeTime) {
	_fLifeTime = fLifeTime;
}
void CParticleSystem::setParticles(int iParticles) {
	_iNumParticles = iParticles;
}
void CParticleSystem::setTexture(int iParticlesType) {
	_iParticlesType = iParticlesType;
}
void CParticleSystem::setSpin(float fSpin) {
	_fSpin = fSpin;
}
void CParticleSystem::setRotate(int iRotate) {//�}�l���઺�}��
	_iRotate = iRotate;
}
void CParticleSystem::setRandomTexture(int iRandomTexture) {//�}�l���઺�}��
	if (iRandomTexture) {
		_bRandomTexture = true;
	}
	else {
		_bRandomTexture = false;
	}
}
void  CParticleSystem::setWind(float fWind) {
	_fWind = fWind;
}
void  CParticleSystem::setSize(float fSize) {
	_fSize = fSize;
}

CParticleSystem::~CParticleSystem()
{
	if (_iInUsed != 0) _InUsedList.clear(); // �����Ҧ��� NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // ����Ҧ����o�귽
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}
void CParticleSystem::onTouchesBegan(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{

	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case RANDOMS_FALLING :
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case EXPLOSION:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 100) {
			for (int i = 0; i < 100; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(EXPLOSION);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				get->setSize(_fSize);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case HEARTSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(HEARTSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case BUTTERFLYSHAPE:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(BUTTERFLYSHAPE);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case TAIL:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(TAIL);
			get->setSpin(_fSpin);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);

			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case RAND:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 30) {
			for (int i = 0; i < 30; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(RAND);
				get->setPosition(touchPoint);
				get->setGravity(-20);
				get->setSize(0.5f);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FLOWER:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree > 150) {
			for (int i = 0; i < 150; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(FLOWER);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FIREWORK:
		if (_iFree != 15 && fireworkTimer < 0.5f) {
			fireworkOn = true;
			_fireworkPt = touchPoint;
			_fireworkExploPt = touchPoint /*+ Vec2(0, 10)*/;
			_fireworkExploPt.y = touchPoint.y + 290;
			for (int i = 0; i < 15; i++) {
				get = _FreeList.front();
				get->setParticleTexture(_iParticlesType);
				get->setBehavior(FIREWORKUP);
				get->setPosition(touchPoint);
				get->setGravity(_fGravity);
				_FreeList.pop_front();
				_InUsedList.push_front(get);
				_iFree--; _iInUsed++;
			}
		}
		
		else return;// �S�����l, �ҥH�N������
		
		break;
	}
	

}
void CParticleSystem::onTouchesMoved(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(STAY_FOR_TWOSECONDS);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case RANDOMS_FALLING:
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(RANDOMS_FALLING);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case FREE_FLY:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(FREE_FLY);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case TAIL:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(TAIL);
			get->setPosition(touchPoint);
			log("%f", touchPoint.y);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	case RAND:
		// �q _FreeList ���o�@�Ӥ��l����� _InUsed
		if (_iFree != 0) {
			get = _FreeList.front();
			get->setParticleTexture(_iParticlesType);
			get->setBehavior(RAND);
			get->setPosition(touchPoint);
			get->setGravity(_fGravity);
			_FreeList.pop_front();
			_InUsedList.push_front(get);
			_iFree--; _iInUsed++;
		}
		else return;// �S�����l, �ҥH�N������
		break;
	}
}
void CParticleSystem::onTouchesEnded(const cocos2d::Point& touchPoint) {

}