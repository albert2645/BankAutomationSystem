#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

time_t t;
struct tm *zaman;

struct musteri
{
    char *isim;
    char *soyisim;
    struct tarih
    {
        int gun, ay, yil;
    } dogumTarihi, limitTarihi;
    int musteriID, sifre, limit;
};

struct hesap
{
    int hesapID, musteriID;
    struct tarih acilmaTarihi;
    float bakiye;
};

int havaleHesapKontrol(int hesapNo)
{
    FILE *hesap;
    struct hesap kontrol;
    int hesapBulundu = 0;
    hesap = fopen("hesaplar.txt", "r");
    while (fscanf(hesap, "%d %d %d/%d/%d %f", &kontrol.musteriID, &kontrol.hesapID, &kontrol.acilmaTarihi.gun, &kontrol.acilmaTarihi.ay, &kontrol.acilmaTarihi.yil, &kontrol.bakiye) != EOF)
        if (hesapNo == kontrol.hesapID)
            hesapBulundu = 1;
    return hesapBulundu;
}
int paraUstuTamamlama(int musteriNo, int hesapNo, float miktar)
{
    FILE *hesap;
    struct hesap tamamlama;

    hesap = fopen("hesaplar.txt", "r");
    while (fscanf(hesap, "%d %d %d/%d/%d %f", &tamamlama.musteriID, &tamamlama.hesapID, &tamamlama.acilmaTarihi.gun, &tamamlama.acilmaTarihi.ay, &tamamlama.acilmaTarihi.yil, &tamamlama.bakiye) != EOF)
    {
        if (tamamlama.musteriID == musteriNo || tamamlama.hesapID != hesapNo)
            miktar -= tamamlama.bakiye;
    }
    fclose(hesap);
    if (miktar <= 0)
        return 1;
    else
        return 0;
}

