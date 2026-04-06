#include "models/GameModel.h"

GameModel::~GameModel()
{
    for (auto c : _playFieldCards) delete c;
    _playFieldCards.clear();

    for (auto c : _handCards) delete c;
    _handCards.clear();
}

void GameModel::addPlayFieldCard(CardModel* card)
{
    if (card) _playFieldCards.push_back(card);
}

void GameModel::addHandCard(CardModel* card)
{
    if (card) _handCards.push_back(card);
}

const std::vector<CardModel*>& GameModel::getPlayFieldCards() const { return _playFieldCards; }
const std::vector<CardModel*>& GameModel::getHandCards() const { return _handCards; }

CardModel* GameModel::getCardById(int id) const
{
    for (auto c : _playFieldCards) {
        if (c && c->getId() == id) return c;
    }
    for (auto c : _handCards) {
        if (c && c->getId() == id) return c;
    }
    return nullptr;
}

void GameModel::setTopFace(int face) { _topFace = face; }
int GameModel::getTopFace() const { return _topFace; }
void GameModel::setTopSuit(int suit) { _topSuit = suit; }
int GameModel::getTopSuit() const { return _topSuit; }
void GameModel::setTopCardPosition(const cocos2d::Vec2& pos) { _topCardPosition = pos; }
const cocos2d::Vec2& GameModel::getTopCardPosition() const { return _topCardPosition; }