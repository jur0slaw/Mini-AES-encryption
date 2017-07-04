#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int redukcyjny[] = { 1 , 0 , 0 , 1 , 1 };
int przesuniecia[][4]={{0,0,1,2},{-1,0,0,2},{0,-2,1,0},{-1,-2,0,0}};
int m[] = {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1};
int klucz_poczatkowy[] = {1,0,1,1,0,0,1,0,1,1,1,1,0,1,1,0};
int e[] = {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7};
int d[] = {14,3,4,8,1,12,10,15,7,13,9,6,11,2,0,5};
int glupia_kolejnosc_obsrana[]={0,2,1,3};
int rak[]={0,5,11,12};

void podzial(int * in, int out[4][4]){
    int i,j,k;
    k=0;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            out[i][j]=in[k];
            k++;
        }
    }

}

 int todec(int * in, int size){
        int i;
        int wynik =0;
        for(i=0;i<size;i++){
            wynik=wynik+(in[i]<<(size-(i+1)));
        }
        return wynik;
 }

 void tobin(int in, int * out, int size){
     int i;
     for(i=0;i<size;i++){
       // printf("%i ",in);
        out[i]=in/(1<<(size-(i+1)));
        in = in%(1<<(size-(i+1)));

     }
 }

 void self_modulo(int * in,int size){
    int i;
    for(i=0;i<size;i++){
        in[i]=in[i]%2;
    }
 }

void mnozenie_wielomianow(int * in1, int size1, int * in2, int size2, int * out){
    int i,j;
    memset(out,0,7*sizeof(int));
    for(i=0;i<size1;i++){
        for(j=0;j<size2;j++){
            out[i+j]=(out[i+j] + in1[i]*in2[j])%2;
        }
    }
    self_modulo(out,7);
}

void wypisz(int * in, int size){
    int i;
    for(i=0;i<size;i++){
            printf("%i",in[i]);
    }
    printf(" ");
}

void wypisz_macierzowe(int in[][4]){
    int i;
    for(i=0;i<4;i++){
        wypisz(&in[i][0],4);
    }
    printf("\n");
}

int szukaj(int * in){
    int i;
    for(i=0;i<7;i++){
        if(in[i]==1){
            return i;
        }
    }
    return i;
}

void cpy(int *in,int size , int * out){
    int i;
    for(i=0;i<size;i++){
        out[i]=in[i];
    }
}

void  dodawanie(int * in1, int * in2, int size, int * out){
    int i;
    for(i=0;i<size;i++){
        out[i]=(in1[i]+in2[i])%2;
    }
}

void duze_dodawanie(int in1[][4] , int in2[][4] , int out[][4]){
    int i;
    for(i=0;i<4;i++){
        dodawanie(&in1[i][0],&in2[i][0],4,&out[i][0]);
    }
}

void reszta(int * in1, int size1, int * in2, int size2, int * out){
    int temp1[7];
    mnozenie_wielomianow(in1,4,in2,4,temp1);
    int temp2[3];
    int temp3[7];
    int temp4[7];


    while(szukaj(temp1)<3){
        memset(temp2,0,3*sizeof(int));
        temp2[szukaj(temp1)]=1;
        mnozenie_wielomianow(temp2,3,redukcyjny,5,temp3);
        cpy(temp1,7,temp4);
        dodawanie(temp4,temp3,7,temp1);
    }
    self_modulo(temp1,7);

    int i;
    for(i=0;i<4;i++){
        out[i]=temp1[i+3];
    }

}


void duze_mnozenie(int in1[][4], int in2[][4],int out[][4]){
    int i;
    int temp1[4];
    int temp2[4];
    int temp3[4];


    for(i=0;i<4;i++){


        reszta(&in1[i+przesuniecia[i][0]][0],4,&in2[i+przesuniecia[i][1]][0],4,temp1);
        reszta(&in1[i+przesuniecia[i][2]][0],4,&in2[i+przesuniecia[i][3]][0],4,temp2);

        dodawanie(temp1,temp2,4,temp3);
        cpy(temp3,4,&out[i][0]);
    }
}

void zk(int in[][4]){
    int temp,i;
    for(i=0;i<4;i++){
        temp=in[2][i];
        in[2][i]=in[3][i];
        in[3][i]=temp;
    }

}

void sbox(int in[][4],int * wzor){
  int i;
  for(i=0;i<4;i++){
    tobin(wzor[todec(&in[i][0],4)],&in[i][0],4);
  }
}

void generacja_kluczy(int in[][4],int out[][4],int r){
    int i;
    int temp[4];

    for(i=0;i<4;i++){
        if(i==0){
            tobin(e[todec(&in[3][0],4)],temp,4);
            dodawanie(&in[0][0],temp,4,&out[0][0]);
            out[i][r]=(out[i][r]+1)%2;
        }else{
            dodawanie(&in[glupia_kolejnosc_obsrana[i]][0],&out[glupia_kolejnosc_obsrana[i-1]][0],4,&out[glupia_kolejnosc_obsrana[i]][0]);
        }
    }
}

int main()
{
    char start[16];
    int tekst[4];
    int tekst2[16]={0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1};
    int wymysl[16]={0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0};
    scanf("%s",start);
    int i;
    for(i=0;i<4;i++){
        if(start[i]==49){
            tekst[i]=1;
        }
        else{
            tekst[i]=0;
        }
    }

    for(i=0;i<4;i++){
        wymysl[rak[i]]=tekst[i];
    }

    int tekst_poczatkowy[4][4];

    podzial(tekst2,tekst_poczatkowy);

    printf("Tekst poczatkowy: \n");

    wypisz_macierzowe(tekst_poczatkowy);



    int duzy_poczatkowy[4][4];
    int prep[4][4];
    int pierwszej_rundy[4][4];
    int drugiej_rundy[4][4];

    podzial(wymysl,duzy_poczatkowy);
    podzial(wymysl,prep);
    generacja_kluczy(prep,pierwszej_rundy,3);
    generacja_kluczy(pierwszej_rundy,drugiej_rundy,2);

    printf("Klucz poczatkowy:  \n");
    wypisz_macierzowe(duzy_poczatkowy);
    printf("Klucz pierwszej rundy:  \n");

    wypisz_macierzowe(pierwszej_rundy);
    printf("Klucz drugiej rundy:  \n");
    wypisz_macierzowe(drugiej_rundy);


    int bufor[4][4];
    int bufor2[4][4];

    duze_dodawanie(duzy_poczatkowy,tekst_poczatkowy,bufor);
    printf("Po dodaniu klucza poczatkowego:  \n");
    wypisz_macierzowe(bufor);

    sbox(bufor,e);
    printf("Po sboxie:  \n");
    wypisz_macierzowe(bufor);


    zk(bufor);
    printf("Po zk:  \n");
    wypisz_macierzowe(bufor);


    int marek[4][4];
    podzial(m,marek);

    duze_mnozenie(marek, bufor, bufor2);
    printf("Po mnozeniu:  \n");
    wypisz_macierzowe(bufor2);

    duze_dodawanie(bufor2,pierwszej_rundy,bufor);
    printf("Po dodaniu klucza pierwszej rundy:  \n");
    wypisz_macierzowe(bufor);

    sbox(bufor,e);
    printf("Po sboxie 2:  \n");
    wypisz_macierzowe(bufor);

    zk(bufor);
    printf("Po zk 2:  \n");
    wypisz_macierzowe(bufor);


    duze_dodawanie(bufor,drugiej_rundy,bufor2);
    printf("Zaszyfrowany tekst:  \n");
    wypisz_macierzowe(bufor2);



    return 0;
}
