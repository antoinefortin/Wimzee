#pragma once
#include <miniaudio.h>
#include <string>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();
    
    bool Init();
    void PlayThatSound(const std::string& filePath);
    void LoadSound(const std::string& audiofile);
private:
    ma_engine m_Engine;
    bool m_Initialized;
};