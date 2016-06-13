#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));*/

    // create menu, it's an autorelease object
    /*
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    */

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    /*
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    */

    // position the label on the center of the screen
    /*
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
                            */

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    _batchNode = SpriteBatchNode::create("Spritesheets/Sprites.pvr.ccz");
    this->addChild(_batchNode, 0);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Spritesheets/Sprites.plist");

    // _ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
    _ship = Sprite::createWithSpriteFrameName("SpaceFlier_lg_2.png");
    _ship->setPosition(Vec2(visibleSize.width * 0.1 + origin.x, visibleSize.height * 0.5 + origin.y));
    _batchNode->addChild(_ship, 1);

    _backgroundNode = ParallaxNodeExtras::node();
    // _backgroundNode = ParallaxNode::create();
    this->addChild(_backgroundNode, -1);

    _spacedust1 = Sprite::create("Backgrounds/bg_front_spacedust.png");
    _spacedust2 = Sprite::create("Backgrounds/bg_front_spacedust.png");
    _planetsunrise = Sprite::create("Backgrounds/bg_planetsunrise.png");
    _galaxy = Sprite::create("Backgrounds/bg_galaxy.png");
    _spacialanomaly = Sprite::create("Backgrounds/bg_spacialanomaly.png");
    _spacialanomaly2 = Sprite::create("Backgrounds/bg_spacialanomaly2.png");

    Point dustSpeed = Vec2(0.1, 0.1);
    Point bgSpeed = Vec2(0.05, 0.05);

    _backgroundNode->addChild(_spacedust1, 0, dustSpeed,
        Vec2(origin.x, origin.y + visibleSize.height * 0.5));
    _backgroundNode->addChild(_spacedust2, 0, dustSpeed,
        Vec2(origin.x + _spacedust1->getContentSize().width, origin.y + visibleSize.height * 0.5));
    _backgroundNode->addChild(_galaxy, -1, bgSpeed,
        Vec2(origin.x, origin.y + visibleSize.height * 0.7));
    _backgroundNode->addChild(_planetsunrise, -1, bgSpeed,
        Vec2(origin.x + 600, origin.y + 0));
    _backgroundNode->addChild(_spacialanomaly, -1, bgSpeed,
        Vec2(origin.x + 900, origin.y + visibleSize.height * 0.3));
    _backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed,
        Vec2(origin.x + 1500, origin.y + visibleSize.height * 0.9));

    this->addChild(ParticleSystemQuad::create("Particles/Stars1.plist"));
    this->addChild(ParticleSystemQuad::create("Particles/Stars2.plist"));
    this->addChild(ParticleSystemQuad::create("Particles/Stars3.plist"));

    #define KNUMLASERS 5
    _nextShipLaser = 0;
    // _shipLasers = new Vector<Sprite *>(KNUMLASERS);
    for (int i = 0; i < KNUMLASERS; ++i) {
        Sprite *shipLaser = Sprite::createWithSpriteFrameName("laserbeam_blue.png");
        shipLaser->setVisible(false);
        _batchNode->addChild(shipLaser);
        _shipLasers.pushBack(shipLaser);
    }
    this->setTouchEnabled(true);

    SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/SpaceGame.wav",true);
    SimpleAudioEngine::getInstance()->preloadEffect("Sounds/explosion_large.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("Sounds/laser_ship.wav");

    #define KNUMASTEROIDS 15
    for (int i = 0; i < KNUMASTEROIDS; ++i) {
        Sprite *asteroid = Sprite::createWithSpriteFrameName("asteroid.png");
        asteroid->setVisible(false);
        _batchNode->addChild(asteroid);
        _asteroids.pushBack(asteroid);
    }

    #define KNUMENEMYSHIPS 3
    for (int i = 0; i < KNUMENEMYSHIPS; ++i) {
        Sprite *enemyShip = Sprite::createWithSpriteFrameName("enemy_spaceship.png");
        enemyShip->setVisible(false);
        _batchNode->addChild(enemyShip);
        _enemyShips.pushBack(enemyShip);
    }

    _lives = 3;
    double curTime = getTimeTick();
    _gameOverTime = curTime + 30000;

    this->scheduleUpdate();
    this->setAccelerometerEnabled(true);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
    #endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::update(float dt) {
    Point backgroundScrollVert = Vec2(-1000, 0);
    _backgroundNode->setPosition(_backgroundNode->getPosition() + backgroundScrollVert * dt);

    __Array *spaceDusts = __Array::createWithCapacity(2);
    spaceDusts->addObject(_spacedust1);
    spaceDusts->addObject(_spacedust2);

    for (int ii = 0; ii < spaceDusts->count(); ii++) {
        Sprite * spaceDust = (Sprite *)(spaceDusts->getObjectAtIndex(ii));
        float xPosition = _backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x;
        float size = spaceDust->getContentSize().width;
        if (xPosition < -1 * size / 2) {
            _backgroundNode->incrementOffset(Vec2(spaceDust->getContentSize().width*2,0), spaceDust);
        }
    }

    __Array *backGrounds = __Array::createWithCapacity(4);
    backGrounds->addObject(_galaxy);
    backGrounds->addObject(_planetsunrise);
    backGrounds->addObject(_spacialanomaly);
    backGrounds->addObject(_spacialanomaly2);
    for (int ii = 0; ii < backGrounds->count(); ii++) {
        Sprite * background = (Sprite *)(backGrounds->getObjectAtIndex(ii));
        float xPosition = _backgroundNode->convertToWorldSpace(background->getPosition()).x;
        float size = background->getContentSize().width;
        if (xPosition < -1 * size) {
            _backgroundNode->incrementOffset(Vec2(2000, 0), background);
        }
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    float maxY = visibleSize.height - _ship->getContentSize().height/2;
    float minY = _ship->getContentSize().height/2 + 30;

    float diff = (_shipPointsPerSecY * dt);
    float newY = _ship->getPosition().y * diff;
    newY = MIN(MAX(newY, minY ), maxY);
    _ship->setPosition(Vec2(_ship->getPosition().x, newY));

    float curTimeMillis = getTimeTick();
    if (curTimeMillis > _nextAsteroidSpawn) {
        float randMillisecs = randomValueBetween(0.20, 1.0) * 1000;
        _nextAsteroidSpawn = randMillisecs + curTimeMillis;

        float randY = randomValueBetween(0.0, visibleSize.height);
        float randDuration = randomValueBetween(2.0, 10.0);

        Sprite *asteroid = (Sprite *)_asteroids.at(_nextAsteroid++);

        if (_nextAsteroid >= _asteroids.size()) {
            _nextAsteroid = 0;
        }

        asteroid->stopAllActions();
        asteroid->setPosition(Vec2(visibleSize.width + asteroid->getContentSize().width / 2, randY));
        asteroid->setVisible(true);
        asteroid->runAction(Sequence::create(MoveBy::create(randDuration,
            Vec2(-1 * visibleSize.width - asteroid->getContentSize().width, 0)),
            CallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL));
    }

    if (curTimeMillis > _nextEnemySpawn) {
        float randMillisecs = randomValueBetween(0.20, 1.0) * 2000;
        _nextEnemySpawn = randMillisecs + curTimeMillis;

        float randY = randomValueBetween(0.0, visibleSize.height);
        float randDuration = randomValueBetween(2.0, 10.0);
        Sprite *enemyShip = (Sprite *)_enemyShips.at(_nextEnemyShip++);

        if (_nextEnemyShip >= _enemyShips.size()) {
            _nextEnemyShip = 0;
        }

        enemyShip->stopAllActions();
        enemyShip->setPosition(Vec2(visibleSize.width + enemyShip->getContentSize().width / 2, randY));
        enemyShip->setVisible(true);
        enemyShip->runAction(Sequence::create(MoveBy::create(randDuration,
            Vec2(-1 * visibleSize.width - enemyShip->getContentSize().width, 0)),
            CallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL));
    }

    for (int i = 0; i < _asteroids.size(); ++i) {
        Sprite *asteroid = (Sprite *)_asteroids.at(i);
        if (!asteroid->isVisible()) {
            continue;
        }

        for (int j = 0; j < _shipLasers.size(); ++j) {
            Sprite *shipLaser = (Sprite *)_shipLasers.at(j);
            if (!shipLaser->isVisible()) {
                continue;
            }
            if (shipLaser->getBoundingBox().intersectsRect(asteroid->getBoundingBox())) {
                shipLaser->setVisible(false);
                asteroid->setVisible(false);
                continue;
            }
        }

        if (_ship->getBoundingBox().intersectsRect(asteroid->getBoundingBox())) {
            SimpleAudioEngine::sharedEngine()->playEffect("Sounds/explosion_large.wav");
            asteroid->setVisible(false);
            _ship->runAction(Blink::create(1.0, 9));
            _lives--;
        }
    }

    if (_lives <= 0) {
        _ship->stopAllActions();
        _ship->setVisible(false);
        this->endScene(KENDREASONLOSE);
    } else if (curTimeMillis >= _gameOverTime) {
        this->endScene(KENDREASONWIN);
    }
}

void HelloWorld::onAcceleration(Acceleration* pAccelerationValue, Event* unused_event) {

    #define KFILTERINGFACTOR 0.1
    #define KRESTACCELX -0.6
    #define KSHIPMAXPOINTSPERSEC (visibleSize.height * 0.5)
    #define KMAXDIFFX 0.2

    double rollingX;

    pAccelerationValue->x = pAccelerationValue->y;
    rollingX = (pAccelerationValue->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
    float accelX = pAccelerationValue->x - rollingX;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float accelDiff = accelX - KRESTACCELX;
    float accelFraction = accelDiff / KMAXDIFFX;
    _shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) {
    if (!_gameOver) {
        SimpleAudioEngine::getInstance()->playEffect("Sounds/laser_ship.wav");
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Sprite *shipLaser = (Sprite *)_shipLasers.at(_nextShipLaser++);
        if (_nextShipLaser >= _shipLasers.size()) {
            _nextShipLaser = 0;
        }
        shipLaser->setPosition(_ship->getPosition() + Vec2(shipLaser->getContentSize().width / 2, 0));
        shipLaser->setVisible(true);
        shipLaser->stopAllActions();
        shipLaser->runAction(Sequence::create(MoveBy::create(0.5, Vec2(visibleSize.width, 0)),
            CallFuncN::create(this, callfuncN_selector(HelloWorld::setInvisible)), NULL));
    }
}

void HelloWorld::setInvisible(Node * node) {
    node->setVisible(false);
}

float HelloWorld::randomValueBetween(float low, float high) {
    return (((float) arc4random() / 0xFFFFFFFFu) * (high - low)) + low;
}

float HelloWorld::getTimeTick() {
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (float) millisecs;
}

void HelloWorld::restartTapped(cocos2d::Ref * ignore) {
    Director::getInstance()->replaceScene(
        (TransitionZoomFlipX::create(0.5, HelloWorld::createScene())));
    // reschedule
    this->scheduleUpdate();
}

void HelloWorld::endScene( EndReason endReason ) {
    if (_gameOver)
        return;
    _gameOver = true;

    Size visibleSize = Director::getInstance()->getWinSize();
    char message[10] = "You Win";
    if (endReason == KENDREASONLOSE) {
        strcpy(message,"You Lose");
    }
    LabelBMFont * label ;
    label = LabelBMFont::create(message, "fonts/Arial.fnt");
    label->setScale(0.1);
    label->setPosition(Vec2(visibleSize.width/2 , visibleSize.height*0.6));
    this->addChild(label);

    LabelBMFont * restartLabel;
    strcpy(message,"Restart");
    restartLabel = LabelBMFont::create(message, "fonts/Arial.fnt");
    MenuItemLabel *restartItem = MenuItemLabel::create(restartLabel, this, menu_selector(HelloWorld::restartTapped));
    restartItem->setScale(0.1);
    restartItem->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.4));

    Menu *menu = Menu::create(restartItem, NULL);
    menu->setPosition(Vec2(0, 0));
    this->addChild(menu);

    // clear label and menu
    restartItem->runAction(ScaleTo::create(0.5, 1.0));
    label ->runAction(ScaleTo::create(0.5, 1.0));
    // Terminate update callback
    this->unscheduleUpdate();
}
