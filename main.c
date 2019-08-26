#include <stdio.h>
#include <stdlib.h>

//Takimlarin özellikleri struct kullanilarak tanimlandi.
struct takim{
    char takmaIsim;
    char takimUzunIsim[12];
    int oynananMacSayisi,galibiyetSayisi,berSayisi,magSayisi,aGolSayisi,yGolSayisi,averaj,puan;
};
//Fonksiyon prototipleri
void takimOlusum(struct takim *takimlar,int takimSayisi);
void ozellik(int *takimSayisi,int *gPuani,int *bPuani,int *yPuani);
void maclariOkuma(struct takim *takimlar,int takimSayisi,int gPuani,int bPuani,int yPuani);
void maclariGirme(struct takim *takimlar,int takimSayisi,int gPuani,int bPuani,int yPuani);
void puanTablosuGoster(struct takim *takimlar,int takimSayisi);
void puanTablosuDosyayaYaz(struct takim *takimlar,int takimSayisi);
void puanaGoreSiralama(struct takim *takimlar,int takimSayisi);
void takmaIsmeGoreSiralama(struct takim *takimlar,int takimSayisi);

int main()
{
    int takimSayisi,gPuani,bPuani,yPuani;//Gerekli tanimlamalar yapildi.
    ozellik(&takimSayisi,&gPuani,&bPuani,&yPuani);//ozellik fonksiyon çaðrisi.
    struct takim takimlar[takimSayisi];//Boyutu takimSayisi olacak sekilde takimlar dizisi struct kullanilarak olusturuldu.
    char secim;
    takimOlusum(&takimlar,takimSayisi);//takimOlusum fonksiyonu çagrisi.
    struct mac *maclar;

    //Arayuz
    do{
        system("cls"); //

        printf("[0] MAC GIRISI\n");
        printf("[1] DOSYADAKI MACLARI OKU\n");
        printf("[2] PUAN TABLOSUNU GOSTER\n");
        printf("[3] PUAN TABLOSUNU SIFIRLA\n");
        printf("[4] PUANA GORE SIRALAMA\n");
        printf("[5] PUAN TABLOSUNU DOSYAYA YAZ\n");
        printf("[6] TAKMA ISIME GORE SIRALAMA\n");

        scanf(" %c",&secim);

        switch(secim)
        {
            case '0' : maclariGirme(&takimlar,takimSayisi,gPuani,bPuani,yPuani); break;
            case '1' : maclariOkuma(&takimlar,takimSayisi,gPuani,bPuani,yPuani); break;
            case '2' : puanTablosuGoster(&takimlar,takimSayisi); break;
            case '3' : takimOlusum(&takimlar,takimSayisi); break;
            case '4' : puanaGoreSiralama(&takimlar,takimSayisi); break;
            case '5' : puanTablosuDosyayaYaz(&takimlar,takimSayisi); break;
            case '6' : takmaIsmeGoreSiralama(&takimlar,takimSayisi); break;
        }
    }while(1);
    return 0;
}
//takimOlusum fonksiyonunda takimlar.txt dosyasından takımların uzun ismi okundu ve takimların bütün degerlerine 0 atandı.
void takimOlusum(struct takim *takimlar,int takimSayisi)
{
    int ascii = 65;
    FILE *fp;
    fp = fopen("takimlar.txt","r");
    for(int i = 0;i<takimSayisi;i++)
    {
        fscanf(fp,"%s",&takimlar[i].takimUzunIsim);
        takimlar[i].takmaIsim = ascii + i;
        takimlar[i].oynananMacSayisi = 0;
        takimlar[i].galibiyetSayisi = 0;            //Her takim icin takim bilgilerini
        takimlar[i].berSayisi = 0;                  //baslangıc degerleri 0 olarak atanir.
        takimlar[i].magSayisi = 0;                  //takimlar.txt dosyasından takimuzun isimleri okundu.
        takimlar[i].aGolSayisi = 0;
        takimlar[i].yGolSayisi = 0;
        takimlar[i].averaj = 0;
        takimlar[i].puan = 0;
    }
    fclose(fp);
}
//ozellik fonksiyonunda ayarlar.txt dosyasindan okunan deðerler ozellikler dizisi olusturularak diziye aktarildi.
void ozellik(int *takimSayisi,int *gPuani,int *bPuani,int *yPuani)
{
    FILE *ftp;
    ftp = fopen("ayarlar.txt","r");
    int ozellikler[4][1];
    for(int i = 0;i<4;i++)
    {
        for(int j = 0;j<1;j++)
        {
            fscanf(ftp,"%d",&ozellikler[i][j]);//ayarlar.txt dosyasinin verileri ozellikler dizisine aktarildi.
        }
    }
    *takimSayisi = ozellikler[0][0];//ayarlar.txt dosyasýnýn ilk satýrý takimSayisi'na aktarildi.
    *gPuani = ozellikler[1][0];//ayarlar.txt dosyasinin 2.satiri gPuanina aktarildi.
    *bPuani = ozellikler[2][0];//ayarlar.txt dosyasinin 3.satiri bPuanina aktarildi.
    *yPuani = ozellikler[3][0];//ayarlar.txt dosyasinin 4.satiri yPuanina aktarildi.
}
void maclariOkuma(struct takim *takimlar,int takimSayisi,int gPuani,int bPuani,int yPuani)
{
    //Gereklı tanımlamalar yapıldı.
    char firstTeam,secondTeam;
    int firstScore,secondScore;
    FILE *ftp;
    ftp = fopen("maclar1.txt","r"); //maclar1.txt dosyası okuma modunda acıldı.
    while(!feof(ftp))
    {
        fscanf(ftp,"%c %d %c %d\n",&firstTeam,&firstScore,&secondTeam,&secondScore);
        if(firstTeam == secondTeam) continue; //fırstTeam secondTeam'e esıt olma durumunda contınue deyımı ıle ısleme alınmayıp devam edıldı.
        if(firstScore > secondScore)
        {
            takimlar[firstTeam-65].aGolSayisi += firstScore;
            takimlar[firstTeam-65].yGolSayisi += secondScore;                   //Birinci takimin golü ikinci takimin golünden
            takimlar[firstTeam-65].galibiyetSayisi++;                           //fazla oldugu durumunda birinci takimin degerleri
            takimlar[firstTeam-65].oynananMacSayisi++;                          //güncellendi.
            takimlar[firstTeam-65].puan += gPuani;
            takimlar[firstTeam-65].averaj += firstScore-secondScore;
            //
            takimlar[secondTeam-65].aGolSayisi += secondScore;
            takimlar[secondTeam-65].yGolSayisi += firstScore;                   //Birinci takimin golü ikinci takimin golünden
            takimlar[secondTeam-65].magSayisi++;                                //fazla oldugu durumunda ikinci takimin degerleri
            takimlar[secondTeam-65].oynananMacSayisi++;                         //güncellendi.
            takimlar[secondTeam-65].puan += yPuani;
            takimlar[secondTeam-65].averaj += secondScore-firstScore;
            //
        }
        else if(firstScore < secondScore)
        {
            takimlar[secondTeam-65].aGolSayisi += secondScore;
            takimlar[secondTeam-65].yGolSayisi += firstScore;                   //Birinci takimin golü ikinci takimin golünden
            takimlar[secondTeam-65].galibiyetSayisi++;                          //az oldugu durumunda birinci takimin degerleri
            takimlar[secondTeam-65].oynananMacSayisi++;                         //güncellendi.
            takimlar[secondTeam-65].puan += gPuani;
            takimlar[secondTeam-65].averaj += secondScore-firstScore;
            //
            takimlar[firstTeam-65].aGolSayisi += firstScore;
            takimlar[firstTeam-65].yGolSayisi += secondScore;                   //Birinci takimin golü ikinci takimin golünden
            takimlar[firstTeam-65].magSayisi++;                                 //az oldugu durumunda ikinci takimin degerleri
            takimlar[firstTeam-65].oynananMacSayisi++;                          //guncellendi.
            takimlar[firstTeam-65].puan += yPuani;
            takimlar[firstTeam-65].averaj += firstScore-secondScore;
            //
        }
        else
        {
            takimlar[secondTeam-65].aGolSayisi += secondScore;                  //Takim golleri eşit durumunda birinci takimin
            takimlar[secondTeam-65].yGolSayisi += firstScore;                   //degerleri guncellendi.
            takimlar[secondTeam-65].berSayisi++;
            takimlar[secondTeam-65].oynananMacSayisi++;
            takimlar[secondTeam-65].puan += bPuani;
            //
            takimlar[firstTeam-65].aGolSayisi += firstScore;                    //Takim golleri esit durumunda ikinci takimin
            takimlar[firstTeam-65].yGolSayisi += secondScore;                   //degerleri guncellendi.
            takimlar[firstTeam-65].berSayisi++;
            takimlar[firstTeam-65].oynananMacSayisi++;
            takimlar[firstTeam-65].puan += bPuani;
            //
        }
    }//end of while
}
void maclariGirme(struct takim *takimlar,int takimSayisi,int gPuani,int bPuani,int yPuani)
{
    //Gereklı tanımlamalar yapıldı.
    char firstTeam,secondTeam,secim;
    int firstScore,secondScore;
    printf("Mac girisi : ");
    scanf(" %c%d %c%d",&firstTeam,&firstScore,&secondTeam,&secondScore);
    if(firstTeam == secondTeam) return; //firstTeam secondTeam'e esit olma durumunda puan durumuna ıslenmedı.
    //ıf-else kosulları ıle galıbıyet beraberlık ve maglubıyet durumlarında takımların ozellıklerı guncellendı.
    if(firstScore > secondScore)
    {
        takimlar[firstTeam-65].aGolSayisi += firstScore;
        takimlar[firstTeam-65].yGolSayisi += secondScore;
        takimlar[firstTeam-65].galibiyetSayisi++;
        takimlar[firstTeam-65].oynananMacSayisi++;
        takimlar[firstTeam-65].puan += gPuani;
        takimlar[firstTeam-65].averaj += firstScore-secondScore;
            //
        takimlar[secondTeam-65].aGolSayisi += secondScore;
        takimlar[secondTeam-65].yGolSayisi += firstScore;
        takimlar[secondTeam-65].magSayisi++;
        takimlar[secondTeam-65].oynananMacSayisi++;
        takimlar[secondTeam-65].puan += yPuani;
        takimlar[secondTeam-65].averaj += secondScore-firstScore;
    }
    else if(secondScore > firstScore)
    {
        takimlar[secondTeam-65].aGolSayisi += secondScore;
        takimlar[secondTeam-65].yGolSayisi += firstScore;
        takimlar[secondTeam-65].galibiyetSayisi++;
        takimlar[secondTeam-65].oynananMacSayisi++;
        takimlar[secondTeam-65].puan += gPuani;
        takimlar[secondTeam-65].averaj += secondScore-firstScore;
        //
        takimlar[firstTeam-65].aGolSayisi += firstScore;
        takimlar[firstTeam-65].yGolSayisi += secondScore;
        takimlar[firstTeam-65].magSayisi++;
        takimlar[firstTeam-65].oynananMacSayisi++;
        takimlar[firstTeam-65].puan += yPuani;
        takimlar[firstTeam-65].averaj += firstScore-secondScore;
    }
    else
    {
        takimlar[secondTeam-65].aGolSayisi += secondScore;
        takimlar[secondTeam-65].yGolSayisi += firstScore;
        takimlar[secondTeam-65].berSayisi++;
        takimlar[secondTeam-65].oynananMacSayisi++;
        takimlar[secondTeam-65].puan += bPuani;
        //
        takimlar[firstTeam-65].aGolSayisi += firstScore;
        takimlar[firstTeam-65].yGolSayisi += secondScore;
        takimlar[firstTeam-65].berSayisi++;
        takimlar[firstTeam-65].oynananMacSayisi++;
        takimlar[firstTeam-65].puan += bPuani;
    }
}
void puanTablosuGoster(struct takim *takimlar,int takimSayisi)
{
    printf("\t\t\t\tTurkiye Sanal Super Lig\n\n");
    printf("TkmIsim\t\tTkmUzunIsim\t\tOynMacSys\tGaSys\tBerSys\tMagSys\tAGolSys\tYGolSys\tAveraj\tPuan\n");
        for(int j = 0;j<takimSayisi;j++)
        {
            printf("%4c\t\t%10s\t\t%4d\t\t%d\t%4d\t%4d\t%4d\t%4d\t%4d\t%4d\n",takimlar[j].takmaIsim,takimlar[j].takimUzunIsim,
                takimlar[j].oynananMacSayisi,takimlar[j].galibiyetSayisi,takimlar[j].berSayisi,takimlar[j].magSayisi,
                takimlar[j].aGolSayisi,takimlar[j].yGolSayisi,takimlar[j].averaj,takimlar[j].puan);
        }
        char x;
        printf("Ana ekrana donmek icin bir tusa basiniz.");
        x = getch();
}
void puanTablosuDosyayaYaz(struct takim *takimlar,int takimSayisi)
{
    FILE *ftp;
    ftp = fopen("puanDurumu.txt","w"); //puanDurumu.txt dosyası yazma modunda acıldı.
    fprintf(ftp,"\t\t\t\tTurkiye Sanal Super Lig\n\n");
    fprintf(ftp,"TkmIsim\t\tTkmUzunIsim\t\tOynMacSys\tGaSys\tBerSys\tMagSys\tAGolSys\tYGolSys\tAveraj\tPuan\n");
    for(int j = 0;j<takimSayisi;j++)
    {
        fprintf(ftp,"%4c\t\t%10s\t\t%4d\t\t%d\t%4d\t%4d\t%4d\t%4d\t%4d\t%4d\n",takimlar[j].takmaIsim,takimlar[j].takimUzunIsim,
            takimlar[j].oynananMacSayisi,takimlar[j].galibiyetSayisi,takimlar[j].berSayisi,takimlar[j].magSayisi,
            takimlar[j].aGolSayisi,takimlar[j].yGolSayisi,takimlar[j].averaj,takimlar[j].puan);
    }
    fclose(ftp);
}
void puanaGoreSiralama(struct takim *takimlar,int takimSayisi)
{
    struct takim temp;
    for(int i = 0;i<takimSayisi;i++)
    {
        for(int j = 1;j<takimSayisi;j++)
        {
            if(takimlar[j-1].puan < takimlar[j].puan)
            {
                temp = takimlar[j-1];                                 //takimlar dizisinin elemanlarinin puan degerleri karsilastirildi.
                takimlar[j-1] = takimlar[j];
                takimlar[j] = temp;
            }
        }
    }
}
void takmaIsmeGoreSiralama(struct takim *takimlar,int takimSayisi)
{
    struct takim temp;
    for(int i = 0;i<takimSayisi;i++)
    {
        for(int j = 1;j<takimSayisi;j++)
        {
            if(takimlar[j-1].takmaIsim > takimlar[j].takmaIsim)
            {
                temp = takimlar[j-1];
                takimlar[j-1] = takimlar[j];
                takimlar[j] = temp;
            }
        }
    }
}
