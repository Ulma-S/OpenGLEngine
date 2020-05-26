#pragma once
#include "Shape.h"

class ShapeIndex : public Shape{
public:
    ShapeIndex(GLint size, GLsizei vertexCount, const Object::Vertex *vertex,
               GLsizei indexCount, const GLuint *index);
    
    virtual void Execute() const override;
    
protected:
    const GLsizei indexCount;
};
