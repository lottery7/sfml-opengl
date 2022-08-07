#include "EBO.h"
#include "GL/glew.h"


EBO::EBO(GLuint *data, int data_length, GLenum usage)
{
    glGenBuffers(1, &ID);
    set_data(data, data_length, usage);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &ID);
}

void EBO::set_data(GLuint *data, int data_length, GLenum usage)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_length * sizeof(data), data, usage);
    this->data_length = data_length;
    unbind();
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, data_length, GL_UNSIGNED_INT, nullptr);
    unbind();
}
