//
//  DrawLine.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 10/23/16.
//
//

#ifndef DrawLine_h
#define DrawLine_h

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;

class DrawLine: public Ref {
private:
  DrawLine();
public:
  static DrawLine* getInstance();
  virtual ~DrawLine();
  void drawLineTwoPoint(Node* node, const Point& p1, const Point& p2, float timeDisplayLineColor);
};

#endif /* DrawLine_h */
