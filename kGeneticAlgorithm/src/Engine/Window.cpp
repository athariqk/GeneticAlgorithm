#include "Window.h"
#include "Logger.h"

Window::Window(const char* title,
	int width, int height, bool fullscreen)
{
	int flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		LOG_INFO("SDL initialized");
	}
	else {
		LOG_ERROR("SDL failed to initialize!");
		return;
	}

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

	SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (SDLWindow) {
		LOG_INFO("Created window with resolution: {} x {}, ID: {}",
			width, height, GetSDLWindowID());
	}
	else {
		LOG_ERROR("Failed to create window!");
		return;
	}

	GPU_SetInitWindow(GetSDLWindowID());
	target = GPU_Init(width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (target == NULL) {
		LOG_ERROR("SDL GPU failed to initialize!");
		return;
	}
	else {
		LOG_INFO("SDL GPU initialized");
	}

	glContext = target->context->context;
}

Window::~Window() {
	LOG_INFO("Destroyed window {}", GetSDLWindowID());
}
