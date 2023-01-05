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
};

class ProgressBarCustom: public Node {
public:
  float updatePercent;
  int loadingStatus, value, countTime;
  DelegateProgress* mDelegate;
  ui::LoadingBar* loadingBar;
public:
  void createUIProgressBar(const Vec2& pos);
  ProgressBarCustom();
  virtual ~ProgressBarCustom();
  virtual void onEnter();
  virtual void onExit();
  void update(float dt);
  void setStatus(int status);
  void setValue(float value);
  float getValue();
  static ProgressBarCustom* getInstanceProgress(int valueLoading,  int status);
  void setDelegate(DelegateProgress* delegate);
  void setTimeUpdate(float dt);
};

#endif /* ProgressBarCustom_h */
