//
//  RandomIndex.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/28/16.
//
//

#ifndef RandomIndex_h
#define RandomIndex_h

#include <stdio.h>
#include "cocos2d.h"

class RandomIndex {
private:
  int totalAllPairInGame;
  std::vector<int> defaultIndexes;
  std::vector<int> dropTypes;
  std::vector<int> createDefaultIndexes();
  std::vector<int> getRandomPairIndexes(int numberOfPair);
  std::vector<int> createPairIndexes(int numberOfPair, std::vector<int> targetIndexes);
public:
  RandomIndex();
  virtual ~RandomIndex();
  static RandomIndex* getInstance();
  int getRandomIndexFromTargetIndexes(std::vector<int> &array);
  std::vector<int> createDefaultTargetedIndexes(int level);
  void swapValue(int &a, int &b);
  int getDropObjectType(int level);
};

#endif /* RandomIndex_h */
