//
//  ButtonCustom.h
//  MatchingMaster
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
  int tagButton;
  Sprite* buttonSprite;
  ui::Button* button;
  Label* textLabel;
  DelegateButton* mDelegate;
public:
  
  ButtonCustom(const char* fileName);
  virtual ~ButtonCustom();
  void setValueText(int value);
  void setTagButton(int tag);
  void buttonClick(Ref* pSender);
  void setDelegate(DelegateButton* delegate);
  void setDisable();
  Size getContentSize();
};

#endif /* ButtonCustom_h */
