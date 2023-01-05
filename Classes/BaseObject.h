//
//  BaseObject.h
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#ifndef BaseObject_h
#define BaseObject_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BaseObject: public Node {
public:
  int type;
  Sprite *backgroundSprite, *characterSprite;
  Vec2 matrixPosition;
public:
  
  BaseObject();
  virtual ~BaseObject();
  void setTypeObject(int type);
  int getTypeObject();
  void setMatrixPosition(Vec2 matrixPosition);
  Vec2 getMatrixPosition();
};

#endif /* BaseObject_h */
