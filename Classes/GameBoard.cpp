//
//  GameBoard.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#include "GameBoard.h"
#include "GameDefine.h"
#include "RandomIndex.h"

std::vector<std::string> imageNames {
  "pieces1.png","pieces2.png","pieces3.png","pieces4.png","pieces5.png","pieces6.png",
  "pieces7.png","pieces8.png","pieces9.png","pieces10.png","pieces11.png","pieces12.png",
  "pieces13.png","pieces14.png","pieces15.png","pieces16.png","pieces17.png","pieces18.png",
  "pieces19.png","pieces20.png","pieces21.png","pieces22.png","pieces23.png","pieces24.png",
  "pieces25.png","pieces26.png","pieces27.png","pieces28.png","pieces29.png","pieces30.png",
  "pieces31.png","pieces32.png","pieces33.png","pieces34.png","pieces35.png","pieces36.png"
};

GameBoard::GameBoard(int width, int height, int dropType) {
  isPausing = false;
  widthMatrixGameBoard = width;
  heightMatrixGameBoard = height;
  this->dropType = dropType;
  size = Size(width * SHAPE_WIDTH, height * SHAPE_HEIGHT);
  if(!listObjects.empty()) { listObjects.clear(); }
}

GameBoard::~GameBoard() {}

std::vector<MainObject*> GameBoard::getArrayValueObject() {
  return listObjects;
}

bool GameBoard::isTouchingInsideGameBoard(const Vec2& position) {
  if(position.x < SHAPE_WIDTH ||
     position.x > size.width - SHAPE_WIDTH ||
     position.y < SHAPE_HEIGHT ||
     position.y > size.height - SHAPE_HEIGHT) {
    return false;
  } else {
    return true;
  }
}

Vec2 GameBoard::convertMatrixGameBoard(const Vec2& touchLocation) {
  Vec2 pos = Vec2(touchLocation.x - this->getPositionX(), touchLocation.y - this->getPositionY());
  if (!isTouchingInsideGameBoard(pos)) {
    return OUT_OF_GAME_BOARD_MATRIX;
  }
  int x = pos.x/SHAPE_WIDTH;
  int y = pos.y/SHAPE_HEIGHT;
  return Vec2(x, y);
}

Vec2 GameBoard::getGameBoardPosition(const Vec2& matrix) {
  float pointX = matrix.x * SHAPE_WIDTH;
  float pointY = matrix.y * SHAPE_HEIGHT;
  return Vec2(pointX,pointY);
}

Vec2 GameBoard::convertDrawLinePosition(const Vec2& matrix) {
  float pointX = matrix.x * SHAPE_WIDTH + SHAPE_WIDTH/2.0;
  float pointY = matrix.y * SHAPE_HEIGHT + SHAPE_HEIGHT/2.0;
  return Vec2(pointX,pointY);
}

void GameBoard::createGameBoard(int level) {
  std::vector<int> targetIndexes = RandomIndex::getInstance()->createDefaultTargetedIndexes(level);
  for (int i = 0; i < heightMatrixGameBoard; i++) {
    for (int j = 0; j < widthMatrixGameBoard; j++) {
      MainObject* object = new MainObject(imageNames);
      int visible, type;
      if(i == 0 || i == heightMatrixGameBoard-1 || j == 0 || j ==  widthMatrixGameBoard-1) {
        type = 0;
        visible = HIDDEN_OBJECT;
      } else {
        visible = VISIBLE_OBJECT;
        type = RandomIndex::getInstance()->getRandomIndexFromTargetIndexes(targetIndexes);
      }
      object->setTypeObject(type);
      object->setValueVisible(visible);
      object->setMatrixPosition(Vec2(j, i));
      object->setPosition(this->getGameBoardPosition(Vec2(j, i)));
      object->createUIObject();
      int tag = (j + (heightMatrixGameBoard - i)* widthMatrixGameBoard);
      object->setTagObject(tag);
      this->addChild(object, tag);
      listObjects.push_back(object);
    }
  }
}


MainObject* GameBoard::getAtPosGameBoard(const Vec2& pos) {
  return listObjects.at(pos.x + pos.y*widthMatrixGameBoard);;
}

