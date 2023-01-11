//
//  GameBoard.h
//  MatchingMaster
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
private:
  Size size;
  std::vector<int> getListTypeObject(std::vector<MainObject*> objects);
  bool isTouchingInsideGameBoard(const Vec2& position);
  void dropLeft();
  void dropRight();
  void dropUp();
  void dropDown();
  void swapTag(int &a, int &b);
public:
  bool isPausing;
  int widthMatrixGameBoard, heightMatrixGameBoard, dropType;
  std::vector<MainObject*> listObject;
  CheckPairBot* checkPairBot;
public:
  GameBoard(int width, int height, int dropType);
  virtual ~GameBoard();
  void createGameBoard(int level);
  
  std::vector<MainObject*> getListObject();
  Vec2 convertMatrixGameBoard(const Vec2& touchLocation);
  Vec2 getGameBoardPosition(const Vec2& matrix);
  Vec2 convertDrawLinePosition(const Vec2& matrix);
  MainObject* getAtPosGameBoard(const Vec2& matrix);
  
  void setHiddenObjects(const Vec2& pos1, const Vec2& pos2);
  void dropObjectInGameBoard();
  
  void swapTwoObject(const Vec2& pos1, const Vec2& pos2);
  void findPairConnectionObject(bool isDrawingLineColor, float timeDisplayLineColor);
  void setSuggestBotForGame(CheckPairBot* checkPairBot);
  bool hasPairConnection(const Vec2& pos, const Vec2 &pos2, bool isDrawingLineColor, float timeDisplayLineColor);
  void pauseGameBoard();
  void playGameBoard();
  void refreshGameBoard();
  Size getRealContentSize();
  std::vector<MainObject*> getCurrentListVisibleObject();
};

#endif /* GameBoard_h */
