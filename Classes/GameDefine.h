//
//  GameDefine.h
//  MatchingMaster
//
//  Created by Harry Nguyen on 8/18/16.
//
//

#ifndef GameDefine_h
#define GameDefine_h

typedef enum {
  IDLE_PROGRESS = 1,
  PAUSE_PROGRESS = 2,
  ADDITION_TIME_PROGRESS = 3,
  STOP = 4
} STATUS_LOADING;

typedef enum {
  TAG_BTN_REFRESH = 201,
  TAG_BTN_PAUSE = 202,
  TAG_BTN_BACK =203,
  TAG_BTN_SUGGEST =204
}TAG_BUTTON;

typedef enum{
  DROP_LEFT = 0,
  DROP_RIGHT = 1,
  DROP_UP = 2,
  DROP_DOWN = 3,
  DROP_IDLE = 4
}STATUS_DROP;

typedef enum {
  LINE  = 0,
  Z_SHAPE = 1,
  L_SHAPE = 2,
  U_SHAPE = 3
}DRAW_TYPE;

typedef enum {
  TAG_YES_BUTTON = 100,
  TAG_NO_BUTTON = 101,
  TAG_WIN_NEXT = 102,
  TAG_OVER_REPLAY = 103,
  TAG_OVER_MAIN_HOME = 104,
  TAG_PAUSE_PLAY = 105,
  TAG_PAUSE_HOME = 106,
}TAG_POP_UP_BUTTON;

typedef enum {
  TAG_POP_UP_BACK = 1401,
  TAG_POP_UP_WIN = 1402,
  TAG_POP_UP_GAME_OVER = 1403,
  TAG_POP_UP_PAUSE = 1404,
  TAG_LAYER_START_GAME = 1405,
}TAG_POPUP;

#define MAX_WIDTH 14
#define MAX_HEIGHT 7

#define BUFFER_DRAW_Y 26
#define BUFFER_DRAW_X 10

#define WIDTH_DRAW_LINE 8.0

#define ADD_TIME_PROGRESS_BAR 3.0f
#define TIME_UPDATE_PROGRESS_BAR 0.02f

#define TIME_DELAY_DRAW_LINE 0.1f
#define TIME_DELAY_DRAW_SUGGEST_LINE 1.0f
#define TOTAL_OBJECT_IN_GAME 36

#define X_AXIS 1
#define Y_AXIS 2

#define SHAPE_WIDTH 160
#define SHAPE_HEIGHT 200

#define HIDDEN_OBJECT 0
#define VISIBLE_OBJECT 1

#define BG_POP_UP_COLOR Color4B(50.0f, 50.0f, 50.0f,100.0f)
#define TITLE_GAME "Matching Master"

#define OPEN_GAME_SCENE_KEY "OPEN_GAME_SCENE_KEY"
#define OPEN_GAME_SCENE_FREQUENCY 6

#endif /* GameDefine_h */