void paraCekme(int musteriNo)
{
    int hesapVar = 0, hesapNo, bakiyeYeterli = 0, limit, tercih = 0, paraUstuKontrol = 0;
    float islemMiktari;
    FILE *musteri, *hesap, *yeniHesap, *dekont;
    struct hesap islem1;
    struct musteri okunan;

    okunan.isim = malloc(sizeof(char) * 25);
    okunan.soyisim = malloc(sizeof(char) * 25);

    time(&t);
    zaman = localtime(&t);
    if (musteri < 55555)
        musteri = fopen("ticariMusteri.txt", "r");
    else
        musteri = fopen("bireyselMusteri.txt", "r");
    while (fscanf(musteri, "%s\t%s\t%d.%d.%d\t%d\t%d\t%d\t%d", okunan.isim, okunan.soyisim, &okunan.dogumTarihi.gun, &okunan.dogumTarihi.ay, &okunan.dogumTarihi.yil, &okunan.musteriID, &okunan.sifre, &okunan.limit, &okunan.limitTarihi.gun) != EOF)
    {
        if (musteriNo == okunan.musteriID)
        {
            limit = okunan.limit;
        }
    }
    fclose(musteri);

    printf("\nIslem yapmak istediginiz hesap numarasini giriniz-> ");
    scanf("%d", &hesapNo);

    hesap = fopen("hesaplar.txt", "r");
    yeniHesap = fopen("islem1.txt", "w");

    while (fscanf(hesap, "%d %d %d/%d/%d %f", &islem1.musteriID, &islem1.hesapID, &islem1.acilmaTarihi.gun, &islem1.acilmaTarihi.ay, &islem1.acilmaTarihi.yil, &islem1.bakiye) != EOF)
    {
        if (islem1.hesapID == hesapNo)
        {
            printf("\nCekmek istediginiz tutari giriniz-->");
            scanf("%f", &islemMiktari);
            if (islemMiktari <= limit)
            {
                if (islemMiktari <= islem1.bakiye)
                {
                    hesapVar = 1;
                    islem1.bakiye -= islemMiktari;
                    printf("\nPara cekme islemi basarili");
                    fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
                }
                else
                {
                    printf("\nHesabinizda yeterli bakiye bulunmamaktadir!");
                    printf("\nBaska bir hesabinizdan ustunu tamamlamak icin 1, ana menuye donmek icin herhangi bir tusa basiniz-> ");
                    scanf("%d", &tercih);
                    if (tercih == 1)
                    {
                        int tamamlama = paraUstuTamamlama(musteriNo, hesapNo, (islemMiktari - islem1.bakiye));
                        if (tamamlama)
                        {
                            paraUstuKontrol = 1;
                            islem1.bakiye = 0;
                            hesapVar = 1;
                            fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
                        }
                        else
                        {
                            printf("\nHesaplarinizda yeterli bakiye bulunmamaktadır!!");
                            fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
                        }
                    }
                    fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
                }
            }
            else
            {
                printf("\nGunluk islem limitini astiniz!!!");
                fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
            }
        }
        else
        {
            fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
        }
    }

    fclose(hesap);
    fclose(yeniHesap);

    remove("hesaplar.txt");
    rename("islem1.txt", "hesaplar.txt");

    if (paraUstuKontrol)
    {
        hesap = fopen("hesaplar.txt", "r");
        yeniHesap = fopen("yeniHesap.txt", "w");
        while (fscanf(hesap, "%d %d %d/%d/%d %f", &islem1.musteriID, &islem1.hesapID, &islem1.acilmaTarihi.gun, &islem1.acilmaTarihi.ay, &islem1.acilmaTarihi.yil, &islem1.bakiye) != EOF)
        {
            if ((islem1.musteriID == musteriNo || islem1.hesapID != hesapNo) && islemMiktari != 0)
            {
                if (islem1.bakiye < islemMiktari)
                {
                    islemMiktari -= islem1.bakiye;
                    islem1.bakiye = 0;
                    fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
                }
                else
                {
                    islem1.bakiye -= islemMiktari;
                    islemMiktari = 0;
                    fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
                }
            }
            else
            {
                fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem1.musteriID, islem1.hesapID, islem1.acilmaTarihi.gun, islem1.acilmaTarihi.ay, islem1.acilmaTarihi.yil, islem1.bakiye);
            }
        }
        printf("\nPara cekme islemi basarili");
        fclose(hesap);
        fclose(yeniHesap);
        remove("hesaplar.txt");
        rename("islem1.txt", "hesaplar.txt");
    }

    if (hesapVar)
    {
        time(&t);
        zaman = localtime(&t);
        dekont = fopen("dekont.txt", "a");
        fprintf(dekont, "%d/%d/%d %d %s %f %d\n", zaman->tm_mday, zaman->tm_mon, zaman->tm_year, hesapNo, "Para_cekme", 0 - islemMiktari, 0);
        fclose(dekont);
    }
    else
        printf("\nBir hata olustu!");

    int anaMenu;
    printf("Tekrar denemek için 1, ana menuye donmek icin herhangi bir tusa basiniz->");
    scanf("%d", &anaMenu);
    if (anaMenu)
        paraCekme(musteriNo);
}

void paraYatirma()
{
    FILE *hesap, *yeniHesap, *dekont;
    int hesapNo, hesapVar = 0;
    float islemMiktari;
    struct hesap islem2;
    time(&t);
    zaman = localtime(&t);
    printf("\nPara yatirmak istediginiz hesap numarasini giriniz-> ");
    scanf("%d", &hesapNo);
    hesap = fopen("hesaplar.txt", "r");
    yeniHesap = fopen("yeniHesap.txt", "w");
    while (fscanf(hesap, "%d %d %d/%d/%d %f", &islem2.musteriID, &islem2.hesapID, &islem2.acilmaTarihi.gun, &islem2.acilmaTarihi.ay, &islem2.acilmaTarihi.yil, &islem2.bakiye) != EOF)
    {
        if (islem2.hesapID == hesapNo)
        {
            hesapVar = 1;
            printf("\nYatirmak istediginiz tutari giriniz-> ");
            scanf("%f", &islemMiktari);
            islem2.bakiye += islemMiktari;
            printf("\nPara yatirma islemi basarili!");
        }
        fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem2.musteriID, islem2.hesapID, islem2.acilmaTarihi.gun, islem2.acilmaTarihi.ay, islem2.acilmaTarihi.yil, islem2.bakiye);
    }
    fclose(hesap);
    fclose(yeniHesap);
    remove("hesaplar.txt");
    rename("yeniHesap.txt", "hesaplar.txt");
    if (hesapVar)
    {
        time(&t);
        zaman = localtime(&t);
        dekont = fopen("dekont.txt", "a");
        fprintf(dekont, "%d/%d/%d %d %s %f %d\n", zaman->tm_mday, zaman->tm_mon, zaman->tm_year, hesapNo, "Para_Yatirma", islemMiktari, 0);
        fclose(dekont);
    }
    else
        printf("\nHesap bulunamadi!");
    int anaMenu;
    printf("Tekrar denemek için 1, ana menuye donmek icin herhangi bir tusa basiniz->");
    scanf("%d", &anaMenu);
    if (anaMenu)
        paraYatirma();
}

