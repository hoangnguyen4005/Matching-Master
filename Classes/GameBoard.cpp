//
//  GameBoard.cpp
//  One Connection
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#include "GameBoard.h"
#include "GameDefine.h"
#include "RandomBot.h"

std::vector<std::string> pieces {
  "pieces1.png","pieces2.png","pieces3.png","pieces4.png","pieces5.png","pieces6.png",
  "pieces7.png","pieces8.png","pieces9.png","pieces10.png","pieces11.png","pieces12.png",
  "pieces13.png","pieces14.png","pieces15.png","pieces16.png","pieces17.png","pieces18.png",
  "pieces19.png","pieces20.png","pieces21.png","pieces22.png","pieces23.png","pieces24.png",
  "pieces25.png","pieces26.png","pieces27.png","pieces28.png","pieces29.png","pieces30.png",
  "pieces31.png","pieces32.png","pieces33.png","pieces34.png","pieces35.png","pieces36.png"
};

GameBoard::GameBoard(int width, int height) {
  isPausing = false;
  widthMatrixGameBoard = width;
  heightMatrixGameBoard = height;
  if(!listObjects.empty()) {
    listObjects.clear();
  }
}

GameBoard::~GameBoard() {}

std::vector<MainObject*> GameBoard::getArrayValueObject() {
  return listObjects;
}

void GameBoard::setObjectTypes(std::vector<int> array) {
  this->indexes = array;
}

Vec2 GameBoard::convertPosGameBoard(const Vec2& pos) {
  Vec2 posConvert = Vec2(this->convertToWorldSpace(this->getPosition()).x + SHAPE_WIDTH /2,
                         this->convertToWorldSpace(this->getPosition()).y + SHAPE_HEIGHT/2);
  if(pos.x < posConvert.x ||
     pos.y < posConvert.y ||
     pos.x > posConvert.x + (widthMatrixGameBoard) *SHAPE_WIDTH ||
     pos.y > posConvert.y + (heightMatrixGameBoard)* SHAPE_HEIGHT) {
    return Vec2(-1, -1);
  } else {
    int realWidth = pos.x - posConvert.x;
    int realHeight = pos.y - posConvert.y;
    int cellPosX = realWidth/SHAPE_WIDTH;
    int cellPosY = realHeight/SHAPE_HEIGHT;
    return Vec2(cellPosX, cellPosY);
  }
}

Vec2 GameBoard::getPositionScene(const Vec2& pos) {
  if(pos.x < 0 ||
     pos.y < 0 ||
     pos.x > widthMatrixGameBoard-1 ||
     pos.y > heightMatrixGameBoard-1) {
    return Vec2(-1,-1);
  } else {
    float pointX = pos.x * SHAPE_WIDTH/2 + this->getPositionX() + SHAPE_WIDTH/2;
    float pointY = pos.y * SHAPE_HEIGHT/2 + this->getPositionY() + SHAPE_HEIGHT/2;
    return Vec2(pointX,pointY);
  }
}

void GameBoard::createGameBoard() {
  std::vector<std::string> tileNames = pieces;
  for (int i = 0; i < heightMatrixGameBoard; i++) {
    for (int j = 0; j < widthMatrixGameBoard; j++) {
      MainObject* object = new MainObject(tileNames);
      int visibleTag = 0;
      int type;
      if(i == 0 || i == heightMatrixGameBoard-1 || j == 0 || j ==  widthMatrixGameBoard-1) {
        type = 0;
        visibleTag = HIDDEN_OBJECT;
      } else {
        visibleTag = VISIBLE_OBJECT;
        type = RandomBot::getInstance()->randomIndexFromVector(indexes)-1;
      }
      if(type <= 0) { type = 0; }
      if(type >= 35) { type = 35; }
      object->setTypeObject(type);
      object->setValueVisible(visibleTag);
      object->setMatrixPosition(Vec2(j, i));
      object->setPosition(this->getPositionScene(Vec2(j, i)));
      object->createUIObject();
      int tagObject = (j + (heightMatrixGameBoard - i)* widthMatrixGameBoard);
      object->setTagObject(tagObject);
      gameScene->addChild(object, tagObject);
      listObjects.push_back(object);
    }
  }
}

