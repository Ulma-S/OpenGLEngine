#include <string>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#ifdef __x86_64
/* Ignore osX warning */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdocumentation"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#ifndef SHADER_PATH_
#define SHADER_PATH_
static const std::string SHADER_PATH = "Shader/";
#endif // !SHADER_PATH_

#define VIEW_WIDTH WINOW_WIDTH * 2
#define VIEW_HEIGHT WINDOW_HEIGHT * 2

#elif _WIN32 | _WIN64

#ifndef SHADER_PATH_
#define SHADER_PATH_
static const std::string SHADER_PATH = "..\\Shader\\";
#endif // !SHADER_PATH_

#define VIEW_WIDTH WINDOW_WIDTH
#define VIEW_HEIGHT WINDOW_HEIGHT
#endif
