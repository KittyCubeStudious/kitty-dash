// extra.h
#ifndef EXTRA_H
#define EXTRA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

enum OyunDurumu {
    ACILIS,
    MENU,
    OYNANIS,
    OYUN_BITTI,
    HAKKIMIZDA,
    AYARLAR
};

inline TTF_Font* OzelFontYukle(const char* dosyaYolu, int boyut) {
    TTF_Font* font = TTF_OpenFont(dosyaYolu, boyut);
    if (!font) {
        font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", boyut);
    }
    return font;
}

inline void CizCerceve(SDL_Renderer* renderer, SDL_Rect rect, int kalinlik) {
    for (int i = 0; i < kalinlik; i++) {
        SDL_Rect r = { rect.x - i, rect.y - i, rect.w + (i * 2), rect.h + (i * 2) };
        SDL_RenderDrawRect(renderer, &r);
    }
}

inline void YaziCiz(SDL_Renderer* renderer, TTF_Font* font, const char* metin, int x, int y, SDL_Color renk) {
    if (!font) return;
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, metin, renk);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            SDL_Rect rect;
            rect.w = surface->w;
            rect.h = surface->h;
            rect.x = x - (rect.w / 2);
            rect.y = y - (rect.h / 2);
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

#endif
