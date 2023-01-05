//
//  RandomBot.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/28/16.
//
//

#include "RandomBot.h"
#include "GameDefine.h"

void swapValue(int &a, int &b) {
  int temp = a;
  a = b ;
  b = temp;
}

// A function to generate a random permutation of array[]
void randomize (std::vector<int> & arr, int n ) {
  srand( (unsigned)time(NULL) );
  for (int i = n-1; i > 0; i--) {
    int j = rand() % (i+1);
    swapValue(arr[i], arr[j]);
  }
}

static RandomBot* randomBot = nullptr;

RandomBot::RandomBot() {}

RandomBot::~RandomBot() {}

RandomBot* RandomBot::getInstance() {
  if(randomBot == nullptr) { randomBot = new RandomBot(); }
  return randomBot;
}

void RandomBot::createIndexes(int width, int hight) {
  if(!arrayIndex.empty()) {
    arrayIndex.clear();
  }
  
  for (int i = 1; i <= hight; i ++ ) {
    for (int j = 1; j <= width ; j++) {
      arrayIndex.push_back(j + (i-1)*width);
    }
  }
}

void RandomBot::setArrayIndex(const std::vector<int> &array) {
  this->arrayIndex = array;
}

void RandomBot::setWithHeightMatrix(int width, int hight) {
  this->withMatrix = width;
  this->heightMatrix = hight;
}

void RandomBot::createVectorRandomIndex() {
  srand( (unsigned)time(NULL) );
  if(!expectedVector.empty()) {
    expectedVector.clear();
  }
  
  if (withMatrix*heightMatrix/2 <= arrayIndex.size()) {}
  else {
    createTempVector();
    size_t sizeIndex = arrayIndex.size();
    for (int i = 0 ; i < TOTAL_OBJECT_IN_GAME - sizeIndex; i++) {
      arrayIndex.push_back(randomIndexFromVector(temp));
    }
  }
  for (int i = 0 ; i < withMatrix*heightMatrix/2; i++) {
    int tempIndex = randomIndexFromVector(arrayIndex);
    expectedVector.push_back(tempIndex);
  }
  cloneVector();
}


void RandomBot::createTempVector() {
  if(!temp.empty()) { temp.clear(); }
  
  srand( (unsigned)time(NULL) );
  int sumNeedIndex = TOTAL_OBJECT_IN_GAME - (int)arrayIndex.size();
  for (int i = 0; i < sumNeedIndex; i++) {
    int k = rand() % (TOTAL_OBJECT_IN_GAME-1);
    if (k < arrayIndex.size()-1) {
      temp.push_back(arrayIndex.at(k));
    } else {
      temp.push_back(k);
    }
  }
}

void RandomBot::cloneVector() {
  std::vector<int> temp;
  for (int i = 0 ; i < withMatrix*heightMatrix/2; i++) {
    temp.push_back(expectedVector.at(i));
    temp.push_back(expectedVector.at(i));
  }
  expectedVector = temp;
  randomize(expectedVector, (int)expectedVector.size());
}

int RandomBot::randomIndexFromVector(std::vector<int> &array) {
  srand( (unsigned)time(NULL) );
  int result = 0 ;
  if(!array.empty()) {
    int j = rand() % array.size();
    result = array.at(j);
    int temp =  array.at(j);
    array.at(j) = array.at(array.size()-1);
    array.at(array.size()-1) = temp;
    array.pop_back();
  }
  return result;
}

std::vector<int> RandomBot::getExpectedVector() {
  return expectedVector;
}
