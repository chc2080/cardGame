#include "controllers/GameController.h"
#include "services/CardMatchService.h"

USING_NS_CC;

GameController::~GameController()
{
    delete _gameModel;
    delete _undoManager;
}

bool GameController::startGame(Node* parentNode)
{
    if (!parentNode) return false;

    _undoManager = new UndoManager();

    createTestGameModel();
    updatePlayFieldFaceUpState();
    createGameView(parentNode);

    return _gameModel && _gameView;
}

void GameController::createTestGameModel()
{
    if (_gameModel) {
        delete _gameModel;
        _gameModel = nullptr;
    }

    _gameModel = new GameModel();
    if (!_gameModel) return;

    float offsetY = 350.0f;
    _gameModel->addPlayFieldCard(new CardModel(0, 12, 0, Vec2(250, 1000 + offsetY)));
    _gameModel->addPlayFieldCard(new CardModel(1, 2, 0, Vec2(300, 800 + offsetY)));
    _gameModel->addPlayFieldCard(new CardModel(2, 2, 1, Vec2(350, 600 + offsetY)));
    _gameModel->addPlayFieldCard(new CardModel(3, 2, 0, Vec2(850, 1000 + offsetY)));
    _gameModel->addPlayFieldCard(new CardModel(4, 2, 0, Vec2(800, 800 + offsetY)));
    _gameModel->addPlayFieldCard(new CardModel(5, 1, 3, Vec2(750, 600 + offsetY)));

    _gameModel->setTopFace(2);
    _gameModel->setTopSuit(0);
    _gameModel->setTopCardPosition(Vec2(650.0f, 290.0f));

    Vec2 deckBasePos(350.0f, 290.0f);

    auto card101 = new CardModel(101, 0, 2, deckBasePos + Vec2(-25, 0));
    card101->setFaceUp(false);
    _gameModel->addHandCard(card101);

    auto card102 = new CardModel(102, 3, 0, deckBasePos);
    card102->setFaceUp(false);
    _gameModel->addHandCard(card102);
}

void GameController::createGameView(Node* parentNode)
{
    if (!parentNode || !_gameModel) return;

    _gameView = GameView::create(_gameModel);
    if (!_gameView) return;

    _gameView->setOnCardClickCallback([this](int cardId) { this->handleCardClick(cardId); });
    _gameView->setOnHandCardClickCallback([this](int cardId) { this->handleHandCardClick(cardId); });
    _gameView->setOnUndoClickCallback([this]() { this->handleUndoClick(); });

    parentNode->addChild(_gameView);
    _gameView->refreshAllCardViews();
}

void GameController::updatePlayFieldFaceUpState()
{
    if (!_gameModel) return;

    const auto& cards = _gameModel->getPlayFieldCards();

    for (auto current : cards) {
        if (!current || current->isRemoved()) continue;

        bool covered = false;
        for (auto other : cards) {
            if (!other || other == current || other->isRemoved()) continue;

            if (other->getPosition().y > current->getPosition().y) {
                float dx = std::abs(other->getPosition().x - current->getPosition().x);
                float dy = std::abs(other->getPosition().y - current->getPosition().y);

                if (dx <= 120.0f && dy <= 260.0f) {
                    covered = true;
                    break;
                }
            }
        }
        current->setFaceUp(!covered);
    }
}

bool GameController::handleCardClick(int cardId)
{
    if (!_gameModel || !_gameView || !_undoManager) return false;

    CardModel* cardModel = _gameModel->getCardById(cardId);
    if (!cardModel || cardModel->isRemoved() || !cardModel->isFaceUp()) return false;

    int topFace = _gameModel->getTopFace();
    int cardFace = cardModel->getFace();
    int cardSuit = cardModel->getSuit();

    if (!CardMatchService::canMatch(cardFace, topFace)) {
        CCLOG("playfield match failed");
        return false;
    }

    UndoModel record(cardId, cardModel->getPosition(), _gameModel->getTopCardPosition(),
        _gameModel->getTopFace(), _gameModel->getTopSuit(), cardModel->isRemoved());
    _undoManager->pushRecord(record);

    _gameView->playMatchAnimation(cardId, _gameModel->getTopCardPosition());

    cardModel->setPosition(_gameModel->getTopCardPosition());
    cardModel->setRemoved(true);

    _gameModel->setTopFace(cardFace);
    _gameModel->setTopSuit(cardSuit);

    updatePlayFieldFaceUpState();
    _gameView->updateTopCardView(cardFace, cardSuit);
    _gameView->refreshAllCardViews();

    return true;
}

bool GameController::handleHandCardClick(int cardId)
{
    if (!_gameModel || !_gameView || !_undoManager) return false;

    CardModel* cardModel = _gameModel->getCardById(cardId);
    if (!cardModel || cardModel->isRemoved()) return false;

    const auto& handCards = _gameModel->getHandCards();
    CardModel* topOfDeck = nullptr;
    for (auto c : handCards) {
        if (!c->isRemoved()) topOfDeck = c;
    }
    if (cardModel != topOfDeck) return false;

    UndoModel record(cardId, cardModel->getPosition(), _gameModel->getTopCardPosition(),
        _gameModel->getTopFace(), _gameModel->getTopSuit(), cardModel->isRemoved());
    _undoManager->pushRecord(record);

    cardModel->setFaceUp(true);
    _gameView->playMatchAnimation(cardId, _gameModel->getTopCardPosition());

    cardModel->setPosition(_gameModel->getTopCardPosition());
    cardModel->setRemoved(true);

    _gameModel->setTopFace(cardModel->getFace());
    _gameModel->setTopSuit(cardModel->getSuit());

    _gameView->updateTopCardView(cardModel->getFace(), cardModel->getSuit());
    _gameView->refreshAllCardViews();

    return true;
}

void GameController::handleUndoClick()
{
    if (!_gameModel || !_gameView || !_undoManager) return;
    if (!_undoManager->canUndo()) return;

    UndoModel record = _undoManager->popRecord();
    CardModel* card = _gameModel->getCardById(record.getCardId());
    if (!card) return;

    bool isFromDeck = false;
    for (auto c : _gameModel->getHandCards()) {
        if (c->getId() == card->getId()) {
            isFromDeck = true;
            break;
        }
    }

    card->setRemoved(false);
    card->setPosition(record.getFromPos());

    if (isFromDeck) card->setFaceUp(false);

    _gameModel->setTopFace(record.getPrevTopFace());
    _gameModel->setTopSuit(record.getPrevTopSuit());

    if (auto view = _gameView->getCardViewById(record.getCardId())) {
        view->setVisible(true);
        view->setLocalZOrder(2000);
        view->setPosition(_gameModel->getTopCardPosition());
        _gameView->playMatchAnimation(card->getId(), record.getFromPos());
    }

    updatePlayFieldFaceUpState();
    _gameView->updateTopCardView(record.getPrevTopFace(), record.getPrevTopSuit());
    _gameView->refreshAllCardViews();
}