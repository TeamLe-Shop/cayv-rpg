#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>

int main() {
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result != 0) {
        std::cout << "The terrible tale of SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Window * window = SDL_CreateWindow(
        "Cayv Story",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_OPENGL
    );
    SDL_GLContext glc = SDL_GL_CreateContext(window);

    bool quit = false;

    while (!quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glc);
    SDL_DestroyWindow(window);
    SDL_Quit();
}