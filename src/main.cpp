#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstring>


#include "GL/glew.h"

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"


static const int FPS = 60;
static int WIDTH = 800;
static int HEIGHT = 800;
static const float PI = 3.1415927f;


int main()
{
    sf::Window window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    window.setFramerateLimit(FPS);
    window.setKeyRepeatEnabled(false);
    window.setActive();


    // std::cout << (window.getSettings().majorVersion) << ' ' << (window.getSettings().minorVersion) << std::endl;
    // std::cout << glGetString(GL_VERSION) << std::endl;

    char button_pressed[256];
    std::memset(button_pressed, 0, 256);


    GLfloat vertices[] = {
        0.5, 0.5, 0.5,
        0.5, 0.5, -0.5,
        0.5, -0.5, 0.5,
        0.5, -0.5, -0.5,
        -0.5, 0.5, 0.5,
        -0.5, 0.5, -0.5,
        -0.5, -0.5, 0.5,
        -0.5, -0.5, -0.5,
    };

    GLfloat colors[] = {
        1.0f, 0.4f, 0.6f,
        1.0f, 0.9f, 0.2f,
        0.7f, 0.3f, 0.8f,
        0.5f, 0.3f, 1.0f,

        0.2f, 0.6f, 1.0f,
        0.6f, 1.0f, 0.4f,
        0.6f, 0.8f, 0.8f,
        0.4f, 0.8f, 0.8f,
    };

    GLuint indices[] = {
        // front
        0, 2, 6,
        6, 4, 0,
        // back
        1, 3, 7,
        7, 5, 1,
        // top
        0, 1, 5,
        5, 4, 0,
        // bottom
        2, 3, 7,
        7, 6, 2,
        // left
        4, 5, 7,
        7, 6, 4,
        // right
        0, 1, 3,
        3, 2, 0
    };


    glewInit();
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    

    Shader *cube_shader = new Shader("../shaders/vertex_shader.vert", "../shaders/fragment_shader.frag");

    VBO *vbo_cube_vert = new VBO(vertices, 24, GL_STATIC_DRAW);
    VBO *vbo_cube_col = new VBO(colors, 24, GL_STATIC_DRAW);

    EBO *ebo_cube = new EBO(indices, 36, GL_STATIC_DRAW);

    VAO *vao_cube = new VAO();


    vbo_cube_vert->bind();
    vao_cube->set_pointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat));
    vbo_cube_vert->unbind();

    vbo_cube_col->bind();
    vao_cube->set_pointer(1, 3, GL_FLOAT, 3 * sizeof(GLfloat));
    vbo_cube_col->unbind();


    float *angle = new float[3];
    std::memset(angle, 0.0f, 3 * sizeof(float));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
                WIDTH = event.size.width;
                HEIGHT = event.size.height;
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                int code = event.key.code;
                if (code >= 0)
                    button_pressed[code] = 1;
                // std::cout << code << '\n';
            }

            else if (event.type == sf::Event::KeyReleased)
            {
                int code = event.key.code;
                if (code >= 0)
                    button_pressed[code] = 0;
            }
        }

        float dr = 0.007f;

        if (button_pressed[71])
            angle[1] -= dr;
        if (button_pressed[72])
            angle[1] += dr;
        if (button_pressed[73])
            angle[0] += dr;
        if (button_pressed[74])
            angle[0] -= dr;
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cube_shader->bind();
        vao_cube->bind();

        // angle  = std::fmod(angle + 0.01f, 2 * PI);
        // angle += 0.01f;
        glUniform1f(2, angle[0]);
        glUniform1f(3, angle[1]);
        glUniform1f(4, angle[2]);

        ebo_cube->draw();

        cube_shader->unbind();
        vao_cube->unbind();

        window.display();
    }
    

    delete vbo_cube_vert;
    delete vbo_cube_col;
    delete ebo_cube;
    delete vao_cube;
    delete cube_shader;
    
    return 0;
}
    