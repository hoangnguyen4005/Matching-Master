//
//  MyLine.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/22/16.
//
//

#ifndef MyLine_h
#define MyLine_h

#include "cocos2d.h"

USING_NS_CC;

class MyLine {
public:
  Point pos1;
  Point pos2;
public:
  MyLine();
  MyLine(Point pos1, Point pos2);
  bool isZeroLine();
};

#endif /* MyLine_h */
