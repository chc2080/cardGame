#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include <unordered_map>
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/CardView.h"

// 负责游戏主场景的渲染、动画分发与全局 UI 交互
class GameView : public cocos2d::Node
{
public:
    GameView() = default;
    ~GameView();

    static GameView* create(GameModel* gameModel);

    void setOnCardClickCallback(const std::function<void(int)>& callback);
    void setOnHandCardClickCallback(const std::function<void(int)>& callback);
    void setOnUndoClickCallback(const std::function<void()>& callback);

    void refreshAllCardViews();
    void playMatchAnimation(int cardId, const cocos2d::Vec2& targetPosition);

    CardView* getCardViewById(int cardId) const;

    void initTopCardView(int face, int suit, const cocos2d::Vec2& position);
    void updateTopCardView(int face, int suit);

protected:
    bool initWithModel(GameModel* gameModel);

    void buildPlayFieldViews();
    void buildHandCardViews();
    void createUndoButton();
    void onUndoButtonClicked(cocos2d::Ref* sender);

private:
    GameModel* _gameModel{ nullptr };
    std::unordered_map<int, CardView*> _cardViewMap;
    std::vector<CardView*> _handCardViews;

    CardView* _topCardView{ nullptr };
    cocos2d::Menu* _undoMenu{ nullptr };

    std::function<void(int)> _onCardClickCallback;
    std::function<void(int)> _onHandCardClickCallback;
    std::function<void()> _onUndoClickCallback;
};

#endif // __GAME_VIEW_H__