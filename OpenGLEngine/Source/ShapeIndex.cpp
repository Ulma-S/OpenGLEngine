#include "ShapeIndex.h"

ShapeIndex::ShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex,
                       GLsizei indexCount, const GLuint *index)
    :Shape(size, vertexCount, vertex, indexCount, index)
    ,indexCount(indexCount)
{}


void ShapeIndex::Execute() const{
    glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
}
