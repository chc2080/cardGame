#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <vector>
#include "models/CardModel.h"

class GameModel
{
public:
    GameModel() = default;
    ~GameModel();

    // ÈÝÆ÷¹ÜÀí
    void addPlayFieldCard(CardModel* card);
    void addHandCard(CardModel* card);
    const std::vector<CardModel*>& getPlayFieldCards() const;
    const std::vector<CardModel*>& getHandCards() const;
    CardModel* getCardById(int id) const;

    // ¶¥²¿µ×ÅÆ×´Ì¬
    void setTopFace(int face);
    int getTopFace() const;
    void setTopSuit(int suit);
    int getTopSuit() const;
    void setTopCardPosition(const cocos2d::Vec2& pos);
    const cocos2d::Vec2& getTopCardPosition() const;

private:
    std::vector<CardModel*> _playFieldCards;
    std::vector<CardModel*> _handCards;

    int _topFace{ 5 };
    int _topSuit{ 0 };
    cocos2d::Vec2 _topCardPosition{ cocos2d::Vec2(540.0f, 260.0f) };
};

#endif // __GAME_MODEL_H__