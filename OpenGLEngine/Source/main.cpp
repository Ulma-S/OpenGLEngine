#include "Environment.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Matrix.h"
#include "Shape.h"
#include "ShapeIndex.h"
#include "Shader.h"
#include "SolidShape.h"
#include "SolidShapeIndex.h"
#include "Window.h"

//constexpr Object::Vertex octahedronVertex[] = {
//    { 0.0f,  1.0f,  0.0f},
//    {-1.0f,  0.0f,  0.0f},
//    { 0.0f, -1.0f,  0.0f},
//    { 1.0f,  0.0f,  0.0f},
//    { 0.0f,  1.0f,  0.0f},
//    { 0.0f,  0.0f,  1.0f},
//    { 0.0f, -1.0f,  0.0f},
//    { 0.0f,  0.0f, -1.0f},
//    {-1.0f,  0.0f,  0.0f},
//    { 0.0f,  0.0f,  1.0f},
//    { 1.0f,  0.0f,  0.0f},
//    { 0.0f,  0.0f, -1.0f}
//};

constexpr Object::Vertex cubeVertex[] = {
    {-1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f},
    {-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.8f},
    {-1.0f,  1.0f,  1.0f,  0.0f,  0.8f,  0.0f},
    {-1.0f,  1.0f, -1.0f,  0.0f,  0.8f,  0.8f},
    { 1.0f,  1.0f, -1.0f,  0.8f,  0.0f,  0.0f},
    { 1.0f, -1.0f, -1.0f,  0.8f,  0.0f,  0.8f},
    { 1.0f, -1.0f,  1.0f,  0.8f,  0.8f,  0.0f},
    { 1.0f,  1.0f,  1.0f,  0.8f,  0.8f,  0.8f}
};

//constexpr GLuint wireCubeIndex[] = {
//    1, 0,
//    2, 7,
//    3, 0,
//    4, 7,
//    5, 0,
//    6, 7,
//    1, 2,
//    2, 3,
//    3, 4,
//    4, 5,
//    5, 6,
//    6, 1
//};

constexpr Object::Vertex solidCubeVertex[] = {
    { -1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.1f },
    { -1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.1f },
    { -1.0f,  1.0f,  1.0f, 0.1f, 0.8f, 0.1f },
    { -1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.1f },
    { -1.0f,  1.0f,  1.0f, 0.1f, 0.8f, 0.1f },
    { -1.0f,  1.0f, -1.0f, 0.1f, 0.8f, 0.1f },
    
    {  1.0f, -1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
    { -1.0f, -1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
    { -1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
    {  1.0f, -1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
    { -1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
    {  1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.8f },
    
    { -1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.8f },
    {  1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.8f },
    {  1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.8f },
    { -1.0f, -1.0f, -1.0f, 0.1f, 0.8f, 0.8f },
    {  1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.8f },
    { -1.0f, -1.0f,  1.0f, 0.1f, 0.8f, 0.8f },
    
    {  1.0f, -1.0f,  1.0f, 0.1f, 0.1f, 0.8f },
    {  1.0f, -1.0f, -1.0f, 0.1f, 0.1f, 0.8f },
    {  1.0f,  1.0f, -1.0f, 0.1f, 0.1f, 0.8f },
    {  1.0f, -1.0f,  1.0f, 0.1f, 0.1f, 0.8f },
    {  1.0f,  1.0f, -1.0f, 0.1f, 0.1f, 0.8f },
    {  1.0f,  1.0f,  1.0f, 0.1f, 0.1f, 0.8f },
    
    { -1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.1f },
    { -1.0f,  1.0f,  1.0f, 0.8f, 0.1f, 0.1f },
    {  1.0f,  1.0f,  1.0f, 0.8f, 0.1f, 0.1f },
    { -1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.1f },
    {  1.0f,  1.0f,  1.0f, 0.8f, 0.1f, 0.1f },
    {  1.0f,  1.0f, -1.0f, 0.8f, 0.1f, 0.1f },
    
    { -1.0f, -1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
    {  1.0f, -1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
    {  1.0f,  1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
    { -1.0f, -1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
    {  1.0f,  1.0f,  1.0f, 0.8f, 0.8f, 0.1f },
    { -1.0f,  1.0f,  1.0f, 0.8f, 0.8f, 0.1f }
};

constexpr GLuint solidCubeIndex[] = {
     0,  1,  2,  3,  4,  5,
     6,  7,  8,  9, 10, 11,
    12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35
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
    glViewport(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
    
    /* Create shader program object */
    const GLuint program(LoadProgram("point.vert", "point.frag"));
    
    /* Get uniform variable location */
    const GLint modelviewLoc(glGetUniformLocation(program, "modelview"));
    const GLint projectionLoc(glGetUniformLocation(program, "projection"));

    /* Create shape data */
    std::unique_ptr<const Shape> shape(new SolidShapeIndex(3, 36, solidCubeVertex, 36, solidCubeIndex));
    
    glfwSetTime(0.0f);
    
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
        const Matrix r(Matrix::Rotate(static_cast<GLfloat>(glfwGetTime()), 0.0f, 1.0f, 0.0f));
        const Matrix model(Matrix::Translate(location[0], location[1], 0.0f) * r);
                        
        const Matrix view(Matrix::Lookat(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
        
        const Matrix modelview(view * model);
        
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.Data());
        glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, modelview.Data());
        
        std::cout << glfwGetTime() << std::endl;
        
        /* Draw shape */
        shape->Draw();
        
        /* Swap front and back buffers */
        window.SwapBuffers();

        /* Wait events */
        glfwWaitEvents();
    }

    return 0;
}
