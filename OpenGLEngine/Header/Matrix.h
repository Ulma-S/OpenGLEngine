#pragma once
#include <algorithm>
#include <GL/glew.h>
#include <cmath>

#define PI 3.14159265

class Matrix{
public:
    Matrix();
    
    Matrix(const GLfloat *a);
    
    inline const GLfloat &operator[](std::size_t i) const {
        return m_matrix[i];
    }
    
    inline GLfloat &operator[](std::size_t i){
        return m_matrix[i];
    }
    
    inline const GLfloat* Data() const {
        return m_matrix;
    }
    
    inline void LoadIdentity(){
        std::fill(m_matrix, m_matrix+16, 0.0f);
        m_matrix[0] = m_matrix[5] = m_matrix[10] = m_matrix[15] = 1.0f;
    }
    
    inline static Matrix Identity(){
        Matrix t;
        t.LoadIdentity();
        return t;
    }
    
    inline static Matrix Translate(GLfloat x, GLfloat y, GLfloat z){
        Matrix t;
        t.LoadIdentity();
        t[12] = x;
        t[13] = y;
        t[14] = z;
        return t;
    }
    
    inline static Matrix Scale(GLfloat x, GLfloat y, GLfloat z){
        Matrix t;
        t.LoadIdentity();
        t[0] = x;
        t[5] = y;
        t[10] = z;
        return t;
    }
    
    inline static Matrix RotateX(float rot){
        Matrix t;
        t.LoadIdentity();
        t[5] = std::cosf(PI * rot/180.0f);
        t[6] = std::sinf(PI * rot/180.0f);
        t[9] = std::sinf(PI * rot/180.0f) * -1.0f;
        t[10] = std::cosf(PI * rot/180.0f);
        return t;
    }
    
    inline static Matrix RotateY(float rot){
        Matrix t;
        t.LoadIdentity();
        t[0] = std::cosf(PI * rot/180.0f);
        t[2] = std::sinf(PI * rot/180.0f) * -1.0f;
        t[8] = std::sinf(PI * rot/180.0f);
        t[10] = std::cosf(PI * rot/180.0f);
        return t;
    }
    
    inline static Matrix RotateZ(float rot){
        Matrix t;
        t.LoadIdentity();
        t[0] = std::cosf(PI * rot/180.0f);
        t[1] = std::sinf(PI * rot/180.0f);
        t[4] = std::sinf(PI * rot/180.0f) * -1.0f;
        t[5] = std::cosf(PI * rot/180.0f);
        return t;
    }
    
    inline static Matrix Rotate(GLfloat rot, GLfloat x, GLfloat y, GLfloat z){
        Matrix t;
        const GLfloat d(sqrt(x*x + y*y + z*z));
        if(d > 0.0f){
            const GLfloat l(x/d), m(y/d), n(z/d);
            const GLfloat l2(l * l), m2(m * m), n2(n * n);
            const GLfloat lm(l * m), mn(m * n), nl(n * l);
            const GLfloat c(std::cosf(rot)), c1(1.0f - c), s(std::sinf(rot));
    
            t.LoadIdentity();
            t[ 0] = (1.0f - l2) * c + l2;
            t[ 1] = lm * c1 + n * s;
            t[ 2] = nl * c1 - m * s;
            t[ 4] = lm * c1 - n * s;
            t[ 5] = (1.0f - m2) * c + m2;
            t[ 6] = mn * c1 + l * s;
            t[ 8] = nl * c1 + m * s;
            t[ 9] = mn * c1 - l * s;
            t[10] = (1.0f - n2) * c + n2;
        }
        return t;
    }
    
    inline Matrix operator*(const Matrix &m) const {
        Matrix t;
        for(int i=0;i<16;i++){
            const int j(i & 3), k(i & ~3);
            t[i] = m_matrix[0+j] * m[k+0] +
                   m_matrix[4+j] * m[k+1] +
                   m_matrix[8+j] * m[k+2] +
                   m_matrix[12 + j] * m[k+3];
        }
        return t;
    }
    
