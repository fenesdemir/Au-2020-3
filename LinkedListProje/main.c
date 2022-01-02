#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Komsular
{
    int komsuPlaka;
    struct Komsular *next;
};

struct Dugum
{
    int plaka;
    char sehir[20];
    char bolge[3];
    int komsuSayisi;
    struct Dugum *sonraki;
    struct Komsular *komsu;
};

void listeYazdir(struct Dugum *n, char dosyaAdi[20])
{
    FILE *yazilacak;
    yazilacak = fopen(dosyaAdi, "a");

    while(n != NULL)
    {
        struct Komsular* son_komsu = n->komsu;
        fprintf(yazilacak,"%d, ", n->plaka);
        fprintf(yazilacak,"%s, ", n->sehir);
        fprintf(yazilacak,"%s, ", n->bolge);
        fprintf(yazilacak,"%d -> ", n->komsuSayisi);
        if(n->komsu != NULL)
        {
            for(int i = 0; i<n->komsuSayisi; i++)
            {
                if(i == n->komsuSayisi-1){
                    fprintf(yazilacak,"%d", son_komsu->komsuPlaka);
                }else{
                    fprintf(yazilacak,"%d -> ", son_komsu->komsuPlaka);
                    son_komsu = son_komsu->next;
                }
            }
        }
        if(n->sonraki != NULL){
            fprintf(yazilacak,"\n");
            fprintf(yazilacak,"|\n");
            fprintf(yazilacak,"v\n");
        }

        n = n->sonraki;
    }
    fprintf(yazilacak,"\n\n");
    fclose(yazilacak);
}

int plakaAra(struct Dugum *n, char ad[20])
{
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(strcmp(current->sehir, ad) == 0)
        {
            return current->plaka;
        }
        current = current->sonraki;
    }
    return 0;
}

void komsuEkle(struct Dugum** liste, int eklenecek[])
{
    int iterasyon = 0;
    struct Dugum* son_dugum = *liste;
    while(son_dugum->sonraki != NULL)
    {
        int yukari = iterasyon + son_dugum->komsuSayisi;
        for(int i = iterasyon; i<yukari; i++)
        {
            struct Komsular* yeni_komsu = (struct Komsular*)malloc(sizeof(struct Komsular));
            struct Komsular* son_komsu = son_dugum->komsu;

            yeni_komsu->komsuPlaka = eklenecek[i];
            yeni_komsu->next = NULL;

            if(son_dugum->komsu == NULL)
            {
                son_dugum->komsu = yeni_komsu;
                goto etiket;
            }

            while(son_komsu->next != NULL)
            {
                son_komsu = son_komsu->next;
            }

            son_komsu->next = yeni_komsu;
etiket:
            ;
        }
        iterasyon = yukari;
        son_dugum = son_dugum->sonraki;
    }

    if(son_dugum->sonraki == NULL)
    {
        int bottom = iterasyon;
        int top = bottom + son_dugum->komsuSayisi;
        for(int i = bottom; i< top; i++)
        {
            struct Komsular* yeni_komsu = (struct Komsular*)malloc(sizeof(struct Komsular));
            struct Komsular* son_komsu = son_dugum->komsu;

            yeni_komsu->komsuPlaka = eklenecek[i];
            yeni_komsu->next = NULL;

            if(son_dugum->komsu == NULL)
            {
                son_dugum->komsu = yeni_komsu;
                goto tag;
            }

            while(son_komsu->next != NULL)
            {
                son_komsu = son_komsu->next;
            }

            son_komsu->next = yeni_komsu;
tag:
            ;
        }
    }

    return;
}

void sonaEkle(struct Dugum** kafa, int plakaNum, char sehirAd[20], char bolgeTag[3], int kSayisi)
{
    struct Dugum* yeni_dugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    struct Dugum* son_dugum = *kafa;

    yeni_dugum->plaka = plakaNum;
    strcpy(yeni_dugum->sehir, sehirAd);
    strcpy(yeni_dugum->bolge, bolgeTag);
    yeni_dugum->komsuSayisi = kSayisi;
    yeni_dugum->sonraki = NULL;
    yeni_dugum->komsu = NULL;

    if(*kafa == NULL)
    {
        *kafa = yeni_dugum;
        return;
    }

    while(son_dugum->sonraki != NULL)
    {
        son_dugum = son_dugum->sonraki;
    }

    son_dugum->sonraki = yeni_dugum;
    return;
}

