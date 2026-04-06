#include "views/GameView.h"

USING_NS_CC;

GameView::~GameView()
{
    if (_topCardView) delete _topCardView->getCardModel();
}

GameView* GameView::create(GameModel* gameModel)
{
    auto ret = new (std::nothrow) GameView();
    if (ret && ret->initWithModel(gameModel)) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool GameView::initWithModel(GameModel* gameModel)
{
    if (!Node::init()) return false;
    _gameModel = gameModel;

    buildPlayFieldViews();
    buildHandCardViews();
    createUndoButton();

    if (_gameModel) {
        initTopCardView(_gameModel->getTopFace(), _gameModel->getTopSuit(), _gameModel->getTopCardPosition());
    }
    return true;
}

void GameView::buildPlayFieldViews()
{
    if (!_gameModel) return;

    for (auto cardModel : _gameModel->getPlayFieldCards()) {
        if (!cardModel) continue;
        auto cardView = CardView::create(cardModel);
        if (!cardView) continue;

        cardView->setLocalZOrder(2080 - static_cast<int>(cardModel->getPosition().y));
        cardView->setOnCardClickCallback([this](int cardId) {
            if (_onCardClickCallback) _onCardClickCallback(cardId);
            });

        addChild(cardView);
        _cardViewMap[cardModel->getId()] = cardView;
    }
}

void GameView::buildHandCardViews()
{
    if (!_gameModel) return;

    for (auto cardModel : _gameModel->getHandCards()) {
        if (!cardModel) continue;
        auto cardView = CardView::create(cardModel);
        if (!cardView) continue;

        cardView->setOnCardClickCallback([this](int cardId) {
            if (_onHandCardClickCallback) _onHandCardClickCallback(cardId);
            });

        addChild(cardView);
        _cardViewMap[cardModel->getId()] = cardView;
        _handCardViews.push_back(cardView);
    }
}

void GameView::createUndoButton()
{
    auto undoLabel = Label::createWithSystemFont("UNDO", "Arial", 46, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    undoLabel->setTextColor(Color4B::WHITE);

    auto bg = LayerColor::create(Color4B(0, 0, 0, 100), 160, 80);
    bg->ignoreAnchorPointForPosition(false);
    bg->setAnchorPoint(Vec2(0.5f, 0.5f));
    bg->setPosition(Vec2(undoLabel->getContentSize().width / 2, undoLabel->getContentSize().height / 2));
    undoLabel->addChild(bg, -1);

    auto undoItem = MenuItemLabel::create(undoLabel, CC_CALLBACK_1(GameView::onUndoButtonClicked, this));
    _undoMenu = Menu::create(undoItem, nullptr);
    _undoMenu->setPosition(Vec2(900.0f, 290.0f));
    addChild(_undoMenu, 20);
}

void GameView::onUndoButtonClicked(Ref* sender) { if (_onUndoClickCallback) _onUndoClickCallback(); }
void GameView::setOnCardClickCallback(const std::function<void(int)>& callback) { _onCardClickCallback = callback; }
void GameView::setOnHandCardClickCallback(const std::function<void(int)>& callback) { _onHandCardClickCallback = callback; }
void GameView::setOnUndoClickCallback(const std::function<void()>& callback) { _onUndoClickCallback = callback; }

void GameView::refreshAllCardViews()
{
    for (auto& pair : _cardViewMap) {
        if (pair.second) pair.second->refreshView();
    }
    if (_topCardView) _topCardView->refreshView();
}

void GameView::playMatchAnimation(int cardId, const Vec2& targetPosition)
{
    if (auto cardView = getCardViewById(cardId)) {
        cardView->setLocalZOrder(2080);
        cardView->playMoveTo(targetPosition, 0.3f);
    }
}

CardView* GameView::getCardViewById(int cardId) const
{
    auto it = _cardViewMap.find(cardId);
    return it != _cardViewMap.end() ? it->second : nullptr;
}

void GameView::initTopCardView(int face, int suit, const Vec2& position)
{
    if (_topCardView) return;
    CardModel* topCardModel = new CardModel(-1000, face, suit, position);
    _topCardView = CardView::create(topCardModel);
    if (_topCardView) addChild(_topCardView, 10);
}

void GameView::updateTopCardView(int face, int suit)
{
    Vec2 pos = _gameModel ? _gameModel->getTopCardPosition() : Vec2(540.0f, 260.0f);
    if (_topCardView) {
        CardModel* oldModel = _topCardView->getCardModel();
        removeChild(_topCardView);
        delete oldModel;
        _topCardView = nullptr;
    }
    CardModel* newTopModel = new CardModel(-1000, face, suit, pos);
    _topCardView = CardView::create(newTopModel);
    if (_topCardView) addChild(_topCardView, 10);
}