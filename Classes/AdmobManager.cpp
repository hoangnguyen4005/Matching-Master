//
//  AdmobManager.cpp
//  MatchingMaster
//
//  Created by Harry Nguyen on 5/1/23.
//

#include "AdmobManager.h"
#include "cocos2d.h"
using namespace std;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

AdmobManager* AdmobManager::instance= nullptr;

AdmobManager* AdmobManager::getInstance() {
  if(instance == nullptr) { instance = new AdmobManager(); }
  return instance;
}

void AdmobManager::init(const std::string &bannerId, const std::string &interstitialId) {}

void AdmobManager::showBanner() {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo minfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","showBanner","()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
  }
#endif
}

void AdmobManager::hideBanner() {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo minfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","hideBanner","()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
  }
#endif
}


void AdmobManager::showInterstitial() {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  cocos2d::JniMethodInfo minfo;
  if (cocos2d::JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","showInterstitial","()V")) {
    minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
  }
#endif
}