void yeniKayit_komsulukEkle(struct Dugum** kafa,char sehirAd[20],int kSayisi, int komsular[])
{
    struct Dugum* current = *kafa;

    while (current != NULL)
    {
        if(strcmp(current->sehir, sehirAd) == 0)
        {
            for(int i = 0; i<kSayisi; i++)
            {
            struct Komsular* yeni_komsu = (struct Komsular*)malloc(sizeof(struct Komsular));
            struct Komsular* son_komsu = current->komsu;

            yeni_komsu->komsuPlaka = komsular[i];
            yeni_komsu->next = NULL;

            if(current->komsu == NULL)
            {
                current->komsu = yeni_komsu;
                goto tag_komsu;
            }

            while(son_komsu->next != NULL)
            {
                son_komsu = son_komsu->next;
            }

            son_komsu->next = yeni_komsu;
tag_komsu:
            ;

            }
             return;
        }
        current = current->sonraki;
    }
    return;
}

void basaEkle(struct Dugum** bas, int plakaNum, char sehirAd[20], char bolgeTag[3], int kSayisi)
{
    struct Dugum* yeni_dugum = (struct Dugum*)malloc(sizeof(struct Dugum));

    yeni_dugum->plaka = plakaNum;
    strcpy(yeni_dugum->sehir, sehirAd);
    strcpy(yeni_dugum->bolge, bolgeTag);
    yeni_dugum->komsuSayisi = kSayisi;
    yeni_dugum->sonraki = NULL;
    yeni_dugum->komsu = NULL;

    yeni_dugum->sonraki = (*bas);

    (*bas) = yeni_dugum;
    return;
}

void yeniKomsuluk(struct Dugum** bas, char sehirAd[20], int plaka)
{
    struct Dugum* current = *bas;
    struct Komsular* son_komsu;
    while (current != NULL){
        if(strcmp(current->sehir, sehirAd) == 0){
            son_komsu = current->komsu;
            break;
        }
        current = current->sonraki;
    }

    struct Komsular* yeni_komsu = (struct Komsular*)malloc(sizeof(struct Komsular));
    yeni_komsu->komsuPlaka = plaka;
    yeni_komsu->next = NULL;

    if(current->komsu == NULL)
    {
        current->komsu = yeni_komsu;
        current->komsuSayisi = current->komsuSayisi + 1;
        return;
    }


     while(son_komsu->next != NULL)
            {
                if(son_komsu->komsuPlaka == plaka){
                    printf("Bu komsuluk iliskisi zaten bulunmaktadir.\n");
                    return;
                }
                son_komsu = son_komsu->next;
            }
            if(son_komsu->komsuPlaka == plaka){
                    printf("Bu komsuluk iliskisi zaten bulunmaktadir.\n");
                    return;
                }

            son_komsu->next = yeni_komsu;
            current->komsuSayisi = current->komsuSayisi + 1;
    return;
}

void komsuSil(struct Dugum** bas, char sehirAd[20], int silinecek)
{
    struct Dugum* current = *bas;
    struct Komsular* onceki_komsu;
    struct Komsular* son_komsu;

    while (current != NULL){
        if(strcmp(current->sehir, sehirAd) == 0){
            son_komsu = current->komsu;
            break;
        }
        current = current->sonraki;
    }

    if(son_komsu != NULL && son_komsu->komsuPlaka == silinecek){
      current->komsu = son_komsu->next;
      current->komsuSayisi = current->komsuSayisi - 1;
      free(son_komsu);
      return;
    }

    while(son_komsu != NULL && son_komsu->komsuPlaka != silinecek){
        onceki_komsu = son_komsu;
        son_komsu = son_komsu->next;
    }

    if(son_komsu == NULL){
        printf("Boyle bir komsuluk iliskisi bulunmamaktadir.\n");
        return;
    }

    onceki_komsu->next = son_komsu->next;
    current->komsuSayisi = current->komsuSayisi - 1;
    free(son_komsu);
    return;
}

