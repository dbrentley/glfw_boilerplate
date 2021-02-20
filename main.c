#define GLEW_STATIC

#include <GL/glew.h>

#include "global.h"
#include "mouse.h"

#include <stdio.h>
#include <stdlib.h>


GameState *game_state;

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void resize_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    game_state->window_state->width = width;
    game_state->window_state->height = height;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        game_state->should_close = 1;
    }
}

int main() {
    GLFWwindow *window;
    Timer timer;
    timer.frame_count = 0;

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_SAMPLES, 4); // anti-alias

    window = glfwCreateWindow(1920, 1080, "TradesKill", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    game_state = malloc(sizeof(GameState));
    if (game_state == NULL) {
        fprintf(stderr, "Could not create game state\n");
        exit(-1);
    }
    game_state->window_state = malloc(sizeof(WindowState));
    if (game_state->window_state == NULL) {
        fprintf(stderr, "Could not create game state - window state\n");
        exit(-1);
    }
    game_state->mouse_state = malloc(sizeof(MouseState));
    if (game_state->mouse_state == NULL) {
        fprintf(stderr, "Could not create game state - mouse position\n");
        exit(-1);
    }

    //game_state->cursor = custom_cursor(window);
    game_state->should_close = 0;
    game_state->window_state->width = 1920;
    game_state->window_state->height = 1080;

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // v-sync

    glewExperimental = GL_TRUE;
    glewInit();
    const GLubyte *renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte *version = glGetString(GL_VERSION); // version as a string
    fprintf(stderr, "Renderer: %s\n", renderer);
    fprintf(stderr, "OpenGL version supported %s\n", version);

    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    // depth-testing interprets a smaller value as "closer"
    glDepthFunc(GL_LESS);

    float points[] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };

    // vbo
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

    // vao
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // shader
    const char *vertex_shader =
            "#version 400\n"
            "in vec3 vp;"
            "void main() {"
            "  gl_Position = vec4(vp, 1.0);"
            "}";

    // fragment
    const char *fragment_shader =
            "#version 400\n"
            "out vec4 frag_colour;"
            "void main() {"
            "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
            "}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    timer.previous_time = glfwGetTime();
    while (!game_state->should_close && !glfwWindowShouldClose(window)) {
        timer.time = glfwGetTime();
        timer.start_time = timer.time;
        timer.frame_count++;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
        timer.end_time = timer.time;
        timer.delta = timer.end_time - timer.start_time;

        if (timer.time - timer.previous_time >= 1.0) {
            timer.fps = timer.frame_count;
            timer.frame_count = 0;
            timer.previous_time = timer.time;
        }
    }

    glfwDestroyCursor(game_state->cursor);
    glfwDestroyWindow(window);
    glfwTerminate();

    free(game_state->mouse_state);
    free(game_state->window_state);
    free(game_state);
    game_state = NULL;
    return 0;
}
