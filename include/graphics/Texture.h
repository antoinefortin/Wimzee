#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include "stb_image.h"

class Texture
{
public:
    Texture();
    Texture(const std::string& texturePath);
    ~Texture();
        int width;
    int height;
    int nbrChannel;
    unsigned char *data;
    void CreateOpenGlTexture();
    void sayShit();



    GLuint textureProgramID;



private:
};
