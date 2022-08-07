#pragma once

#include <vector>

#include "GL/glew.h"


class VAO
{
    public:
        VAO();
        ~VAO();
        void bind();    
        void unbind();
        void disable_pointer(int location);
        void enable_pointer(int location);
        void set_pointer(int location, int size, GLenum type, int stride);
    
    private:
        GLuint ID;
        std::vector<int> all_attrib_pointers;
};
