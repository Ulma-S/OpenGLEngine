#pragma once
#include "environment.h"
#include <GL/glew.h>

class Object{
public:
    struct Vertex{
        GLfloat position[2];
    };
    
    Object(GLint size, GLsizei vertexCount, const Vertex *vertex);
    
    virtual ~Object();
    
    void Bind() const;
    
private:
    GLuint vao;
    GLuint vbo;
    
    /* Avoid share pointer */
    Object(const Object &o);
    Object operator=(const Object &o);
};
