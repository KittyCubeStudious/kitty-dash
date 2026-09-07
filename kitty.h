#ifndef KITTY_H
#define KITTY_H

#include <SDL2/SDL.h>

struct Kitty {
    SDL_Rect rect;
    float hizY;
    float yercekimi;
    float zipLamaKuvveti;
    bool yerdedir;
    float aci;
    float hedefAci;
    float baslangicAci;
    
    // Süre/Adım tabanlı kusursuz dönüş takibi
    int havadaGecenSure;
    int toplamHavadaSuresi; // Bir zıplamanın toplam süreceği tahmini kare (frame) sayısı

    void Zipla(int zeminY) {
        if (yerdedir) {
            hizY = zipLamaKuvveti;
            yerdedir = false;
            baslangicAci = hedefAci;
            hedefAci += 180.0f; // Tam 180 derece hedefliyoruz
            
            havadaGecenSure = 0;
            // Yerçekimi 0.85f ve zıplama -15.0f iken kedi havada ortalama 34-36 frame kalır.
            // Bu sayede dönüş tam zeminle buluştuğu an biter.
            toplamHavadaSuresi = 35; 
        }
    }

    void Guncelle(int zeminY, bool basiliTutuyor) {
        hizY += yercekimi;
        rect.y += (int)hizY;

        if (rect.y >= zeminY - rect.h) {
            rect.y = zeminY - rect.h;
            hizY = 0.0f;
            yerdedir = true;
            
            // Yere indiği an açı kesinlikle ve net bir şekilde 180'in katına kilitlenir
            aci = hedefAci;
            havadaGecenSure = 0;
        } else {
            yerdedir = false;
            havadaGecenSure++;

            // İlerleme oranı (0.0'dan 1.0'e kadar)
            float ilerleme = (float)havadaGecenSure / (float)toplamHavadaSuresi;
            if (ilerleme > 1.0f) ilerleme = 1.0f;

            // Zıplama anından yere inene kadar geçen sürede açı tam 180 derece döner
            aci = baslangicAci + (180.0f * ilerleme);
        }
    }
};

#endif
