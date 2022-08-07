#include "Shader.h"
#include "GL/glew.h"


Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path)
{
    vertex_source = get_text(vertex_shader_path);
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    check_shader_compilation(vertex_shader);

    fragment_source = get_text(fragment_shader_path);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    check_shader_compilation(fragment_shader);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
}

Shader::~Shader()
{
    glDetachShader(shader_program, fragment_shader);
    glDetachShader(shader_program, vertex_shader);
    glDeleteProgram(shader_program);
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
    delete[] vertex_source;
    delete[] fragment_source;
}

const GLchar* Shader::get_text(std::string path)
{
    std::string text = "";
    std::fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open())
    {
        std::cout << path << " is failed to open.\n";
        exit(-1);
    }

    std::string tmp;
    while(std::getline(file, tmp))
    {
        text += tmp + '\n';
    }
    file.close();

    const GLchar* result_text = text.c_str();

    return result_text;
}

void Shader::check_shader_compilation(GLuint &shader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER COMPILATION FAILED\n" << infoLog << std::endl;
        exit(-1);
    }
}

void Shader::bind()
{
    glUseProgram(shader_program);
}

void Shader::unbind()
{
    glUseProgram(0);
}