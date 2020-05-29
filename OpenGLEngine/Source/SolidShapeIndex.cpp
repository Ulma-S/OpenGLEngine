#include "SolidShapeIndex.h"

SolidShapeIndex::SolidShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex,
                                 GLsizei indexCount, const GLuint *index)
    :ShapeIndex(size, vertexCount, vertex, indexCount, index)
{}


void SolidShapeIndex::Execute() const {
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
