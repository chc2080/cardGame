#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include "cocos2d.h"

class UndoModel
{
public:
    UndoModel() = default;
    UndoModel(int cardId, const cocos2d::Vec2& fromPos, const cocos2d::Vec2& toPos, int prevTopFace, int prevTopSuit, bool prevRemoved);

    int getCardId() const;
    const cocos2d::Vec2& getFromPos() const;
    const cocos2d::Vec2& getToPos() const;
    int getPrevTopFace() const;
    int getPrevTopSuit() const;
    bool getPrevRemoved() const;

private:
    int _cardId{ -1 };
    cocos2d::Vec2 _fromPos{ cocos2d::Vec2::ZERO };
    cocos2d::Vec2 _toPos{ cocos2d::Vec2::ZERO };
    int _prevTopFace{ 0 };
    int _prevTopSuit{ 0 };
    bool _prevRemoved{ false };
};

#endif // __UNDO_MODEL_H__