void havale(int musteriNo)
{
    FILE *hesap, *yeniHesap, *dekont;
    int hesapNo, hesapNoKontrol = 0, havaleHesapNo, havaleBasarili = 0, hesapVar = 0;
    float islemMiktari;
    struct hesap islem3;
    time(&t);
    zaman = localtime(&t);
    printf("\nHavale isleminde kullanilacak hesap numarasini giriniz-> ");
    scanf("%d", &hesapNo);
    hesap = fopen("hesaplar.txt", "r");
    yeniHesap = fopen("yeniHesap.txt", "w");
    while (fscanf(hesap, "%d %d %d/%d/%d %f", &islem3.musteriID, &islem3.hesapID, &islem3.acilmaTarihi.gun, &islem3.acilmaTarihi.ay, &islem3.acilmaTarihi.yil, &islem3.bakiye) != EOF)
    {
        if (islem3.hesapID == hesapNo)
        {
            hesapVar = 1;
            printf("\nHavale yapilacak hesap numarasini giriniz->");
            scanf("%f", &havaleHesapNo);
            hesapNoKontrol = havaleHesapKontrol(havaleHesapNo);
            if (hesapNoKontrol)
            {
                printf("\nYatirmak istediginiz tutari giriniz-> ");
                scanf("%f", &islemMiktari);
                if (islemMiktari <= islem3.bakiye)
                {
                    havaleBasarili = 1;
                    if (musteriNo < 55555)
                        islem3.bakiye -= islemMiktari;
                    else
                        islem3.bakiye -= (islemMiktari + ((islemMiktari * 2) / 100));
                }
                else
                    printf("\nYetersiz bakiye!");
            }
            else
            {
                printf("\nGecersiz hesap numarasi!!");
            }
        }
        fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem3.musteriID, islem3.hesapID, islem3.acilmaTarihi.gun, islem3.acilmaTarihi.ay, islem3.acilmaTarihi.yil, islem3.bakiye);
    }
    fclose(hesap);
    fclose(yeniHesap);
    remove("hesaplar.txt");
    rename("yeniHesap.txt", "hesaplar.txt");

    if (havaleBasarili)
    {
        hesap = fopen("hesaplar.txt", "r");
        yeniHesap = fopen("yeniHesap.txt", "w");
        while (fscanf(hesap, "%d %d %d/%d/%d %f", &islem3.musteriID, &islem3.hesapID, &islem3.acilmaTarihi.gun, &islem3.acilmaTarihi.ay, &islem3.acilmaTarihi.yil, &islem3.bakiye) != EOF)
        {
            if (havaleHesapNo == islem3.hesapID)
            {
                islem3.bakiye += islemMiktari;
                printf("\nHavale islemi basarili!");
            }
            fprintf(yeniHesap, "%d %d %d/%d/%d %f", islem3.musteriID, islem3.hesapID, islem3.acilmaTarihi.gun, islem3.acilmaTarihi.ay, islem3.acilmaTarihi.yil, islem3.bakiye);
        }
        fclose(hesap);
        fclose(yeniHesap);
        remove("hesaplar.txt");
        rename("yeniHesap.txt", "hesaplar.txt");
    }

    fclose(hesap);
    fclose(yeniHesap);
    remove("hesaplar.txt");
    rename("yeniHesap.txt", "hesaplar.txt");

    if (hesapVar)
    {
        time(&t);
        zaman = localtime(&t);
        dekont = fopen("dekont.txt", "a");
        fprintf(dekont, "%d/%d/%d %d %s %f %d\n", zaman->tm_mday, zaman->tm_mon, zaman->tm_year, hesapNo, "Havale", islemMiktari, havaleHesapNo);
        fclose(dekont);
    }
    else
        printf("\nHesap bulunamadi!");
    int anaMenu;
    printf("Tekrar denemek için 1, ana menuye donmek icin herhangi bir tusa basiniz->");
    scanf("%d", &anaMenu);
    if (anaMenu)
        havale(musteriNo);
}

    void oturum_ac(int tip_no) {

        FILE *hesap;
        struct musteri oturum;

        oturum.isim = malloc(sizeof(char) * 25);
        oturum.soyisim = malloc(sizeof(char) * 25);

        int musteri_no, musteri_no_sifre;
        int musteri_no_onay = 0;
        if (tip_no == 1) {
            printf("Lutfen musteri numaranizi giriniz: ");
            scanf("%d", &musteri_no);


            hesap = fopen("BireyselMusteri.txt", "r");


            while (fscanf(hesap, "%s\t%s\t%d.%d.%d\t%d\t%d\t%d\t%d", oturum.isim, oturum.soyisim, &oturum.dogumTarihi.gun, &oturum.dogumTarihi.ay, &oturum.dogumTarihi.yil, &oturum.musteriID, &oturum.sifre, &oturum.limit, &oturum.limitTarihi.gun) != EOF)
            {

                if (musteri_no == oturum.musteriID) {
                    musteri_no_onay = 1;

                }
            }
            fclose(hesap);

            if (musteri_no_onay != 1) {
                printf("Girdiginiz musteri no kayitli degil.\n");
                oturum_ac(1);
            }
        printf("Girdiginiz musteri numarasinin sifresini giriniz: ");
        scanf("%d", &musteri_no_sifre);


            hesap = fopen("BireyselMusteri.txt", "r");

            while (fscanf(hesap, "%s\t%s\t%d.%d.%d\t%d\t%d\t%d\t%d", oturum.isim, oturum.soyisim, &oturum.dogumTarihi.gun, &oturum.dogumTarihi.ay, &oturum.dogumTarihi.yil, &oturum.musteriID, &oturum.sifre, &oturum.limit, &oturum.limitTarihi.gun) != EOF)
            {
                if (musteri_no_sifre == oturum.sifre) {
                    musteri_no_onay = 1;
                } else {musteri_no_onay = 0;}
            }
            fclose(hesap);

            if (musteri_no_onay != 1) {
                printf("Girdiginiz sifre yanlis. Tekrar oturum acmak uzere yonlendiriliyorsunuz...\n");
                oturum_ac(1);
            }



        }

        if (tip_no == 2) {
            printf("Lutfen musteri numaranizi giriniz: ");
            scanf("%d", &musteri_no);


            hesap = fopen("ticariMusteri.txt", "r");


            while (fscanf(hesap, "%s\t%s\t%d.%d.%d\t%d\t%d\t%d\t%d", oturum.isim, oturum.soyisim, &oturum.dogumTarihi.gun, &oturum.dogumTarihi.ay, &oturum.dogumTarihi.yil, &oturum.musteriID, &oturum.sifre, &oturum.limit, &oturum.limitTarihi.gun) != EOF)
            {

                if (musteri_no == oturum.musteriID) {
                    musteri_no_onay = 1;

                }
            }
            fclose(hesap);

            if (musteri_no_onay != 1) {
                printf("Girdiginiz musteri no kayitli degil.\n");
                oturum_ac(1);
            }
        printf("Girdiginiz musteri numarasinin sifresini giriniz: ");
        scanf("%d", &musteri_no_sifre);


            hesap = fopen("ticariMusteri.txt", "r");

            while (fscanf(hesap, "%s\t%s\t%d.%d.%d\t%d\t%d\t%d\t%d", oturum.isim, oturum.soyisim, &oturum.dogumTarihi.gun, &oturum.dogumTarihi.ay, &oturum.dogumTarihi.yil, &oturum.musteriID, &oturum.sifre, &oturum.limit, &oturum.limitTarihi.gun) != EOF)
            {
                if (musteri_no_sifre == oturum.sifre) {
                    musteri_no_onay = 1;
                } else {musteri_no_onay = 0;}
            }
            fclose(hesap);

            if (musteri_no_onay != 1) {
                printf("Girdiginiz sifre yanlis. Tekrar oturum acmak uzere yonlendiriliyorsunuz...\n");
                oturum_ac(1);
            }
        }


        printf("\n\nGiris basarili.. Aktariliyorsunuz..\n\n");

    }

    int musteri_id_cookie = 0; //hesap_ac() fonksiyonunda kullanılacak, fonksiyonun oturum acan musteri idsini ayırt etmesi icin #batu

    void hesap_ac(int musteriId) {

        struct hesap hesap_ac;
        FILE *hesap;


        hesap = fopen("hesaplar.txt", "r+");
        if (hesap == NULL) {

            hesap_ac.hesapID = 1001;

            hesap = fopen("hesaplar.txt", "w+");

            printf("Hesap ID'niz otomatik olarak olusturuldu. Hesap ID: 1001\n");
            printf("Bakiye --> 0 TL");

            time(&t);
            zaman = localtime(&t);
            hesap_ac.bakiye = 0; //yeni acilan hesap bakiye 0
            fprintf(hesap, "\n%d\t%d\t%d\t%d\t%d\t%d\n", musteriId, hesap_ac.hesapID, zaman->tm_mday, zaman->tm_mon, zaman->tm_year, hesap_ac.bakiye);
        } else {



        int tmp;
        while (fscanf(hesap, "\n%d\t%d\t%d\t%d\t%d\t%d\n", &hesap_ac.musteriID, &hesap_ac.hesapID, &hesap_ac.acilmaTarihi.gun, &hesap_ac.acilmaTarihi.ay, &hesap_ac.acilmaTarihi.yil, &hesap_ac.bakiye) != EOF)
        {
            tmp = hesap_ac.hesapID;
        }

        tmp++;
        printf("\nHesap ID'niz otomatik olarak olusturuldu. Hesap ID: %d\n", tmp);
            printf("Bakiye --> 0 TL\n\n");
            time(&t);
            zaman = localtime(&t);
            hesap_ac.bakiye = 0; //yeni acilan hesap bakiye 0
            fprintf(hesap, "\n%d\t%d\t%d\t%d\t%d\t%d\n", musteriId, tmp, zaman->tm_mday, zaman->tm_mon, zaman->tm_year, hesap_ac.bakiye);
        }
        fclose(hesap);

    }

    void hesap_no_kontrol(int musteriID, int hesapID) {
        FILE *hesap;
        hesap = fopen("hesaplar.txt", "r+");
        struct hesap hesap_ac;
        int boom = 0;
        if (hesap == NULL) {
            printf("Böyle bir hesap bulunamadı.");
        } else {
            while (fscanf(hesap, "\n%d\t%d\t%d\t%d\t%d\t%d\n", &hesap_ac.musteriID, &hesap_ac.hesapID, &hesap_ac.acilmaTarihi.gun, &hesap_ac.acilmaTarihi.ay, &hesap_ac.acilmaTarihi.yil, &hesap_ac.bakiye) != EOF)
        {
            if (hesap_ac.musteriID == musteriID) {
                if (hesap_ac.hesapID == hesapID) {
                    printf("\nDogrulama basarili...");
                    boom = 1;
                    break;
                } else {
                    continue;
                }
            }
        }

        if (boom != 1)
            printf("Girdiginiz hesap no hatali. Lutfen tekrar deneyin.");
        }
        fclose(hesap);
    }



