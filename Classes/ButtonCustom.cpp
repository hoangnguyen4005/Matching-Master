//
//  ButtonCustom.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#include "ButtonCustom.h"

ButtonCustom::ButtonCustom() {
  valueText = 0;
}

ButtonCustom::~ButtonCustom() {}

void ButtonCustom::createUIButton(const char* fileName) {
  button = ui::Button::create(fileName,"","",ui::Widget::TextureResType::LOCAL);
  button->setPosition(Vec2::ZERO);
  button->setTag(tagButton);
  button->addClickEventListener(CC_CALLBACK_1(ButtonCustom::buttonClick,this));
  this->addChild(button);
  
  buttonSprite = Sprite::create("badge.png");
  buttonSprite->setScale(1.4f);
  buttonSprite->setPosition(Vec2(10, 30));
  button->addChild(buttonSprite);
  
  char strValue[4] = {0};
  snprintf(strValue, sizeof(strValue), "%d",valueText);
  textLabel = Label::createWithTTF(strValue, "GROBOLD.ttf", 50);
  textLabel->setPosition(buttonSprite->getPosition());
  textLabel->setTextColor(Color4B::BLACK);
  button->addChild(textLabel);
  
  if(valueText <= 0) {
    buttonSprite->setVisible(false);
    textLabel->setVisible(false);
  } else {
    buttonSprite->setVisible(true);
    textLabel->setVisible(true);
  }
}

void ButtonCustom::onEnter() {
  Node::onEnter();
  this->scheduleUpdate();
}

void ButtonCustom::onExit() {
  Node::onExit();
  this->unscheduleUpdate();
}

void ButtonCustom::update(float dt) {
  if(valueText > 0) {
    char strValueUpdate[4] = {0};
    snprintf(strValueUpdate, sizeof(strValueUpdate), "%d",valueText);
    textLabel->setString(strValueUpdate);
    textLabel->setVisible(true);
    buttonSprite->setVisible(true);
  } else {
    buttonSprite->setVisible(false);
    textLabel->setVisible(false);
  }
}

void ButtonCustom::setValueText(int value) {
  this->valueText = value;
}

int ButtonCustom::getValueText() {
  return valueText;
}

void ButtonCustom::setTagButton(int tag) {
  this->tagButton = tag;
}

int ButtonCustom::getTagButton() {
  return tagButton;
}

void ButtonCustom::buttonClick(Ref* pSender) {
  int tag = ((ui::Button*)pSender)->getTag();
  if(mDelegate) {
    mDelegate->sendEventClickButton(tag);
  }
}

void ButtonCustom::setDelegate(DelegateButton* delegate) {
  this->mDelegate = delegate;
}

void ButtonCustom::setDisable() {
  button->setEnabled(false);
}
