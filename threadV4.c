#include "threadV4.h"

using namespace std;

stack<int> s;
struct data{
  int *rows;
  int *cols;
  int *triangles;
} arg;
mutex mtx;

void *ParallelCode(void * unused){
  int i;
  while(!s.empty()){

    mtx.lock();
    i = s.top();
    s.pop();
    mtx.unlock();

    for(int j = arg.rows[i]; j < arg.rows[i+1]; j++){
      int index1 = arg.rows[i];
      int index2 = arg.rows[arg.cols[j]];
      while((index1 < arg.rows[i+1])
          &&(index2 < arg.rows[arg.cols[j]+1]))
          {
          if(arg.cols[index1]<arg.cols[index2]){
            index1++;
          } else if(arg.cols[index1]>arg.cols[index2]){
            index2++;
          } else{
            index1++;
            index2++;
            arg.triangles[i]++;
          }
      }
    }
    arg.triangles[i]=arg.triangles[i]/2;
  }
  pthread_exit(NULL);
}

void triangleFind(int rows[], int cols[], int nz, int N, int threadNo){
  struct timespec ts_start;
  struct timespec ts_end;

  int *triangles = (int *)malloc(N * sizeof(N));
  for(int i = 0; i < N; i++){
    triangles[i]=0;
  }
  pthread_t threads[threadNo];

  for(int i = 0; i < N+1; i++){
    s.push(i);
  }
  arg.rows = rows;
  arg.cols = cols;
  arg.triangles = triangles;

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into thread V4\n");

  for(int t = 0; t < threadNo; t++){
    pthread_create(&threads[t], NULL, ParallelCode, NULL);
  }

  for(int t = 0; t < threadNo; t++){
    pthread_join(threads[t],NULL);
  }


  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  int counter = 0;
  for(int i = 0; i < N; i++){
    counter+=arg.triangles[i];
  }
  printf("\n%d triangles found with thread V4\n",counter/3);
  printf("\nThread V4 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
  free(triangles);
}
