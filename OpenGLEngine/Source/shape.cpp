#include "shape.h"

Shape::Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex)
    :object(new Object(size, vertexCount, vertex))
    ,vertexCount(vertexCount)
{}


void Shape::Draw() const{
    object->Bind();
    Execute();
}


void Shape::Execute() const{
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}
