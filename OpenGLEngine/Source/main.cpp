#include "Environment.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Material.h"
#include "Matrix.h"
#include "Shape.h"
#include "ShapeIndex.h"
#include "Shader.h"
#include "SolidShape.h"
#include "SolidShapeIndex.h"
#include "Uniform.h"
#include "Vector.h"
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

//constexpr Object::Vertex cubeVertex[] = {
//    {-1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f},
//    {-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.8f},
//    {-1.0f,  1.0f,  1.0f,  0.0f,  0.8f,  0.0f},
//    {-1.0f,  1.0f, -1.0f,  0.0f,  0.8f,  0.8f},
//    { 1.0f,  1.0f, -1.0f,  0.8f,  0.0f,  0.0f},
//    { 1.0f, -1.0f, -1.0f,  0.8f,  0.0f,  0.8f},
//    { 1.0f, -1.0f,  1.0f,  0.8f,  0.8f,  0.0f},
//    { 1.0f,  1.0f,  1.0f,  0.8f,  0.8f,  0.8f}
//};

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

//constexpr Object::Vertex solidCubeVertex[] = {
//    { -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f },
//    { -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f },
//    { -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f },
//    { -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f },
//    { -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f },
//    { -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f },
//
//    {  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f },
//    { -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f },
//    { -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f },
//    {  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f },
//    { -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f },
//    {  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f },
//
//    { -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f },
//    {  1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f },
//    {  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f },
//    { -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f },
//    {  1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f },
//    { -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f },
//
//    {  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f },
//    {  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f },
//    {  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f },
//    {  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f },
//    {  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f },
//    {  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f },
//
//    { -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f },
//    { -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f },
//    {  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f },
//    { -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f },
//    {  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f },
//    {  1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f },
//
//    { -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f },
//    {  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f },
//    {  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f },
//    { -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f },
//    {  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f },
//    { -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f }
//};

