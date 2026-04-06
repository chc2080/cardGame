#include "models/CardModel.h"

CardModel::CardModel(int id, int face, int suit, const cocos2d::Vec2& position)
    : _id(id), _face(face), _suit(suit), _position(position), _originalPosition(position) {
}

int CardModel::getId() const { return _id; }
int CardModel::getFace() const { return _face; }
int CardModel::getSuit() const { return _suit; }
const cocos2d::Vec2& CardModel::getPosition() const { return _position; }
const cocos2d::Vec2& CardModel::getOriginalPosition() const { return _originalPosition; }
void CardModel::setPosition(const cocos2d::Vec2& position) { _position = position; }
bool CardModel::isFaceUp() const { return _isFaceUp; }
void CardModel::setFaceUp(bool faceUp) { _isFaceUp = faceUp; }
bool CardModel::isRemoved() const { return _isRemoved; }
void CardModel::setRemoved(bool removed) { _isRemoved = removed; }