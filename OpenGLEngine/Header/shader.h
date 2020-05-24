#pragma once
#include "environment.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLboolean PrintShaderInfoLog(GLuint shader, const char *str);

GLboolean PrintProgramInfoLog(GLuint program);

GLuint CreateProgram(const char *vsrc, const char *fsrc);

bool ReadShaderSource(const char *name, std::vector<GLchar> &buffer);

GLuint LoadProgram(const char *vert, const char *frag);
