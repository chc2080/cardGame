#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

// 核心业务控制器：协调游戏模型与视图，处理匹配、发牌、撤销等全局逻辑
class GameController
{
public:
    GameController() = default;
    ~GameController();

    bool startGame(cocos2d::Node* parentNode);

    bool handleCardClick(int cardId);
    bool handleHandCardClick(int cardId);
    void handleUndoClick();

private:
    void createTestGameModel();
    void createGameView(cocos2d::Node* parentNode);
    void updatePlayFieldFaceUpState();

private:
    GameModel* _gameModel{ nullptr };
    GameView* _gameView{ nullptr };
    UndoManager* _undoManager{ nullptr };
};

#endif // __GAME_CONTROLLER_H__