#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <omp.h>

void triangleFind(int rows[], int cols[], int nz, int N, int threadNo);
