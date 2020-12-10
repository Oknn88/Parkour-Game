#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*Parkur uzunluğunu ve engel sayısını tutan struct
*/
struct Parkur{
     int uzunluk;
     int engel_sayisi;
};
/*parkuruzunlugu fonksiyonu:
  Parkur uzunlugunu ratgele belirliyor.
  r_parkur parkur uzunlugunu tutuyor.
*/
void parkuruzunlugu(int *r_parkur)
{
    srand(time(NULL));
    *r_parkur = rand() %51 + 50;
}

/*parkurengel fonksiyonu:
  parkurda kaç engel çıkacapını belirliyor. Bunu r_engelsayisi pointeri tutuyor.
*/
void parkurengelsayisi(int *r_engelsayisi)
{
    srand(time(NULL));
    *r_engelsayisi = rand() % 4 + 2;
}

/*parkurengel fonksiyonu:
  engellerin kaçıncı metrede çıkacağını belirliyor. Bunu engekacmet pointeri tutuyor.
  bu çıkan engel metrelerini küçükten büyüğe sıralıyor.
  parkuruz parkurun uzunluğunu tutuyor. Bunu parkur_uz pointeri tutuyor.
*/
void parkurengel(int engel_sa, int parkur_uz, int *engelkacmet)
{
    int gecici;
    bool ayni_sayi = false ;
    for(int i=0; i< engel_sa; i++)
    {
        int metre;
        metre = rand() % (parkur_uz - 4) + 5;
        for(int j=0; j<i;j++)
        {
            if (metre == *(engelkacmet + j * sizeof(int)))
            {
                i--;
                break;
                ayni_sayi = true;
            }
        }
        if(!ayni_sayi)
        {
           *(engelkacmet + i * sizeof(int)) = metre;
        }

    }

   for(int i=0; i<engel_sa-1;i++)
    {
        for(int j=i+1; j<engel_sa; j++)
        {
            if(*(engelkacmet + i * sizeof(int)) > *(engelkacmet + j * sizeof(int)))
            {
                gecici = *(engelkacmet + i * sizeof(int));
                *(engelkacmet + i * sizeof(int)) = *(engelkacmet + j * sizeof(int));
                *(engelkacmet + j * sizeof(int)) = gecici;
            }
        }
    }
}
/*aralarindaasal fonksiyonu:
  yarısmacının yaşam puanı ile engelle karşılaştığı metrenin aralarında asal olup olmadığını kotrol ediyor.
  aralarında asalsa 0 return ediyorç
*/
int aralaridaasal(int yasampuani, int karsilasilanmetre)
{
    int buyuk, kucuk, kontrol=1;
        if (yasampuani > karsilasilanmetre)
        {
            buyuk = yasampuani;
            kucuk = karsilasilanmetre;
        }
        else
        {
            buyuk = karsilasilanmetre;
            kucuk = yasampuani;
        }

        for(int j=2; j<=kucuk; j++)
        {
            if( (buyuk % j == 0) && (kucuk % j == 0) )
            {
                kontrol = 0;
                break;
            }
        }
        return kontrol;
}
/*logdosya:
  logtxt adında bir dosya oluşturup oyunda yazılması gereken metinleri bu dosyaya yazıyor.
*/
void logdosya(int *yasam_puani, int *engelinmetresi, int parkurunuzunlugu, int engel_sayisi)
{
    int engel_metre[engel_sayisi];
        for(int i=0; i< engel_sayisi; i++)
    {
        engel_metre[i] = *(engelinmetresi + i * sizeof(int));
    }

    int kontrol_asal,engel_anlik;
    FILE *logtxt = fopen("log.txt" , "w");
    fprintf(logtxt, "Yarisma Basladi!!\n");
    fprintf(logtxt, "Yarismaci HP = %d\n", *yasam_puani);

    for(int parkur_index= 0; parkur_index <engel_sayisi;parkur_index++)
    {
          engel_anlik = engel_metre[parkur_index];
          kontrol_asal = aralaridaasal(*yasam_puani, engel_anlik);
          if(kontrol_asal==1)
          {
              fprintf(logtxt, "Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n", engel_anlik);
              fprintf(logtxt, "Yarismaci %d. metrede engel var. %d ve %d aralarinda asaldir.\n", engel_anlik, *yasam_puani, engel_anlik);
              *yasam_puani = *yasam_puani -  engel_metre[parkur_index];
              fprintf(logtxt, "HP = %d\n",*yasam_puani);

             if(*yasam_puani<=0)
             {
              fprintf(logtxt, "Yarismaci HP = %d\nUzgunum !!! Yarismayi tamamliyamadin.", *yasam_puani);
              break;
             }

          }
          else
          {
              fprintf(logtxt, "Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n", engel_anlik);
               fprintf(logtxt, "Yarismaci %d. metrede engel var. %d ve %d aralarinda asal degildir.\n", engel_anlik, *yasam_puani, engel_anlik);
               fprintf(logtxt, "HP = %d\n",*yasam_puani);
          }
        }

  if(*yasam_puani>0)
  {
      fprintf(logtxt, "Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n",parkurunuzunlugu);
      fprintf(logtxt, "Tebrikler !!! Yarismayi %d HP ile bitirdiniz.", *yasam_puani);
  }

    fclose(logtxt);

}


int main()
{
    struct Parkur parkur;
    int Yasam_Puani = 100;
    parkuruzunlugu(&parkur.uzunluk);
    parkurengelsayisi(&parkur.engel_sayisi);
    int *engel_metre = (int *)malloc(parkur.engel_sayisi * sizeof(int));
    parkurengel(parkur.engel_sayisi ,parkur.uzunluk, engel_metre);
    logdosya(&Yasam_Puani, engel_metre, parkur.uzunluk,parkur.engel_sayisi);
 return 0;

}