void arayaEkle(struct Dugum** bas, int plakaNum, char sehirAd[20], char bolgeTag[3], int kSayisi)
{
    struct Dugum* son_dugum = *bas;

    while(son_dugum->sonraki != NULL)
    {
        if(son_dugum->plaka < plakaNum && son_dugum->sonraki->plaka > plakaNum){
            break;
        }
        son_dugum = son_dugum->sonraki;
    }
    struct Dugum* yeni_dugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    yeni_dugum->plaka = plakaNum;
    strcpy(yeni_dugum->sehir, sehirAd);
    strcpy(yeni_dugum->bolge, bolgeTag);
    yeni_dugum->komsuSayisi = kSayisi;
    yeni_dugum->sonraki = son_dugum->sonraki;
    yeni_dugum->komsu = NULL;

    son_dugum->sonraki = yeni_dugum;

    return;
}

void isimleAra(struct Dugum *n, char ad[20], char dosyaAdi[20])
{
    FILE *yazilacak;
    yazilacak = fopen(dosyaAdi, "a");
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(strcmp(current->sehir, ad) == 0)
        {
            struct Komsular* son_komsu = current->komsu;
            fprintf(yazilacak, "%d ,", current->plaka);
            fprintf(yazilacak, "%s, ", current->sehir);
            fprintf(yazilacak, "%s, ", current->bolge);
            fprintf(yazilacak, "%d, ->", current->komsuSayisi);
            if(current->komsu != NULL)
        {
            for(int i = 0; i<current->komsuSayisi; i++)
            {
                if(i == current->komsuSayisi-1){
                    fprintf(yazilacak,"%d", son_komsu->komsuPlaka);
                }else{
                    fprintf(yazilacak,"%d -> ", son_komsu->komsuPlaka);
                    son_komsu = son_komsu->next;
                }
            }
        }
        fprintf(yazilacak,"\n");
        }
        current = current->sonraki;
    }
    fprintf(yazilacak,"\n\n");
    fclose(yazilacak);
    return;
}

void plakaylaAra(struct Dugum *n, int aranacak, char dosyaAdi[20])
{
    FILE *yazilacak;
    yazilacak = fopen(dosyaAdi, "a");
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(current->plaka == aranacak)
        {
            struct Komsular* son_komsu = current->komsu;
            fprintf(yazilacak, "%d ,", current->plaka);
            fprintf(yazilacak, "%s, ", current->sehir);
            fprintf(yazilacak, "%s, ", current->bolge);
            fprintf(yazilacak, "%d, ", current->komsuSayisi);
            if(current->komsu != NULL)
        {
            for(int i = 0; i<current->komsuSayisi; i++)
            {
                if(i == current->komsuSayisi-1){
                    fprintf(yazilacak,"%d", son_komsu->komsuPlaka);
                }else{
                    fprintf(yazilacak,"%d -> ", son_komsu->komsuPlaka);
                    son_komsu = son_komsu->next;
                }
            }
        }
        fprintf(yazilacak,"\n");
        }
        current = current->sonraki;
    }
    fprintf(yazilacak,"\n\n");
    fclose(yazilacak);
    return;
}

void bolgeAra(struct Dugum *n, char bolgeAranacak[3], char dosyaAdi[20])
{
    FILE *yazilacak;
    yazilacak = fopen(dosyaAdi, "a");
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(strcmp(current->bolge, bolgeAranacak) == 0)
        {
            struct Komsular* son_komsu = current->komsu;
            fprintf(yazilacak, "%d ,", current->plaka);
            fprintf(yazilacak, "%s, ", current->sehir);
            fprintf(yazilacak, "%s, ", current->bolge);
            fprintf(yazilacak, "%d, ", current->komsuSayisi);
            if(current->komsu != NULL)
        {
            for(int i = 0; i<current->komsuSayisi; i++)
            {
                if(i == current->komsuSayisi-1){
                    fprintf(yazilacak,"%d", son_komsu->komsuPlaka);
                }else{
                    fprintf(yazilacak,"%d -> ", son_komsu->komsuPlaka);
                    son_komsu = son_komsu->next;
                }
            }
        }
        fprintf(yazilacak,"\n");
        }
        current = current->sonraki;
    }
    fprintf(yazilacak,"\n\n");
    fclose(yazilacak);
    return;
}

