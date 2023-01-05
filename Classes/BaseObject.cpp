//
//  BaseObject.cpp
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#include "BaseObject.h"
BaseObject::BaseObject() {}

BaseObject::~BaseObject() {}

void BaseObject::setTypeObject(int type) {
  this->type = type;
}

int BaseObject::getTypeObject() {
  return type;
}

void BaseObject::setMatrixPosition(Vec2 matrixPosition) {
  this->matrixPosition = matrixPosition;
}

Vec2 BaseObject::getMatrixPosition() {
  return matrixPosition;
}
