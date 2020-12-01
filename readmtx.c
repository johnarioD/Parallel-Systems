#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"
#include "triangleFind.h"
#include <sys/resource.h>
#include <vector>

/*
* This part of the code is responcible for
* reading the adjacency matrix of our graph.
* It is not required for V3 or V4 to run
* as long as there corresponding functions
* are provided with the correct arguments.
*/

int main(int argc, char *argv[])
{
  const rlim_t kStackSize = 32 * 1024 * 1024;   //We allocate 32MB of stack to avoid overflows for larger graphs
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);

  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              fprintf(stderr, "setrlimit returned result = %d\n", result);
          }
      }
  }

  int ret_code;
  MM_typecode matcode;
  FILE *f;
  int M, N, nz;
  int i, *I, *J;

  if (argc < 2)	{
		fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
		exit(1);
	} else  {
      if ((f = fopen(argv[1], "r")) == NULL)
          exit(1);
  }

  if (mm_read_banner(f, &matcode) != 0)  {
      printf("Could not process Matrix Market banner.\n");
      exit(1);
  }

  if (mm_is_complex(matcode) && mm_is_matrix(matcode) &&
          mm_is_sparse(matcode) ) {
      printf("Sorry, this application does not support ");
      printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
      exit(1);
  }

  if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nz)) !=0) exit(1);

  if(M!=N){
    printf("\nYou did not input a graph\n");
    return 1;
  }

  //mm_write_banner(stdout, matcode);
  printf("\n");
  mm_write_mtx_crd_size(stdout, M, N, nz);

  std::vector<std::vector<int>> vec(N);
  int *cols = (int *) malloc(2 * nz * sizeof(int));
  int *rows = (int *) malloc((N+1) * sizeof(int));

  I = (int *) malloc(nz * sizeof(int));
  J = (int *) malloc(nz * sizeof(int));

  for(i=0; i < nz; i++){
    fscanf(f, "%d %d\n", &I[i], &J[i]);
    I[i]--;
    J[i]--;
    rows[I[i]+1]++;
    rows[J[i]+1]++;
  }

  if (f !=stdin) fclose(f);

  for(i=1; i < N+1; i++){
    rows[i] += rows[i-1];
  }

  for(i = 0; i< nz; i ++){
    vec[I[i]].push_back(J[i]);
    vec[J[i]].push_back(I[i]);
  }

  for(i = 0; i < N+1; i++){
    for(int j = 0; j < rows[i+1]-rows[i];j++){
      cols[rows[i]+j] = vec[i][j];
    }
  }

  //calcV2(A,N);
  //calcV3(rows,cols,2*nz,N);
  //calcV3cilk(rows,cols,2*nz,N);
  //calcV3open(rows,cols,2*nz,N);
  calcV4(rows,cols,2*nz,N);
  calcV4cilk(rows,cols,2*nz,N);
  calcV4open(rows,cols,2*nz,N,4);
  calcV4thread(rows,cols,2*nz,N,4);
  free(I);
  free(J);
return 0;
}

/*int **A;
A = new int *[N];
for(int i = 0; i < N; i++){
  A[i] = new int[N];
  for(int j = 0; j < N; j++){
    A[i][j]=0;
  }
}

for(int i = 0; i < nz; i++){
  A[I[i]][J[i]] = val[i];
  A[J[i]][I[i]] = val[i];
}*/

/*for(int i = 0; i < N; i++){
  printf("\n");
  for(int j = 0; j < N; j++){
    printf("%d ",A[i][j]);
  }
}*/
