#pragma once


#include "GL/glew.h"


class EBO
{
    public:
        EBO(GLuint *data, int data_length, GLenum usage);
        ~EBO();
        void set_data(GLuint *data, int data_length, GLenum usage);
        void bind();
        void unbind();
        void draw();
    private:
        GLuint ID;
        GLint data_length;
};