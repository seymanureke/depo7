#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @struct GunlukDugumu
 * @brief Sistem gunlugu (Syslog) verilerini saklamak icin dugum yapisi.
 */
typedef struct GunlukDugumu {
    char zaman_damgasi[32];  // Olayin gerceklesme zamani
    char birim_adi[64];      // Logu ureten servis (SSH, Kernel, Auth vb.)
    char mesaj[256];         // Olayin aciklamasi
    struct GunlukDugumu* sonraki; // Listedeki bir sonraki dugumun adresi
} GunlukDugumu;

/**
 * @brief Bellekten yeni bir gunluk dugumu ayirir ve verileri doldurur.
 * @param zaman Olay zamani
 * @param birim Logu ureten birim
 * @param icerik Log mesaji
 * @return Olusturulan dugumun isaretcisi (pointer)
 */
GunlukDugumu* yeni_gunluk_olustur(const char* zaman, const char* birim, const char* icerik) {
    // Dinamik bellek tahsisi
    GunlukDugumu* yeni_dugum = (GunlukDugumu*)malloc(sizeof(GunlukDugumu));

    if (yeni_dugum == NULL) {
        printf("Hata: Sistem bellek ayiramadi!\n");
        return NULL;
    }

    // Verilerin dugum icerisine kopyalanmasi
    strncpy(yeni_dugum->zaman_damgasi, zaman, 31);
    strncpy(yeni_dugum->birim_adi, birim, 63);
    strncpy(yeni_dugum->mesaj, icerik, 255);

    // Yeni dugumun sonrasi simdilik bos
    yeni_dugum->sonraki = NULL;

    return yeni_dugum;
}

/**
 * @brief Loglari listenin sonuna ekler (Kronolojik sirayi korumak icin).
 */
void gunluk_ekle(GunlukDugumu** bas, const char* zaman, const char* birim, const char* icerik) {
    GunlukDugumu* yeni = yeni_gunluk_olustur(zaman, birim, icerik);

    // Liste bossa yeni dugum baslangic olur
    if (*bas == NULL) {
        *bas = yeni;
        return;
    }

    // Listenin sonuna kadar git
    GunlukDugumu* gecici = *bas;
    while (gecici->sonraki != NULL) {
        gecici = gecici->sonraki;
    }

    // Son dugumun sonrasina yeni dugumu bagla
    gecici->sonraki = yeni;
}

/**
 * @brief Tum sistem gunluklerini ekrana formatli bir sekilde basar.
 */
void gunlukleri_listele(GunlukDugumu* bas) {
    if (bas == NULL) {
        printf("Sistemde kayitli gunluk bulunmamaktadir.\n");
        return;
    }

    printf("\n================ LINUX SYSLOG IZLEYICI =================\n");
    printf("%-20s | %-12s | %s\n", "ZAMAN", "BIRIM", "MESAJ");
    printf("--------------------------------------------------------\n");

    GunlukDugumu* suanki = bas;
    while (suanki != NULL) {
        printf("%-20s | %-12s | %s\n",
               suanki->zaman_damgasi,
               suanki->birim_adi,
               suanki->mesaj);
        suanki = suanki->sonraki;
    }
    printf("========================================================\n");
}

/**
 * @brief Program kapanirken bellek sızıntısını önlemek için listeyi temizler.
 */
void bellegi_bosalt(GunlukDugumu* bas) {
    GunlukDugumu* silinecek;
    while (bas != NULL) {
        silinecek = bas;
        bas = bas->sonraki;
        free(silinecek);
    }
}

int main() {
    // Bagli listenin baslangic isaretcisi
    GunlukDugumu* sistem_loglari = NULL;

    // Ornek verilerin sisteme girilmesi
    gunluk_ekle(&sistem_loglari, "10 Mart 21:45:01", "KERNEL", "Islemci sicakligi normal.");
    gunluk_ekle(&sistem_loglari, "10 Mart 21:46:12", "AUTH", "Kullanici 'seymanur' giris yapti.");
    gunluk_ekle(&sistem_loglari, "10 Mart 21:48:30", "NETWORK", "Wi-Fi baglantisi kesildi, tekrar deneniyor.");
    gunluk_ekle(&sistem_loglari, "10 Mart 21:50:05", "CRON", "Haftalik yedekleme baslatildi.");

    // Gunlukleri ekrana yazdir
    gunlukleri_listele(sistem_loglari);

    // Islemler bittikten sonra bellek iadesi
    bellegi_bosalt(sistem_loglari);

    return 0;
}