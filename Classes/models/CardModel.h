#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "cocos2d.h"

class CardModel
{
public:
    CardModel() = default;
    CardModel(int id, int face, int suit, const cocos2d::Vec2& position);

    int getId() const;
    int getFace() const;
    int getSuit() const;
    const cocos2d::Vec2& getPosition() const;
    const cocos2d::Vec2& getOriginalPosition() const;

    void setPosition(const cocos2d::Vec2& position);
    bool isFaceUp() const;
    void setFaceUp(bool faceUp);
    bool isRemoved() const;
    void setRemoved(bool removed);

private:
    int _id{ -1 };
    int _face{ 0 };
    int _suit{ 0 };
    cocos2d::Vec2 _position{ cocos2d::Vec2::ZERO };
    cocos2d::Vec2 _originalPosition{ cocos2d::Vec2::ZERO };
    bool _isFaceUp{ true };
    bool _isRemoved{ false };
};

#endif // __CARD_MODEL_H__