
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//
#include "GameScene.h"
#include "ButtonCustom.h"
#include "GameDefine.h"
#include "HomeScene.h"
#include "MainObject.h"
#include "MyLine.h"
#include "DrawLine.h"
#include "PopupGame.h"
#include "AdmobManager.h"

Scene* GameScene::createSceneGameScene() {
  auto scene = Scene::create();
  auto layer = GameScene::create();
  scene->addChild(layer);
  return scene;
}

bool GameScene::init() {
  if (!Layer::init()) { return false; }
  countSuggest = 3;
  countRefresh = 3;
  isPausing = false;
  
  countTouch = 0;
  winSize = Director::getInstance()->getWinSize();
  auto background = Sprite::create("bgGameScene.png");
  background->setPosition(Vec2(winSize.width/2, winSize.height/2));
  this->addChild(background);
  
  level = UserDefault::getInstance()->getIntegerForKey("highestLevel", 1);
  gameBoard = new GameBoard(TOTAL_ROW,TOTAL_COLUMN, RandomIndex::getInstance()->getDropObjectType(level));
  gameBoard->setPosition(Vec2((winSize.width - gameBoard->getRealContentSize().width)/2.0, -SHAPE_HEIGHT + SHAPE_HEIGHT/2.0 + THICKNESS_DRAW_LINE));
  gameBoard->createGameBoard(level);

  checkPairBot = new CheckPairBot();
  checkPairBot->setWidthAndHeightMatrix(TOTAL_ROW, TOTAL_COLUMN);
  checkPairBot->setArrayValueVisible(gameBoard->getArrayValueObject());
  checkPairBot->setDelegate(this);
  
  gameBoard->setSuggestBotForGame(checkPairBot);
  gameBoard->findPairConnectionObject(false, 0.0);
  this->addChild(gameBoard, TAG_GAME_BOARD);
  
  this->createHeaderGameScene(level);
  this->createLayerStartGame();
  
  auto touch = EventListenerTouchOneByOne::create();
  touch->setSwallowTouches(true);
  touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBeginGameScene, this);
  touch->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEndGameScene, this);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
  this->scheduleUpdate();
  showFullScreenAdvertisement(OPEN_GAME_SCENE_KEY, OPEN_GAME_SCENE_FREQUENCY);
  return true;
}

bool GameScene::onTouchBeginGameScene(Touch* mtouch, Event* pEvent) {
  if(gameBoard && !isPausing) {
    if(countTouch < 2) {
      Vec2 pos = gameBoard->convertMatrixGameBoard(mtouch->getLocation());
      if(pos.x >= 1 && pos.x <= TOTAL_ROW-2 && pos.y >=1 && pos.y <= TOTAL_COLUMN-2) {
        if(gameBoard->getAtPosGameBoard(pos)->getValueVisible() != HIDDEN_OBJECT) {
          if (pos.x == posTouchOne.x && pos.y == posTouchOne.y && countTouch == 1) {
            MainObject* object = gameBoard->getAtPosGameBoard(pos);
            object->backToNormalObject();
            posTouchOne = OUT_OF_GAME_BOARD_MATRIX;
            countTouch = 0;
          } else {
            countTouch ++;
            if(countTouch %2 == 1) { posTouchOne = pos; }
            MainObject* object = gameBoard->getAtPosGameBoard(pos);
            object->actionWhenClick();
            return true;
          }
        }
      }
    }
  }
  return false;
}

