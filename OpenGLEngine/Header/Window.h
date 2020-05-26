#pragma once
#include "Environment.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{
public:
    Window(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, const char* title = "OpenGL Engine");
    
    ~Window();

    explicit operator bool();
    
    void SwapBuffers() const;
    
    static void Resize(GLFWwindow *const window, int width, int height);
    
    static void Wheel(GLFWwindow *const window, double x, double y);
    
    static void Keyboard(GLFWwindow *const window, int key, int scanCode, int action, int mods);
        
    inline const GLfloat* GetSize() { return m_size; }
    
    GLfloat GetScale() const { return m_scale; }
    
    inline const GLfloat* GetLocation() { return m_location; }
    
private:
    GLFWwindow *const m_window;
    GLfloat m_size[2];
    GLfloat m_scale;
    GLfloat m_location[2];
    int keyStatus;
};