int main()
{
    printf("\n\t\t BANKA UYGULAMAMIZA HOSGELDINIZ\n\n\n");

    while (1)
    {

        int secim1;

        printf("Lutfen yapmak istediginiz secimi giriniz!\n");
        printf("\nYeni musteri eklemek icin bir(1)");
        printf("\nMusteri profiline girmek icin iki(2)");
        printf("\nCikis icin uce (3) basiniz...");
        printf("\n-->");
        scanf("%d", &secim1);

        if (secim1 == 1)
        {
            typedef struct musteri musteri;
            int musteriTipi;
            time(&t);
            zaman = localtime(&t);
            while (1)
            {
                printf("\n\nLutfen sahip olmak istediginiz musteri tipini seciniz!\n");
                printf("Ticari Musteri icin bir(1)");
                printf("\nBireysel Musteri icin ikiye(2) basiniz");
                printf("\nCikis (3)\n");
                scanf("%d", &musteriTipi);

                if (musteriTipi == 1)
                {
                    musteri okunan;
                    okunan.isim = (char *)malloc(sizeof(char) * 25);
                    printf("\nIsminizi giriniz:");
                    scanf("%s", okunan.isim);
                    okunan.soyisim = (char *)malloc(sizeof(char) * 25);
                    printf("\nSoy isminizi giriniz:");
                    scanf("%s", okunan.soyisim);
                    printf("\nDogum Gununuzu giriniz:");
                    scanf("%d", &okunan.dogumTarihi.gun);
                    printf("\nDogum Ayinizi giriniz:");
                    scanf("%d", &okunan.dogumTarihi.ay);
                    printf("\nDogum Yilinizi giriniz:");
                    scanf("%d", &okunan.dogumTarihi.yil);

                    srand(time(NULL));
                    okunan.musteriID = 10000 + rand() % 45555;
                    musteri_id_cookie = okunan.musteriID; //musteri_id_cookie main() fonksiyonuun hemen üstünde tanımlandı #batu
                    okunan.limit = 1500;
                    okunan.limitTarihi.gun = zaman->tm_mday;
                    printf("\nMusteri No: %d dir.", okunan.musteriID);
                    printf("\nLutfen islem yapabilmek icin musteri no unutmayiniz!!!");
                    while (1)
                    {
                        printf("\n\nLutfen profilniz icin dort haneli bir sifre belirleyiniz!!!");
                        printf("\n-->");
                        scanf("%d", &okunan.sifre);
                        if (!(okunan.sifre > 9999 || okunan.sifre < 1000))
                            break;
                        else
                            printf("Sifre kurallara uymuyor!! Lutfen tekrar deneyiniz!");
                    }

                    FILE *ticMus;

                    ticMus = fopen("ticariMusteri.txt", "a");
                    if (ticMus == NULL)
                    {
                        printf("Ticari Musteri dosyasi acilamadi!");
                        exit(0);
                    }
                    fprintf(ticMus, "%s\t%s\t%d.%d.%d\t%d\t%d\t%d\t%d\n", okunan.isim, okunan.soyisim, okunan.dogumTarihi.gun, okunan.dogumTarihi.ay, okunan.dogumTarihi.yil, okunan.musteriID, okunan.sifre, okunan.limit, okunan.limitTarihi.gun);
                    printf("\n\n.....Musteri ekleme islemi basarili bir sekilde gerceklesmistir.....\n\n");

                    fclose(ticMus);
                    free(okunan.isim);
                    free(okunan.soyisim);

                    break;
                }
                if (musteriTipi == 2)
                {
                    musteri okunan;
                    okunan.isim = (char *)malloc(sizeof(char) * 25);
                    printf("\nIsminizi giriniz:");
                    scanf("%s", okunan.isim);
                    okunan.soyisim = (char *)malloc(sizeof(char) * 25);
                    printf("\nSoy isminizi giriniz:");
                    scanf("%s", okunan.soyisim);
                    printf("\nDogum Gununuzu giriniz:");
                    scanf("%d", &okunan.dogumTarihi.gun);
                    printf("\nDogum Ayinizi giriniz:");
                    scanf("%d", &okunan.dogumTarihi.ay);
                    printf("\nDogum Yilinizi giriniz:");
                    scanf("%d", &okunan.dogumTarihi.yil);

                    srand(time(NULL));
                    okunan.musteriID = 55555 + rand() % 44444;
                    printf("\nMusteri No: %d dir.", okunan.musteriID);
                    printf("\nLutfen islem yapabilmek icin musteri no unutmayiniz!!!");

                    while (1)
                    {
                        printf("\n\nLutfen profilniz icin dort haneli bir sifre belirleyiniz!!!");
                        printf("\n-->");
                        scanf("%d", &okunan.sifre);
                        if (!(okunan.sifre > 9999 || okunan.sifre < 1000))
                            break;
                        else
                            printf("Sifre kurallara uymuyor!! Lutfen tekrar deneyiniz!");
                    }

                    FILE *BirMus;

                    BirMus = fopen("BireyselMusteri.txt", "a");
                    if (BirMus == NULL)
                    {
                        printf("Bireysel Musteri dosyasi acilamadi!");
                        exit(0);
                    }
                    fprintf(BirMus, "\n%s\t%s\t%d.%d.%d\t%d\t%4d\n", okunan.isim, okunan.soyisim, okunan.dogumTarihi.gun, okunan.dogumTarihi.ay, okunan.dogumTarihi.yil, okunan.musteriID, okunan.sifre);
                    fclose(BirMus);
                    free(okunan.isim);
                    free(okunan.soyisim);
                    break;
                }
                if (musteriTipi == 3)
                    break;
            }
        }
        if (secim1 == 2)
        {
            int oturum_tip_secimi;

            printf("Musteri hesabinizin kayitli oldugu oldugu tipi seciniz.\n");
            printf("\n(bireysel hesap icin 1, ticari hesap icin 2)\n");
            scanf("%d", &oturum_tip_secimi);

            oturum_ac(oturum_tip_secimi);

            printf(".... Hosgeldiniz");

            int secim2;
            int musteri_no;
            printf("\n\nYeni hesap acmak icin bir(1)");
            printf("\n Var olan bir hesaba girmek icin ikiye(2) basiniz!");
            scanf("%d", &secim2);

            if (secim2 == 1)
            {

                printf("Lutfen musteri numaranizi giriniz:");
                scanf("%d", &musteri_no);
                hesap_ac(musteri_no);
                secim2 = 2;

            }
            if (secim2 == 2)
            {
                int secim3;
                int hesap_no;
                int musteriID;

                printf("Lutfen musteri numaraninizi giriniz:");
                scanf("%d", &musteriID);

                printf("Lutfen islem yapmak istediginiz hesap no'yu giriniz:");
                scanf("%d", &hesap_no);
                hesap_no_kontrol(musteriID, hesap_no);

                printf("\n\nLutfen yapmak istediginiz islemi seciniz!!!");
                printf("\n\nHesabinizdan para cekme islemi icin (1)");
                printf("\nHesabiniza para yatirmak icin (2)");
                printf("\nBaska bir hesaba havale icin (3)");
                printf("\nHesap ozetini gormek icin (4)");
                printf("\nHesabinizi kapatmak icin lutfen (5)'e basiniz");
                printf("\n-->");
                scanf("%d", &secim3);

                if (secim3 == 1)
                {
                    //PARA CEKME ISLEMLERI
                }
                if (secim3 == 2)
                {
                    //PARA YATIRMA ISLEMLERI
                }
                if (secim3 == 3)
                {
                    //HAVALE ISLEMLERI
                }
                if (secim3 == 4)
                {
                    //HESAP OZETI ISLEMLERI
                }
                if (secim3 == 5)
                {
                    //HESAP KAPAMA ISLEMLERI
                }
            }

            if (secim1 == 3)
                break;
        }
    }

    return 0;
}
