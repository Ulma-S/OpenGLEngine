#include "Object.h"

Object::Object(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount, const GLuint *index){
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount*sizeof(Vertex), vertex, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->position);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<Vertex*>(0)->color);
    glEnableVertexAttribArray(1);
    
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), index, GL_STATIC_DRAW);
}


Object::~Object(){
    glDeleteVertexArrays(1, &m_vao);
    
    glDeleteBuffers(1, &m_vbo);
    
    glDeleteBuffers(1, &m_ibo);
}


void Object::Bind() const{
    glBindVertexArray(m_vao);
}
