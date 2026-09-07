#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "kitty.h"
#include "engeller.h"
#include "extra.h"
#include "menu.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    srand(time(NULL));

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    int cihazW = dm.w;
    int cihazH = dm.h;

    SDL_Window* window = SDL_CreateWindow("Kitty Dash", 
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                        cihazW, cihazH, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int mantiksalW = 960;
    int mantiksalH = 540;
    SDL_RenderSetLogicalSize(renderer, mantiksalW, mantiksalH);

    const char* benimFontum = "kittydash.ttf";
    TTF_Font* fontBuyuk = OzelFontYukle(benimFontum, 52);
    TTF_Font* fontOrta  = OzelFontYukle(benimFontum, 24);
    TTF_Font* fontKucuk = OzelFontYukle(benimFontum, 16);

    SDL_Surface* openSurface = IMG_Load("open.png");
    SDL_Texture* openTexture = NULL;
    if (openSurface) {
        openTexture = SDL_CreateTextureFromSurface(renderer, openSurface);
        SDL_FreeSurface(openSurface);
    }

    SDL_Surface* kediSurface = IMG_Load("kitty.png");
    SDL_Texture* kediTexture = NULL;
    if (kediSurface) {
        kediTexture = SDL_CreateTextureFromSurface(renderer, kediSurface);
        SDL_FreeSurface(kediSurface);
    }

    SDL_Surface* zeminSurface = IMG_Load("zemin.png");
    SDL_Texture* zeminTexture = NULL;
    if (zeminSurface) {
        zeminTexture = SDL_CreateTextureFromSurface(renderer, zeminSurface);
        SDL_FreeSurface(zeminSurface);
    }

    SDL_Surface* bulutSurface = IMG_Load("bulut.png");
    SDL_Texture* bulutTexture = NULL;
    if (bulutSurface) {
        bulutTexture = SDL_CreateTextureFromSurface(renderer, bulutSurface);
        SDL_FreeSurface(bulutSurface);
    }

    SDL_Surface* spikeSurface = IMG_Load("spike.png");
    SDL_Texture* spikeTexture = NULL;
    if (spikeSurface) {
        spikeTexture = SDL_CreateTextureFromSurface(renderer, spikeSurface);
        SDL_FreeSurface(spikeSurface);
    }

    SDL_Surface* minispikeSurface = IMG_Load("minispike.png");
    SDL_Texture* minispikeTexture = NULL;
    if (minispikeSurface) {
        minispikeTexture = SDL_CreateTextureFromSurface(renderer, minispikeSurface);
        SDL_FreeSurface(minispikeSurface);
    }

    SDL_Surface* blockSurface = IMG_Load("block.png");
    SDL_Texture* blockTexture = NULL;
    if (blockSurface) {
        blockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
        SDL_FreeSurface(blockSurface);
    }

    OyunDurumu mevcutDurum = ACILIS;
    Uint32 acilisBaslangicZamani = SDL_GetTicks();
    int zeminY = 420;

    Kitty kedi;
    kedi.rect = { 120, zeminY - 50, 50, 50 };
    kedi.hizY = 0.0f;
    kedi.yercekimi = 1.0f;
    kedi.zipLamaKuvveti = -17.5f; 
    kedi.yerdedir = true;
    kedi.aci = 0.0f;
    kedi.hedefAci = 0.0f;

    bool ekranaBasiliyor = false;

    float zeminX1 = 0.0f;
    float zeminX2 = mantiksalW;
    float bulutX1 = 0.0f;
    float bulutX2 = mantiksalW;

    const int MAX_ENGEL = 5;
    Engel engeller[MAX_ENGEL];
    int aktifEngelSayisi = 3;

    float baslangicHizi = 8.5f; 
    float oyunHizi = baslangicHizi;
    int skor = 0;
    int enYuksekSkor = 0;

    SDL_Rect baslatButonu = { (mantiksalW / 2) - 200, 260, 400, 60 };
    SDL_Rect nasilOynanirButonu = { (mantiksalW / 2) - 200, 340, 400, 60 };
    SDL_Rect tekrarBaslaButonu = { (mantiksalW / 2) - 200, 250, 400, 60 };
    SDL_Rect menuDonButonu = { (mantiksalW / 2) - 125, 330, 250, 45 };

    auto DesenOlustur = [&](int& countOut) {
        int desenTipi = rand() % 5;
        int basX = mantiksalW + 100;

        for(int i=0; i<MAX_ENGEL; i++) engeller[i].aktif = false;

        if (desenTipi == 0) {
            countOut = 3;
            for (int i = 0; i < 3; i++) {
                engeller[i] = { { basX, zeminY - 45, 45, 45 }, 0, true };
                basX += 45;
            }
        }
        else if (desenTipi == 1) {
            countOut = 2;
            for (int i = 0; i < 2; i++) {
                engeller[i] = { { basX, zeminY - 30, 30, 30 }, 1, true };
                basX += 30;
            }
        }
        else if (desenTipi == 2) {
            countOut = 1;
            engeller[0] = { { basX, zeminY - 50, 50, 50 }, 2, true };
        }
        else if (desenTipi == 3) {
            countOut = 2;
            engeller[0] = { { basX, zeminY - 50, 50, 50 }, 2, true };
            basX += 55;
            engeller[1] = { { basX, zeminY - 45, 45, 45 }, 0, true };
        }
        else {
            countOut = 3;
            for (int i = 0; i < 2; i++) {
                engeller[i] = { { basX, zeminY - 45, 45, 45 }, 0, true };
                basX += 45;
            }
            basX += 10;
            engeller[2] = { { basX, zeminY - 50, 50, 50 }, 2, true };
        }
    };

    bool calisiyor = true;
    SDL_Event event;

    while (calisiyor) {
        Uint32 simdikiZaman = SDL_GetTicks();
        
        if (mevcutDurum == ACILIS && simdikiZaman - acilisBaslangicZamani > 2500) {
            mevcutDurum = MENU;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                calisiyor = false;
            }
            
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_FINGERDOWN) {
                // İntroyu tıklayarak geçme engellendi (buradaki ACILIS kontrolü kaldırıldı)

                ekranaBasiliyor = true;

                int tiklamaX = 0, tiklamaY = 0;
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    tiklamaX = event.button.x;
                    tiklamaY = event.button.y;
                } else if (event.type == SDL_FINGERDOWN) {
                    tiklamaX = (int)(event.tfinger.x * mantiksalW);
                    tiklamaY = (int)(event.tfinger.y * mantiksalH);
                }

                if (mevcutDurum == MENU) {
                    if (tiklamaX >= baslatButonu.x && tiklamaX <= baslatButonu.x + baslatButonu.w &&
                        tiklamaY >= baslatButonu.y && tiklamaY <= baslatButonu.y + baslatButonu.h) {
                        mevcutDurum = OYNANIS;
                        kedi.rect.y = zeminY - 50;
                        kedi.hizY = 0;
                        skor = 0;
                        oyunHizi = baslangicHizi;
                        kedi.aci = 0.0f;
                        kedi.hedefAci = 0.0f;
                        zeminX1 = 0.0f;
                        zeminX2 = mantiksalW;
                        bulutX1 = 0.0f;
                        bulutX2 = mantiksalW;
                        DesenOlustur(aktifEngelSayisi);
                    }
                    else if (tiklamaX >= nasilOynanirButonu.x && tiklamaX <= nasilOynanirButonu.x + nasilOynanirButonu.w &&
                             tiklamaY >= nasilOynanirButonu.y && tiklamaY <= nasilOynanirButonu.y + nasilOynanirButonu.h) {
                        mevcutDurum = NASIL_OYNANIR;
                    }
                }
                else if (mevcutDurum == NASIL_OYNANIR) {
                    SDL_Rect kapatButonu = { (mantiksalW / 2) + 230, 110, 40, 40 };
                    if (tiklamaX >= kapatButonu.x && tiklamaX <= kapatButonu.x + kapatButonu.w &&
                        tiklamaY >= kapatButonu.y && tiklamaY <= kapatButonu.y + kapatButonu.h) {
                        mevcutDurum = MENU;
                    }
                }
                else if (mevcutDurum == OYUN_BITTI) {
                    if (tiklamaX >= tekrarBaslaButonu.x && tiklamaX <= tekrarBaslaButonu.x + tekrarBaslaButonu.w &&
                        tiklamaY >= tekrarBaslaButonu.y && tiklamaY <= tekrarBaslaButonu.y + tekrarBaslaButonu.h) {
                        mevcutDurum = OYNANIS;
                        kedi.rect.y = zeminY - 50;
                        kedi.hizY = 0;
                        skor = 0;
                        oyunHizi = baslangicHizi;
                        kedi.aci = 0.0f;
                        kedi.hedefAci = 0.0f;
                        zeminX1 = 0.0f;
                        zeminX2 = mantiksalW;
                        bulutX1 = 0.0f;
                        bulutX2 = mantiksalW;
                        DesenOlustur(aktifEngelSayisi);
                    }
                    else if (tiklamaX >= menuDonButonu.x && tiklamaX <= menuDonButonu.x + menuDonButonu.w &&
                             tiklamaY >= menuDonButonu.y && tiklamaY <= menuDonButonu.y + menuDonButonu.h) {
                        mevcutDurum = MENU;
                    }
                }
            }
            
            if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_FINGERUP) {
                ekranaBasiliyor = false;
            }
        }

        if (mevcutDurum == OYNANIS) {
            if (ekranaBasiliyor && kedi.yerdedir) {
                kedi.Zipla();
            }

            zeminX1 -= oyunHizi;
            zeminX2 -= oyunHizi;
            if (zeminX1 <= -mantiksalW) zeminX1 = zeminX2 + mantiksalW;
            if (zeminX2 <= -mantiksalW) zeminX2 = zeminX1 + mantiksalW;

            bulutX1 -= (oyunHizi * 0.3f);
            bulutX2 -= (oyunHizi * 0.3f);
            if (bulutX1 <= -mantiksalW) bulutX1 = bulutX2 + mantiksalW;
            if (bulutX2 <= -mantiksalW) bulutX2 = bulutX1 + mantiksalW;

            kedi.Guncelle(zeminY, ekranaBasiliyor);

            bool tumEngellerGecti = true;
            for (int i = 0; i < aktifEngelSayisi; i++) {
                if (engeller[i].aktif) {
                    engeller[i].rect.x -= (int)oyunHizi;
                    if (engeller[i].rect.x + engeller[i].rect.w > 0) {
                        tumEngellerGecti = false;
                    }
                }
            }

            if (tumEngellerGecti) {
                skor++;
                if (skor % 5 == 0 && oyunHizi < 22.0f) oyunHizi += 0.5f;
                DesenOlustur(aktifEngelSayisi);
            }

            for (int i = 0; i < aktifEngelSayisi; i++) {
                if (!engeller[i].aktif) continue;
                SDL_Rect& engel = engeller[i].rect;
                bool carpismaVar = (kedi.rect.x + kedi.rect.w - 5 > engel.x && kedi.rect.x + 5 < engel.x + engel.w &&
                                    kedi.rect.y + kedi.rect.h - 5 > engel.y && kedi.rect.y < engel.y + engel.h);

                if (carpismaVar) {
                    if (engeller[i].tip == 2) {
                        if (kedi.hizY >= 0 && (kedi.rect.y + kedi.rect.h - (int)kedi.hizY) <= engel.y + 12) {
                            kedi.rect.y = engel.y - kedi.rect.h;
                            kedi.hizY = 0.0f;
                            kedi.yerdedir = true;
                        } else {
                            mevcutDurum = OYUN_BITTI;
                        }
                    } else {
                        mevcutDurum = OYUN_BITTI;
                    }
                }
            }

            if (mevcutDurum == OYUN_BITTI && skor > enYuksekSkor) {
                enYuksekSkor = skor;
            }
        }

        if (mevcutDurum == ACILIS) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            if (openTexture) {
                SDL_Rect ekranRect = { 0, 0, mantiksalW, mantiksalH };
                SDL_RenderCopy(renderer, openTexture, NULL, &ekranRect);
            }

            Uint32 gecenSure = simdikiZaman - acilisBaslangicZamani;
            if (gecenSure > 1900) {
                float oran = (float)(gecenSure - 1900) / 600.0f;
                if (oran > 1.0f) oran = 1.0f;
                Uint8 alfa = (Uint8)(oran * 255.0f);

                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, alfa);
                SDL_Rect ekranRect = { 0, 0, mantiksalW, mantiksalH };
                SDL_RenderFillRect(renderer, &ekranRect);
            }
        }
        else {
            SDL_SetRenderDrawColor(renderer, 8, 10, 18, 255);
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer, 18, 22, 32, 255);
            for (int x = 0; x < mantiksalW; x += 45) SDL_RenderDrawLine(renderer, x, 0, x, mantiksalH);
            for (int y = 0; y < mantiksalH; y += 45) SDL_RenderDrawLine(renderer, 0, y, mantiksalW, y);

            SDL_Color beyaz = { 255, 255, 255, 255 };
            SDL_Color pembe = { 255, 40, 100, 255 };
            SDL_Color turkuaz = { 0, 220, 255, 255 };
            SDL_Color gri = { 150, 160, 180, 255 };

            if (mevcutDurum == MENU) {
                MenuCiz(renderer, fontBuyuk, fontOrta, fontKucuk, kediTexture, baslatButonu, nasilOynanirButonu, enYuksekSkor, mantiksalW);
            }
            else if (mevcutDurum == NASIL_OYNANIR) {
                SDL_Rect bilgiKutusu = { (mantiksalW / 2) - 300, 100, 600, 300 };
                SDL_SetRenderDrawColor(renderer, 15, 25, 40, 255);
                SDL_RenderFillRect(renderer, &bilgiKutusu);
                SDL_SetRenderDrawColor(renderer, 0, 220, 255, 255);
                CizCerceve(renderer, bilgiKutusu, 2);

                YaziCiz(renderer, fontOrta, "NASIL OYNANIR?", mantiksalW / 2, 150, turkuaz);
                YaziCiz(renderer, fontKucuk, "Ekrana basili tutarak surekli ziplayin.", mantiksalW / 2, 220, beyaz);
                YaziCiz(renderer, fontKucuk, "Parcayi birakinca yukari ziplama kesilir!", mantiksalW / 2, 280, beyaz);

                SDL_Rect kapatButonu = { (mantiksalW / 2) + 230, 110, 40, 40 };
                SDL_SetRenderDrawColor(renderer, 255, 40, 100, 255);
                SDL_RenderFillRect(renderer, &kapatButonu);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                CizCerceve(renderer, kapatButonu, 2);
                YaziCiz(renderer, fontOrta, "X", kapatButonu.x + 20, kapatButonu.y + 20, beyaz);
            }
            else if (mevcutDurum == OYNANIS) {
                if (bulutTexture) {
                    SDL_Rect bulutRect1 = { (int)bulutX1, 50, 280, 100 };
                    SDL_Rect bulutRect2 = { (int)bulutX2, 50, 280, 100 };
                    SDL_RenderCopy(renderer, bulutTexture, NULL, &bulutRect1);
                    SDL_RenderCopy(renderer, bulutTexture, NULL, &bulutRect2);
                }

                if (zeminTexture) {
                    SDL_Rect zeminRect1 = { (int)zeminX1, zeminY, mantiksalW, 120 };
                    SDL_Rect zeminRect2 = { (int)zeminX2, zeminY, mantiksalW, 120 };
                    SDL_RenderCopy(renderer, zeminTexture, NULL, &zeminRect1);
                    SDL_RenderCopy(renderer, zeminTexture, NULL, &zeminRect2);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 180, 255, 255);
                    SDL_Rect zeminRect = { 0, zeminY, mantiksalW, 120 };
                    SDL_RenderFillRect(renderer, &zeminRect);
                }

                for (int i = 0; i < aktifEngelSayisi; i++) {
                    if (!engeller[i].aktif) continue;
                    if (engeller[i].tip == 0) {
                        if (spikeTexture) SDL_RenderCopy(renderer, spikeTexture, NULL, &engeller[i].rect);
                        else { SDL_SetRenderDrawColor(renderer, 255, 40, 40, 255); SDL_RenderFillRect(renderer, &engeller[i].rect); }
                    } 
                    else if (engeller[i].tip == 1) {
                        if (minispikeTexture) SDL_RenderCopy(renderer, minispikeTexture, NULL, &engeller[i].rect);
                        else { SDL_SetRenderDrawColor(renderer, 255, 150, 0, 255); SDL_RenderFillRect(renderer, &engeller[i].rect); }
                    } 
                    else if (engeller[i].tip == 2) {
                        if (blockTexture) SDL_RenderCopy(renderer, blockTexture, NULL, &engeller[i].rect);
                        else { SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255); SDL_RenderFillRect(renderer, &engeller[i].rect); }
                    }
                }

                if (kediTexture) {
                    SDL_RenderCopyEx(renderer, kediTexture, NULL, &kedi.rect, kedi.aci, NULL, SDL_FLIP_NONE);
                } else {
                    SDL_SetRenderDrawColor(renderer, 50, 255, 120, 255);
                    SDL_RenderFillRect(renderer, &kedi.rect);
                }

                char skorMetni[32];
                snprintf(skorMetni, sizeof(skorMetni), "SKOR: %d", skor);
                YaziCiz(renderer, fontOrta, skorMetni, mantiksalW - 100, 40, beyaz);
            }
            else if (mevcutDurum == OYUN_BITTI) {
                YaziCiz(renderer, fontBuyuk, "OYUN BITTI!", mantiksalW / 2, 100, pembe);

                char sonSkor[32];
                snprintf(sonSkor, sizeof(sonSkor), "SKOR: %d  |  REKOR: %d", skor, enYuksekSkor);
                YaziCiz(renderer, fontOrta, sonSkor, mantiksalW / 2, 170, turkuaz);

                SDL_SetRenderDrawColor(renderer, 12, 20, 30, 255);
                SDL_RenderFillRect(renderer, &tekrarBaslaButonu);
                SDL_SetRenderDrawColor(renderer, 0, 220, 255, 255);
                CizCerceve(renderer, tekrarBaslaButonu, 3);
                YaziCiz(renderer, fontOrta, "TEKRAR BASLA", mantiksalW / 2, 280, turkuaz);

                SDL_SetRenderDrawColor(renderer, 15, 20, 30, 255);
                SDL_RenderFillRect(renderer, &menuDonButonu);
                SDL_SetRenderDrawColor(renderer, 150, 160, 180, 255);
                CizCerceve(renderer, menuDonButonu, 2);
                YaziCiz(renderer, fontKucuk, "MENUYE GIT", mantiksalW / 2, 352, gri);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (openTexture) SDL_DestroyTexture(openTexture);
    if (kediTexture) SDL_DestroyTexture(kediTexture);
    if (zeminTexture) SDL_DestroyTexture(zeminTexture);
    if (bulutTexture) SDL_DestroyTexture(bulutTexture);
    if (spikeTexture) SDL_DestroyTexture(spikeTexture);
    if (minispikeTexture) SDL_DestroyTexture(minispikeTexture);
    if (blockTexture) SDL_DestroyTexture(blockTexture);
    if (fontBuyuk) TTF_CloseFont(fontBuyuk);
    if (fontOrta) TTF_CloseFont(fontOrta);
    if (fontKucuk) TTF_CloseFont(fontKucuk);
    
    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
