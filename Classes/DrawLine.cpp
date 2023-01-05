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

void DrawLine::drawLineTwoPoint(const Point& p1, const Point& p2, float timeDisplayLineColor) {
  Node* node = new Node();
  node->setPosition(p1);
  mainScene->addChild(node, 1000);
  DrawNode* drawerLine = DrawNode::create();
  if(p1.x == p2.x) {
    if(p1.y > p2.y) {
      drawerLine->drawSegment(p1,Vec2(p2.x , p2.y - p1.distance(p2)), WIDTH_DRAW_LINE, Color4F::RED);
    } else {
      drawerLine->drawSegment(p1,Vec2(p2.x , p2.y + p1.distance(p2)), WIDTH_DRAW_LINE, Color4F::RED);
    }
  }
  if(p1.y == p2.y) {
    if (p1.x > p2.x) {
      drawerLine->drawSegment(p1,Vec2(p2.x - p1.distance(p2), p2.y), WIDTH_DRAW_LINE, Color4F::RED);
    } else {
      drawerLine->drawSegment(p1,Vec2(p2.x + p1.distance(p2), p2.y), WIDTH_DRAW_LINE, Color4F::RED);
    }
  }
  node->addChild(drawerLine);
  auto delayTime = DelayTime::create(timeDisplayLineColor);
  auto actionHidden = CallFunc::create([=](){ node->setVisible(false); });
  drawerLine->runAction(Sequence::create(delayTime,actionHidden, NULL));
}

void DrawLine::initWithScene(Node* node) {
  mainScene = (Scene*) node;
}
