#pragma once
#include <SDL.h>
#include <SDL_gpu.h>

class Window {
public:
	Window(const char* title, int width, int height, bool fullscreen);
	~Window();

	inline SDL_GLContext& GetGLContext() {
		return glContext;
	}

	inline GPU_Target* GetTarget() {
		return target;
	}

	inline SDL_Window* GetWindow(){
		return SDLWindow;
	}

	uint32_t GetSDLWindowID() const {
		return SDL_GetWindowID(SDLWindow);
	}

private:
	SDL_Window* SDLWindow;
	GPU_Target* target;
	SDL_GLContext glContext;
};
