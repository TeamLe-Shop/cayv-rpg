#include "SDL.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win;
    SDL_Renderer * ren;
    SDL_CreateWindowAndRenderer(512, 512, 0, &win, &ren);
    SDL_Texture * tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, 512, 512);

    bool quit = false;
    int t = 0;

    while (!quit) {
        Uint32 frame_begin = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        void * rawpx;
        int pitch;

        struct Rgb888 {
            char r;
            char g;
            char b;
            char unused_alignment;
        };

        SDL_LockTexture(tex, NULL, &rawpx, &pitch);
        Rgb888 * pixuls = static_cast<Rgb888*>(rawpx);
        for (int y = 0; y < 512; ++y) {
            for (int x = 0; x < 512; ++x) {
                Rgb888 * pixul = &pixuls[y * 512 + x];
                pixul->r = x ^ y + t;
                pixul->g = x ^ y + (t * 2);
                pixul->b = x ^ y + (t * 4);
            }
        }
        SDL_UnlockTexture(tex);

        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
        Uint32 time_took = SDL_GetTicks() - frame_begin;
        const Uint32 IDEAL_FRAME_TIME_MS = 17;
        if (time_took < IDEAL_FRAME_TIME_MS) {
            SDL_Delay(IDEAL_FRAME_TIME_MS - time_took);
        }
        t++;
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
