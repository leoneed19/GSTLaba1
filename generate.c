#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    int N,M,i,j;
    scanf("%d",&N);
    scanf("%d",&M);
    int A[N][M];
    int B[N];

   /* for (i  = 0; i < N; i++ ) {
          //for (j = 0; j < M; j++) {
              //A[i][j] = 10 + rand() % (20 - 10 + 1);
              B[i] = 10 + rand() % (20 - 10 + 1);
              printf("%d ", B[i]);
          //}
          printf("\n");
    }
    printf("\n");
*/
    if ((file=fopen("../IN.txt","w"))==NULL) {
        printf("Невозможно открыть файл\n");
        exit(1);
    };
  /*  for (i = 0; i < N; i++) {
        //for (j = 0; j < M; j++){
        fwrite(B, sizeof(int), N, file);

        //}

    }*/

for (j = 0; j < N; j++) {


    for (i  = 0; i < M; i++ ) {
        //for (j = 0; j < M; j++) {
        //A[i][j] = 10 + rand() % (20 - 10 + 1);
        B[i] = 10 + rand() % (40 - 10 + 1);
        printf("%d ", B[i]);
        //}
        printf("\n");
    }
    printf("\n");

    for (i = 0; i < M; i++) {
        fprintf(file, "%i ", B[i]);
    }
    fprintf(file, "\n");
}

    fclose(file);
}