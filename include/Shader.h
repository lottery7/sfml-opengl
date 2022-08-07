#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "GL/glew.h"

class Shader
{
    public:
        Shader(std::string vertex_shader_path, std::string fragment_shader_path);
        ~Shader();
        const GLchar* get_text(std::string path);
        void check_shader_compilation(GLuint &shader);
        void bind();
        void unbind();
        
    private:
        const char *vertex_source;
        const char *fragment_source;
        GLuint vertex_shader;
        GLuint fragment_shader;
        GLuint shader_program;
};