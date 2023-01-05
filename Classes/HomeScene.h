//
//  HomeScene.h
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#ifndef HomeScene_h
#define HomeScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class HomeScene : public Layer {
public:
  Size winSize;
public:
  static Scene* createHomeScene();
  HomeScene();
  virtual ~HomeScene();
  void createUIHomeScene();
  void handleClickButtonHomeScene(Ref* pSender);
  void createChartGame();
};

#endif /* HomeScene_h */
