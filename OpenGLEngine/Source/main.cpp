#include "environment.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shape.h"
#include "shader.h"
#include "window.h"

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
    Window window;
    
    /* Set background color */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /* Set viewport */
    glViewport(0, 0, WINDOW_WIDTH*2, WINDOW_HEIGHT*2);
    
    /* Create shader program object */
    const GLuint program(LoadProgram("point.vert", "point.frag"));
    
    /* Get uniform variable location */
    const GLint sizeLoc(glGetUniformLocation(program, "size"));
    const GLint scaleLoc(glGetUniformLocation(program, "scale"));
    const GLint locationLoc(glGetUniformLocation(program, "location"));

    /* Create shape data */
    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectAngleVertex));
    
    /* Loop until window closed */
    while (window){
        /* Reset window color */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        
        glUniform2fv(sizeLoc, 1, window.GetSize());
        glUniform1f(scaleLoc, window.GetScale());
        glUniform2fv(locationLoc, 1, window.GetLocation());
                
        /* Draw shape */
        shape->Draw();
        
        /* Swap front and back buffers */
        window.SwapBuffers();

        /* Wait events */
        glfwWaitEvents();
    }

    return 0;
}
