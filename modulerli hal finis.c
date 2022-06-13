#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LENGTH 100
#define MAX_EL 10
#define MAX_ITERATION 100.0
struct arrEl{
    float katsayi[MAX_EL];
    float us[MAX_EL];
    float tur[MAX_EL];
};
//Fonksiyon kullanma fonksiyonlari
void fonksiyonAl(struct arrEl* arrEl);
void fonksiyonBol(char denklem[],char elements[][MAX_LENGTH]);
void elementBol(char elements[][MAX_LENGTH],struct arrEl* arrEl);
int returnPos(char element[MAX_LENGTH],char ch);
float sonucuHesapla(struct arrEl* arrEl,float x);
void turevAl(struct arrEl* arrEl);
int returnCharTrue(char element[MAX_LENGTH], char x);
void arrElSifirla(struct arrEl* arrEL);
void arrElYazdir(struct arrEl* arrEl);
void arrElcopy (struct arrEl* arrEl1,struct arrEl* arrEl2);
//Ln felan icin fonksiyonlar
int rst(char element[MAX_LENGTH],char x[MAX_LENGTH]);
void basaKaydir(char element[MAX_LENGTH],int kacKaydir);

//Matris kullanma fonksiyonlari

int matrisAl(float matris[MAX_EL][MAX_EL]);
void matrisYazdir(float matris[MAX_EL][MAX_EL],int matrisBuyukluk);
float determinant(float matris[MAX_EL][MAX_EL],int matrisBuyukluk);
void kucukmatrisYap(float matris[MAX_EL][MAX_EL],float matris2[MAX_EL][MAX_EL],int matrisBuyukluk,int xCoord,int yCoord);
void minorAl(float matris[MAX_EL][MAX_EL],float minor[MAX_EL][MAX_EL],int matrisBuyukluk);
int sonucluMatrisAl(float matris[MAX_EL][MAX_EL],float sonuc[MAX_EL]);
//Bisection Method fonksiyonlari
void bisectionMethod();
//Regula Falsi Method fonksiyonlari
void regulaFalsiMethod();
//Newton-Raphson Method fonksiyonlari
void newtonRaphsonMethod();
//Matris tersi alma fonksiyonlari
void tersiniAlanzi();
//Gauss eliminasyon fonksiyonlari
void gaussEliminasyon();
//Gauss seidal fonksiyonlari
void gaussSeidal();
//Sayisal Turev fonksiyonlari
void sayisalTurev();
//Simpson yontemi fonksiyonlari
void simpsonYontemi();
//Trapez yontemi fonksiyonlari
void trapezYontemi();
//Gregory Newton Fonksiyonlari
void gregoryNewton();
//Gregory Newton Ozel Denklem Carpma Fonksiyonlari
void denklemCarpma(float denklem1[MAX_EL],float denklem2[MAX_EL]);
void denklemKatsayiCarp(float denklem1[MAX_EL],float katsayi);
void denklemTopla(float denklem1[MAX_EL],float denklem2[MAX_EL]);
float denklemHesaplaritto(float denklem[MAX_EL],int buyukluk,float xdegeri);
//Menu fonkisyon
void skipper();
int menu();
int main() {
    int sayi;
    do{

        sayi=menu();
        fflush(stdin);
        system("cls");
        switch(sayi){
            case 1:
                bisectionMethod();
                break;
            case 2:
                regulaFalsiMethod();
                break;
            case 3:
                newtonRaphsonMethod();
                break;
            case 4:
                tersiniAlanzi();
                break;
            case 5:
                gaussEliminasyon();
                break;
            case 6:
                gaussSeidal();
                break;
            case 7:
                sayisalTurev();
                break;
            case 8:
                simpsonYontemi();
                break;
            case 9:
                trapezYontemi();
                break;
            case 10:
                gregoryNewton();
                break;
            default:
                printf("Invalid number.");
        }
        skipper();
        system("cls");
    }
    while(sayi!=0);
    return 0;
}
void skipper(){
    int sayi=0;
    while(sayi!=-1){
        printf("Cikmak istiyorsaniz -1 yazip entere basiniz\n");
        scanf("%d",&sayi);
    }
}
int menu(){
    int menuSayisi;
    printf("Yapmak istediginiz isleme gore assagidaki sayilardan birini seciniz.\n");
    printf("0-Exit\n1-Bisection Yontemi\n2-Regula-Falsi Yontemi\n3-Newton-Raphson Yontemi\n4-NxN'lik bir matrisin tersi\n5-Gauss Eleminasyon\n6-Gauss Seidal Yontemleri\n7-Sayisal Turev\n8-Simpson yontemi\n9-Trapez Yontemi\n10-Gregory newton Enterpolasyonu\n");
    scanf("%d",&menuSayisi);
    return menuSayisi;
}
void gregoryNewton(){
    float x0,h;
    int n,i,j,deltaBuyuklugu=0;
    float x[MAX_EL],deltaMatris[MAX_EL][MAX_EL],deltalar[MAX_EL]={0},faktoriyel=1;
    float denklem1[MAX_EL]={0},denklem2[MAX_EL]={0},cevapDenklem[MAX_EL]={0},xdegeri;
    printf("Baslangic degeri(x0):");
    scanf("%f",&x0);
    printf("h:");
    scanf("%f",&h);
    printf("Girilecek deger sayisi(n)(max 10):");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("f(%f)=",x0+i*h);
        scanf(" %f",&x[i]);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            deltaMatris[i][j]=0.0;
        }
    }
    for(i=0;i<n;i++){
        deltaMatris[i][0]=x[i];
    }
    for(i=1;i<n;i++){
        for(j=i;j<n;j++){
            deltaMatris[j][i]=deltaMatris[j][i-1]-deltaMatris[j-1][i-1];
        }
    }
    for(i=0;i<n;i++){
        if(deltaMatris[i][i]!=0){
            deltalar[i]=deltaMatris[i][i];
            deltaBuyuklugu++;
        }
    }
    denklem1[1]=1/h;
    denklem1[0]=-x0/h;
    for(i=0;i<deltaBuyuklugu;i++){
        if(i==0){
            cevapDenklem[0]+=deltalar[0];
        }
        else if(i==1){
            denklemKatsayiCarp(denklem1,deltalar[1]);
            denklemTopla(denklem1,cevapDenklem);
            denklemKatsayiCarp(denklem1,1/deltalar[1]);
        }
        else{
            faktoriyel=faktoriyel*i;
            denklem2[1]=1/h;
            denklem2[0]=(-x0-(i-1)*h)/h;
            denklemCarpma(denklem2,denklem1);
            denklemKatsayiCarp(denklem1,deltalar[i]/faktoriyel);
            denklemTopla(denklem1,cevapDenklem);
            denklemKatsayiCarp(denklem1,faktoriyel/deltalar[i]);
        }
    }
    for(i=deltaBuyuklugu-1;i>=0;i--){
        printf("%2fx^%d",cevapDenklem[i],i);
        if(i!=0){
            printf(" + ");
        }
    }
    printf("\nx:");
    scanf("%f",&xdegeri);
    printf("Result: %f\n",denklemHesaplaritto(cevapDenklem,deltaBuyuklugu,xdegeri));
}
float denklemHesaplaritto(float denklem[MAX_EL],int buyukluk,float xdegeri){
    int i,j;
    float sonuc=0,carpan=1;
    for(i=0;i<buyukluk;i++){
        for(j=0;j<i;j++){
            carpan=carpan*xdegeri;
        }
        carpan=carpan*denklem[i];
        sonuc+=carpan;
        carpan=1;
    }
    return sonuc;
}
void denklemTopla(float denklem1[MAX_EL],float denklem2[MAX_EL]){
    int i;
    for(i=0;i<MAX_EL;i++){
        denklem2[i]+=denklem1[i];
    }
}
void denklemCarpma(float denklem1[MAX_EL],float denklem2[MAX_EL]){
    int i,j;
    float cevap[MAX_EL*2]={0};
    for(i=0;i<MAX_EL;i++){
        for(j=0;j<MAX_EL;j++){
            cevap[i+j]+=denklem1[i]*denklem2[j];
        }
    }
    for(i=0;i<MAX_EL;i++){
        denklem2[i]=cevap[i];
    }
}
void denklemKatsayiCarp(float denklem[MAX_EL],float katsayi){
    int i;
    for(i=0;i<MAX_EL;i++){
        denklem[i]*=katsayi;
    }
}
void trapezYontemi(){
    struct arrEl arrEl;
    float h,sonuc=0.0,baslangic,bitis,i,parca;
    arrElSifirla(&arrEl);
	fonksiyonAl(&arrEl);
    printf("Integral baslangic degerini giriniz: ");
    scanf("%f",&baslangic);
    printf("Integral bitis degerini giriniz: ");
    scanf("%f",&bitis);
    printf("Parca sayisini giriniz: ");
    scanf("%f",&parca);
    h=(bitis-baslangic)/(parca);
    for (i = baslangic; i != bitis; i = i + h) {
        sonuc += sonucuHesapla(&arrEl, i) + sonucuHesapla(&arrEl, i + h);
        printf("i=%f Sonuc: %f\n",i,sonuc);
    }
    sonuc = sonuc * (h/2.0);
    printf("Sonuc: %f\n",sonuc);
}
void simpsonYontemi(){
    int integralTuru;
    struct arrEl arrEl;
    float h,sonuc=0.0,baslangic,bitis,i,parca;
    arrElSifirla(&arrEl);
	fonksiyonAl(&arrEl);
    printf("Integral baslangic degerini giriniz: ");
    scanf("%f",&baslangic);
    printf("Integral bitis degerini giriniz: ");
    scanf("%f",&bitis);
    printf("Parca sayisini giriniz: ");
    scanf("%f",&parca);
    printf("Simpsonun turunu belirlemek icin assagidaki degerlerden birini giriniz:\n1-1/3\n2-3/8\n");
    scanf("%d",&integralTuru);
    if(integralTuru==1) {
        h=(bitis-baslangic)/(2*parca);
        for (i = baslangic; i != bitis; i = i + 2 * h) {
            sonuc += sonucuHesapla(&arrEl, i) + 4 * sonucuHesapla(&arrEl, i + h) +
                     sonucuHesapla(&arrEl, i + 2 * h);
        }
        sonuc = sonuc * (h / 3.0);
    }
    else if(integralTuru==2){
        h=(bitis-baslangic)/(3*parca);
        for (i = baslangic; i != bitis; i = i + 3 * h) {
            sonuc += sonucuHesapla(&arrEl, i) + 3 * sonucuHesapla(&arrEl, i + h) +
                     3 * sonucuHesapla(&arrEl, i + 2 * h) + sonucuHesapla(&arrEl, i + 3 * h);
        }
        sonuc = sonuc * (3.0 * h / 8.0);
    }
    printf("Sonuc: %f\n",sonuc);
}
void sayisalTurev(){
    int turevTuru;
    struct arrEl arrEl;
    float h,sonuc,x0;
    arrElSifirla(&arrEl);
    fonksiyonAl(&arrEl);
    printf("Ileri geri ya da merkezi turev icin asagidaki degerleri giriniz:\n1-Ileri\n2-Geri\n3-Merkez\n");
    scanf("%d",&turevTuru);
    printf("x0 degerini giriniz: ");
    scanf("%f",&x0);
    printf("h degerini giriniz: ");
    scanf("%f",&h);
    if(turevTuru==1){
        sonuc=sonucuHesapla(&arrEl,x0+h)-sonucuHesapla(&arrEl,x0);
        sonuc=sonuc/h;
        printf("Bulunan deger=%f\n",sonuc);
    }
    else if(turevTuru==2){
        sonuc=sonucuHesapla(&arrEl,x0)-sonucuHesapla(&arrEl,x0-h);
        sonuc=sonuc/h;
        printf("Bulunan deger=%f\n",sonuc);
    }
    else if(turevTuru==3){
        sonuc=sonucuHesapla(&arrEl,x0+h)-sonucuHesapla(&arrEl,x0-h);
        sonuc=sonuc/(2*h);
        printf("Bulunan deger=%f\n",sonuc);
    }
    else{
        printf("Yanlis turev secimi yaptiniz.\n");
    }
}
void gaussSeidal(){
    int i,j,k,enBuyukIndex,sonucSaglandi=0;
    float enBuyuk=-9999.0,temp,hata,yedekSonuc;
    float matris[MAX_EL][MAX_EL];
    float deger[MAX_EL],yenideger[MAX_EL];
    float sonuc[MAX_EL];
    int boy = sonucluMatrisAl(matris,sonuc);
    int iteration=0;
    for(i=0;i<boy;i++){
        printf("%d. Baslangic degerini giriniz:",i+1);
        scanf("%f",&deger[i]);
    }
    for(i=0;i<boy;i++){
        yenideger[i]=deger[i];
    }
    printf("Epsilon degerini giriniz:");
    scanf("%f",&hata);
    for(i=0;i<boy;i++){
        for(j=0;j<boy;j++){
            if(fabs(matris[i][j])>enBuyuk){
                enBuyuk=fabs(matris[i][j]);
                enBuyukIndex=j;
            }

        }
        enBuyuk=-9999.0;
        for(k=0;k<boy;k++){
            temp=matris[enBuyukIndex][k];
            matris[enBuyukIndex][k]=matris[i][k];
            matris[i][k]=temp;
            temp=sonuc[enBuyukIndex];
            sonuc[enBuyukIndex]=sonuc[i];
            sonuc[i]=temp;
        }
    }
    printf("Diagonally dominant matrix:\n");
    matrisYazdir(matris,boy);
    while(!sonucSaglandi){
        for(i=0;i<boy;i++){
            deger[i]=yenideger[i];
        }
        for(i=0;i<boy;i++){
            yedekSonuc=sonuc[i];
            for(j=0;j<boy;j++){
                if(j!=i){
                    yedekSonuc=yedekSonuc-matris[i][j]*yenideger[j];
                }
            }
            yenideger[i]=yedekSonuc/matris[i][i];
        }
        iteration++;
        printf("iteration:%d\n",iteration);
        for(i=0;i<boy;i++){
            printf("  %d. deger=%f",i+1,yenideger[i]);
        }
        printf("\n");
        if(iteration>=MAX_ITERATION){
            printf("Max iterations reached.\n");
            return;
        }
        for(i=0;i<boy;i++){
            if(fabs(yenideger[i]-deger[i])<hata){
                sonucSaglandi=1;
            }
            else{
                sonucSaglandi=0;
                i=boy;
            }
        }
    }
}
void gaussEliminasyon(){
    int i,j,k;
    float matris[MAX_EL][MAX_EL];
    float sonuc[MAX_EL];
    float katsayi;
    int boy = sonucluMatrisAl(matris,sonuc);
    printf("Matris=\n");
    matrisYazdir(matris,boy);
    printf("Sonuc=\n");
    for(i=0;i<boy;i++){
        printf("%f ",sonuc[i]);
    }
    printf("\n");
    for(i=0;i<boy-1;i++){
        for(j=i+1;j<boy;j++){
            katsayi=matris[j][i]/matris[i][i];
            for(k=0;k<boy;k++){
                matris[j][k]=matris[j][k]-matris[i][k]*katsayi;

            }
            sonuc[j]=sonuc[j]-sonuc[i]*katsayi;
        }

    }
    for(i=0;i<boy;i++){
        katsayi=1/matris[i][i];
        for(k=0;k<boy;k++){
            matris[i][k]*=katsayi;
        }
        sonuc[i]=sonuc[i]*katsayi;
    }
    for(i=boy-1;i>0;i--){
        for(j=i-1;j>=0;j--){
            katsayi=matris[j][i]/matris[i][i];
            matris[j][i]=matris[j][i]-katsayi*matris[i][i];
            sonuc[j]=sonuc[j]-sonuc[i]*katsayi;
        }
    }
    for(i=0;i<boy;i++){
        printf("x%d: %f\n",i+1,sonuc[i]);
    }
}
int sonucluMatrisAl(float matris[MAX_EL][MAX_EL],float sonuc[MAX_EL]){
    int boy= matrisAl(matris),i;
    for(i=0;i<boy;i++){
        printf("%d.Sonucu giriniz:",i+1);
        scanf("%f",&sonuc[i]);
    }
    return boy;
}
float determinant(float matris[MAX_EL][MAX_EL],int matrisBuyukluk){
    float s = 1, det = 0.0, matris2[MAX_EL][MAX_EL];
    int i, j, m, n, c;

    if (matrisBuyukluk == 1)
    {
        return (matris[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < matrisBuyukluk; c++)
        {
            kucukmatrisYap(matris, matris2, matrisBuyukluk, c, 0);
            det = det + s * (matris[0][c] * determinant(matris2, matrisBuyukluk - 1));
            s = -1 * s;
        }
    }
    return det;
}
void kucukmatrisYap(float matris[MAX_EL][MAX_EL],float matris2[MAX_EL][MAX_EL],int matrisBuyukluk,int xCoord,int yCoord){
    int m,n,i,j;
    m = 0;
    n = 0;
    for (i = 0;i < matrisBuyukluk; i++)
    {
        for (j = 0 ;j < matrisBuyukluk; j++)
        {
            matris2[i][j] = 0;
            if (i != yCoord && j != xCoord)
            {
                matris2[m][n] = matris[i][j];
                if (n < (matrisBuyukluk - 2))
                    n++;
                else
                {
                    n = 0;
                    m++;
                }
            }
        }
    }
}
void minorAl(float matris[MAX_EL][MAX_EL],float minor[MAX_EL][MAX_EL],int matrisBuyukluk){
    int i,j,c=1;
    float matris2[MAX_EL][MAX_EL];
    for(i=0;i<MAX_EL;i++){
        for(j=0;j<MAX_EL;j++){
            kucukmatrisYap(matris, matris2, matrisBuyukluk, i, j);
            minor[j][i]=determinant(matris2,matrisBuyukluk-1)*c;
            c=c*-1;
        }

    }
}
void tersiniAlanzi(){
    float sonMatriske[MAX_EL][MAX_EL]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    float matris[MAX_EL][MAX_EL]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    int matrisBuyukluk = matrisAl(matris);
    int i,j;
    minorAl(matris,sonMatriske,matrisBuyukluk);
    float det=determinant(matris,matrisBuyukluk);
    printf("Ilk matris=\n");
    matrisYazdir(matris,matrisBuyukluk);
    printf("Det=%f\nMinor=\n",det);
    matrisYazdir(sonMatriske,matrisBuyukluk);
    for(i=0;i<matrisBuyukluk;i++){
        for(j=0;j<matrisBuyukluk;j++){
            sonMatriske[i][j]=sonMatriske[i][j]/det;
        }
    }
    printf("Inverse Matris=\n");
    matrisYazdir(sonMatriske,matrisBuyukluk);
}
int matrisAl(float matris[MAX_EL][MAX_EL]){
    int matrisBuyukluk;
    printf("Matrisin boyutunu giriniz: ");
    scanf("%d",&matrisBuyukluk);
    int i,j;
    for(i=0;i<matrisBuyukluk;i++){
        for(j=0;j<matrisBuyukluk;j++){
            printf("[%d][%d]:",i+1,j+1);
            scanf(" %f",&matris[i][j]);
            fflush(stdin);
        }
    }
    return matrisBuyukluk;
}
void matrisYazdir(float matris[MAX_EL][MAX_EL],int matrisBuyukluk){
    int i,j;
    for(i=0;i<matrisBuyukluk;i++){
        for(j=0;j<matrisBuyukluk;j++){
            printf("%f ",matris[i][j]);
        }
        printf("\n");
    }
}
void newtonRaphsonMethod(){
    struct arrEl arrEl,arrElTurev;
    arrElSifirla(&arrEl);
    fonksiyonAl(&arrEl);
    float x1,epsilon;
    printf("x1 giriniz: ");
    scanf(" %f",&x1);
    printf("epsilon giriniz: ");
    scanf(" %f",&epsilon);
    float fx1,x3,iteration=0.0;
    float fturevx1;
    arrElcopy(&arrElTurev,&arrEl);
    fx1=sonucuHesapla(&arrEl,x1);
    turevAl(&arrElTurev);
    fturevx1=sonucuHesapla(&arrElTurev,x1);
    printf("Iteration: %f\n",iteration+1);
    printf("x1: %f\n",x1);
    printf("f(x): %f\n",fx1);
    printf("f'(x): %f\n",fturevx1);
    printf("x2: %f\n",x3);
    printf("\n");
    x3=x1-fx1/fturevx1;
    while(fabs(x3-x1)>epsilon){
        x1=x3;
        fx1=sonucuHesapla(&arrEl,x1);
        fturevx1=sonucuHesapla(&arrElTurev,x1);
        x3=x1-fx1/fturevx1;
        iteration++;
        printf("Iteration: %f\n",iteration+1);
        printf("x1: %f\n",x1);
        printf("f(x): %f\n",fx1);
        printf("f'(x): %f\n",fturevx1);
        printf("x2: %f\n",x3);
        printf("\n");
        if(iteration>MAX_ITERATION){
            printf("Maximum iteration reached.\n");
            printf("Bisection Method ile bulunan x degeri: %f\n",x3);
            return;
        }

    }

    printf("Newton Raphson Method ile bulunan x degeri: %f\n",x3);
}
void arrElcopy (struct arrEl* arrEl1,struct arrEl* arrEl2)
{
    int i;
    for(i=0;i<MAX_EL;i++){
        arrEl1->katsayi[i]=arrEl2->katsayi[i];
        arrEl1->tur[i]=arrEl2->tur[i];
        arrEl1->us[i]=arrEl2->us[i];
    }
}
void turevAl(struct arrEl* arrEl){
    int i;
    for(i=0;i<MAX_EL;i++){
        if(arrEl->tur[i]==0) {
            arrEl->katsayi[i] = arrEl->katsayi[i] * arrEl->us[i];
            arrEl->us[i]--;
            if (arrEl->us[i] == -1) {
                arrEl->us[i] = 0;
            }
        }
        else{
            arrEl->tur[i]=arrEl->tur[i]+10;
        }
    }
}
void arrElSifirla(struct arrEl* arrEl){
	int i;
	for(i=0;i<MAX_EL;i++){
		arrEl->katsayi[i]=0;
		arrEl->tur[i]=0;
		arrEl->us[i]=0;
	}
}
void regulaFalsiMethod() {
    struct arrEl arrEl;
    arrElSifirla(&arrEl);
    fonksiyonAl(&arrEl);
    float x1,x2,epsilon,eskix1,eskix2;
    printf("x1 giriniz: ");
    scanf(" %f",&x1);
    printf("x2 giriniz: ");
    scanf(" %f",&x2);
    printf("epsilon giriniz: ");
    scanf(" %f",&epsilon);
    float fx1,fx2,fx3,x3,n=2.0,iteration=1.0;
    fx1=sonucuHesapla(&arrEl,x1);
    fx2=sonucuHesapla(&arrEl,x2);
    if(fx1*fx2>0) {
        printf("Girdiginiz x1 ve x2 arasinda bir fonksiyon degeri 0 degil.\n");
        return;
    }
    eskix1=x1;
    eskix2=x2;
    while(fabs(eskix1-eskix2)>epsilon*n) {
        x3 = ((x2 * fx1) - (x1 * fx2)) / (fx1 - fx2);
        fx3 = sonucuHesapla(&arrEl, x3);
        printf("Start=%f|Sonuc=%f\nEnd=%f|Sonuc=%f\nMiddle=%f|Sonuc=%f\nIteration=%f\n\n", x1, fx1, x2, fx2, x3, fx3,
               iteration);

        if (fx3 == 0) {
            printf("Regula Falsi Method ile bulunan x degeri: %f\n", x3);
            return;
        }
        eskix1=x1;
        eskix2=x2;
        if (fx1 * fx3 <= 0) {
            x2 = x3;
            fx2 = fx3;
        } else {
            x1 = x3;
            fx1= fx3;
        }
        n = n * 2.0;
        iteration = iteration + 1.0;
        if(iteration>MAX_ITERATION){
            printf("Maximum iteration reached.\n");
            printf("Bisection Method ile bulunan x degeri: %f\n",x3);
            return;
        }
    }
    printf("Regula Falsi Method ile bulunan x degeri: %f\n",x3);
}
void bisectionMethod() {
    struct arrEl arrEl;
    arrElSifirla(&arrEl);
    fonksiyonAl(&arrEl);
    float x1,x2,epsilon,eskix1,eskix2;
    printf("x1 giriniz: ");
    scanf(" %f",&x1);
    printf("x2 giriniz: ");
    scanf(" %f",&x2);
    printf("epsilon giriniz: ");
    scanf(" %f",&epsilon);
    float x3;
    float n=1.0,iteration=0.0;
    float fx1,fx2,fx3;
    fx1=sonucuHesapla(&arrEl,x1);
    fx2=sonucuHesapla(&arrEl,x2);
    if(fx1*fx2>0) {
        printf("Girdiginiz x1 ve x2 arasinda bir fonksiyon degeri 0 degil.\n");
        return;
    }
    eskix1=x1;
    eskix2=x2;
    while(fabs(eskix2-eskix1)>epsilon*n) {
        x3=(x1+x2)/2;
        fx3=sonucuHesapla(&arrEl,x3);
        printf("Start=%f|Sonuc=%f\nEnd=%f|Sonuc=%f\nMiddle=%f|Sonuc=%f\nIteration=%f\n\n",x1,fx1,x2,fx2,x3,fx3,iteration+1);
        if(fx3==0) {
            printf("Bisection Method ile bulunan x degeri: %f\n",x3);
            return;
        }
        eskix1=x1;
        eskix2=x2;
        if(fx1*fx3<=0) {
            x2=x3;
            fx2=fx3;
        }
        else {
            x1=x3;
            fx1=fx3;
        }
        n=n*2.0;
        iteration=iteration+1.0;
        if(iteration>MAX_ITERATION){
            printf("Maximum iteration reached.\n");
            printf("Bisection Method ile bulunan x degeri: %f\n",x3);
            return;
        }
    }
    printf("Bisection Method ile bulunan x degeri: %f\n",x3);
}
void arrElYazdir(struct arrEl* arr){
	int i;
	for(i=0;i<MAX_EL;i++){
		printf("%f,%f,%f\n",arr->katsayi[i],arr->tur[i],arr->us[i]);
	}
}
float sonucuHesapla(struct arrEl* arrEl,float x)
{
    int elemanSayisi = MAX_EL;
    float sonuc=0;
    float elSonuc[MAX_EL],turevliSonuc[MAX_EL];
    int i;
    for(i=0;i<elemanSayisi;i++)
    {
        elSonuc[i]=arrEl->katsayi[i]*pow(x,arrEl->us[i]);
        turevliSonuc[i]=arrEl->katsayi[i]*arrEl->us[i]*pow(x,arrEl->us[i]-1);
        if(arrEl->tur[i]==0){
            sonuc=sonuc+elSonuc[i];
        }
        if(arrEl->tur[i]==1){
            sonuc=sonuc+sinf(elSonuc[i]);
        }
        if(arrEl->tur[i]==2){
            sonuc=sonuc+cosf(elSonuc[i]);
        }
        if(arrEl->tur[i]==3){
            sonuc=sonuc+tanf(elSonuc[i]);
        }
        if(arrEl->tur[i]==4){
            sonuc=sonuc+(1/tanf(elSonuc[i]));
        }
        if(arrEl->tur[i]==5){
            sonuc=sonuc+asinf(elSonuc[i]);
        }
        if(arrEl->tur[i]==6){
            sonuc=sonuc+acosf(elSonuc[i]);
        }
        if(arrEl->tur[i]==7){
            sonuc=sonuc+atanf(elSonuc[i]);
        }
        if(arrEl->tur[i]==8){
            sonuc=sonuc+(1/atanf(elSonuc[i]));
        }
        if(arrEl->tur[i]==9){
            sonuc=sonuc+logf(elSonuc[i]);
        }
        if(arrEl->tur[i]==10){
            sonuc=sonuc+expf(elSonuc[i]);
        }
        if(arrEl->tur[i]==11){
            sonuc=sonuc+cosf(elSonuc[i])*turevliSonuc[i];
        }
        if(arrEl->tur[i]==12){
            sonuc=sonuc+sinf(elSonuc[i])*turevliSonuc[i]*(-1);
        }
        if(arrEl->tur[i]==13){
            sonuc=sonuc+(tanf(elSonuc[i])*tanf(elSonuc[i])+1)*turevliSonuc[i];
        }
        if(arrEl->tur[i]==14){
            sonuc=sonuc+((1/tanf(elSonuc[i]))*(1/tanf(elSonuc[i]))+1)*turevliSonuc[i]*(-1);
        }
        if(arrEl->tur[i]==15){
            sonuc=sonuc+turevliSonuc[i]/sqrtf(1-elSonuc[i]*elSonuc[i]);
        }
        if(arrEl->tur[i]==16){
            sonuc=sonuc+turevliSonuc[i]/sqrtf(1-elSonuc[i]*elSonuc[i])*(-1);
        }
        if(arrEl->tur[i]==17){
            sonuc=sonuc+turevliSonuc[i]/(1+elSonuc[i]*elSonuc[i]);
        }
        if(arrEl->tur[i]==18){
            sonuc=sonuc+turevliSonuc[i]/(1+elSonuc[i]*elSonuc[i])*(-1);
        }
        if(arrEl->tur[i]==19){
            sonuc=sonuc+turevliSonuc[i]/elSonuc[i];
        }
        if(arrEl->tur[i]==20){
            sonuc=sonuc+turevliSonuc[i]*expf(elSonuc[i]);
        }
    }
    return sonuc;
}
void fonksiyonAl(struct arrEl* arrEl){
    char denklem[MAX_LENGTH];
    char elements[MAX_EL][MAX_LENGTH]={{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}};
    printf("Denklem girilme sekli:2x +3x^2 -4 \nsin,cos,tan,cot,arcsin,arccos,arctan,arccot,ln,eUzeri kelimeleriyle beraber bu yontemleri de kullanabilirsiniz\nOrnek=ln1x cos+1x sin+2x^3\nHer elemandan sonra 1 bosluk koyarak yaziniz\nEn fazla 10 element giriniz\nUs olarak en fazla 9 giriniz\nMaximum iterasyon sayisi:100\nx^2 yerine 1x^2 giriniz\n\n");
    printf("fonksiyonGiriniz:\n");
    gets(denklem);
    fonksiyonBol(denklem,elements);
    elementBol(elements,arrEl);
}
void fonksiyonBol(char denklem[],char elements[][MAX_LENGTH]){
    int i,j=0,k=0;
    for(i=0;i<MAX_LENGTH;i++){
        if(denklem[i]==' '){
            elements[j][k+1]=0;
            k=0;
            j++;
        }
        else{
            elements[j][k]=denklem[i];
            k++;
        }
    }
}

int returnPos(char element[MAX_LENGTH],char ch){
    int i=0;
    while(element[i]!=ch){
        if(i==MAX_LENGTH){
            return 0;
        }
        i++;
    }
    return i;
}//Returns false if there is no element
int returnCharTrue(char element[MAX_LENGTH],char x){
    int i=0;
    while(element[i]!=0){
        if(element[i]==x){
            return 1;
        }
        i++;
    }
    return 0;
}
int rst(char element[MAX_LENGTH],char x[MAX_LENGTH]){//return string true
    if(strstr(element,x)==NULL){
        return 0;
    }
    return 1;
}
void basaKaydir(char element[MAX_LENGTH],int kacKaydir){
    int i=0;
    while(element[i+kacKaydir]!=0){
        element[i]=element[i+kacKaydir];
        i++;
    }
    element[i]=0;
}
void elementBol(char elements[][MAX_LENGTH],struct arrEl* arrEl){
    //arrElements 0 katsayi 1 exponent 2 tur
    int i=0;
    while(elements[i][0]!=0) {
        //Takes sin/cos/ln side of an element
        if (rst(elements[i],"sin")) {
            arrEl->tur[i] = 1;
            basaKaydir(elements[i],3);
        }
        else if(rst(elements[i],"cos")){
            arrEl->tur[i] = 2;
            basaKaydir(elements[i],3);
        }
        else if(rst(elements[i],"tan")){
            arrEl->tur[i] = 3;
            basaKaydir(elements[i],3);
        }
        else if(rst(elements[i],"cot")){
            arrEl->tur[i] = 4;
            basaKaydir(elements[i],3);
        }
        else if(rst(elements[i],"arcsin")){
            arrEl->tur[i] = 5;
            basaKaydir(elements[i],6);
        }
        else if(rst(elements[i],"arccos")){
            arrEl->tur[i] = 6;
            basaKaydir(elements[i],6);
        }
        else if(rst(elements[i],"arctan")){
            arrEl->tur[i] = 7;
            basaKaydir(elements[i],6);
        }
        else if(rst(elements[i],"arccot")){
            arrEl->tur[i] = 8;
            basaKaydir(elements[i],6);
        }
        else if(rst(elements[i],"ln")){
            arrEl->tur[i] = 9;
            basaKaydir(elements[i],2);
        }
        else if(rst(elements[i],"eUzeri")){
            arrEl->tur[i] = 10;
            basaKaydir(elements[i],6);
        }
        else(arrEl->tur[i] = 0);
        //Takes x side of an element
        int xpos = returnPos(elements[i], 'x');
        int exPos = returnPos(elements[i], '^');
        int xvalue = returnCharTrue(elements[i],'x');
        int exValue = returnCharTrue(elements[i], '^');
        int artiPos = returnCharTrue(elements[i],'+');
        int eksiPos = returnCharTrue(elements[i],'-');
        int artiEksiPos = returnCharTrue(elements[i],'-') || returnCharTrue(elements[i],'+');
        if (!xvalue && !artiEksiPos) {
            arrEl->us[i] = atof(elements[i]);
            arrEl->us[i] = 0;
        } else if (!xvalue && artiEksiPos) {
            if(artiPos){arrEl->katsayi[i] = atof(elements[i]+1);}
            if(eksiPos){arrEl->katsayi[i] = -atof(elements[i]+1);}
            arrEl->us[i] = 0;

        } else if (xvalue && !artiEksiPos) {
            if (!exValue) {
                elements[i][xpos] = 0;
                arrEl->katsayi[i] = atof(elements[i]);
                arrEl->us[i] = 1;
            }
            else if (exValue) {
                elements[i][xpos] = 0;
                elements[i][exPos] = 0;
                arrEl->katsayi[i] = atof(elements[i]);
                arrEl->us[i] = elements[i][exPos + 1] - 48;
            }
        } else if (xvalue && artiEksiPos) {
            if (artiPos) {
                if (!exValue) {
                    elements[i][xpos] = 0;
                    arrEl->katsayi[i] = atof(elements[i]+1);
                    arrEl->us[i] = 1;
                }
                else if (exValue) {
                    elements[i][xpos] = 0;
                    elements[i][exPos] = 0;
                    arrEl->katsayi[i] = atof(elements[i]+1);
                    arrEl->us[i] = elements[i][exPos + 1] - 48;
                }
            }
            else if (eksiPos) {

                if (!exValue) {
                    elements[i][xpos] = 0;
                    arrEl->katsayi[i] = -atof(elements[i]+1);
                    arrEl->us[i] = 1;
                }
                else if (exValue) {
                    elements[i][xpos] = 0;
                    elements[i][exPos] = 0;
                    arrEl->katsayi[i] = -atof(elements[i]+1);
                    arrEl->us[i] = elements[i][exPos + 1] - 48;
                }
            }
        }
        printf("%d.eleman=%f %d.us=%f %d.Tur=%f\n",i+1,arrEl->katsayi[i],i+1,arrEl->us[i],i+1,arrEl->tur[i]);
        i++;
    }
}

//1x^3 -7x^2 +14x -6
