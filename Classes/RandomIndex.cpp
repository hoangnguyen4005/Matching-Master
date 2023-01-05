//
//  RandomIndex.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/28/16.
//
//

#include "RandomIndex.h"
#include "GameDefine.h"
#include <algorithm>
#include <random>

std::vector<int> defaultDropTypes{ DROP_LEFT, DROP_RIGHT, DROP_UP, DROP_DOWN };

RandomIndex::RandomIndex() {
  defaultIndexes.clear();
  totalAllPairInGame = ((TOTAL_ROW - 2) * (TOTAL_COLUMN - 2))/2;
  defaultIndexes = createDefaultIndexes();
}
RandomIndex::~RandomIndex() {}

static RandomIndex* instance = nullptr;

RandomIndex* RandomIndex::getInstance() {
  if(instance == nullptr) { instance = new RandomIndex(); }
  return instance;
}

int RandomIndex::getDropObjectType(int level) {
  if(level == 1) { return DROP_IDLE; }
  if(dropTypes.empty()) { dropTypes = defaultDropTypes; }
  return getRandomIndexFromTargetIndexes(dropTypes);
}

int RandomIndex::getRandomIndexFromTargetIndexes(std::vector<int> &array) {
  if(array.empty()) { return 0;}
  srand((unsigned)time(NULL));
  int size = int(array.size());
  int index = rand() % size;
  int value = array.at(index);
  array.erase(array.begin() + index);
  return value;
}

std::vector<int> RandomIndex::createDefaultTargetedIndexes(int level) {
  if (level >= 1 && level <= 2) {
    return getRandomPairIndexes(TOTAL_RESOURCE_GAME - 12); //24
  } else if(level > 2 && level <= 5) {
    return getRandomPairIndexes(TOTAL_RESOURCE_GAME - 8); // 28
  } else if(level > 5 && level <= 9) {
    return getRandomPairIndexes(TOTAL_RESOURCE_GAME - 4); // 32
  } else {
    return getRandomPairIndexes(TOTAL_RESOURCE_GAME);     // 36
  }
}

void RandomIndex::swapValue(int &a, int &b) {
  int tempValue = a;
  a = b ;
  b = tempValue;
}

std::vector<int> RandomIndex::createDefaultIndexes() {
  std::vector<int> result;
  for(int i = 0; i < TOTAL_RESOURCE_GAME; i++){ result.push_back(i); }
  return result;
}

std::vector<int> RandomIndex::createPairIndexes(int numberOfPair, std::vector<int> targetIndexes) {
  std::vector<int> result;
  std::vector<int> indexes;
  for(int k = 0; k < numberOfPair; k++) {
    if(indexes.empty()) { indexes = targetIndexes; }
    int value = getRandomIndexFromTargetIndexes(indexes);
    result.push_back(value);
  }
  return result;
}

std::vector<int> RandomIndex::getRandomPairIndexes(int numberOfPair) {
  std::vector<int> indexes = createPairIndexes(numberOfPair, defaultIndexes);
 
  /// create left indexes
  if(totalAllPairInGame > numberOfPair) {
    std::vector<int> leftIndexes = createPairIndexes(totalAllPairInGame - numberOfPair, indexes);
    indexes.insert(indexes.end(), leftIndexes.begin(), leftIndexes.end() );
  }
  
  /// Double pair  indexes vector
  std::vector<int> pairIndexes;
  for (int index = 0; index < indexes.size(); index++) {
    pairIndexes.push_back(indexes[index]);
    pairIndexes.push_back(indexes[index]);
  }
  
  /// shuffle indexes vector
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(pairIndexes), std::end(pairIndexes), rng);
  return pairIndexes;
}
