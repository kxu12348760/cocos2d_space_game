#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ParallaxNodeExtras.h"

USING_NS_CC;

typedef enum {
  KENDREASONWIN,
  KENDREASONLOSE
} EndReason;

class HelloWorld : public cocos2d::Layer
{
private:
    SpriteBatchNode * _batchNode;
    Sprite * _ship;
    ParallaxNodeExtras * _backgroundNode;
    // ParallaxNode * _backgroundNode;
    Sprite * _spacedust1;
    Sprite * _spacedust2;
    Sprite * _planetsunrise;
    Sprite * _galaxy;
    Sprite * _spacialanomaly;
    Sprite * _spacialanomaly2;
    float _shipPointsPerSecY;

    Vector<Sprite *> _shipLasers;
    int _nextShipLaser;

    Vector<Sprite *> _asteroids;
    int _nextAsteroid;
    float _nextAsteroidSpawn;

    Vector<Sprite *> _enemyShips;
    int _nextEnemyShip;
    float _nextEnemySpawn;

    int _lives;

    void update(float dt);

    double _gameOverTime;
    bool _gameOver;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    virtual void onAcceleration(Acceleration* pAccelerationValue, Event* unused_event);

    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);

    void setInvisible(Node * node);
    float randomValueBetween(float low, float high);
    float getTimeTick();

    void endScene(EndReason endReason);
    void restartTapped(cocos2d::Ref * ignore);
};

#endif // __HELLOWORLD_SCENE_H__