MainObject* GameBoard::getAtPosGameBoard(const Vec2& pos) {
  return listObjects.at(pos.x + pos.y*widthMatrixGameBoard);;
}

void GameBoard::initWithScene(Node* gameScene) {
  this->gameScene = (Scene*)gameScene;
}

void GameBoard::setHiddenObjects(const Vec2& pos1, const Vec2& pos2) {
  listObjects.at(pos1.x + pos1.y* widthMatrixGameBoard)->setValueVisible(HIDDEN_OBJECT);
  listObjects.at(pos2.x + pos2.y* widthMatrixGameBoard)->setValueVisible(HIDDEN_OBJECT);
}

void GameBoard::setDropTypeObject(int dropType) {
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
    object1->updateNewPosition(getPositionScene(Vec2(pos2.x, pos2.y)));
    object1->setMatrixPosition(pos2);
    object1->setValueVisible(HIDDEN_OBJECT);
    object1->setTagObject(a);
    object1->setLocalZOrder(a);
    
    object2->updateNewPosition(getPositionScene(Vec2(pos1.x, pos1.y)));
    object2->setMatrixPosition(pos1);
    object2->setValueVisible(VISIBLE_OBJECT);
    object2->setTagObject(b);
    object2->setLocalZOrder(b);
    
    listObjects.at(pos1.x + pos1.y*widthMatrixGameBoard) = object2;
    listObjects.at(pos2.x + pos2.y*widthMatrixGameBoard) = object1;
  }
}