    inline static Matrix Lookat(
        GLfloat ex, GLfloat ey, GLfloat ez,
        GLfloat gx, GLfloat gy, GLfloat gz,
        GLfloat ux, GLfloat uy, GLfloat uz){
        const Matrix tv(Translate(-ex, -ey, -ez));
        
        const GLfloat tx(ex-gx);
        const GLfloat ty(ey-gy);
        const GLfloat tz(ez-gz);
        
        const GLfloat rx(uy*tz - uz*ty);
        const GLfloat ry(uz*tx - ux*tz);
        const GLfloat rz(ux*ty - uy*tx);
        
        const GLfloat sx(ty*rz - tz*ry);
        const GLfloat sy(tz*rx - tx*rz);
        const GLfloat sz(tx*ry - ty*rx);
        
        const GLfloat s2(sx*sx + sy*sy + sz*sz);
        if(s2 == 0.0f) return tv;
        
        Matrix rv;
        rv.LoadIdentity();
        
        const GLfloat r(sqrt(rx*rx + ry*ry + rz*rz));
        rv[0] = rx/r;
        rv[4] = ry/r;
        rv[8] = rz/r;
        
        const GLfloat s(sqrt(s2));
        rv[1] = sx/s;
        rv[5] = sy/s;
        rv[9] = sz/s;
        
        const GLfloat t(sqrt(tx*tx + ty*ty + tz*tz));
        rv[2] = tx/t;
        rv[6] = ty/t;
        rv[10] = tz/t;
        
        return rv * tv;
    }
    
    inline static Matrix Orthogonal(GLfloat left, GLfloat right,
                             GLfloat bottom, GLfloat top,
                             GLfloat zNear, GLfloat zFar){
        Matrix t;
        const GLfloat dx(right-left);
        const GLfloat dy(top-bottom);
        const GLfloat dz(zFar-zNear);
        
        if(dx != 0 && dy != 0 && dz != 0){
            t.LoadIdentity();
            t[0] = 2.0f/dx;
            t[5] = 2.0f/dy;
            t[10] = -2.0f/dz;
            t[12] = -(right+left)/dx;
            t[13] = -(top+bottom)/dy;
            t[14] = -(zFar+zNear)/dz;
        }
        
        return t;
    }
    
    inline static Matrix Frustum(GLfloat left, GLfloat right,
                                 GLfloat bottom, GLfloat top,
                                 GLfloat zNear, GLfloat zFar){
        Matrix t;
        const GLfloat dx(right-left);
        const GLfloat dy(top-bottom);
        const GLfloat dz(zFar-zNear);
        
        if(dx != 0.0f && dy != 0.0f && dz != 0.0f){
            t.LoadIdentity();
            t[0] = 2.0f * zNear / dx;
            t[5] = 2.0f * zNear / dy;
            t[8] = (right + left) / dx;
            t[9] = (top + bottom) / dy;
            t[10] = -(zNear + zFar) / dz;
            t[11] = -1.0f;
            t[14] = -2.0f * zFar * zNear / dz;
            t[15] = 0.0f;
        }
        return t;
    }
    
    inline static Matrix Perspective(GLfloat fovy, GLfloat aspect,
                                     GLfloat zNear, GLfloat zFar){
        Matrix t;
        const GLfloat dz(zFar - zNear);
        
        if(dz != 0.0f){
            t.LoadIdentity();
            t[5] = std::tanf(fovy * 0.5f);
            t[0] = t[5] / aspect;
            t[10] = -(zFar + zNear) / dz;
            t[11] = -1.0f;
            t[14] = -2.0f * zFar * zNear / dz;
            t[15] = 0.0f;
        }
        return t;
    }
    inline void GetNormalMatrix(GLfloat *m) const {
        m[0] = m_matrix[ 5] * m_matrix[10] - m_matrix[ 6] * m_matrix[ 9];
        m[1] = m_matrix[ 6] * m_matrix[ 8] - m_matrix[ 4] * m_matrix[10];
        m[2] = m_matrix[ 4] * m_matrix[ 9] - m_matrix[ 5] * m_matrix[ 8];
        m[3] = m_matrix[ 9] * m_matrix[ 2] - m_matrix[10] * m_matrix[ 1];
        m[4] = m_matrix[10] * m_matrix[ 0] - m_matrix[ 8] * m_matrix[ 2];
        m[5] = m_matrix[ 8] * m_matrix[ 1] - m_matrix[ 9] * m_matrix[ 0];
        m[6] = m_matrix[ 1] * m_matrix[ 6] - m_matrix[ 2] * m_matrix[ 5];
        m[7] = m_matrix[ 2] * m_matrix[ 4] - m_matrix[ 0] * m_matrix[ 6];
        m[8] = m_matrix[ 0] * m_matrix[ 5] - m_matrix[ 1] * m_matrix[ 4];
    }
    
private:
    GLfloat m_matrix[16];
};
