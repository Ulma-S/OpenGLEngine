#include "Shape.h"

Shape::Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex, GLsizei indexCount, const GLuint *index)
    :m_object(new Object(size, vertexCount, vertex, indexCount, index))
    ,vertexCount(vertexCount)
{}


void Shape::Draw() const{
    m_object->Bind();
    Execute();
}


void Shape::Execute() const{
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}
