#pragma once
#include "ShapeIndex.h"

class SolidShapeIndex : public ShapeIndex{
public:
    SolidShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex,
                    GLsizei indexCount, const GLuint *index);
    
    virtual void Execute() const override;
};
