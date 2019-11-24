#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
SDL_Window *window;
SDL_Renderer *ren;
SDL_Surface *bmp;
SDL_Texture *tex;
SDL_Event e;

SDL_Rect dest;
int setup();

int main() {
    setup();
    _Bool quit = 0;

    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w = 80;
    dest.h = 10;
    dest.x = 0;
    dest.y = 240 / 2;
    while (!quit) {
        dest.x += 1;
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, &dest);
        SDL_RenderPresent(ren);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        dest.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        dest.x += 5;
                        break;
                    case SDLK_UP:
                        dest.y -= 5;
                        break;
                    case SDLK_DOWN:
                        dest.y += 5;
                        break;
                    case SDLK_u:
                        quit = 1;
                        break;
                    case SDLK_y:
                        dest.y += 5;
                        break;
                }
                break;
            }
        }
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
int setup() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
        printf("hw!");
    } else {
        printf("SDL Initialisation Failed!: %s\n", SDL_GetError());

        return -1;
    }

    window = SDL_CreateWindow("Test Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 320, 240,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Error while creating window! %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    ren = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        printf("Error while creating renderer! %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    bmp = SDL_LoadBMP("./bg.bmp");
    if (!bmp) {
        printf("Error while loading BMP file! %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);

    return 0;
}