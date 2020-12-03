#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cilk/cilk.h>

void triangleFind(int rows[], int cols[], int nz, int N, int threadNo);
