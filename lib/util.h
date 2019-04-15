#ifndef _OPENGL_UTIL_H_
#define _OPENGL_UTIL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <cstdlib>
#include <cstdarg>

GLFWwindow * init_window_context(unsigned int screen_width, unsigned int screen_height, const char *title);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void clean_up(unsigned int *,unsigned int *,unsigned int *);
int createShader(GLenum shaderType, const char *shaderSource);
int create_program(int num_of_shaders, ...);
int create_program_from_files(const char* vertexPath, const char* fragmentPath);

#ifdef __cplusplus
}
#endif

#endif