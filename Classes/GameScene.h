
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ProgressBarCustom.h"
#include "ButtonCustom.h"
#include "GameBoard.h"
#include "CheckPairBot.h"
#include "PopupGame.h"
#include "ButtonCustom.h"
#include "RandomBot.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer, DelegateButton, DelegateDrawer, DelegateProgress, DelegateEventPopup {
public:
  bool isPausing, isShowingPopup;
  int level, dropObjectType;
  int countRefresh, countSuggest, countTouch;
  int widthMatrixGameBoard, heightMatrixGameBoard;
  Size winSize;
  Vec2 posTouchOne, posTouchTwo;
  Label* levelLabel;
  GameBoard* gameBoard;
  CheckPairBot* checkPairBot;
  ProgressBarCustom* progressBar;
  ButtonCustom *suggestButton, *refreshButton, *pauseButton;
  Sprite* loadingSprite;
public:
  static cocos2d::Scene* createSceneGameScene();
  virtual bool init();
  CREATE_FUNC(GameScene);
  void createProgressBarGameScene(int level);
  void createRightLayout();
  void createLeftLayout();
  void sendEventClickButton(int tag);
  void handleClickButton(Ref* pSender);
  void update(float dt);
  bool onTouchStartGame(Touch* mTouch, Event* pEvent);
  bool onTouchBeginGameScene(Touch* mTouch, Event* pEvent);
  void onTouchEndGameScene(Touch* mTouch, Event* pEvent);
  
  virtual void endTime();
  
  virtual void listerDrawer(int type, int typeSub, int result, const Point& p1, const Point& p2, float timeDisplayLineColor);
  virtual void listerDrawerUL(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2, float timeDisplayLineColor);
  void drawerLine(const Point& p1,const Point& p2, const Point& p3, const Point& p4, float timeDisplayLineColor);

  virtual void handleClickEventOnPopUp(int tag);
  
  void createPopupBack();
  void createPopUpWin();
  void createPopupGameOver();
  void createPopUpPause();
  void createLayerStartGame();
  
  void randomLevelPlay(int level , RandomBot* randomBot);
  void showFullScreenAdvertisement(const char* key, int frequency);
};

#endif // __GAME_SCENE_H__
