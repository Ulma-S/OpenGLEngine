#include "environment.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "matrix.h"
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
    const GLint modelviewLoc(glGetUniformLocation(program, "modelview"));
    const GLint projectionLoc(glGetUniformLocation(program, "projection"));

    /* Create shape data */
    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectAngleVertex));
    
    /* Loop until window closed */
    while (window){
        /* Reset window color */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        
        const GLfloat *const size(window.GetSize());
        const GLfloat fovy(window.GetScale() * 0.01f);
        const GLfloat aspect(size[0]/size[1]);
        const Matrix projection(Matrix::Perspective(fovy, aspect, 1.0f, 10.0f));
        
        const GLfloat *const location(window.GetLocation());
        const Matrix model(Matrix::Translate(location[0], location[1], 0.0f));
                        
        const Matrix view(Matrix::Lookat(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
        
        const Matrix modelview(view * model);
        
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.Data());
        glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, modelview.Data());
        
        /* Draw shape */
        shape->Draw();
        
        /* Swap front and back buffers */
        window.SwapBuffers();

        /* Wait events */
        glfwWaitEvents();
    }

    return 0;
}
