//
//  ButtonCustom.h
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#ifndef ButtonCustom_h
#define ButtonCustom_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class DelegateButton{
public:
  virtual void sendEventClickButton(int tag) = 0;
};

class ButtonCustom: public Node {
public:
  int valueText, tagButton;
  Sprite* buttonSprite;
  ui::Button* button;
  Label* textLabel;
  DelegateButton* mDelegate;
public:
  
  ButtonCustom();
  virtual ~ButtonCustom();
  void createUIButton(const char* fileName);
  void setValueText(int value);
  int getValueText();
  void onEnter();
  void onExit();
  void update(float dt);
  void setTagButton(int tag);
  int getTagButton();
  void buttonClick(Ref* pSender);
  void setDelegate(DelegateButton* delegate);
  void setDisable();
};

#endif /* ButtonCustom_h */
