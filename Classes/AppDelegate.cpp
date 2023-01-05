#include "AppDelegate.h"
#include "HomeScene.h"
#include "AndroidScene.h"
#include "GameDefine.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(2208, 1242);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
  //set OpenGL context attributions,now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
  
  GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
  return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if(!glview) {
    glview = GLViewImpl::create("MatchingMaster");
    director->setOpenGLView(glview);
  }
  
  // turn on display FPS
  director->setDisplayStats(false);
  
  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / 60);
  
  // Set the design resolution
  glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
  
  register_all_packages();
  /*Add search path*/
  FileUtils::getInstance()->addSearchPath("fonts");
  FileUtils::getInstance()->addSearchPath("imagegameScene");
  FileUtils::getInstance()->addSearchPath("popup");
  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_frame_cache.plist");
  #if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
  auto scene = HomeScene::createHomeScene();
  director->runWithScene(scene);
  #endif
  #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
  auto scene = AndroidScene::CreateScene();
  director->runWithScene(scene);
  #endif
  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
  Director::getInstance()->stopAnimation();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
  Director::getInstance()->startAnimation();
}