void komsuSayisiAralik(struct Dugum *n, int arananAlt, int arananUst, char dosyaAdi[20])
{
    FILE *yazilacak;
    yazilacak = fopen(dosyaAdi, "a");
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(current->komsuSayisi >= arananAlt && current->komsuSayisi <= arananUst)
        {
            struct Komsular* son_komsu = current->komsu;
            fprintf(yazilacak, "%d ,", current->plaka);
            fprintf(yazilacak, "%s, ", current->sehir);
            fprintf(yazilacak, "%s, ", current->bolge);
            fprintf(yazilacak, "%d, ", current->komsuSayisi);
            if(current->komsu != NULL)
        {
            for(int i = 0; i<current->komsuSayisi; i++)
            {
                if(i == current->komsuSayisi-1){
                    fprintf(yazilacak,"%d", son_komsu->komsuPlaka);
                }else{
                    fprintf(yazilacak,"%d -> ", son_komsu->komsuPlaka);
                    son_komsu = son_komsu->next;
                }
            }
        }
        fprintf(yazilacak,"\n");
        }
        current = current->sonraki;
    }
    fprintf(yazilacak,"\n\n");
    fclose(yazilacak);
    return;
}

void isimleSil(struct Dugum** basDugum, char ad[])
{
    struct Dugum* temp = *basDugum, *onceki;

    if(temp != NULL && strcmp(temp->sehir, ad) == 0)
    {
        *basDugum = temp->sonraki;
        free(temp);
        return;
    }

    while(temp != NULL && strcmp(temp->sehir, ad) != 0)
    {
        onceki = temp;
        temp = temp->sonraki;
    }

    if(temp == NULL)
    {
        return;
    }

    onceki->sonraki = temp->sonraki;
    free(temp);

    return;
}

void bonus(struct Dugum* bas, int alt, int ust, int komsular[], int boyut, char dosyaAdi[20])
{
    FILE *yazilacak;
    yazilacak = fopen(dosyaAdi, "a");
    struct Dugum* current = bas;

    while (current != NULL)
    {
        struct Komsular* son_komsu = current->komsu;
        int durum = 0;

        if(current->komsu != NULL)
        {
            for(int i = 0; i<current->komsuSayisi; i++)
            {
                for(int j = 0 ; j < boyut; j++)
                {
                    if(son_komsu->komsuPlaka == komsular[j])
                    {
                        durum ++;
                    }
                }
                son_komsu = son_komsu->next;
            }
        }
        if(durum == boyut && current->komsuSayisi >= alt && current->komsuSayisi <= ust)
        {
        struct Komsular* yazilacak_komsu = current->komsu;
        fprintf(yazilacak,"%d, ", current->plaka);
        fprintf(yazilacak,"%s, ", current->sehir);
        fprintf(yazilacak,"%s, ", current->bolge);
        fprintf(yazilacak,"%d, ", current->komsuSayisi);
         if(current->komsu != NULL)
        {
            for(int i = 0; i<current->komsuSayisi; i++)
            {
                if(i == current->komsuSayisi-1){
                    fprintf(yazilacak,"%d", yazilacak_komsu->komsuPlaka);
                }else{
                    fprintf(yazilacak,"%d -> ", yazilacak_komsu->komsuPlaka);
                    yazilacak_komsu = yazilacak_komsu->next;
                }
            }
        }
        fprintf(yazilacak,"\n");
        }
        current = current->sonraki;
    }
    fprintf(yazilacak,"\n\n");
    fclose(yazilacak);
    return;
}

int sonPlaka(struct Dugum* bas)
{
    struct Dugum* current = bas;

    while (current->sonraki != NULL)
    {
        current = current->sonraki;
    }
    int plaka = current->plaka;
    return plaka;
}

