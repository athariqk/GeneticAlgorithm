#include "AudioManager.h"

#include "Logger.h"

void AudioManager::Init() {
    if (!SDL_Init(SDL_INIT_AUDIO)) {
        LOG_ERROR("Failed to initialize SDL audio submodule");
    } else {
        LOG_INFO("SDL Audio initialized");
    }

    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wavSpec, nullptr, nullptr);
    SDL_ResumeAudioStreamDevice(stream);
}

void AudioManager::Clear() { SDL_free(wavBuffer); }

void AudioManager::PlayWAV(const char *path) {
    if (!SDL_LoadWAV(path, &wavSpec, &wavBuffer, &wavLength)) {
        LOG_ERROR("Couldn't open audio: {}", SDL_GetError());
    } else {
        LOG_INFO("Playing audio path: {}", path);
    }

    if (SDL_GetAudioStreamQueued(stream) < static_cast<int>(wavLength)) {
        SDL_PutAudioStreamData(stream, wavBuffer, wavLength);
    }
}
