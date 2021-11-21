//Se encuentran las librerías utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"

//Se define el número de threads
#define NUM_THREADS 1

int main()
{
    //Se definen todas las variables a usar
    omp_set_num_threads(NUM_THREADS);
    FILE *image, *outputImage, *lecturas;
    const double startTime = omp_get_wtime();
    image = fopen("f3.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("f3_b.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    int num_line=0;
    int cont=0;
    int beg_line=0;
    int end_line=ancho;
    int partial=0;
    int x=1;
    int w_k = 13; //espacio para que la ventana entre completa
    unsigned char r, g, b;               //Pixel
    unsigned char* ptr;
    unsigned char* res;
    unsigned char xx[54];
    int cuenta = 0;

    
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    //Se reserva memoria para la imagen de entrada y de salida
    ptr = (unsigned char*)malloc(alto*ancho*3*sizeof(unsigned char));
    res = (unsigned char*)malloc(alto*ancho*3*sizeof(unsigned char));
    
    while(!feof(image)){
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);

    //Se lleva a cabo la conversión a escala de grises
      unsigned char pixel =0.3*r+0.59*g+0.1*b;;

      ptr[cuenta] = pixel; //b

      cuenta++;
    }  
    //Se definen las fronteras para que la ventana del filtro de media pueda entrar completa
      for(int i=0; i<(alto*ancho); i++){
        if(num_line<=w_k || num_line>=(alto-w_k) || i<=(beg_line+w_k) || i>=(end_line-w_k)){
          res[i] = ptr[i];
        }else{
        //Se lleva a cabo la suma y promedio de los pixeles de la ventana del filtro
          for(int h = -w_k; h <= w_k ; h++){
            x = i+(ancho*h); 
            partial= partial + ( ptr[i - 13] + ptr[i - 12]+ ptr[i - 11] + ptr[i - 10] + ptr[i - 9]+ ptr[i - 8] + ptr[i - 7] + ptr[i - 6]+ ptr[i - 5] + ptr[i - 4] + ptr[i - 3] + ptr[i - 2] +  ptr[i - 1] + ptr[i] + ptr[i + 13] + ptr[i + 12]+ ptr[i + 11] + ptr[i + 10] + ptr[i + 9]+ ptr[i + 8] + ptr[i + 7] + ptr[i + 6]+ ptr[i + 5] + ptr[i + 4] + ptr[i + 3] + ptr[i + 2] +  ptr[i + 1]);
            //partial= partial + (ptr[i - 7] + ptr[i - 6]+ ptr[i - 5] + ptr[i - 4] + ptr[i - 3] + ptr[i - 2] +  ptr[i - 1] + ptr[i] + ptr[i + 7] + ptr[i + 6]+ ptr[i + 5] + ptr[i + 4] + ptr[i + 3] + ptr[i + 2] +  ptr[i + 1]);
            //partial= partial + (ptr[i - 21] + ptr[i - 20] + ptr[i - 19] + ptr[i - 18]+ ptr[i - 17] + ptr[i - 16]+ptr[i - 15] + ptr[i - 14] + ptr[i - 13] + ptr[i - 12]+ ptr[i - 11] + ptr[i - 10] + ptr[i - 9]+ ptr[i - 8] + ptr[i - 7] + ptr[i - 6]+ ptr[i - 5] + ptr[i - 4] + ptr[i - 3] + ptr[i - 2] +  ptr[i - 1] + ptr[i] + ptr[i + 21] + ptr[i + 20] + ptr[i + 19] + ptr[i + 18]+ ptr[i + 17] + ptr[i + 16] + ptr[i + 15] + ptr[i + 14] + ptr[i + 13] + ptr[i + 12]+ ptr[i + 11] + ptr[i + 10] + ptr[i + 9]+ ptr[i + 8] + ptr[i + 7] + ptr[i + 6]+ ptr[i + 5] + ptr[i + 4] + ptr[i + 3] + ptr[i + 2] +  ptr[i + 1]);
            //partial= partial + (ptr[i - 32] + ptr[i - 31] + ptr[i - 30] + ptr[i - 29] + ptr[i - 28] + ptr[i - 27]+ ptr[i - 26] + ptr[i - 25] + ptr[i - 24]+ ptr[i - 23] + ptr[i - 22] + ptr[i - 21]+ ptr[i - 20] + ptr[i - 19] + ptr[i - 18] +ptr[i - 17] + ptr[i - 16] + ptr[i - 15] + ptr[i - 14] + ptr[i - 13] + ptr[i - 12]+ ptr[i - 11] + ptr[i - 10] + ptr[i - 9]+ ptr[i - 8] + ptr[i - 7] + ptr[i - 6]+ ptr[i - 5] + ptr[i - 4] + ptr[i - 3] + ptr[i - 2] +  ptr[i - 1] + ptr[i] + ptr[i + 32] + ptr[i + 31] + ptr[i + 30] + ptr[i + 29] + ptr[i + 28] + ptr[i + 27]+ ptr[i + 26] + ptr[i + 25] + ptr[i + 24]+ ptr[i + 23] + ptr[i + 22] + ptr[i + 21]+ ptr[i + 20] + ptr[i + 19] + ptr[i + 18] +ptr[i + 17] + ptr[i + 16] + ptr[i + 15] + ptr[i + 14] + ptr[i + 13] + ptr[i + 12]+ ptr[i + 11] + ptr[i + 10] + ptr[i + 9]+ ptr[i + 8] + ptr[i + 7] + ptr[i + 6]+ ptr[i + 5] + ptr[i + 4] + ptr[i + 3] + ptr[i + 2] +  ptr[i + 1]);
          }
          //res[i] = partial / 225; //Ventana de 15X15
          res[i] = partial / 729; //Ventana de 27X27
          //res[i] = partial / 1849; //Ventana de 43X43
          //res[i] = partial / 4225; //Ventana de 65X65
          partial=0;
        }
        cont=cont+1;
        if(cont==ancho){
          cont = 0;
          num_line++;
          beg_line = num_line*ancho;
          end_line = beg_line + (ancho);
        }
      }

    
    //Se imprime la imagen procesada
    #pragma omp parallel
    {
      #pragma omp for schedule(dynamic)
      for (int i = 0; i < alto*ancho*3; ++i) {
        fputc(res[i], outputImage);
        fputc(res[i], outputImage);
        fputc(res[i], outputImage);
      }
    }

    //Se libera el espacio solicitado
    const double endTime = omp_get_wtime();
    printf("tomo (%lf) segundos\n",(endTime - startTime));
    free(ptr);
    free(res);
    fclose(image);
    fclose(outputImage);
    return 0;
}