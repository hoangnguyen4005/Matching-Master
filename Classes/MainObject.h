//
//  MainObject.h
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#ifndef MainObject_h
#define MainObject_h

#include "cocos2d.h"
#include "BaseObject.h"

class MainObject: public BaseObject {
private:
  std::vector<std::string> imageNames;
public:
  int tagObject, valueVisible;
  MainObject(std::vector<std::string> imageNames);
  virtual ~MainObject();
  virtual void actionWhenClick();
  virtual void effectWhenDieObject();
  virtual void backToNormalObject();
  virtual void setValueVisible(int valueVisible);
  virtual int getValueVisible();
  virtual void setTagObject(int tagObject);
  virtual void setVisibleSprite();
  virtual void update(float dt);
  virtual void updateUI(int type);
  void updateNewPosition(const Vec2& position);
  void createUIObject();
  void objectWhenPause();
  void objectWhenPlay();
  int getTagObject();
};

#endif /* MainObject_h */
