//
//  DrawLine.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 10/23/16.
//
//

#include "DrawLine.h"
#include "GameDefine.h"

DrawLine::DrawLine() {}

DrawLine::~DrawLine() {}

static DrawLine* instance = nullptr;

DrawLine* DrawLine::getInstance() {
  if(instance == nullptr) { instance = new DrawLine(); }
  return instance;
}

void DrawLine::drawLineTwoPoint(Node* node, const Point& p1, const Point& p2, float timeDisplayLineColor) {
  DrawNode* drawerLine = DrawNode::create();
  drawerLine->drawSegment(p1, p2, THICKNESS_DRAW_LINE, Color4F::RED);
  node->addChild(drawerLine, 99999);
  auto delayTime = DelayTime::create(timeDisplayLineColor);
  auto actionHidden = CallFunc::create([=](){ drawerLine->setVisible(false); });
  drawerLine->runAction(Sequence::create(delayTime,actionHidden, NULL));
}
