#include "ompV3.h"

using namespace std;

void triangleFind(int rows[], int cols[], int nz, int N, int threadNo){
  struct timespec ts_start;
  struct timespec ts_end;

  int i;
  int *triangles = (int *)malloc( N * sizeof(int));
  for(i = 0; i < N; i++){
    triangles[i]=0;
  }

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into V3 serial\n");

  #pragma omp parallel for private(i)
  for(i = 0; i < N; i++){
    for(int j = rows[i]; j < rows[i+1]; j++){
      if(cols[j]>i){
        for(int k = rows[cols[j]]; k < rows[cols[j]+1]; k++){
          if(cols[k]>cols[j]){
            for(int l = rows[cols[k]]; l < rows[cols[k]+1]; l++){
              if(cols[l]==i){
                triangles[i]++;
              }
            }
          }
        }
      }
    }
  }

  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  int counter = 0;
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with V3 serial\n",counter);
  printf("\nSerial V3 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
  free(triangles);

}
