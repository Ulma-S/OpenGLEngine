#pragma once
#include "Shape.h"

class SolidShape : public Shape {
public:
    SolidShape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex);
    
    virtual void Execute() const override;
};