void GameScene::onTouchEndGameScene(Touch* mTouch, Event* pEvent) {
  if(countTouch == 2 && !isPausing) {
    posTouchTwo = gameBoard->convertMatrixGameBoard(mTouch->getLocation());
    if(posTouchTwo.x >= 1 && posTouchTwo.x <= TOTAL_ROW-2 && posTouchTwo.y >=1 && posTouchTwo.y <= TOTAL_COLUMN-2) {
      MyLine lineGame = checkPairBot->checkTwoPoint(posTouchOne, posTouchTwo, true, TIME_DELAY_DRAW_LINE);
      MainObject* object1 = gameBoard->getAtPosGameBoard(posTouchOne);
      MainObject* object2 = gameBoard->getAtPosGameBoard(posTouchTwo);
      if (lineGame.isZeroLine()) {
        object1->backToNormalObject();
        object2->backToNormalObject();
      } else {
        if(object1->getTypeObject() == object2->getTypeObject()) {
          this->scheduleOnce([=](float dt){
            object1->effectWhenDieObject();
            object2->effectWhenDieObject();
            gameBoard->setHiddenObjects(posTouchOne, posTouchTwo);
            gameBoard->dropObjectInGameBoard();
            checkPairBot->setArrayValueVisible(gameBoard->getArrayValueObject());
            if(gameBoard->getCurrentListVisibleObject().empty()) {
              isPausing = true;
              this->createPopUpWin();
            } else {
              gameBoard->findPairConnectionObject(false, 0.0);
            }
          }, TIME_DELAY_DRAW_LINE, "drop_object");
        } else {
          object1->backToNormalObject();
          object2->backToNormalObject();
        }
      }
      countTouch = 0;
    }
  }
}

void GameScene::createHeaderGameScene(int level) {
  float topGameBoard = gameBoard->getPositionY() + gameBoard->getRealContentSize().height - 32.0;
  progressBar = new ProgressBarCustom();
  progressBar->setPosition(Vec2(winSize.width/2, topGameBoard));
  progressBar->createUIProgressBar();
  progressBar->setDelegate(this);
  this->addChild(progressBar);
  
  ui::Button* backButton = ui::Button::create("backButton.png","","",ui::Widget::TextureResType::LOCAL);
  backButton->setPosition(Vec2(gameBoard->getPositionX()
                               + SHAPE_WIDTH/2.0
                               + backButton->getContentSize().width,
                               progressBar->getPositionY()));
  backButton->setTag(TAG_BTN_BACK);
  backButton->addClickEventListener(CC_CALLBACK_1(GameScene::handleClickButton,this));
  this->addChild(backButton);
  
  char bufferLevel[20] = {0};
  snprintf(bufferLevel, sizeof(bufferLevel), "Level: %d", level);
  Label* levelLabel = Label::createWithTTF(bufferLevel, "GROBOLD.ttf", 50);
  levelLabel->setAnchorPoint(Vec2(0, 0.5));
  levelLabel->setPosition(Vec2(backButton->getPositionX() + backButton->getContentSize().width/2.0 + 64.0,
                               backButton->getPositionY()));
  this->addChild(levelLabel);
  
  pauseButton = new ButtonCustom("pauseButton.png");
  pauseButton->setTagButton(TAG_BTN_PAUSE);
  pauseButton->setValueText(0);
  pauseButton->setPosition(Vec2(gameBoard->getPositionX() + gameBoard->getRealContentSize().width - SHAPE_WIDTH
                                - pauseButton->getContentSize().width/2,
                                progressBar->getPositionY()));
  pauseButton->setDelegate(this);
  this->addChild(pauseButton);
  
  refreshButton = new ButtonCustom("refreshButton.png");
  refreshButton->setPosition(Vec2(pauseButton->getPositionX()
                                  - pauseButton->getContentSize().width/2.0
                                  - refreshButton->getContentSize().width,
                                  pauseButton->getPositionY()));
  refreshButton->setValueText(countRefresh);
  refreshButton->setTagButton(TAG_BTN_REFRESH);
  refreshButton->setDelegate(this);
  this->addChild(refreshButton);
  
  suggestButton = new ButtonCustom("suggestButton.png");
  suggestButton->setTagButton(TAG_BTN_SUGGEST);
  suggestButton->setValueText(countSuggest);
  suggestButton->setPosition(Vec2(refreshButton->getPositionX()
                                  - refreshButton->getContentSize().width/2.0
                                  - suggestButton->getContentSize().width,
                                  pauseButton->getPositionY()));
  suggestButton->setDelegate(this);
  this->addChild(suggestButton);
}

void GameScene::endTime() {
  this->createPopupGameOver();
}

void GameScene::receiveTimeRemainingFromProgressBar(int timeRemaining) {
  if(timeRemaining == TOTAL_TIME_SECOND_PROGRESS_BAR/2 + AD_DURATION) {
    AdmobManager::getInstance()->showBanner();
  } else if(timeRemaining == TOTAL_TIME_SECOND_PROGRESS_BAR/2) {
    AdmobManager::getInstance()->hideBanner();
  }
}

