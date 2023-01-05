//
//  DrawLine.h
//  One Connection
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
public:
  Scene* mainScene;
  
public:
  DrawLine();
  virtual ~DrawLine();
  void drawLineTwoPoint(const Point& p1, const Point& p2, float timeDisplayLineColor);
  void initWithScene(Node* node);
};

#endif /* DrawLine_h */
