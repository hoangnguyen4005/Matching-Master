//
//  CheckPairBot.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/19/16.
//
//

#ifndef suggestionBot_h
#define suggestionBot_h

#include <stdio.h>
#include <algorithm> 
#include "cocos2d.h"
#include "MainObject.h"
#include "MyLine.h"
USING_NS_CC;

class DelegateDrawer {
public:
  virtual void listerDrawer(int type, int typeSub, int result, const Point& p1, const Point& p2, float timeDisplayLineColor)=0;
  virtual void listerDrawerUL(int type, int typeSub, int downAndUp, int result, const Point& p1, const Point& p2, float timeDisplayLineColor)=0;
};

class CheckPairBot {
private:
  bool isDrawingLineColor;
  float timeDisplayLineColor;
  bool checkLineY(int y1, int y2, int x);
  bool checkLineX(int x1, int x2, int y);
  int checkRectX(Point p1, Point p2);
  int checkRectY(Point p1, Point p2);
  int checkMoreLineY(Point p1, Point p2, int type);
  int checkMoreLineX(Point p1, Point p2, int type);
  int countNumberObjectBetween(const Point& p1, const Point& p2);
public:
  int width, height;
  std::vector<MainObject*> listMainObject;
  DelegateDrawer* delegate;
  CheckPairBot();
  virtual ~CheckPairBot();
  static CheckPairBot* getInstance();
  void setArrayValueVisible(const std::vector<MainObject*> &array);
  void setWidthAndHeightMatrix(int width, int height);
  void setDelegate(DelegateDrawer* mDelegate);
  MyLine checkTwoPoint(Point p1, Point p2, bool isDrawingLineColor, float timeDisplayLineColor);
};

#endif /* suggestionBot_h */
