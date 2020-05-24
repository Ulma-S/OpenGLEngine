#pragma once
#include "environment.h"
#include <memory>
#include "object.h"

class Shape{
public:
    Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex);
    
    void Draw() const;
    
    virtual void Execute() const;
    
protected:
    const GLsizei vertexCount;
    
private:
    std::shared_ptr<const Object> m_object;
};
