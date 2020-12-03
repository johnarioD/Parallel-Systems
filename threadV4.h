#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>
#include <pthread.h>
#include <mutex>

void PrallelCode(void * unused);
void triangleFind(int rows[], int cols[], int nz, int N, int threadNo);
