#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "controllers/GameController.h"

// 游戏主场景入口，负责初始化基础环境并启动业务 Controller
class HelloWorld : public cocos2d::Scene
{
public:
    HelloWorld() = default;
    virtual ~HelloWorld();

    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(HelloWorld);

private:
    GameController* _gameController{ nullptr };
};

#endif // __HELLOWORLD_SCENE_H__