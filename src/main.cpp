#include "SDL.h"
#include <random>
#include <SDL_mixer.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win;
    SDL_Renderer * ren;
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    const int W = mode.w;
    const int H = mode.h;
    SDL_CreateWindowAndRenderer(W, H, SDL_WINDOW_FULLSCREEN_DESKTOP, &win, &ren);
    SDL_Texture * tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING,
                                          W, H);
    Mix_Init(MIX_INIT_MOD);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 1024);
    Mix_Music* mus = Mix_LoadMUS("herpfucks.xm");
    Mix_PlayMusic(mus, -1);

    bool quit = false;
    int t = 0;
    float cx = 0, chs = 1;
    float cy = 0, cvs = 1;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-2.0, 2.0);

    while (!quit) {
        Uint32 frame_begin = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
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
        cx += chs;
        cy += cvs;
        if (t % 128 == 0) {
            chs += dis(gen);
            cvs += dis(gen);
        }
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                Rgb888 * pixul = &pixuls[y * W + x];
                const char val = (x + (char)cx) ^ (y + (char)cy);
                pixul->r = (val * t / 128);
                pixul->g = (val * t / 128) + x;
                pixul->b = (val * t / 128) + y;
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
