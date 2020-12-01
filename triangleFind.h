#pragma once
#include <time.h>
#include <cilk/cilk.h>
#include <iostream>
#include <omp.h>
#include <pthread.h>
#include <stack>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>

void progress(int i, int N);
void calcV3(int rows[], int cols[], int nz, int N);
void calcV3cilk(int rows[], int cols[], int nz, int N);
void calcV3open(int rows[], int cols[], int nz, int N);
void calcV4(int rows[],int cols[],int nz,int N);
void calcV4cilk(int rows[],int cols[],int nz,int N);
void calcV4open(int rows[],int cols[],int nz,int N,int threadNo);
void calcV4thread(int rows[],int cols[],int nz,int N,int threadNo);