void GameScene::update(float dt) {
  if(isPausing) { return; }
  gameBoard->update(dt);
}


void GameScene::handleClickEventOnPopUp(int tag) {
  switch (tag) {
    case TAG_PAUSE_PLAY:
      if (this->getChildByTag(TAG_POP_UP_PAUSE)) {
        this->removeChildByTag(TAG_POP_UP_PAUSE);
        isPausing = false;
        progressBar->setStatus(RUNNING);
        gameBoard->playGameBoard();
      }
      AdmobManager::getInstance()->hideBanner();
      break;
    case TAG_PAUSE_HOME:
      Director::getInstance()->replaceScene(HomeScene::createHomeScene());
      break;
    case TAG_YES_BUTTON:
      Director::getInstance()->replaceScene(HomeScene::createHomeScene());
      break;
    case TAG_NO_BUTTON:
      if (this->getChildByTag(TAG_POP_UP_BACK)) {
        this->removeChildByTag(TAG_POP_UP_BACK);
        isPausing = false;
        progressBar->setStatus(RUNNING);
        gameBoard->playGameBoard();
      }
      AdmobManager::getInstance()->hideBanner();
      break;
    case TAG_WIN_NEXT:
      UserDefault::getInstance()->setIntegerForKey("highestLevel", UserDefault::getInstance()->getIntegerForKey("highestLevel", 1) + 1);
      Director::getInstance()->replaceScene(GameScene::createSceneGameScene());
      AdmobManager::getInstance()->hideBanner();
      break;
    case TAG_OVER_REPLAY:
      UserDefault::getInstance()->setIntegerForKey("highestLevel", UserDefault::getInstance()->getIntegerForKey("highestLevel", 1));
      Director::getInstance()->replaceScene(GameScene::createSceneGameScene());
      AdmobManager::getInstance()->hideBanner();
      break;
    case TAG_OVER_MAIN_HOME:
      UserDefault::getInstance()->setIntegerForKey("highestLevel",1);
      Director::getInstance()->replaceScene(HomeScene::createHomeScene());
      break;
    default: break;
  }
}

void GameScene::sendEventClickButton(int tag) {
  switch (tag) {
    case TAG_BTN_REFRESH:
      if(countRefresh > 0) {
        countRefresh--;
        gameBoard->refreshGameBoard();
      }
      if(countRefresh <= 0 ) { refreshButton->setDisable(); }
      refreshButton->setValueText(countRefresh);
      break;
    case TAG_BTN_SUGGEST:
      if(countSuggest > 0) {
        countSuggest--;
        gameBoard->findPairConnectionObject(true, TIME_DELAY_DRAW_SUGGEST_LINE);
      }
      if(countSuggest <= 0 ) { suggestButton->setDisable(); }
      suggestButton->setValueText(countSuggest);
      break;
    case TAG_BTN_PAUSE:
      isPausing = true;
      progressBar->setStatus(PAUSE);
      gameBoard->pauseGameBoard();
      createPopUpPause();
      break;
    default: break;
  }
}

void GameScene::handleClickButton(Ref* pSender) {
  int tag = ((ui::Button*)pSender)->getTag();
  switch (tag) {
    case TAG_BTN_BACK:
      progressBar->setStatus(PAUSE);
      gameBoard->pauseGameBoard();
      isPausing = true;
      createPopupBack();
      break;
    default:
      break;
  }
}

void GameScene::createLayerStartGame() {
  AdmobManager::getInstance()->showBanner();
  isPausing = true;
  gameBoard->pauseGameBoard();
  progressBar->setStatus(PAUSE);
  LayerColor* startLayerColor = LayerColor::create(BG_POP_UP_COLOR, winSize.width, winSize.height);
  startLayerColor->setPosition(Vec2::ZERO);
  startLayerColor->setTag(TAG_LAYER_START_GAME);
  this->addChild(startLayerColor,TAG_LAYER_START_GAME);
  
  Label* tapToPlayLabel = Label::createWithTTF("Tap to play", "GROBOLD.ttf", 72);
  tapToPlayLabel->setPosition(Vec2(winSize.width/2, winSize.height/2));
  startLayerColor->addChild(tapToPlayLabel);
  
  auto touch = EventListenerTouchOneByOne::create();
  touch->setSwallowTouches(true);
  touch->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchStartGame, this);
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, startLayerColor);
}