void GameBoard::setHiddenObjects(const Vec2& pos1, const Vec2& pos2) {
  listObjects.at(pos1.x + pos1.y* widthMatrixGameBoard)->setValueVisible(HIDDEN_OBJECT);
  listObjects.at(pos2.x + pos2.y* widthMatrixGameBoard)->setValueVisible(HIDDEN_OBJECT);
}

void GameBoard::dropObjectInGameBoard() {
  MainObject* object = nullptr;
  if(dropType == DROP_LEFT) {
    for (int col = 1; col <= heightMatrixGameBoard-2 ; col++) {
      int rightCount = 0;
      for (int row = 1 ; row <= widthMatrixGameBoard-2; row++) {
        object = listObjects.at(row + col*widthMatrixGameBoard);
        if(object->getValueVisible() == HIDDEN_OBJECT) {
          rightCount ++;
        } else {
          if(rightCount > 0) {
            int newRow = row - rightCount;
            swapTwoObject(Vec2(newRow, col), Vec2(row,col));
          }
        }
      }
    }
  }
  
  if(dropType == DROP_RIGHT) {
    for (int col = 1; col <= heightMatrixGameBoard-2 ; col++) {
      int rightCount = 0;
      for (int row = widthMatrixGameBoard - 2 ; row > 0; row--) {
        object = listObjects.at(row + col*widthMatrixGameBoard);
        if(object->getValueVisible() == HIDDEN_OBJECT) {
          rightCount ++;
        }
        else {
          if(rightCount > 0) {
            int newRow = row + rightCount;
            swapTwoObject(Vec2(newRow, col), Vec2(row,col));
          }
        }
      }
    }
    
  }
  if(dropType == DROP_UP) {
    for (int row = 1 ; row <= widthMatrixGameBoard-2 ; row ++ ) {
      int upCount = 0;
      for (int col = heightMatrixGameBoard - 2; col > 0 ; col--) {
        object = listObjects.at( row + col*widthMatrixGameBoard);
        if(object->getValueVisible() == HIDDEN_OBJECT) {
          upCount++;
        } else {
          if(upCount > 0) {
            int newHeight = col + upCount;
            swapTwoObject(Vec2(row, newHeight), Vec2(row, col));
          }
        }
      }
    }
  }
  if(dropType == DROP_DOWN) {
    for (int row = 1 ; row <= widthMatrixGameBoard-2; row++) {
      int downCount = 0;
      for (int col = 1; col <= heightMatrixGameBoard-2; col++) {
        object = listObjects.at(row + col*widthMatrixGameBoard);
        if (object->getValueVisible() == HIDDEN_OBJECT) {
          downCount ++;
        }
        else {
          if(downCount > 0) {
            int newHeight = col - downCount;
            swapTwoObject(Vec2(row, newHeight), Vec2(row, col));
          }
        }
      }
    }
  }
}

void swapTag(int &a, int &b) {
  int temp = a;
  a = b ;
  b = temp;
}

void GameBoard::swapTwoObject(const Vec2& pos1, const Vec2& pos2) {
  MainObject* object1 = this->getAtPosGameBoard(pos1);
  MainObject* object2 = this->getAtPosGameBoard(pos2);
  
  int a = object1->getTagObject();
  int b = object2->getTagObject();
  swapTag(a, b);
  if(object1 && object2) {
    object1->updateNewPosition(getGameBoardPosition(Vec2(pos2.x, pos2.y)));
    object1->setMatrixPosition(pos2);
    object1->setValueVisible(HIDDEN_OBJECT);
    object1->setTagObject(a);
    object1->setLocalZOrder(a);
    
    object2->updateNewPosition(getGameBoardPosition(Vec2(pos1.x, pos1.y)));
    object2->setMatrixPosition(pos1);
    object2->setValueVisible(VISIBLE_OBJECT);
    object2->setTagObject(b);
    object2->setLocalZOrder(b);
    
    listObjects.at(pos1.x + pos1.y*widthMatrixGameBoard) = object2;
    listObjects.at(pos2.x + pos2.y*widthMatrixGameBoard) = object1;
  }
}

