//
//  ProgressBarCustom.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.


#include "ProgressBarCustom.h"

ProgressBarCustom::ProgressBarCustom() {}

ProgressBarCustom::~ProgressBarCustom() {}

void ProgressBarCustom::createUIProgressBar(const Vec2& pos) {
  loadingBar = ui::LoadingBar::create("progress_bar.png");
  loadingBar->setAnchorPoint(Vec2(0.5,0.5));
  loadingBar->setPosition(pos);
  loadingBar->setPercent(value);
  loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
  this->setContentSize(loadingBar->getContentSize());
  this->addChild(loadingBar);
}

ProgressBarCustom* ProgressBarCustom::getInstanceProgress(int valueLoading, int status) {
  ProgressBarCustom* object = new ProgressBarCustom();
  object->setValue(valueLoading);
  object->setStatus(status);
  return object;
}

void ProgressBarCustom::setValue(float value) {
  this->value = value;
}

float ProgressBarCustom::getValue() {
  return value;
}

void ProgressBarCustom::onEnter() {
  Node::onEnter();
  this->scheduleUpdate();
}

void ProgressBarCustom::onExit() {
  Node::onExit();
  this->unscheduleUpdate();
}

void ProgressBarCustom::update(float dt) {
  if(loadingBar == NULL) { return; }
  
  if(loadingStatus == IDLE_PROGRESS) {
    float value = loadingBar->getPercent();
    value  = value - updatePercent;
    loadingBar->setPercent(value);
    if(value <= 0) {
      if(mDelegate){ mDelegate->endTime(); }
      loadingStatus = STOP;
    }
  }
  
  if(loadingStatus == PAUSE_PROGRESS) {
    float value = loadingBar->getPercent();
    loadingBar->setPercent(value);
  }
  
  if (loadingStatus == ADDITION_TIME_PROGRESS) {
    float value = loadingBar->getPercent();
    value += ADD_TIME_PROGRESS_BAR;
    loadingBar->setPercent(value);
    loadingStatus = IDLE_PROGRESS;
  }
}

void ProgressBarCustom::setStatus(int status) {
  this->loadingStatus = status;
}

void ProgressBarCustom::setDelegate(DelegateProgress* delegate) {
  mDelegate = delegate;
}

void ProgressBarCustom::setTimeUpdate(float dt) {
  updatePercent = dt;
}
