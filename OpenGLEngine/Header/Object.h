#pragma once
#include "Environment.h"
#include <GL/glew.h>

class Object{
public:
    struct Vertex{
        GLfloat position[3];
        
        GLfloat color[3];
    };
    
    Object(GLint size, GLsizei vertexCount, const Vertex *vertex,
           GLsizei indexCount = 0, const GLuint *index = nullptr);
    
    virtual ~Object();
    
    void Bind() const;
    
private:
    GLuint m_vao;
    GLuint m_vbo;
    
    GLuint m_ibo;
    
    /* Avoid share pointer */
    Object(const Object &o);
    Object operator=(const Object &o);
};