bool GameScene::onTouchStartGame(Touch* mTouch, Event* pEvent) {
  this->removeChildByTag(TAG_LAYER_START_GAME);
  gameBoard->playGameBoard();
  
  this->scheduleOnce([=](float dt){
    AdmobManager::getInstance()->hideBanner();
    isPausing = false;
    progressBar->setStatus(RUNNING);
  }, 0.4f, "StartGame");
  return true;
}

void GameScene::createPopupBack() {
  AdmobManager::getInstance()->showBanner();
  progressBar->setStatus(PAUSE);
  Sprite* tempButtonSize = Sprite::create("yesButton.png");
  PopupGame* popupBack = new PopupGame();
  popupBack->setDelegate(this);
  popupBack->setPosition(Vec2::ZERO);
  popupBack->createLayoutWithZOrder();
  popupBack->createWithFileName("backPopUp.png");
  popupBack->createPopupWithFileName("yesButton.png",Vec2( winSize.width/2 - tempButtonSize->getContentSize().width/2 - 10, winSize.height*0.36),TAG_YES_BUTTON);
  popupBack->createPopupWithFileName("noButton.png", Vec2(winSize.width/2  + tempButtonSize->getContentSize().width/2 + 10,winSize.height*0.36), TAG_NO_BUTTON);
  popupBack->setTag(TAG_POP_UP_BACK);
  this->addChild(popupBack, TAG_POP_UP_BACK);
}

void GameScene::createPopUpWin() {
  AdmobManager::getInstance()->showBanner();
  progressBar->setStatus(PAUSE);
  PopupGame* popupWin = new PopupGame();
  popupWin->setDelegate(this);
  popupWin->setPosition(Vec2::ZERO);
  popupWin->createLayoutWithZOrder();
  popupWin->createWithFileName("winPopUp.png");
  popupWin->createPopupWithFileName("nextLevelButton.png",Vec2( winSize.width/2, winSize.height/4),TAG_WIN_NEXT);
  popupWin->setTag(TAG_POP_UP_WIN);
  this->addChild(popupWin, TAG_POP_UP_WIN);
  
  Label* congratulationLabel = Label::createWithTTF("Congratulation!", "GROBOLD.ttf", 64);
  congratulationLabel->setPosition(Vec2(winSize.width/2, winSize.height/2.0 - congratulationLabel->getContentSize().height));
  popupWin->setLabelPopup(congratulationLabel);
}

void GameScene::createPopupGameOver() {
  AdmobManager::getInstance()->showBanner();
  progressBar->setStatus(PAUSE);
  Sprite* temp = Sprite::create("gotoHomeButton.png");
  PopupGame* popupGameOver = new PopupGame();
  popupGameOver->setDelegate(this);
  popupGameOver->setPosition(Vec2::ZERO);
  popupGameOver->createLayoutWithZOrder();
  popupGameOver->createWithFileName("gameOverPopUp.png");
  popupGameOver->createPopupWithFileName("gotoHomeButton.png",Vec2( winSize.width/2 - temp->getContentSize().width*2/3, winSize.height*0.28),TAG_OVER_MAIN_HOME);
  popupGameOver->createPopupWithFileName("replayButton.png",Vec2(winSize.width/2 + temp->getContentSize().width*2/3,winSize.height*0.28), TAG_OVER_REPLAY);
  this->addChild(popupGameOver, TAG_POP_UP_GAME_OVER);
}

void GameScene::createPopUpPause() {
  AdmobManager::getInstance()->showBanner();
  progressBar->setStatus(PAUSE);
  Sprite* temp = Sprite::create("gotoHomeButton.png");
  PopupGame* popupPause = new PopupGame();
  popupPause->setDelegate(this);
  popupPause->setPosition(Vec2::ZERO);
  popupPause->createLayoutWithZOrder();
  popupPause->createWithFileName("pausePopUp.png");
  popupPause->createPopupWithFileName("gotoHomeButton.png",Vec2( winSize.width/2 - temp->getContentSize().width*2/3, winSize.height*0.28),TAG_PAUSE_HOME);
  popupPause->createPopupWithFileName("playButton.png",Vec2(winSize.width/2 + temp->getContentSize().width*2/3,winSize.height*0.28), TAG_PAUSE_PLAY);
  popupPause->setTag(TAG_POP_UP_PAUSE);
  this->addChild(popupPause, TAG_POP_UP_PAUSE);
}

