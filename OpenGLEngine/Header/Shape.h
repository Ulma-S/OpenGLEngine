#pragma once
#include "Environment.h"
#include <memory>
#include "Object.h"

class Shape{
public:
    Shape(GLint size, GLsizei vertexCount, const Object::Vertex *vertex,
          GLsizei indexCount = 0, const GLuint *index = nullptr);
    
    void Draw() const;
    
    virtual void Execute() const;
    
protected:
    const GLsizei vertexCount;
    
private:
    std::shared_ptr<const Object> m_object;
};
