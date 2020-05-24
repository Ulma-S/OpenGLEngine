#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdocumentation"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shape.h"
#include "shader.h"

constexpr Object::Vertex rectAngleVertex[] = {
    {-0.5f, -0.5f},
    { 0.5f, -0.5f},
    { 0.5f,  0.5f},
    {-0.5f,  0.5f}
};

int main(void) {
    /* Initialize GLFW */
    if(glfwInit() == GL_FALSE){
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return 1;
    }
    
    /* Set callback at the end of the program */
    atexit(glfwTerminate);
    
    /* Set OpenGL core profile */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create window */
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (window == nullptr){
        std::cerr << "Failed to create window." << std::endl;
        return 1;
    }

    /* Set current OpenGL context */
    glfwMakeContextCurrent(window);
    
    /* Initialize GLEW */
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW." << std::endl;
        return 1;
    }
    
    /* Set vsync */
    glfwSwapInterval(1);
    
    /* Set background color */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /* Create shader program object */
    const GLuint program(LoadProgram("Shader/point.vert", "Shader/point.frag"));
    
    /* Create shape data */
    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectAngleVertex));
    
    /* Loop until window closed */
    while (glfwWindowShouldClose(window) == GL_FALSE){
        /* Reset window color */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        
        /* Draw shape */
        shape->Draw();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Wait events */
        glfwWaitEvents();
    }

    return 0;
}
