#include "VAO.h"
#include "GL/glew.h"


VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
    bind();
    for (auto p: all_attrib_pointers)
        glDisableVertexAttribArray(p);
    glDeleteVertexArrays(1, &ID);
    unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::disable_pointer(int location)
{
    bind();
    glDisableVertexAttribArray(location);
    unbind();
}

void VAO::enable_pointer(int location)
{
    bind();
    glEnableVertexAttribArray(location);
    unbind();
}

void VAO::set_pointer(int location, int size, GLenum type, int stride)
{
    bind();
    glVertexAttribPointer(location, size, type, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(location);
    all_attrib_pointers.push_back(location);
    unbind();
}
