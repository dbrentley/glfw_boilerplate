//
// Created by brent on 2/17/2021.
//

#include "global.h"
#include "mouse.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void hide_cursor(GLFWwindow *window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void show_cursor(GLFWwindow *window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

GLFWcursor *custom_cursor(GLFWwindow *window) {
    unsigned char cursor_pixels[16 * 16 * 4];
    memset(cursor_pixels, 0xff, sizeof(cursor_pixels));
    GLFWimage cursor_image;
    cursor_image.width = 16;
    cursor_image.height = 16;
    cursor_image.pixels = cursor_pixels;

    GLFWcursor *cursor = glfwCreateCursor(&cursor_image, 0, 0);
    if (cursor == NULL) {
        fprintf(stderr, "Could not create cursor\n");
        exit(-1);
    }
    glfwSetCursor(window, cursor);
    return cursor;
}

void cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos) {
    if (x_pos < 0) {
        x_pos = 0;
    }
    if (x_pos > game_state->window_state->width) {
        x_pos = game_state->window_state->width;
    }
    if (y_pos < 0) {
        y_pos = 0;
    }
    if (x_pos > game_state->window_state->height) {
        x_pos = game_state->window_state->height;
    }
    game_state->mouse_state->x_pos = x_pos;
    game_state->mouse_state->y_pos = y_pos;
}

void scroll_callback(GLFWwindow *window, double x_offset, double y_offset) {
    game_state->mouse_state->scroll_x_offset = x_offset;
    game_state->mouse_state->scroll_y_offset = y_offset;
}