void GameScene::showFullScreenAdvertisement(const char* key, int frequency) {
  int currentCount = UserDefault::getInstance()->getIntegerForKey(key, 0);
  if(currentCount == frequency) {
    AdmobManager::getInstance()->showInterstitial();
    UserDefault::getInstance()->setIntegerForKey(key, 0);
  } else {
    UserDefault::getInstance()->setIntegerForKey(key, currentCount + 1);
  }
}

void GameScene::drawPairConnection(int drawType, int typeCoordinator, int result, const Point& p1, const Point& p2, float timeDisplayLineColor) {
  if(gameBoard == NULL) { return; }
  MainObject* object1 = gameBoard->getAtPosGameBoard(p1);
  MainObject* object2 = gameBoard->getAtPosGameBoard(p2);
  if(object1->getTypeObject() == object2->getTypeObject()) {
    
    if(drawType == LINE) {
      Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
      Point pos2 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
      DrawLine::getInstance()->drawLineTwoPoint(gameBoard, pos1, pos2, timeDisplayLineColor);
    } else {
      switch (drawType) {
        case Z_LINE:
          if(typeCoordinator == X_AXIS) {
            Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
            Point pos2 = gameBoard->convertDrawLinePosition(Vec2(result, p1.y));
            Point pos3 = gameBoard->convertDrawLinePosition(Vec2(result, p2.y));
            Point pos4 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
            this->drawerLine(pos1, pos2, pos3, pos4, timeDisplayLineColor);
          } else{
            Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
            Point pos2 = gameBoard->convertDrawLinePosition(Vec2(p1.x, result));
            Point pos3 = gameBoard->convertDrawLinePosition(Vec2(p2.x, result));
            Point pos4 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
            this->drawerLine(pos1, pos2, pos3, pos4, timeDisplayLineColor);
          }
          break;
        case U_LINE:
          if(typeCoordinator == X_AXIS) {
            Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
            Point pos2 = gameBoard->convertDrawLinePosition(Vec2(result, p1.y));
            Point pos3 = gameBoard->convertDrawLinePosition(Vec2(result, p2.y));
            Point pos4 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
            this->drawerLine(pos1, pos2, pos3, pos4, timeDisplayLineColor);
          }
          if(typeCoordinator == Y_AXIS) {
            Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
            Point pos2 = gameBoard->convertDrawLinePosition(Vec2(p1.x, result));
            Point pos3 = gameBoard->convertDrawLinePosition(Vec2(p2.x, result));
            Point pos4 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
            this->drawerLine(pos1, pos2, pos3, pos4, timeDisplayLineColor);
          }
          break;
        case L_LINE:
          if(typeCoordinator == X_AXIS) {
            Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
            Point pos2 = gameBoard->convertDrawLinePosition(Vec2(result, p1.y));
            Point pos3 = gameBoard->convertDrawLinePosition(Vec2(result, p2.y));
            Point pos4 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
            this->drawerLine(pos1, pos2, pos3, pos4, timeDisplayLineColor);
          }
          if(typeCoordinator == Y_AXIS) {
            Point pos1 = gameBoard->convertDrawLinePosition(Vec2(p1.x, p1.y));
            Point pos2 = gameBoard->convertDrawLinePosition(Vec2(p1.x, result));
            Point pos3 = gameBoard->convertDrawLinePosition(Vec2(p2.x, result));
            Point pos4 = gameBoard->convertDrawLinePosition(Vec2(p2.x, p2.y));
            this->drawerLine(pos1, pos2, pos3, pos4, timeDisplayLineColor);
          }
        default: break;
      }
    }
  }
}

void GameScene::drawerLine(const Point& p1,const Point& p2, const Point& p3, const Point& p4, float timeDisplayLineColor) {
  DrawLine::getInstance()->drawLineTwoPoint(gameBoard, p1, p2, timeDisplayLineColor);
  DrawLine::getInstance()->drawLineTwoPoint(gameBoard, p2, p3, timeDisplayLineColor);
  DrawLine::getInstance()->drawLineTwoPoint(gameBoard, p3, p4, timeDisplayLineColor);
}
