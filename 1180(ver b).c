#include <stdio.h>

int main (){

    int N;
    scanf("%d", &N);

    int x[N];

    for (int i = 0; i < N; i++){
        scanf("%d", &x[i]);
    }

    int *p =x;
    int menor= *p;
    int posicao=0;
    
    for(int i=0; i<N; i++){

        if(*(p+i)<menor){
            menor=(*p+i);
            posicao=i;
        }
    }

    printf("A menor valor é %i", menor);
    printf("A posicao deste é em: %i", posicao);
}
