//
//  HomeScene.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//
#include "HomeScene.h"
#include "GameScene.h"
#include "GameDefine.h"
#include "AdmobManager.h"

Scene* HomeScene::createHomeScene() {
  auto scene = Scene::create();
  auto layer = new HomeScene();
  layer->createUIHomeScene();
  scene->addChild(layer);
  return scene;
}

HomeScene::HomeScene() {}

HomeScene::~HomeScene() {}

void HomeScene::createUIHomeScene() {
  winSize = Director::getInstance()->getWinSize();
  auto background =  Sprite::create("bgGameScene.png");
  background->setPosition(Vec2(winSize.width/2, winSize.height/2));
  this->addChild(background);
  
  auto titleLabel = Label::createWithTTF(TITLE_GAME, "GROBOLD.ttf", 106);
  titleLabel->setTextColor(Color4B::WHITE);
  titleLabel->setPosition(Vec2(winSize.width/2, winSize.height/2 + 64.0));
  this->addChild(titleLabel);
  
  ui::Button* startButton = ui::Button::create("startButton.png","","",cocos2d::ui::Widget::TextureResType::LOCAL);
  startButton->setPosition(Vec2(winSize.width/2,
                                titleLabel->getPositionY()
                                - titleLabel->getContentSize().height
                                - startButton->getContentSize().height/2.0));
  startButton->setZoomScale(0.1);
  startButton->addClickEventListener(CC_CALLBACK_1(HomeScene::handleClickButtonHomeScene,this));
  this->addChild(startButton);
  AdmobManager::getInstance()->showBanner();
}

void HomeScene::handleClickButtonHomeScene(Ref* pSender) {
  Director::getInstance()->replaceScene(GameScene::createSceneGameScene());
}