void GameBoard::findPairConnectionObject(bool isDrawingLineColor, float timeDisplayLineColor) {
  std::vector<MainObject*> listVisibleObject = getCurrentListVisibleObject();
  if(listVisibleObject.empty()) { return; }
  
  std::map<int, std::vector<MainObject*>> dictionary;
  
  for (int i = 0; i < listVisibleObject.size(); i++) {
    int type = listVisibleObject[i]->getTypeObject();
    std::vector<MainObject*> list = dictionary[type];
    list.push_back(listVisibleObject[i]);
    dictionary[type] = list;
  }
  
  std::map<int, std::vector<MainObject*> >::iterator it;
  
  bool hasPairObject = false;
  for (it = dictionary.begin(); it != dictionary.end(); it++) {
    if(hasPairObject) { break; }
    for(int i = 0; i < it->second.size(); i++) {
      if(hasPairObject) { break; }
      for(int j = 0; j < it->second.size(); j++) {
        if(hasPairConnection(it->second[i]->getMatrixPosition(),
                                           it->second[j]->getMatrixPosition(),
                                           isDrawingLineColor,
                                           timeDisplayLineColor)) {
          hasPairObject = true;
          break;;
        }
      }
    }
  }
  /*auto shuffle object when do not have pair */
  if(hasPairObject == false) {
    refreshGameBoard();
    findPairConnectionObject(isDrawingLineColor, timeDisplayLineColor);
  }
}

void GameBoard::setSuggestBotForGame(CheckPairBot* checkPairBot) {
  this->checkPairBot = checkPairBot;
}

bool GameBoard::hasPairConnection(const Vec2& pos, const Vec2 &pos2, bool isDrawingLineColor, float timeDisplayLineColor) {
  MyLine line = checkPairBot->checkTwoPoint(pos, pos2, isDrawingLineColor, timeDisplayLineColor);
  if(!line.isZeroLine()) { return true; }
  return false;
}

void GameBoard::pauseGameBoard() {
  isPausing  = true;
  for(int i = 0; i < widthMatrixGameBoard; i ++) {
    for (int j = 0; j < heightMatrixGameBoard; j++) {
      MainObject* object = listObjects.at(i + j*widthMatrixGameBoard);
      object->objectWhenPause();
    }
  }
}

void GameBoard::playGameBoard() {
  isPausing = false;
  for(int i = 0; i < widthMatrixGameBoard; i ++) {
    for (int j = 0; j < heightMatrixGameBoard; j++) {
      MainObject* object = listObjects.at(i + j*widthMatrixGameBoard);
      object->objectWhenPlay();
    }
  }
}

void GameBoard::refreshGameBoard() {
  std::vector<MainObject*> listVisibleObject = getCurrentListVisibleObject();
  if(listVisibleObject.empty()) { return; }
  
  std::vector<int> targetTypeArray = getListTypeObject(listVisibleObject);
  
  for (int i = 0; i < listVisibleObject.size(); i ++) {
    MainObject* object = listVisibleObject.at(i);
    int newType = RandomIndex::getInstance()->getRandomIndexFromTargetIndexes(targetTypeArray);
    object->setTypeObject(newType);
    object->updateUI(newType);
    Vec2 matrix = object->getMatrixPosition();
    int index = matrix.x + matrix.y*widthMatrixGameBoard;
    if(index >= 0 && index <= listObjects.size() - 1) {
      listObjects.at(index) = object;
    }
  }
}

std::vector<MainObject*> GameBoard::getCurrentListVisibleObject() {
  std::vector<MainObject*> result;
  for (int i = 0; i < listObjects.size(); i++) {
    if(listObjects.at(i)->getValueVisible() == VISIBLE_OBJECT) {
      result.push_back(listObjects.at(i));
    }
  }
  return result;
}

std::vector<int> GameBoard::getListTypeObject( std::vector<MainObject*> objects) {
  std::vector<int> result;
  for(int i = 0 ; i < objects.size(); i++) {
    if(objects.at(i)->getValueVisible() == VISIBLE_OBJECT){
      result.push_back(objects.at(i)->getTypeObject());
    }
  }
  return result;
}

Size GameBoard::getRealContentSize() { return size; }
