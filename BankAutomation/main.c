#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct musteri{
    char *isim;
    char *soyisim;
    int dogumYil;
    int dogumGun;
    int dogumAy;

};

int main()
{
     printf("\n\t\t BANKA UYGULAMAMIZA HOSGELDINIZ\n\n\n");

     while(1){

   int secim1;

   printf("Lutfen yapmak istediginiz secimi giriniz!\n");
   printf("\nYeni musteri eklemek icin bir(1)");
   printf("\nMusteri profiline girmek icin iki(2)");
   printf("\nCikis icin uce (3) basiniz...");
   printf("\n-->");
   scanf("%d", &secim1);


   if(secim1==1)
   {
    typedef struct musteri xyz;
    int musteriTipi;
    while(1)
    {
        printf("\n\nLutfen sahip olmak istediginiz musteri tipini seciniz!\n");
        printf("Ticari Musteri icin bir(1)");
        printf("\nBireysel Musteri icin ikiye(2) basiniz");
        printf("\nCikis (3)\n");
        scanf("%d", &musteriTipi);


        if(musteriTipi==1)
        {
            xyz okunan;
            okunan.isim=(char*)malloc(sizeof(char)*100);
            printf("\nIsminizi giriniz:");
            scanf("%s", okunan.isim);
            okunan.soyisim=(char*)malloc(sizeof(char)*100);
            printf("\nSoy isminizi giriniz:");
            scanf("%s", okunan.soyisim);
            printf("\nDogum Gununuzu giriniz:");
            scanf("%d", &okunan.dogumGun);
            printf("\nDogum Ayinizi giriniz:");
            scanf("%d", &okunan.dogumAy);
            printf("\nDogum Yilinizi giriniz:");
            scanf("%d", &okunan.dogumYil);

            int musteriNo1;
            srand(time(NULL));
            musteriNo1=10000+rand()%55555;
            printf("\nMusteri No: %d dir.", musteriNo1);
            printf("\nLutfen islem yapabilmek icin musteri no unutmayiniz!!!");

            int musterisifre1;
            printf("\n\nLutfen profilniz icin dort haneli bir sifre belirleyiniz!!!");
            printf("\n-->");
            scanf("%d", &musterisifre1);

            FILE *ticMus;


            ticMus=fopen("ticariMusteri.txt","a");
            if(ticMus==NULL)
            {
                printf("Ticari Musteri dosyasi acilamadi!");
                exit(0);
            }
            fprintf(ticMus,"\n%s\t%s\t%d.%d.%d\t%d\t%4d\n", okunan.isim,okunan.soyisim,okunan.dogumGun,okunan.dogumAy,okunan.dogumYil,musteriNo1,musterisifre1);
            printf("\n\n.....Musteri ekleme islemi basarili bir sekilde gerceklesmistir.....\n\n");

            fclose(ticMus);
            break;
        }
        if (musteriTipi==2)
        {
             xyz okunan;
            okunan.isim=(char*)malloc(sizeof(char)*100);
            printf("\nIsminizi giriniz:");
            scanf("%s", okunan.isim);
            okunan.soyisim=(char*)malloc(sizeof(char)*100);
            printf("\nSoy isminizi giriniz:");
            scanf("%s", okunan.soyisim);
            printf("\nDogum Gununuzu giriniz:");
            scanf("%d", &okunan.dogumGun);
            printf("\nDogum Ayinizi giriniz:");
            scanf("%d", &okunan.dogumAy);
            printf("\nDogum Yilinizi giriniz:");
            scanf("%d", &okunan.dogumYil);

            int musteriNo2;
            srand(time(NULL));
            musteriNo2=55555+rand()%99999;
            printf("\nMusteri No: %d dir.", musteriNo2);
            printf("\nLutfen islem yapabilmek icin musteri no unutmayiniz!!!");

            int musterisifre2;
            printf("\n\nLutfen profilniz icin dort haneli bir sifre belirleyiniz!!!");
            printf("\n-->");
            scanf("%d", &musterisifre2);


            FILE *BirMus;


            BirMus=fopen("BireyselMusteri.txt","a");
            if(BirMus==NULL)
            {
                printf("Bireysel Musteri dosyasi acilamadi!");
                exit(0);
            }
            fprintf(BirMus,"\n%s\t%s\t%d.%d.%d\t%d\t%4d\n",okunan.isim,okunan.soyisim,okunan.dogumGun,okunan.dogumAy,okunan.dogumYil,musteriNo2,musterisifre2);
            fclose(BirMus);
            break;
        }
        if(musteriTipi==3)
            break;
   }
   }
   if(secim1==2)
   {
       //Hesap giris.....
       // profile giris yapildiktan sonra islem yapılması icin hesap acilmasi gerekir....
       printf(".... Hosgeldiniz");

       int secim2;
       printf("\n\nYeni hesap acmak icin bir(1)");
       printf("\n Var olan bir hesaba girmek icin ikiye(2) basiniz!");
       scanf("%d", secim2);

       if(secim2==1)
       {
           // Yeni hesap acma islemleri gerceklesecek...

           break;
       }
       if (secim2==2)
       {
           int secim3;
           printf("\n\nLutfen yapmak istediginiz islemi seciniz!!!");
           printf("\n\nHesabinizdan para cekme islemi icin (1)");
           printf("\nHesabiniza para yatirmak icin (2)");
           printf("\nBaska bir hesaba havele icin (3)");
           printf("\nHesap ozetini gormek icin (4)");
           printf("\nHesabinizi kapatmak icin lutfen (5)'e basiniz");
           printf("\n-->");
           scanf("%d", &secim3);

           if (secim3==1)
           {
               //PARA CEKME ISLEMLERI
           }
            if (secim3==2)
           {
               //PARA YATIRMA ISLEMLERI
           }
            if (secim3==3)
           {
               //HAVALE ISLEMLERI
           }
            if (secim3==4)
           {
               //HESAP OZETI ISLEMLERI
           }
            if (secim3==5)
           {
               //HESAP KAPAMA ISLEMLERI
           }
       }




   if (secim1==3)
       break;

     }
     }

    return 0;
}
