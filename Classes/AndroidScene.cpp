
//  AndroidScene.cpp
//
//  Created by Harry Nguyen on 7/3/15.
//
//
#include "AndroidScene.h"
#include "HomeScene.h"
#include "GameDefine.h"

Scene* AndroidScene::CreateScene(){
  auto newScene = Scene::create();
  auto layer = AndroidScene::create();
  newScene->addChild(layer);
  return newScene;
}

bool AndroidScene::init(){
  if(!Layer::init()){ return false; }
  Size winSize = Director::getInstance()->getWinSize();
  auto background =  Sprite::create("bgGameScene.png");
  background->setPosition(Vec2(winSize.width/2, winSize.height/2));
  this->addChild(background);
  
  auto titleLabel = Label::createWithTTF(TITLE_GAME, "GROBOLD.ttf", 106);
  titleLabel->setTextColor(Color4B::WHITE);
  titleLabel->setPosition(Vec2(winSize.width/2, winSize.height/2 + 64.0));
  this->addChild(titleLabel);
  
  scheduleOnce(schedule_selector(AndroidScene::update), 1.0f);
  return true;
}

void AndroidScene::update(float dt){
  Director::getInstance()->replaceScene(HomeScene::createHomeScene());
}
