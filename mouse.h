//
// Created by brent on 2/17/2021.
//

#ifndef TRADESKILL_MOUSE_H
#define TRADESKILL_MOUSE_H


void show_cursor(GLFWwindow *window);

void hide_cursor(GLFWwindow *window);

GLFWcursor *custom_cursor(GLFWwindow *window);

void cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos);

void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);

#endif //TRADESKILL_MOUSE_H
