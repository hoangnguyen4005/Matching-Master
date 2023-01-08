//
//  ProgressBarCustom.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//
#ifndef ProgressBarCustom_h
#define ProgressBarCustom_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"
USING_NS_CC;

class DelegateProgress {
public:
  virtual void endTime() = 0;
  virtual void receiveTimeRemainingFromProgressBar(int percent) = 0;
};

class ProgressBarCustom: public Node {
private:
  int timeRemaining;
public:
  int loadingStatus;
  DelegateProgress* mDelegate;
  ui::LoadingBar* loadingBar;
  Sprite* loadingSprite;
public:
  void createUIProgressBar();
  ProgressBarCustom();
  virtual ~ProgressBarCustom();
  virtual void onEnter();
  virtual void onExit();
  void update(float dt);
  void updateTimeRemaining(float dt);
  void setStatus(int status);
  void setDelegate(DelegateProgress* delegate);
};

#endif /* ProgressBarCustom_h */
