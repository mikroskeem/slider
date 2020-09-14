#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#define NK_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define W_WIDTH  800
#define W_HEIGHT 480
#define MAX_VERTEX_BUFFER (512 * 1024)
#define MAX_ELEMENT_BUFFER (128 * 1024)

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

static float slider_value = 0.0f;

static void error_cb(int n, const char *msg){
  printf("Error %d: %s\n", n, msg);
}

static void slider_cb(float f) {
  printf("Value: %d\n", ((int) (f * 100)));
}

int main(int argc, char **argv) {
  struct nk_glfw glfw = {0};
  static GLFWwindow *win;
  struct nk_context *ctx;

  glfwSetErrorCallback(error_cb);
  if (!glfwInit()) {
    fprintf(stderr, "[GFLW] failed to init!\n");
    return 1;
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  
  win = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Slider", NULL, NULL);
  glfwMakeContextCurrent(win);

  glViewport(0, 0, W_WIDTH, W_HEIGHT);
  glewExperimental = 1;
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to setup GLEW\n");
    exit(1);
  }

  ctx = nk_glfw3_init(&glfw, win, NK_GLFW3_INSTALL_CALLBACKS);

  // Load fonts
  struct nk_font_atlas *atlas;
  nk_glfw3_font_stash_begin(&glfw, &atlas);
  nk_glfw3_font_stash_end(&glfw);
  
  while (!glfwWindowShouldClose(win)) {
    glfwPollEvents();
    nk_glfw3_new_frame(&glfw);

    if (nk_begin(ctx, "", nk_rect(0, 0, W_WIDTH, W_HEIGHT), 0)) {      
      nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
      
      nk_layout_row_push(ctx, 50);
      nk_label(ctx, "slideeeee", NK_TEXT_CENTERED);
      nk_layout_row_push(ctx, 110);

      float new_slider_value = slider_value;
      nk_slider_float(ctx, 0, &new_slider_value, 1.0f, 0.1f);

      if (new_slider_value != slider_value) {
        slider_cb(new_slider_value);
      }

      slider_value = new_slider_value;
      
      nk_layout_row_end(ctx);
    }
    nk_end(ctx);

    glViewport(0, 0, W_WIDTH, W_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
    glfwSwapBuffers(win);
  }

  nk_free(ctx);
  glfwTerminate();

  return 0;
}
