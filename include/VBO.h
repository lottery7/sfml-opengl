#pragma once

#include "GL/glew.h"


class VBO
{
    public:
        VBO(GLfloat *data, int data_length, GLenum usage);
        ~VBO();
        void set_data(GLfloat *data, int data_length, GLenum usage);
        void bind();
        void unbind();

    private:
        GLuint ID;
};