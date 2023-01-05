//
//  MyLine.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/22/16.
//
//

#include "MyLine.h"

MyLine::MyLine() {}

MyLine::MyLine(Point pos1, Point pos2) {
  this->pos1 = pos1;
  this->pos2 = pos2;
}

bool MyLine::isZeroLine() {
  if (pos1.distance(pos2) == 0) { return true; }
  return false;
}
