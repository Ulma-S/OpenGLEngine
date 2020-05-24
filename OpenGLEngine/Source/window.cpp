#include "window.h"

Window::Window(int width, int height, const char* title)
    :m_window(glfwCreateWindow(width, height, title, nullptr, nullptr))
    ,m_scale(100.0f)
{
    /* Create window */
    if(m_window == nullptr){
        std::cerr << "Failed to create GLFW window." << std::endl;
        exit(1);
    }
    
    /* Set current GLFW context */
    glfwMakeContextCurrent(m_window);
    
    /* Initialize GLEW */
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize " << std::endl;
        exit(1);
    }
    
    /* Set vsync */
    glfwSwapInterval(1);
    
    /* Register this pointer for window */
    glfwSetWindowUserPointer(m_window, this);
    
    /* Register callback when window size changed */
    glfwSetWindowSizeCallback(m_window, Resize);
    
    Resize(m_window, width, height);
}


Window::~Window(){
    glfwDestroyWindow(m_window);
}


Window::operator bool(){
    glfwWaitEvents();
    
    return !glfwWindowShouldClose(m_window);
}


void Window::SwapBuffers() const{
    glfwSwapBuffers(m_window);
}


void Window::Resize(GLFWwindow *const window, int width, int height){
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    
    glViewport(0, 0, fbWidth, fbHeight);
    
    Window *const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
    
    if(instance != nullptr){
        instance->m_size[0] = static_cast<GLfloat>(width);
        instance->m_size[1] = static_cast<GLfloat>(height);
    }
}
