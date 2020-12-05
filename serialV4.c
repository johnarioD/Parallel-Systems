#include "serialV4.h"

void triangleFind(int rows[], int cols[], int nz, int N, int threadNo){
  struct timespec ts_start;
  struct timespec ts_end;

  int *triangles = (int *)malloc(N * sizeof(int));
  for(int i = 0; i < N; i++){
    triangles[i]=0;
  }

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  //printf("\nGetting into serial V4\n");

  for(int i = 0; i < N; i++){
    for(int j = rows[i]; j < rows[i+1]; j++){

      int index1=rows[i];
      int index2=rows[cols[j]];
      while((index1<rows[i+1])&&(index2<rows[cols[j]+1])){
        if(cols[index1]<cols[index2]){
          index1++;
        } else if(cols[index1]>cols[index2]){
          index2++;
        } else{
          index1++;
          index2++;
          triangles[i]++;
        }
      }
    }
    triangles[i]=triangles[i]/2;
  }

  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  int counter = 0;
  /*for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with serial V4\n",counter/3);*/
  printf("%ld.%ld\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
  free(triangles);
}
