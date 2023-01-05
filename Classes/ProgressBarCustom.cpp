//
//  ProgressBarCustom.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.


#include "ProgressBarCustom.h"

ProgressBarCustom::ProgressBarCustom() {}

ProgressBarCustom::~ProgressBarCustom() {}

void ProgressBarCustom::createUIProgressBar() {
  loadingStatus = PAUSE;
  timeRemaining = TOTAL_TIME_SECOND_PROGRESS_BAR;
  loadingSprite = Sprite::create("background_progress_bar.png");
  loadingSprite->setPosition(Vec2::ZERO);
  this->addChild(loadingSprite);
  
  loadingBar = ui::LoadingBar::create("progress_bar.png");
  loadingBar->setPosition(Vec2::ZERO);
  loadingBar->setPercent(TOTAL_PERCENT_PROGRESS_BAR);
  loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
  this->setContentSize(loadingBar->getContentSize());
  this->addChild(loadingBar);
}

void ProgressBarCustom::onEnter() {
  Node::onEnter();
  this->scheduleUpdate();
  this->schedule(schedule_selector(ProgressBarCustom::updateTimeRemaining), 1.0);
}

void ProgressBarCustom::onExit() {
  Node::onExit();
  this->unscheduleUpdate();
}

void ProgressBarCustom::update(float dt) {
  if(loadingBar == NULL || loadingStatus == PAUSE) { return; }
  float percent = loadingBar->getPercent();
  percent -= dt* TOTAL_PERCENT_PROGRESS_BAR/TOTAL_TIME_SECOND_PROGRESS_BAR;
  loadingBar->setPercent(percent);
}

void ProgressBarCustom::updateTimeRemaining(float dt) {
  if(loadingBar == NULL || loadingStatus == PAUSE) { return; }
  timeRemaining -= dt;
  if(timeRemaining <= 0) {
    loadingStatus = PAUSE;
    if(mDelegate){ mDelegate->endTime(); }
  } else {
    if(mDelegate){ mDelegate->receiveTimeRemainingFromProgressBar(timeRemaining); }
  }
}

void ProgressBarCustom::setStatus(int status) {
  this->loadingStatus = status;
}

void ProgressBarCustom::setDelegate(DelegateProgress* delegate) {
  mDelegate = delegate;
}
