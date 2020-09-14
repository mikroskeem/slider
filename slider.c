#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_IMPLEMENTATION
#include "nuklear.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define W_HEIGHT 800
#define W_WIDTH  480
#define MAX_MEMORY 1024 * 1024 * 1024 * 64

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

static void error_cb(int n, const char *msg){
  printf("Error %d: %s\n", n, msg);
}

int main(int argc, char **argv) {
  static GLFWwindow *win;
  struct nk_context ctx;

  glfwSetErrorCallback(error_cb);
  if (!glfwInit()) {
    fprintf(stderr, "[GFLW] failed to init!\n");
    return 1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  win = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Demo", NULL, NULL);
  glfwMakeContextCurrent(win);

  glViewport(0, 0, W_WIDTH, W_HEIGHT);
  glewExperimental = 1;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to setup GLEW\n");
    exit(1);
  }

  struct nk_font *font;
  nk_init_fixed(&ctx, calloc(1, MAX_MEMORY), MAX_MEMORY, *font);

  while (!glfwWindowShouldClose(win)) {
    glfwPollEvents();

    //nk_window_set_bounds(&ctx, "Window", nk_rect(0, 0, W_WIDTH, W_HEIGHT));
    nk_begin(&ctx, "Slider", nk_rect(0, 0, W_HEIGHT, W_WIDTH), 0);
    
    nk_end(&ctx);

    glfwSwapBuffers(win);
  }

  nk_free(&ctx);
  glfwTerminate();

  return 0;
}
