#include "models/UndoModel.h"

UndoModel::UndoModel(int cardId, const cocos2d::Vec2& fromPos, const cocos2d::Vec2& toPos, int prevTopFace, int prevTopSuit, bool prevRemoved)
    : _cardId(cardId), _fromPos(fromPos), _toPos(toPos), _prevTopFace(prevTopFace), _prevTopSuit(prevTopSuit), _prevRemoved(prevRemoved) {
}

int UndoModel::getCardId() const { return _cardId; }
const cocos2d::Vec2& UndoModel::getFromPos() const { return _fromPos; }
const cocos2d::Vec2& UndoModel::getToPos() const { return _toPos; }
int UndoModel::getPrevTopFace() const { return _prevTopFace; }
int UndoModel::getPrevTopSuit() const { return _prevTopSuit; }
bool UndoModel::getPrevRemoved() const { return _prevRemoved; }