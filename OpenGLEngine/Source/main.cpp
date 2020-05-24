#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdocumentation"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
    const bool vstat(ReadShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(ReadShaderSource(frag, fsrc));
    
    if(vstat && fstat){
        return CreateProgram(vsrc.data(), fsrc.data());
    }else{
        return 0;
    }
}


int main(void) {
    /* Initialize GLFW */
    if(glfwInit() == GL_FALSE){
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return 1;
    }
    
    /* Set callback at the end of the program */
    atexit(glfwTerminate);
    
    /* Set OpenGL core profile */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create window */
    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (window == nullptr){
        std::cerr << "Failed to create window." << std::endl;
        return 1;
    }

    /* Set current OpenGL context */
    glfwMakeContextCurrent(window);
    
    /* Initialize GLEW */
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to initialize GLEW." << std::endl;
        return 1;
    }
    
    /* Set vsync */
    glfwSwapInterval(1);
    
    /* Set background color */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /* Create shader program object */
    const GLuint program(LoadProgram("Shader/point.vert", "Shader/point.frag"));
    
    /* Loop until window closed */
    while (glfwWindowShouldClose(window) == GL_FALSE){
        /* Reset window color */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Wait events */
        glfwWaitEvents();
    }

    return 0;
}
