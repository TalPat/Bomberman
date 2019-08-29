#include "Particle.hpp"
#include <GL/glew.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "stb_image.h"

typedef short int16;
typedef int int32;
typedef unsigned short uint16;
typedef unsigned int uint32;

const uint32
    WINDOW_WIDTH = 600,
    WINDOW_HEIGHT = 600,
    // object count is static number in this example, but it can be made a bit
    // more flexible (however remember that you will never have much freedom
    // with constant block of memory which is required by targeted performance)
    OBJECT_COUNT = 100;

struct Texture
{
    uint16 width, height;
    float u1, v1, u2, v2;
};
struct Object
{
    int16 x, y;
    Texture texture;
};

GLuint shaderProgramId, vao, vbo, ubo, textureId;

Texture
    watermelon = {64, 64, 0.0f, 0.0f, 0.5f, 0.5f},
    pineapple = {64, 64, 0.5f, 0.0f, 1.0f, 0.5f},
    orange = {32, 32, 0.0f, 0.5f, 0.25f, 0.75f},
    grapes = {32, 32, 0.25f, 0.5f, 0.5f, 0.75f},
    pear = {32, 32, 0.0f, 0.75f, 0.25f, 1.0f},
    banana = {32, 32, 0.25f, 0.75f, 0.5f, 1.0f},
    strawberry = {16, 16, 0.5f, 0.5f, 0.625f, 0.625f},
    raspberry = {16, 16, 0.625f, 0.5f, 0.75f, 0.625f},
    cherries = {16, 16, 0.5f, 0.625f, 0.625f, 0.75f};

Texture textures[9] =
    {
        watermelon,
        pineapple,
        orange,
        grapes,
        pear,
        banana,
        strawberry,
        cherries,
        raspberry};

static Object objects[OBJECT_COUNT];

static int16 vertices[OBJECT_COUNT * 12];
static float uvs[OBJECT_COUNT * 12];

Particle::Particle(/* args */)
{

    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrComponents;
    unsigned char *data = stbi_load("../../renderer3D/src/Flame_Particle.png", &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "TEXTURE FAILED TO LOAD PATH " << std::endl;
        stbi_image_free(data);
    }
    for (uint32 i = 0; i < OBJECT_COUNT; i++)
    {
        Texture t = textures[rand() % 9];
        objects[i] =
            {
                (int16)(rand() % (WINDOW_WIDTH - t.width)),
                (int16)(rand() % (WINDOW_HEIGHT - t.height)),
                t};

        // vertices
        {
            // top right
            vertices[i * 12] = objects[i].x + objects[i].texture.width;
            vertices[i * 12 + 1] = objects[i].y;

            // bottom right
            vertices[i * 12 + 2] = objects[i].x + objects[i].texture.width;
            vertices[i * 12 + 3] = objects[i].y + objects[i].texture.height;

            // top left
            vertices[i * 12 + 4] = objects[i].x;
            vertices[i * 12 + 5] = objects[i].y;

            // bottom right
            vertices[i * 12 + 6] = objects[i].x + objects[i].texture.width;
            vertices[i * 12 + 7] = objects[i].y + objects[i].texture.height;

            // bottom left
            vertices[i * 12 + 8] = objects[i].x;
            vertices[i * 12 + 9] = objects[i].y + objects[i].texture.height;

            // top left
            vertices[i * 12 + 10] = objects[i].x;
            vertices[i * 12 + 11] = objects[i].y;
            std::cout << "done " <<  i << " "<< vertices[i * 12] << std::endl;
        }

        // uvs
        // {
        //     // top right
        //     uvs[i * 12] = objects[i].texture.u2;
        //     uvs[i * 12 + 1] = objects[i].texture.v2;

        //     // bottom right
        //     uvs[i * 12 + 2] = objects[i].texture.u2;
        //     uvs[i * 12 + 3] = objects[i].texture.v1;

        //     // top left
        //     uvs[i * 12 + 4] = objects[i].texture.u1;
        //     uvs[i * 12 + 5] = objects[i].texture.v2;

        //     // bottom right
        //     uvs[i * 12 + 6] = objects[i].texture.u2;
        //     uvs[i * 12 + 7] = objects[i].texture.v1;

        //     // bottom left
        //     uvs[i * 12 + 8] = objects[i].texture.u1;
        //     uvs[i * 12 + 9] = objects[i].texture.v1;

        //     // top left
        //     uvs[i * 12 + 10] = objects[i].texture.u1;
        //     uvs[i * 12 + 11] = objects[i].texture.v2;
        // }
    }
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ubo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, 2 * sizeof(int16), 0);

    glBindBuffer(GL_ARRAY_BUFFER, ubo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(GLfloat), 0);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // those usually go to render(), but this example uses just one shader, vao
    // and texture so it is enough to set them once
    glUseProgram(shaderProgramId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glBindVertexArray(vao);
}

Particle::~Particle()
{
}