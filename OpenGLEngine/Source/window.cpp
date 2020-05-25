#include "window.h"

Window::Window(int width, int height, const char* title)
    :m_window(glfwCreateWindow(width, height, title, nullptr, nullptr))
    ,m_scale(100.0f)
    ,m_location{0.0f, 0.0f}
    ,keyStatus(GLFW_RELEASE)
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
    
    /* Register callback when scrolled */
    glfwSetScrollCallback(m_window, Wheel);
    
    /* Register callback when key status changed */
    glfwSetKeyCallback(m_window, Keyboard);
    
    Resize(m_window, width, height);
}


Window::~Window(){
    glfwDestroyWindow(m_window);
}


Window::operator bool(){
    if(keyStatus == GLFW_RELEASE){
        glfwWaitEvents();
    }else{
        glfwPollEvents();
    }
    
    float speed = 6.0f;
    if(glfwGetKey(m_window, GLFW_KEY_LEFT) != GLFW_RELEASE){
        m_location[0] -= speed/m_size[0];
    }else if(glfwGetKey(m_window, GLFW_KEY_RIGHT) != GLFW_RELEASE){
        m_location[0] += speed/m_size[0];
    }else if(glfwGetKey(m_window, GLFW_KEY_DOWN) != GLFW_RELEASE){
        m_location[1] -= speed/m_size[1];
    }else if(glfwGetKey(m_window, GLFW_KEY_UP) != GLFW_RELEASE){
        m_location[1] += speed/m_size[1];
    }
    
    if(glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE){
        /* Get mouse cursor location */
        double x, y;
        glfwGetCursorPos(m_window, &x, &y);
    
        m_location[0] = static_cast<GLfloat>(x)*2.0f/m_size[0] -1.0f;
        m_location[1] = 1.0f - static_cast<GLfloat>(y)*2.0f/m_size[1];
    }
    
    return !glfwWindowShouldClose(m_window) && !glfwGetKey(m_window, GLFW_KEY_ESCAPE);
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


void Window::Wheel(GLFWwindow *const window, double x, double y){
    Window *const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
    
    if(instance != nullptr){
        instance->m_scale += static_cast<GLfloat>(y);
    }
}

void Window::Keyboard(GLFWwindow *const window, int key, int scanCode, int action, int mods){
    Window *const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));
    
    if(instance != nullptr){
        instance->keyStatus = action;
    }
}
