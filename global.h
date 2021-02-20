//
// Created by brent on 2/17/2021.
//

#ifndef TRADESKILL_GLOBAL_H
#define TRADESKILL_GLOBAL_H

#include <GLFW/glfw3.h>


typedef struct mouse_state_t {
    double x_pos;
    double y_pos;
    double scroll_x_offset;
    double scroll_y_offset;
} MouseState;

typedef struct window_state_t {
    int width;
    int height;
} WindowState;

typedef struct timer_t {
    double time;
    double previous_time;
    double start_time;
    double end_time;
    double delta;
    int frame_count;
    int fps;
} Timer;

typedef struct game_state_t {
    int should_close;
    GLFWcursor *cursor;
    WindowState *window_state;
    MouseState *mouse_state;
} GameState;


extern GameState *game_state;

#endif //TRADESKILL_GLOBAL_H
