#define MINIAUDIO_IMPLEMENTATION
#include "audio/AudioManager.h"
#include <spdlog/spdlog.h>

AudioManager::AudioManager() : m_Initialized(false)
{
    //m_Initialized = Init();

}


AudioManager::~AudioManager()
{
    
}

bool AudioManager::Init()
{
    if(ma_engine_init(NULL, &m_Engine) == MA_SUCCESS)
    {
        spdlog::info("Audio engine runninng");
        m_Initialized = true;
        return m_Initialized;
    }
    else 
    {
        spdlog::error("Canot initiate the audio engine");
    }
    return false;
    
}

void AudioManager::PlayThatSound(const std::string& filePath)
{
    if(m_Initialized)
    {
        ma_engine_play_sound(&m_Engine, filePath.c_str(), NULL);

    }

}

