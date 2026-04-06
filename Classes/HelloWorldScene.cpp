#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::~HelloWorld()
{
    if (_gameController) {
        delete _gameController;
        _gameController = nullptr;
    }
}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init()) return false;

    auto topBg = LayerColor::create(Color4B(179, 136, 84, 255), 1080, 1500);
    topBg->setPosition(Vec2(0, 580));
    this->addChild(topBg, -1);

    auto bottomBg = LayerColor::create(Color4B(153, 33, 153, 255), 1080, 580);
    bottomBg->setPosition(Vec2(0, 0));
    this->addChild(bottomBg, -1);

    _gameController = new GameController();
    _gameController->startGame(this);

    return true;
}