// dil.h
#ifndef DIL_H
#define DIL_H

enum DilSecenegi {
    DIL_TURKCE,
    DIL_INGILIZCE
};

struct Metinler {
    const char* basla;
    const char* hakkimizda;
    const char* ayarlar;
    const char* oyunBitti;
    const char* tekrarBasla;
    const char* menuyeGit;
    const char* skor;
    const char* rekor;
    const char* ayarlarBaslik;
    const char* nasilOynanirBaslik;
    const char* nasilOynanir1;
    const char* nasilOynanir2;
    const char* nasilOynanir3;
    const char* hakkimizdaAciklama1;
    const char* hakkimizdaAciklama2;
    const char* hakkimizdaAciklama3;
    const char* iyiEglenceler;
};

inline Metinler DilGetir(DilSecenegi dil) {
    Metinler m;
    if (dil == DIL_TURKCE) {
        m.basla = "BASLA";
        m.hakkimizda = "HAKKIMIZDA";
        m.ayarlar = "AYARLAR";
        m.oyunBitti = "OYUN BITTI!";
        m.tekrarBasla = "TEKRAR BASLA";
        m.menuyeGit = "MENUYE GIT";
        m.skor = "SKOR";
        m.rekor = "REKOR";
        m.ayarlarBaslik = "AYARLAR";
        m.nasilOynanirBaslik = "NASIL OYNANIR?";
        m.nasilOynanir1 = "Ekrana basili tutarak surekli ziplayin.";
        m.nasilOynanir2 = "Parcayi birakinca yukari ziplama kesilir!";
        m.nasilOynanir3 = "Bloklarin uzerine basarak ilerleyebilirsiniz.";
        m.hakkimizdaAciklama1 = "Kitty Studios 2026 (R) Tum Haklari Saklidir.";
        m.hakkimizdaAciklama2 = "Gmail: kittystudiosofficiall@gmail.com";
        m.hakkimizdaAciklama3 = "Instagram: kittystudiosofficial, ondergunal07";
        m.iyiEglenceler = "Kitty Studios Iyi Eglenceler Diler.";
    } 
    else {
        m.basla = "START";
        m.hakkimizda = "ABOUT";
        m.ayarlar = "SETTINGS";
        m.oyunBitti = "GAME OVER!";
        m.tekrarBasla = "PLAY AGAIN";
        m.menuyeGit = "MAIN MENU";
        m.skor = "SCORE";
        m.rekor = "BEST";
        m.ayarlarBaslik = "SETTINGS";
        m.nasilOynanirBaslik = "HOW TO PLAY?";
        m.nasilOynanir1 = "Hold down on the screen to keep jumping.";
        m.nasilOynanir2 = "Releasing cuts short your upward jump!";
        m.nasilOynanir3 = "You can land and run on top of blocks.";
        m.hakkimizdaAciklama1 = "Kitty Studios 2026 (R) All Rights Reserved.";
        m.hakkimizdaAciklama2 = "Gmail: kittystudiosofficiall@gmail.com";
        m.hakkimizdaAciklama3 = "Instagram: kittystudiosofficial, ondergunal07";
        m.iyiEglenceler = "Kitty Studios Have a Great Time Playing!";
    }
    return m;
}

#endif
