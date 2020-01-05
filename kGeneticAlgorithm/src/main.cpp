#include "game.h"
#include "config.h"

#include "Logger.h"

int main(int argc, char* argv[]) {
	Logger::Init();
	LOG_TRACE("Log initialized");

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	uint64_t frameStart;
	int frameTime;

	Game* game = new Game();

	game->Init("Genetic Algorithm Test", WINDOW_WIDTH, WINDOW_HEIGHT, false);

	while (Game::Get()->running()) {
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

	}

	Game::Get()->Clean();

	return 0;
}
