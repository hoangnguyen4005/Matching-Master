//
//  MainObject.cpp
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#include "MainObject.h"
#include "GameDefine.h"

MainObject::MainObject(std::vector<std::string> imageNames) {
  this->imageNames = imageNames;
}

MainObject::~MainObject() {}

void MainObject::createUIObject() {
  backgroundSprite = Sprite::create("shapeBackground.png");
  backgroundSprite->setPosition(this->getPosition());
  this->addChild(backgroundSprite);
  characterSprite = Sprite::createWithSpriteFrameName(imageNames[type]);
  
  characterSprite->setPosition(this->getPosition());
  characterSprite->setScale(3);
  this->addChild(characterSprite);
  if (valueVisible == VISIBLE_OBJECT) {
    characterSprite->setVisible(true);
    backgroundSprite->setVisible(true);
  } else {
    characterSprite->setVisible(false);
    backgroundSprite->setVisible(false);
  }
}

void MainObject::updateUI(int type) {
  characterSprite->setSpriteFrame(imageNames[type]);
}

void MainObject::setTagObject(int tagObject) {
  this->tagObject = tagObject;
}

int MainObject::getTagObject() {
  return tagObject;
}

void MainObject::actionWhenClick() {
  auto action1 = ScaleTo::create(0.08f, 0.8f);
  auto action2 = DelayTime::create(0.02f);
  auto sequence = Sequence::create(action1, action2, NULL);
  backgroundSprite->runAction(sequence);
}

void MainObject::effectWhenDieObject() {
  backgroundSprite->setVisible(false);
  characterSprite->setVisible(false);
}

void MainObject::backToNormalObject() {
  backgroundSprite->runAction(ScaleTo::create(0.1f, 1.0f));
}

void MainObject::updateNewPosition(const Vec2& position) {
  this->setPosition(position);
  if(backgroundSprite) {
    backgroundSprite->setPosition(this->getPosition());
  }
  if(characterSprite) {
    characterSprite->setPosition(this->getPosition());
  }
}

void MainObject::setValueVisible(int valueVisible) {
  this->valueVisible = valueVisible;
}

int MainObject::getValueVisible() {
  return valueVisible;
}

void MainObject::update(float dt) {
  if(this->getValueVisible() ==  HIDDEN_OBJECT) {
    backgroundSprite->setVisible(false);
    characterSprite->setVisible(false);
  } else {
    backgroundSprite->setVisible(true);
    characterSprite->setVisible(true);
  }
}

void MainObject::setVisibleSprite() {
  if(backgroundSprite->isVisible() == false) {
    backgroundSprite->setVisible(true);
  }
  if(characterSprite->isVisible() == false) {
    characterSprite->setVisible(true);
  }
}

void MainObject::objectWhenPause() {
  backgroundSprite->setLocalZOrder(10001);
  characterSprite->setLocalZOrder(10000);
}

void MainObject::objectWhenPlay() {
  backgroundSprite->setLocalZOrder(10000);
  characterSprite->setLocalZOrder(10001);
}


