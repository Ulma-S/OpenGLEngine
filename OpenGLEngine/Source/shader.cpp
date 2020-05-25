#include "shader.h"

/* Show compile message of shader object */
GLboolean PrintShaderInfoLog(GLuint shader, const char *str){
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) std::cerr << "Compile error in " << str << std::endl;
    
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
    
    if(bufSize>1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}


/* Show link result message of program object */
GLboolean PrintProgramInfoLog(GLuint program){
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) std::cerr << "Link error." << std::endl;
    
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
    
    if(bufSize>1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}


/* Create program object */
GLuint CreateProgram(const char *vsrc, const char *fsrc){
    const GLuint program(glCreateProgram());
    
    if(vsrc != nullptr){
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, nullptr);
        glCompileShader(vobj);
        
        if(PrintShaderInfoLog(vobj, "vertex shader")){
            glAttachShader(program, vobj);
        }
        glDeleteShader(vobj);
    }
    
    if(fsrc != nullptr){
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, nullptr);
        glCompileShader(fobj);
        
        if(PrintShaderInfoLog(fobj, "fragment shader")){
            glAttachShader(program, fobj);
        }
        glDeleteShader(fobj);
    }
    
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);
    
    if(PrintProgramInfoLog(program)){
        return program;
    }
    
    glDeleteProgram(program);
    return 0;
}


/* Read shader from source file */
bool ReadShaderSource(const char *name, std::vector<GLchar> &buffer){
    if(name == nullptr) return false;
    std::ifstream file(name, std::ios::binary);
    
    if(file.fail()){
        std::cerr << "Failed to open file " << name << std::endl;
        return false;
    }
    
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());
    
    buffer.resize(length+1);
    
    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';
    
    if(file.fail()){
        std::cerr << "Failed to read source " << name << std::endl;
        file.close();
        return false;
    }
    
    file.close();
    return true;
}

/* Load shader from source and create progeam object*/
GLuint LoadProgram(const char *vert, const char *frag){
    std::vector<GLchar> vsrc;
    std::string v = vert;
    std::string tmpVert = SHADER_PATH + v;
    const bool vstat(ReadShaderSource(tmpVert.c_str(), vsrc));
    std::vector<GLchar> fsrc;
    std::string f = frag;
    std::string tmpFrag = SHADER_PATH + f;
    const bool fstat(ReadShaderSource(tmpFrag.c_str(), fsrc));
    
    if(vstat && fstat){
        return CreateProgram(vsrc.data(), fsrc.data());
    }else{
        return 0;
    }
}