//constexpr GLuint solidCubeIndex[] = {
//     0,  1,  2,  3,  4,  5,
//     6,  7,  8,  9, 10, 11,
//    12, 13, 14, 15, 16, 17,
//    18, 19, 20, 21, 22, 23,
//    24, 25, 26, 27, 28, 29,
//    30, 31, 32, 33, 34, 35
//};

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
    
    /* Enable back culling */
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    /* Enable depth buffer*/
    glClearDepth(1.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    
    /* Set viewport */
    glViewport(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
    
    /* Create shader program object */
    const GLuint program(LoadProgram("point.vert", "point.frag"));
    
    /* Get uniform variable location */
    const GLint modelviewLoc(glGetUniformLocation(program, "modelview"));
    const GLint projectionLoc(glGetUniformLocation(program, "projection"));
    const GLint normalMatrixLoc(glGetUniformLocation(program, "normalMatrix"));
    const GLint LposLoc(glGetUniformLocation(program, "Lpos"));
    const GLint LambLoc(glGetUniformLocation(program, "Lamb"));
    const GLint LdiffLoc(glGetUniformLocation(program, "Ldiff"));
    const GLint LspecLoc(glGetUniformLocation(program, "Lspec"));
    
    const GLint materialLoc(glGetUniformBlockIndex(program, "Material"));
    
    glUniformBlockBinding(program, materialLoc, 0);
    
    /* Render sphere */
    const int slices(16), stacks(8);
    
    std::vector<Object::Vertex> solidSphereVertex;
    
    for(int j=0; j<=stacks; ++j){
        const float t(static_cast<float>(j)/static_cast<float>(stacks));
        const float y(cosf(PI * t)), r(sinf(PI * t));
        for(int i=0; i<=slices; ++i){
            const float s(static_cast<float>(i)/static_cast<float>(slices));
            const float z(r * cosf(PI * 2 * s)), x(r * sinf(PI * 2 * s));
            const Object::Vertex v = {x, y, z, x, y, z};
            solidSphereVertex.emplace_back(v);
        }
    }
    
    std::vector<GLuint> solidSphereIndex;
    
    for(int j=0; j<stacks; ++j){
        const int k((slices+1) * j);
        for(int i=0; i<slices; ++i){
            const GLuint k0(k + i);
            const GLuint k1(k0 + 1);
            const GLuint k2(k1 + slices);
            const GLuint k3(k2 + 1);
            
            solidSphereIndex.emplace_back(k0);
            solidSphereIndex.emplace_back(k2);
            solidSphereIndex.emplace_back(k3);
            
            solidSphereIndex.emplace_back(k0);
            solidSphereIndex.emplace_back(k3);
            solidSphereIndex.emplace_back(k1);
        }
    }
    

    /* Create shape data */
    std::unique_ptr<const Shape> shape(new SolidShapeIndex(3, static_cast<GLsizei>(solidSphereVertex.size()), solidSphereVertex.data(), static_cast<GLsizei>(solidSphereIndex.size()), solidSphereIndex.data()));
    
    /* Set lighting data */
    static constexpr int Lcount(2);
    static constexpr Vector Lpos[] = { 0.0f, 0.0f, 5.0f, 1.0f, 8.0f, 0.0f, 0.0f, 1.0f };
    static constexpr GLfloat Lamb[] = { 0.2f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };
    static constexpr GLfloat Ldiff[] = { 1.0f, 0.5f, 0.5f, 0.9f, 0.9f, 0.9f };
    static constexpr GLfloat Lspec[] = { 1.0f, 0.5f, 0.5f, 0.9f, 0.9f, 0.9f };
    
    static constexpr Material color[] = {
        { 0.6f, 0.6f, 0.2f, 0.6f, 0.6f, 0.2f, 0.3f, 0.3f, 0.3f, 30.0f },
        { 0.1f, 0.1f, 0.5f, 0.1f, 0.1f, 0.5f, 0.4f, 0.4f, 0.4f, 60.0f }
    };
    
    const Uniform<Material> material[] = { &color[0], &color[1] };
    
    glfwSetTime(0.0f);
    
    /* Loop until window closed */
    while (window){
        /* Reset window color */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        
        const GLfloat *const size(window.GetSize());
        const GLfloat fovy(window.GetScale() * 0.01f);
        const GLfloat aspect(size[0]/size[1]);
        const Matrix projection(Matrix::Perspective(fovy, aspect, 1.0f, 10.0f));
        
        const GLfloat *const location(window.GetLocation());
        const Matrix r(Matrix::Rotate(static_cast<GLfloat>(glfwGetTime()), 0.0f, 1.0f, 0.0f));
        const Matrix model(Matrix::Translate(location[0], location[1], 0.0f) * r);
                        
        const Matrix view(Matrix::Lookat(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));
        
        GLfloat normalMatrix[9];
        
        const Matrix modelview(view * model);
        
        modelview.GetNormalMatrix(normalMatrix);
        
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.Data());
        glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, modelview.Data());
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, normalMatrix);
        for(int i=0; i<Lcount; ++i){
            glUniform4fv(LposLoc+i, 1, (view * Lpos[i]).data());
        }
        glUniform3fv(LambLoc, Lcount, Lamb);
        glUniform3fv(LdiffLoc, Lcount, Ldiff);
        glUniform3fv(LspecLoc, Lcount, Lspec);
        
        /* Draw shape */
        material[0].Select(0);
        shape->Draw();
        
        const Matrix modelview1(modelview * Matrix::Translate(0.0f, 0.0f, 3.0f));
        
        modelview1.GetNormalMatrix(normalMatrix);
        
        glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, modelview1.Data());
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, normalMatrix);
        
        material[1].Select(0);
        shape->Draw();
        
        /* Swap front and back buffers */
        window.SwapBuffers();

        /* Wait events */
        glfwWaitEvents();
    }

    return 0;
}
