#include "CParticleSystem.h"

#define NUMBER_PARTICLES 2000 // 預設一次取得 1000 個 Particles

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
	_pParticles = new CParticle[NUMBER_PARTICLES]; // 取得所需要的 particle 空間
	 // 讀入儲存多張圖片的 plist 檔
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
	if (_bEmitterOn) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
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
					// 根據 _fSpread 與 _vDir 產生方向
					float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
					t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
					t = (_fDir + t )* M_PI / 180.0f;
					Vec2 vdir(cosf(t), sinf(t));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // 目前已經產生 n 個分子
			
		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;		
	}
	//
	if (_bEmitterOn01) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		int n = (int)(_fElpasedTime * 80); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
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
					float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
					t = 360 - t * 360 * 2; //  產生的角度，轉成弧度
					t = (30 + t) * M_PI / 180.0f;
					Vec2 vdir(cosf(t)* sinf(t), sinf(t)* sinf(t*2));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // 目前已經產生 n 個分子

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= 100) _iGenParticles -= 100;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	//
	if (_bEmitterOn02) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
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
			_iGenParticles = n; // 目前已經產生 n 個分子

		}
		if (_fElpasedTime >= 1.0f) {
			_fElpasedTime -= 1.0f;
			if (_iGenParticles >= _iNumParticles) _iGenParticles -= _iNumParticles;
			else _iGenParticles = 0;
		}
		_fElpasedTime += dt;
	}
	//
	if (_bEmitterOn03) { // 根據 Emitter 設定的相關參數，產生相對應的分子
		// 先計算在累加
		int n = (int)(_fElpasedTime * _iNumParticles); // 到目前為止應該產生的分子個數
		if (n > _iGenParticles) {  // 產生的分子個數不足，產生到 n 個分子
			for (int i = 0; i < n - _iGenParticles; i++) {
				// 根據 Emitter 的相關參數，設定所產生分子的參數
				if (_iFree != 0) {
					get = _FreeList.front();
					get->setParticleTexture(_iParticlesType);
					get->setBehavior(EMITTER03);
					get->setPosition(_emitterPt03);
					/*get->setSize(1.0f);*/

					float t = (rand() % 1001) / 1000.0f; // 產生介於 0 到 1 間的數
					t = _fSpread - t * _fSpread * 2; //  產生的角度，轉成弧度
					t = (_fDir + t) * M_PI / 180.0f;
					Vec2 vdir(cosf(t), sinf(t));
					get->setDirection(vdir);
					_FreeList.pop_front();
					_InUsedList.push_front(get);
					_iFree--; _iInUsed++;
				}
			}
			_iGenParticles = n; // 目前已經產生 n 個分子

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

	if (_iInUsed != 0) { // 有分子需要更新時
		for (it = _InUsedList.begin(); it != _InUsedList.end(); ) {
			if ((*it)->update(dt)) { // 分子生命週期已經到達
									 // 將目前這一個節點的內容放回 _FreeList
				_FreeList.push_front((*it));
				it = _InUsedList.erase(it); // 移除目前這一個, 

				_iFree++; _iInUsed--;
			}
			else it++;
		}
	}

	
}

//
void CParticleSystem::setGravity(float fGravity)
{
	// 設定目前 particle 是在 inused 的 gravity
	_fGravity = fGravity;
	list <CParticle *>::iterator it;
	if (_iInUsed != 0) { // 有分子需要更新時
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
void CParticleSystem::setRotate(int iRotate) {//開始旋轉的開關
	_iRotate = iRotate;
}
void CParticleSystem::setRandomTexture(int iRandomTexture) {//開始旋轉的開關
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
	if (_iInUsed != 0) _InUsedList.clear(); // 移除所有的 NODE
	if (_iFree != 0) _FreeList.clear();
	delete[] _pParticles; // 釋放所有取得資源
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("particletexture.plist");
}
void CParticleSystem::onTouchesBegan(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{

	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case EXPLOSION:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case HEARTSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case BUTTERFLYSHAPE:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case TAIL:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case RAND:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case FLOWER:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
		
		else return;// 沒有分子, 所以就不提供
		
		break;
	}
	

}
void CParticleSystem::onTouchesMoved(const cocos2d::Point &touchPoint)
{
	CParticle *get;
	switch (_iType)
	{
	case STAY_FOR_TWOSECONDS:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
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
		else return;// 沒有分子, 所以就不提供
		break;
	case FREE_FLY:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case TAIL:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	case RAND:
		// 從 _FreeList 取得一個分子給放到 _InUsed
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
		else return;// 沒有分子, 所以就不提供
		break;
	}
}
void CParticleSystem::onTouchesEnded(const cocos2d::Point& touchPoint) {

}