//
//  main.c
//  Heat-Equation
//
//  Created by Xiaobo Sun on 5/12/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "common.h"

#define INIT_FUNC_NUM 4

int printMenu(char* funcNames[]);
void Ut0( double (*f)(double x, double y), double U[Y_N][X_N]);
void writeUtoFile(char* fileName, double U[Y_N][X_N]);

/*************************************************************
 *              main starts from here
 **************************************************************/
int main(int argc, const char * argv[])
{
    char* outputFile = "output/data";
    
    int t = 0;
    double U[Y_N][X_N], newU[Y_N][X_N];
    
    // store different inital functions
    double (*initFuncs[])(double x, double y) = {
        initFunc1,
        initFunc2,
        initFunc3,
        initFunc4
    };
    char* funcNames[] = {
        "u(x,y,0) = N(N+1)/cosh(x-20)^2\t\tN = 0.25",
        "u(x,y,0) = N(N+1)/cosh(x-20)^2\t\tN = 1",
        "u(x,y,0) = (c/2)/cosh2(√c/2 * (x-20))\tc = 10",
        "u(x,y,0) = (c1/2)/cosh2(√c1/2 * (x-10)+(c2/2)/cosh2(√c2/2 * (x-20))"
    };
    
    int useFunc = printMenu(funcNames);
    
    // start processing
    printf("processing: %%0");
    fflush(stdout);
    time_t startTime;
    time(&startTime);
    
    // get inital u
    Ut0(initFuncs[useFunc], U);
    
    // write first frame data
    char fileName[20];
    sprintf(fileName, "%s-%d", outputFile, 0);
    writeUtoFile(fileName, U);
    
    int onePercent = T_N / 100;
    for(t = 1; t < T_N; t++)
    {
        Runge_Kutta(rhsFunc, U, newU);
        
        // save data into file for every specific steps
        if( t % T_STEPS_PER_FILE == 0)
        {
            char fileName[20];
            sprintf(fileName, "%s-%d", outputFile, t / T_STEPS_PER_FILE);
            writeUtoFile(fileName, newU);
        }
        
        // show progress
        if( t % onePercent == 0)
        {
            printf("\rprocessing: %%%d", t / onePercent);
            fflush(stdout);
        }
        
        // update U
        vector_copy(newU, U);
    }
    
    // create plot script
    createPlotScript("animate.plt", useFunc);
    
    // end processing
    time_t endTime;
    time(&endTime);
    printf("\rprocessing:100%%\n");
    printf("process time: %.3f secs\n", difftime(endTime, startTime));
    printf("Please run \"gnuplot animate.plt\" to show the result\n\n");
    
    return 0;
}

int printMenu(char* funcNames[])
{
    int i;
    
    printf("choose inital function:\n");
    printf("***********************************************************\n");
    for(i=0; i<INIT_FUNC_NUM; i++)
    {
        printf("%d  %s\n", i, funcNames[i]);
    }
    printf("***********************************************************\n");
    printf("Enter number:");
    return 0;
    int result;
    while(1)
    {
        result = getchar();
        if(result == '\n')
        printf("Enter number:");
        
        else
        {
            result -= '0';
            if(result >= 0 && result < INIT_FUNC_NUM)
            break;
        }
    }
    
    return result;
    
}

/*************************************************************
 *               get inital data vector
 * f: initial function
 **************************************************************/
void Ut0( double (*f)(double x, double y), double U[Y_N][X_N])
{
    for(int y = 0; y < Y_N; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            U[y][x] = (*f)(x * DELTA_X, y * DELTA_Y );
        }
    }
}

/*************************************************************
 *           write one frame of data U to file
 **************************************************************/
void writeUtoFile(char* fileName, double U[Y_N][X_N])
{
    FILE * file = fopen(fileName, "w");
    
    for(int y = 0; y < Y_N; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            fprintf(file, "%g %g %g\n", x * DELTA_X , y * DELTA_Y, U[y][x]);
        }
    }

    fclose(file);
}

