//
//  GameBoard.h
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#ifndef GameBoard_h
#define GameBoard_h

#include "cocos2d.h"
#include "MainObject.h"
#include "CheckPairBot.h"
USING_NS_CC;

class GameBoard: public Layer {
public:
  bool isPausing;
  int widthMatrixGameBoard, heightMatrixGameBoard;
  Scene* gameScene;
  std::vector<MainObject*> listObjects;
  std::vector<int> indexes;
  CheckPairBot* checkPairBot;
public:
  GameBoard(int width, int height);
  virtual ~GameBoard();
  void createGameBoard();
  void initWithScene(Node* gameScene);
  
  Vec2 convertPosGameBoard(const Vec2& pos);
  Vec2 getPositionScene(const Vec2& pos);
  MainObject* getAtPosGameBoard(const Vec2& pos);
  
  std::vector<MainObject*> getArrayValueObject();
  
  void setHiddenObjects(const Vec2& pos1, const Vec2& pos2);
  void setDropTypeObject(int dropType);
  
  void swapTwoObject(const Vec2& pos1, const Vec2& pos2);
  void setObjectTypes(std::vector<int> array);
  
  void findPairObject(bool isDrawingLineColor, float timeDisplayLineColor);
  void setSuggestBotForGame(CheckPairBot* checkPairBot);
  bool checkCanConnectWithPairPosition(const Vec2& pos, const Vec2 &pos2, bool isDrawingLineColor, float timeDisplayLineColor);
  
  bool isWinGameBoard();
  void pauseGameBoard();
  void playGameBoard();
  void refreshGameBoard();
};

#endif /* GameBoard_h */
