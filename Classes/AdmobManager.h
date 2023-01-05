//
//  AdmobManager.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 5/1/23.
//

#ifndef AdmobManager_h
#define AdmobManager_h

#include <string>

class AdmobManager {
private:
  static AdmobManager* instance;
public:
  static AdmobManager* getInstance();
  void init(const std::string &bannerId, const std::string &interstitialId);
  void showBanner();
  void hideBanner();
  void showInterstitial();
};

#endif /* AdmobManager_h */
