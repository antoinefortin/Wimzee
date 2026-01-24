#include "graphics/Texture.h"
#include <spdlog/spdlog.h>
Texture::Texture()
{   
    spdlog::info("Empty textuyre created");
    
}


Texture::Texture(const std::string& texturePath)
{   
    spdlog::info("texture ath {}", texturePath);
    int width, height, nrChannels;
   // data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0); 
    spdlog::info("Width{}", width);
    spdlog::info("height{}", height);
 //   spdlog::info("w{}, h{}", width,);



    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0); 
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        spdlog::info("Got a texture fucker");
    }
    else 
    {
        spdlog::info("No textiure laoded");
    }

}

Texture::~Texture()
{

}

void Texture::sayShit()
{
    spdlog::warn("SHHHIIT");
}

void Texture::CreateOpenGlTexture()
{
    spdlog::info("Creating open gl texture");
}