#include "views/CardView.h"

USING_NS_CC;

CardView* CardView::create(CardModel* cardModel)
{
    auto ret = new (std::nothrow) CardView();
    if (ret && ret->initWithModel(cardModel)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool CardView::initWithModel(CardModel* cardModel)
{
    if (!Node::init()) return false;
    _cardModel = cardModel;

    _backgroundSprite = Sprite::create("res/card_general.png");
    if (_backgroundSprite) {
        _backgroundSprite->setScale(2.5f);
        addChild(_backgroundSprite, 0);
    }

    _cornerLabel = Label::createWithSystemFont("", "Arial", 28, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
    _cornerLabel->setAnchorPoint(Vec2(0, 1));
    _cornerLabel->setPosition(Vec2(-45, 65));
    addChild(_cornerLabel, 1);

    _cornerSuit = Label::createWithSystemFont("", "Arial", 32, Size::ZERO, TextHAlignment::LEFT, TextVAlignment::TOP);
    _cornerSuit->setAnchorPoint(Vec2(0, 1));
    _cornerSuit->setPosition(Vec2(-15, 62));
    addChild(_cornerSuit, 1);

    _centerLabel = Label::createWithSystemFont("", "Arial", 80, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    _centerLabel->setPosition(Vec2(0, -10));
    addChild(_centerLabel, 1);

    if (_cardModel) setPosition(_cardModel->getPosition());

    refreshView();
    initTouchListener();

    return true;
}

void CardView::initTouchListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        if (!_cardModel || !_backgroundSprite) return false;
        if (_cardModel->isRemoved() || getNumberOfRunningActions() > 0) return false;

        Vec2 localPoint = this->convertToNodeSpace(touch->getLocation());
        if (_backgroundSprite->getBoundingBox().containsPoint(localPoint)) {
            if (_onCardClickCallback) _onCardClickCallback(_cardModel->getId());
            return true;
        }
        return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

CardModel* CardView::getCardModel() const { return _cardModel; }
int CardView::getCardId() const { return _cardModel ? _cardModel->getId() : -1; }

void CardView::refreshView()
{
    if (!_cardModel) return;

    if (_cardModel->isFaceUp()) {
        if (_backgroundSprite) {
            _backgroundSprite->setTexture("res/card_general.png");
            _backgroundSprite->setColor(Color3B::WHITE);
        }

        int face = _cardModel->getFace();
        std::string faceText;
        if (face == 0) faceText = "A";
        else if (face == 10) faceText = "J";
        else if (face == 11) faceText = "Q";
        else if (face == 12) faceText = "K";
        else faceText = std::to_string(face + 1);

        _cornerLabel->setString(faceText);
        _centerLabel->setString(faceText);

        int suit = _cardModel->getSuit();
        std::string suitSymbol;
        Color4B textColor;

        if (suit == 0) { suitSymbol = "\xE2\x99\xA3"; textColor = Color4B::BLACK; }
        else if (suit == 1) { suitSymbol = "\xE2\x99\xA6"; textColor = Color4B::RED; }
        else if (suit == 2) { suitSymbol = "\xE2\x99\xA5"; textColor = Color4B::RED; }
        else if (suit == 3) { suitSymbol = "\xE2\x99\xA0"; textColor = Color4B::BLACK; }

        _cornerLabel->setTextColor(textColor);
        _centerLabel->setTextColor(textColor);
        _cornerSuit->setString(suitSymbol);
        _cornerSuit->setTextColor(textColor);

        _cornerLabel->setVisible(true);
        _centerLabel->setVisible(true);
        _cornerSuit->setVisible(true);
    }
    else {
        if (_backgroundSprite) {
            _backgroundSprite->setTexture("res/card_general.png");
            _backgroundSprite->setColor(Color3B(100, 150, 200));
        }
        _cornerLabel->setVisible(false);
        _centerLabel->setVisible(false);
        _cornerSuit->setVisible(false);
    }

    if (getNumberOfRunningActions() == 0) {
        setVisible(!_cardModel->isRemoved());
        setPosition(_cardModel->getPosition());
    }
}

void CardView::playMoveTo(const Vec2& targetPosition, float duration)
{
    stopAllActions();
    auto callFunc = CallFunc::create([this]() { this->refreshView(); });
    runAction(Sequence::create(MoveTo::create(duration, targetPosition), callFunc, nullptr));
}

void CardView::setOnCardClickCallback(const std::function<void(int)>& callback) { _onCardClickCallback = callback; }