int plakaVarMi(struct Dugum *n, int aranacak)
{
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(current->plaka == aranacak)
        {
            return 1;
        }
        current = current->sonraki;
    }
    return 0;
}

int sehirVarMi(struct Dugum *n, char ad[20])
{
    struct Dugum* current = n;

    while (current != NULL)
    {
        if(strcmp(current->sehir, ad) == 0)
        {
            return 1;
        }
        current = current->sonraki;
    }
    return 0;
}

int main()
{
    struct Dugum* head = NULL;

    char c[500];
    FILE *fptr;
    fptr = fopen("sehirler.txt", "r");
    if( fptr == NULL)
    {
        printf("Dosya acilamadi.!\n");
        exit(1);
    }
    while(fgets(c, 255, fptr) != NULL)
    {
        int satirSayaci = 0;
        int komsuSayisi = 0;
        int plak;
        char isim[20];
        char bolge[3];
        const char *ayrac = ",";
        char *kelime = strtok(c, ayrac);
        while (kelime != NULL)
        {
            if(satirSayaci == 0)
            {
                plak = atoi(kelime);
            }
            else if(satirSayaci == 1)
            {
                strcpy(isim, kelime);
            }
            else if(satirSayaci == 2)
            {
                strcpy(bolge, kelime);
            }
            else
            {
                komsuSayisi++;
            }

            kelime = strtok(NULL, ayrac);
            satirSayaci++;
        }
        sonaEkle(&head, plak, isim, bolge, komsuSayisi);
    }
    fclose(fptr);
    fflush(stdin);
    int toplam = 0;
    struct Dugum* m = NULL;
    m = head;

    while(m != NULL)
    {
        toplam = toplam + m->komsuSayisi;
        m = m->sonraki;
    }
    int torba[toplam];
    int diziSayaci = 0;
    fflush(stdin);

    fptr = fopen("sehirler.txt", "r");
    if( fptr == NULL)
    {
        printf("Error!\n");
        exit(1);
    }
    while(fgets(c, 255, fptr) != NULL)
    {
        int satirSayaci = 0;
        const char *ayrac = ",\n";
        int plaka;
        char *kelime = strtok(c, ayrac);
        while (kelime != NULL)
        {
            if(satirSayaci > 2)
            {
                plaka = plakaAra(head, kelime);
                torba[diziSayaci] = plaka;
                diziSayaci++;
            }
            kelime = strtok(NULL, ayrac);
            satirSayaci++;
        }
    }
    fclose(fptr);

    komsuEkle(&head, torba);
    listeYazdir(head, "cikti.txt");
    int secim = 0;
    printf("Dosya okundu ve mevcut model yazdirildi.\n");
    printf("Menuye hosgeldiniz.\n");
    printf("Yeni kayit eklemek icin 1, Kayit silmek icin 2\n");
    printf("Plaka ile sehir aramak icin 3, Isimle sehir aramak icin 4\n");
    printf("Komsu sayisiyla sorgu icin 5, Bolgeye gore sorgu icin 6\n");
    printf("Bonus sorgu icin 7, Komsuluk eklemek icin 8\n");
    printf("Komsuluk silmek icin 9,Cikmak icin 0\n");

secim_etiket:
    printf("Seciminizi girin\n");
    scanf("%d", &secim);

    if(secim == 1)
    {

        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 1\n");
        fclose(point);
        int plaka, komsuSayisi;
        char sehir[20];
        char bolge[3];

        secimBirEtiket:

        printf("Eklemek istediginiz sehrin plakasini giriniz.\n");
        scanf("%d", &plaka);
        if(plakaVarMi(head, plaka) == 1)
        {
            printf("Bu kayit zaten bulunmaktadir.Yeniden deneyiniz.\n");
            goto secimBirEtiket;
        }
        printf("Eklemek isteginiz sehrin adini giriniz.\n");
        scanf("%s", sehir);
        if(sehirVarMi(head, sehir) == 1)
        {
            printf("Bu kayit zaten bulunmaktadir.Yeniden deneyiniz.\n");
            goto secimBirEtiket;
        }
        printf("Eklemek isteginiz sehrin bolgesini giriniz.\n");
        scanf("%s", bolge);
        printf("Eklemek istediginiz sehrin komsu sayisini giriniz.\n");
        scanf("%d", &komsuSayisi);
        int komsular[komsuSayisi];

        for(int i = 0; i < komsuSayisi; i++)
        {
            printf("Eklemek isteginiz komsunun plakasini giriniz.\n");
            scanf("%d", &komsular[i]);
        }

        int kucukPlaka = head->plaka;
        int buyukPlaka = sonPlaka(head);

        if(plaka < kucukPlaka){
            basaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }else if(plaka > buyukPlaka){
            sonaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }else{
            arayaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }
        listeYazdir(head, "cikti.txt");
        goto secim_etiket;
    }
    else if( secim == 2)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 2\n");
        fclose(point);
        char ad[20];
        secimIkiEtiket:
        printf("Silmek istediginiz kaydin ismini giriniz.\n");
        scanf("%s", ad);
        if(sehirVarMi(head, ad) == 0){
            printf("Boyle bir kayit bulunmamaktadir.\n");
            goto secimIkiEtiket;
        }
        isimleSil(&head, ad);
        listeYazdir(head, "cikti.txt");
        goto secim_etiket;
    }
    else if(secim == 3)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 3\n");
        fclose(point);
        int plaka;
        int secenek;

        printf("Aramak isteginiz plakayi giriniz.\n");
        scanf("%d", &plaka);
        if(plakaVarMi(head, plaka) == 1){
            plakaylaAra(head, plaka, "cikti.txt");
            goto secim_etiket;
        }else{
            printf("Boyle bir kayit bulunmamaktadir eklemek ister misiniz? Evet : 1 , Hayir : 0\n");
            scanf("%d", &secenek);
            if(secenek == 1){
        int plaka, komsuSayisi;
        char sehir[20];
        char bolge[3];

        printf("Eklemek istediginiz sehrin plakasini giriniz.\n");
        scanf("%d", &plaka);
        eklemeEtiket:
        printf("Eklemek isteginiz sehrin adini giriniz.\n");
        scanf("%s", sehir);
        if(sehirVarMi(head, sehir) == 1)
        {
            printf("Bu kayit zaten bulunmaktadir.Yeniden deneyiniz.\n");
            goto eklemeEtiket;
        }
        printf("Eklemek isteginiz sehrin bolgesini giriniz.\n");
        scanf("%s", bolge);
        printf("Eklemek istediginiz sehrin komsu sayisini giriniz.\n");
        scanf("%d", &komsuSayisi);
        int komsular[komsuSayisi];

        for(int i = 0; i < komsuSayisi; i++)
        {
            printf("Eklemek isteginiz komsunun plakasini giriniz.\n");
            scanf("%d", &komsular[i]);
        }

        int kucukPlaka = head->plaka;
        int buyukPlaka = sonPlaka(head);

        if(plaka < kucukPlaka){
            basaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }else if(plaka > buyukPlaka){
            sonaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }else{
            arayaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }
        listeYazdir(head, "cikti.txt");
        goto secim_etiket;

            }else if(secenek == 0){
                goto secim_etiket;
            }
        }
        goto secim_etiket;
    }
    else if(secim == 4)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 4\n");
        fclose(point);
        char ad[20];
        int secenek;

        printf("Aramak isteginiz sehrin ismini giriniz.\n");
        scanf("%s", ad);
        if(sehirVarMi(head, ad) == 1){
            isimleAra(head, ad, "cikti.txt");
            goto secim_etiket;
        }else{
            printf("Boyle bir kayit bulunmamaktadir eklemek ister misiniz? Evet : 1 , Hayir : 0\n");
            scanf("%d", &secenek);
            if(secenek == 1){
        int plaka, komsuSayisi;
        char sehir[20];
        char bolge[3];

        eklemeEtiket2:
        printf("Eklemek istediginiz sehrin plakasini giriniz.\n");
        scanf("%d", &plaka);
        if(plakaVarMi(head, plaka) == 1){
            printf("Bu kayit zaten bulunmaktadir.Yeniden deneyiniz.\n");
            goto eklemeEtiket2;
        }
        printf("Eklemek isteginiz sehrin adini giriniz.\n");
        scanf("%s", sehir);
        printf("Eklemek isteginiz sehrin bolgesini giriniz.\n");
        scanf("%s", bolge);
        printf("Eklemek istediginiz sehrin komsu sayisini giriniz.\n");
        scanf("%d", &komsuSayisi);
        int komsular[komsuSayisi];

        for(int i = 0; i < komsuSayisi; i++)
        {
            printf("Eklemek isteginiz komsunun plakasini giriniz.\n");
            scanf("%d", &komsular[i]);
        }

        int kucukPlaka = head->plaka;
        int buyukPlaka = sonPlaka(head);

        if(plaka < kucukPlaka){
            basaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }else if(plaka > buyukPlaka){
            sonaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }else{
            arayaEkle(&head, plaka, sehir, bolge, komsuSayisi);
            yeniKayit_komsulukEkle(&head, sehir, komsuSayisi, komsular);
        }
        listeYazdir(head, "cikti.txt");
        goto secim_etiket;

            }else if(secenek == 0){
                goto secim_etiket;
            }

        }
        goto secim_etiket;
    }
    else if(secim == 5)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 5\n");
        fclose(point);
        int alt, ust;

        printf("Alt degeri giriniz.\n");
        scanf("%d", &alt);
        printf("Ust degeri giriniz.\n");
        scanf("%d", &ust);
        komsuSayisiAralik(head, alt, ust, "cikti.txt");

        goto secim_etiket;
    }
    else if(secim == 6)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 6\n");
        fclose(point);
        char bolge[20];

        printf("Sorgulamak istediginiz bolgeyi giriniz.\n");
        scanf("%s", bolge);
        bolgeAra(head, bolge, "cikti.txt");

        goto secim_etiket;
    }
    else if(secim == 7)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 7\n");
        fclose(point);
        int alt, ust ,komsuSayi;

        printf("Alt degeri giriniz.\n");
        scanf("%d", &alt);
        printf("Ust degeri giriniz.\n");
        scanf("%d", &ust);
        printf("Kac sayida komsuya gore arama yapmak istiyorsunuz?\n");
        scanf("%d", &komsuSayi);
        int aranacak[komsuSayi];

        for(int i = 0; i< komsuSayi; i++)
        {
            char ad[20];
            printf("Komsu adi giriniz:\n");
            scanf("%s", ad);
            aranacak[i] = plakaAra(head, ad);
        }

        bonus(head, alt, ust, aranacak, komsuSayi, "cikti.txt");
        goto secim_etiket;
    }else if(secim == 8)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 8\n");
        fclose(point);
        int eklenecek;
        char ad[20];

        secimSekizEtiket:

        printf("Komsuluk eklemek istediginiz sehrin adini giriniz.\n");
        scanf("%s", ad);
        if(sehirVarMi(head, ad) == 0){
            printf("Boyle bir sehir bulunmamaktadir.\n");
            goto secimSekizEtiket;
        }
        printf("Eklemek isteginiz plakayi giriniz.\n");
        scanf("%d", &eklenecek);
        yeniKomsuluk(&head, ad, eklenecek);

        listeYazdir(head, "cikti.txt");
        goto secim_etiket;

    }else if(secim == 9)
    {
        FILE *point;
        point = fopen("cikti.txt", "a");
        fprintf(point, "Secim 9\n");
        fclose(point);
        int silinecek;
        char ad[20];

        secimDokuzEtiket:

        printf("Komsuluk silmek istediginiz sehrin adini giriniz.\n");
        scanf("%s", ad);
        if(sehirVarMi(head, ad) == 0){
            printf("Boyle bir sehir bulunmamaktadir.\n");
            goto secimDokuzEtiket;
        }
        printf("Silmek isteginiz plakayi giriniz.\n");
        scanf("%d", &silinecek);

        komsuSil(&head, ad, silinecek);

        listeYazdir(head, "cikti.txt");
        goto secim_etiket;
    }
    else if(secim == 0)
    {
        printf("Cikis yapiliyor\n");
    }

    return 0;
}
