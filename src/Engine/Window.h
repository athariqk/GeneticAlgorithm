#pragma once

#include <cstdint>

class SDL_Renderer;
class SDL_Window;

class Window {
public:
	Window(const char* title, int width, int height, bool fullscreen);
	~Window();

	SDL_Renderer* GetRenderer() const;

	SDL_Window* GetWindow() const;

	uint32_t GetSDLWindowID() const;

	void SetTitle(const char* title) const;

	int ShowMessageBox(uint32_t flags, const char* title, const char* message) const;

private:
	SDL_Window* sdlWindow;
    SDL_Renderer* renderer;
};
