#ifndef __CARDVIEW_H__
#define __CARDVIEW_H__

#include "cocos2d.h"
#include "models/CardModel.h"
#include <functional>

// 负责单张卡牌的 UI 渲染与交互事件监听
class CardView : public cocos2d::Node
{
public:
    CardView() = default;
    ~CardView() = default;

    static CardView* create(CardModel* cardModel);
    bool initWithModel(CardModel* cardModel);

    void setOnCardClickCallback(const std::function<void(int)>& callback);
    void refreshView();
    void playMoveTo(const cocos2d::Vec2& targetPosition, float duration);

    CardModel* getCardModel() const;
    int getCardId() const;

protected:
    void initTouchListener();

private:
    CardModel* _cardModel{ nullptr };
    cocos2d::Sprite* _backgroundSprite{ nullptr };
    cocos2d::Label* _cornerLabel{ nullptr };
    cocos2d::Label* _cornerSuit{ nullptr };
    cocos2d::Label* _centerLabel{ nullptr };

    std::function<void(int)> _onCardClickCallback;
};

#endif // __CARDVIEW_H__