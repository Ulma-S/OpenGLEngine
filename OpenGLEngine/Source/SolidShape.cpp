#include "SolidShape.h"

SolidShape::SolidShape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex)
    :Shape(size, vertexCount, vertex)
{}


void SolidShape::Execute() const {
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
