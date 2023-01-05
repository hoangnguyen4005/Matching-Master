//
//  ButtonCustom.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#include "ButtonCustom.h"

ButtonCustom::ButtonCustom(const char* fileName) {
  button = ui::Button::create(fileName,"","",ui::Widget::TextureResType::LOCAL);
  button->setPosition(Vec2::ZERO);
  button->setTag(tagButton);
  button->addClickEventListener(CC_CALLBACK_1(ButtonCustom::buttonClick,this));
  this->addChild(button);
  
  buttonSprite = Sprite::create("badge.png");
  buttonSprite->setScale(1.4f);
  buttonSprite->setPosition(Vec2(10, 30));
  button->addChild(buttonSprite);
  textLabel = Label::createWithTTF("", "GROBOLD.ttf", 50);
  textLabel->setPosition(buttonSprite->getPosition());
  textLabel->setTextColor(Color4B::BLACK);
  button->addChild(textLabel);
}

Size ButtonCustom::getContentSize() {
  return button->getContentSize();
}

ButtonCustom::~ButtonCustom() {}

void ButtonCustom::setValueText(int value) {
  if(value > 0) {
    char strValueUpdate[4] = {0};
    snprintf(strValueUpdate, sizeof(strValueUpdate), "%d",value);
    textLabel->setString(strValueUpdate);
    textLabel->setVisible(true);
    buttonSprite->setVisible(true);
  } else {
    buttonSprite->setVisible(false);
    textLabel->setVisible(false);
  }
}

void ButtonCustom::setTagButton(int tag) {
  this->tagButton = tag;
}

void ButtonCustom::buttonClick(Ref* pSender) {
  if(mDelegate) {
    mDelegate->sendEventClickButton(tagButton);
  }
}

void ButtonCustom::setDelegate(DelegateButton* delegate) {
  this->mDelegate = delegate;
}

void ButtonCustom::setDisable() {
  button->setEnabled(false);
}
