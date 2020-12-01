#include "triangleFind.h"

using namespace std;

stack<int> s;
struct data{
  int *rows;
  int *cols;
  int *triangles;
} arg;
mutex mtx;

void calcV3(int rows[], int cols[], int nz, int N){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into V3 serial\n");

  for(int i = 0; i < N; i++){
    for(int j = rows[i]; j < rows[i+1]; j++){
      if(cols[j]!=i){
        for(int k = rows[cols[j]]; k < rows[cols[j]+1]; k++){
          for(int l = rows[cols[k]]; l < rows[cols[k]+1]; l++){
            if(cols[l]==i){
              triangles[i]++;
            }
          }
        }
      }
    }
    triangles[i]=triangles[i]/2;
  }


  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  int counter = 0;
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with V3 serial\n",counter);
  /*for(int i = N; i < N; i++){
    printf("%d ", triangles[i]);
  }*/
  printf("\nSerial V3 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));

}

void calcV3cilk(int rows[], int cols[], int nz, int N){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into V3 cilk\n");

  cilk_for(int i = 0; i < N; i++){
    for(int j = rows[i]; j < rows[i+1]; j++){
      if(cols[j]!=i){
        for(int k = rows[cols[j]]; k < rows[cols[j]+1]; k++){
          for(int l = rows[cols[k]]; l < rows[cols[k]+1]; l++){
            if(cols[l]==i){
              triangles[i]++;
            }
          }
        }
      }
    }
    triangles[i]=triangles[i]/2;
  }


  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  int counter = 0;
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with V3 cilk\n",counter);
  /*for(int i = 0; i < N; i++){
    printf("%d ", triangles[i]);
  }*/
  printf("\nCilk V3 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
}

void calcV3open(int rows[], int cols[], int nz, int N){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into V3 openMP\n");

  #pragma omp parallel for
  for(int i = 0; i < N; i++){
    for(int j = rows[i]; j < rows[i+1]; j++){
      if(cols[j]!=i){
        for(int k = rows[cols[j]]; k < rows[cols[j]+1]; k++){
          for(int l = rows[cols[k]]; l < rows[cols[k]+1]; l++){
            if(cols[l]==i){
              triangles[i]++;
            }
          }
        }
      }
    }
    triangles[i]=triangles[i]/2;
  }

  clock_gettime(CLOCK_MONOTONIC, &ts_end);
  int counter = 0;
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with V3 openMP\n",counter);
  /*for(int i = 0; i < N; i++){
    printf("%d ", triangles[i]);
  }*/
  printf("\nOpenMP V3 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
}

void calcV4(int rows[],int cols[],int nz,int N){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into serial V4\n");

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
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with serial V4\n",counter);
  /*for(int i = 0; i < N; i++){
    printf("%d ", triangles[i]);
  }*/
  printf("\nSerial V4 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
}

void calcV4cilk(int rows[],int cols[],int nz,int N){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into cilk V4\n");

  int common[N] = {0};
  cilk_for(int i = 0; i < N; i++){
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
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with cilk V4\n",counter);
  /*for(int i = 0; i < N; i++){
    printf("%d ", triangles[i]);
  }*/
  printf("\nCilk V4 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
}

void calcV4open(int rows[],int cols[],int nz,int N, int threadNo){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};
    omp_set_num_threads(threadNo);

  clock_gettime(CLOCK_MONOTONIC, &ts_start);

  printf("\nGetting into OpenMP V4\n");

  #pragma omp parallel for
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
  for(int i = 0; i < N; i++){
    counter+=triangles[i];
  }
  printf("\n%d triangles found with OpenMP V4\n",counter);
  /*for(int i = 0; i < N; i++){
    printf("%d ", triangles[i]);
  }*/
  printf("\nOpenMP V4 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
}

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

void calcV4thread(int rows[],int cols[],int nz,int N,int threadNo){
  struct timespec ts_start;
  struct timespec ts_end;

  int triangles[N] = {0};
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
  printf("\n%d triangles found with thread V4\n",counter);
  /*for(int i = 0; i < N; i++){
    printf("%d ", arg.triangles[i]);
  }*/
  printf("\nThread V4 time: %ld.%ld sec\n", (ts_end.tv_sec - ts_start.tv_sec), (abs(ts_end.tv_nsec = ts_start.tv_nsec)));
}