/*auto change type when do not have pair */
void GameBoard::findPairObject(bool isDrawingLineColor, float timeDisplayLineColor) {
  std::vector<MainObject*> listVisibleObject;
  std::vector<MainObject*> arraySampleValue;
  if(!listVisibleObject.empty()) {
    listVisibleObject.clear();
  }
  
  for (int i = 0; i < listObjects.size(); i++) {
    if(listObjects.at(i)->getValueVisible() == VISIBLE_OBJECT) {
      listVisibleObject.push_back(listObjects.at(i));
    }
  }
  std::vector<MainObject*> listVisibleObject_Clone = listVisibleObject;
  
  for (int j = 0; j < listVisibleObject.size(); j ++) {
    int type1 = listVisibleObject.at(j)->getTypeObject();
    for (int  k = 0; k < listVisibleObject_Clone.size(); k++) {
      int type2 = listVisibleObject_Clone.at(k)->getTypeObject();
      if(type1 == type2) {
        arraySampleValue.push_back(listVisibleObject_Clone.at(k));
        listVisibleObject_Clone.erase(listVisibleObject_Clone.begin() + k);
        k--;
      }
    }
  }
  
  std::vector<MainObject*> arraySampleValue_Clone = arraySampleValue;
  std::vector<Vec2> subPositionArraySamType;
  
  bool isNeededShuffle = false;
  bool isLastArray = false;
  for (int  h = 0; h < arraySampleValue.size();) {
    int value = arraySampleValue.at(h)->getTypeObject();
    int count = 0;
    for (int m = h; h < arraySampleValue_Clone.size(); m++) {
      if (m >= arraySampleValue_Clone.size()) {
        if(!subPositionArraySamType.empty()) {
          int countLast = 0;
          for (int delta = 0; delta < subPositionArraySamType.size()-1; delta++) {
            countLast++;
            if(checkCanConnectWithPairPosition(subPositionArraySamType.at(delta), subPositionArraySamType.at(delta+1), isDrawingLineColor, timeDisplayLineColor)) {
              isNeededShuffle = true;
              break;
            }
          }
          if(countLast == subPositionArraySamType.size() - 1 && !isNeededShuffle) {
            isLastArray = true;
            subPositionArraySamType.clear();
            break;
          }
          if(isNeededShuffle == true) {
            subPositionArraySamType.clear();
            break;
          }
        }
      } else {
        if(arraySampleValue_Clone.at(m)->getTypeObject() != value) {
          
          h = h + count;
          if (!subPositionArraySamType.empty()) {
            int xCount = 0 ;
            for (int  x = 0 ; x < subPositionArraySamType.size()-1; x++) {
              xCount ++;
              if(checkCanConnectWithPairPosition(subPositionArraySamType.at(x), subPositionArraySamType.at(x+1), isDrawingLineColor, timeDisplayLineColor)) {
                isNeededShuffle = true;
                break;
              }
            }
            
            if(xCount <= subPositionArraySamType.size() ||
               isNeededShuffle == true) {
              subPositionArraySamType.clear();
              break;
            }
          }
          break;
        } else {
          count ++;
          subPositionArraySamType.push_back(arraySampleValue_Clone.at(m)->getMatrixPosition());
        }
      }
    }
    
    if(isNeededShuffle == true || isLastArray == true) {
      break;
    }
  }
  if(isNeededShuffle == false) {
    std::vector<int> targetTypeArray;
    if(!targetTypeArray.empty()) {
      targetTypeArray.clear();
    }
    for (int i = 0; i < arraySampleValue.size(); i++) {
      int type = arraySampleValue.at(i)->getTypeObject();
      targetTypeArray.push_back(type);
    }
    
    for (int i = 0; i < arraySampleValue.size(); i ++) {
      MainObject* objective = arraySampleValue.at(i);
      int newType = RandomBot::getInstance()->randomIndexFromVector(targetTypeArray);
      
      for (int j = 0; j < listObjects.size(); j++) {
        MainObject* objective2 = listObjects.at(j);
        if(objective2->getMatrixPosition() == objective->getMatrixPosition()) {
          objective2->setTypeObject(newType);
          objective2->updateUI(newType);
          listObjects.at(j) = objective2;
        }
      }
    }
  }
}

void GameBoard::setSuggestBotForGame(CheckPairBot* checkPairBot) {
  this->checkPairBot = checkPairBot;
}

bool GameBoard::checkCanConnectWithPairPosition(const Vec2& pos, const Vec2 &pos2, bool isDrawingLineColor, float timeDisplayLineColor) {
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

void GameBoard::refreshGameBoard(){
  std::vector<int> arrayTemp;
  for(int i = 0 ; i < listObjects.size(); i++) {
    if(listObjects.at(i)->getValueVisible() == VISIBLE_OBJECT){
      arrayTemp.push_back(listObjects.at(i)->getTypeObject());
    }
  }
  
  for(int i = 0 ; i < listObjects.size(); i ++) {
    if(listObjects.at(i)->getValueVisible() == VISIBLE_OBJECT){
      MainObject* object = listObjects.at(i);
      int newType =RandomBot::getInstance()->randomIndexFromVector(arrayTemp) - 1;
      if(newType <= 0){ newType = 0; }
      for (int j = 0; j < listObjects.size(); j++) {
        if(listObjects.at(i)->getValueVisible() == VISIBLE_OBJECT){
          MainObject* object2 = listObjects.at(j);
          if(object2->getMatrixPosition() == object->getMatrixPosition()) {
            object2->setTypeObject(newType);
            object2->updateUI(newType);
            listObjects.at(j) = object2;
          }
        }
      }
    }
  }
}

bool GameBoard::isWinGameBoard() {
  bool isWin = true;
  for(int i = 0 ; i < listObjects.size(); i++) {
    if(listObjects.at(i)->getValueVisible() != HIDDEN_OBJECT) {
      isWin = false;
    }
  }
  return isWin;
}
