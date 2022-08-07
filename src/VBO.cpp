#include "VBO.h"
#include "GL/glew.h"


VBO::VBO(GLfloat *data, int data_length, GLenum usage)
{
    glGenBuffers(1, &ID);
    set_data(data, data_length, usage);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &ID);
}

void VBO::set_data(GLfloat *data, int data_length, GLenum usage)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, data_length * sizeof(data), data, usage);
    unbind();
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
