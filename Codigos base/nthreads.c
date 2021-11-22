#include <stdio.h>
#include <math.h>
#include <time.h>
#include<omp.h>

int mat1[600][600];
int mat2[600][600];
int producto[600][600];

int main()
{
    int NUM_THREADS = 1;
    while (NUM_THREADS <= 899)
    {
    const double startTime = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    printf("Numero de THREADS: %d. ", NUM_THREADS);
    for (int i = 0; i < 600; i++) {
        for (int j = 0; j < 600; j++) {
            mat1[i][j] = j + 1 ;
            mat2[i][j] = j + 1 ;
        }
    }  
    
    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
            for (int a = 0; a < 600; a++) {
                for (int i = 0; i < 600; i++) {
                    int sum = 0;
                    for (int j = 0; j < 600; j++) {
                        sum += mat1[i][j] * mat2[j][a];
                    }
                    
                    producto[i][a] = sum;
                }
            }
            
            int id = omp_get_thread_num();
            // data of interest {a0,100},{a10,200},{a20,300},{a30,400},{a40,500},{a500,500}
           /* printf("Imprimiendo resultados %d \n", id);
            printf("res on [0][100] = %d \n", producto[0][100]);
            printf("res on [10][200] = %d \n", producto[10][200]);
            printf("res on [20][300] = %d \n", producto[20][300]);
            printf("res on [30][400] = %d \n", producto[30][400]);
            printf("res on [40][500] = %d \n", producto[40][500]);
            printf("res on [500][500] = %d \n", producto[500][500]);c
            */
    }
    const double endTime = omp_get_wtime();
    printf("tomo (%lf) segundos\n", (endTime - startTime));
    
    if(NUM_THREADS < 100 && NUM_THREADS >=10){
        NUM_THREADS = NUM_THREADS + 9;
    }
    if (NUM_THREADS >= 100)
        {
            NUM_THREADS = NUM_THREADS + 100 - 1;
        }
        if (NUM_THREADS > 99 && NUM_THREADS < 9)
        {
            //NUM_THREADS = NUM_THREADS * 10 - 1;
        }
        else
        {
            NUM_THREADS++;
        }
    }
}