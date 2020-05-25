#include <string>

#ifdef __x86_64
/* Ignore osX warning */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdocumentation"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#ifndef SHADER_PATH_
#define SHADER_PATH_
static const std::string SHADER_PATH = "Shader/";
#endif // !SHADER_PATH_


#elif _WIN32 | _WIN64

#ifndef SHADER_PATH_
#define SHADER_PATH_
static const std::string SHADER_PATH = "..\\Shader\\";
#endif // !SHADER_PATH_

#endif

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480