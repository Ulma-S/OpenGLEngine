#include "Matrix.h"

Matrix::Matrix(){}

Matrix::Matrix(const GLfloat *a){
    std::copy(a, a+16, m_matrix);
}
