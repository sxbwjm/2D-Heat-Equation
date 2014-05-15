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
#include <mpi.h>
#include "common.h"

#define INIT_FUNC_NUM 3

int printMenu(char* funcNames[]);
void decideBlock();
void Ut0( double (*f)(double x, double y), double U[Y_N][X_N]);
void writeUtoFile(char* fileName, double U[Y_N][X_N]);

/*************************************************************
 *              main starts from here
 **************************************************************/
int main(int argc, char * argv[])
{
    char* outputFile = "output/data";
    
    int t = 0;
    double U[Y_N][X_N], newU[Y_N][X_N];
    
    // store different inital functions
    double (*initFuncs[])(double x, double y) = {
        initFunc1,
        initFunc2,
        initFunc3
    };
    char* funcNames[] = {
        "one hot spot - type 1",
        "one hot spot - type 2",
        "two hot spots"
    };
    

    // init mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &glbRank);
    MPI_Comm_size(MPI_COMM_WORLD, &glbSize);
    
    // decide inital func (only process 0 asks input)
    int useFunc = 0;
    if( glbRank == 0)
    {
        useFunc = printMenu(funcNames);
    }
    
    // broadcast decision to other processes
    MPI_Bcast(&useFunc, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    // decide process's own block (y range)
    decideBlock();
    
    // start processing (only process 0 print progress)
    if( glbRank == 0)
    {
        printf("processing: %%0");
    }
    fflush(stdout);
    time_t startTime;
    time(&startTime);
    
    // get inital u
    Ut0(initFuncs[useFunc], U);
    
    // write first frame data
    char fileName[20];
    sprintf(fileName, "%s-%d-%d", outputFile, glbRank, 0);
    writeUtoFile(fileName, U);
    
    int onePercent = T_N / 100;
    for(t = 1; t < T_N; t++)
    {
        Runge_Kutta(rhsFunc, U, newU);
        
        // save data into file for every specific steps
        if( t % T_STEPS_PER_FILE == 0)
        {
            char fileName[20];
            sprintf(fileName, "%s-%d-%d", outputFile, glbRank, t / T_STEPS_PER_FILE);
            writeUtoFile(fileName, newU);
        }
        
        // show progress
        if( t % onePercent == 0 && glbRank == 0)
        {
            printf("\rprocessing: %d%%", t / onePercent);
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
    
    if( glbRank == 0)
    {
        printf("\rprocessing:100%%\n");
        printf("process time: %.3f secs\n", difftime(endTime, startTime));
        printf("Please run \"gnuplot animate.plt\" to show the result\n\n");
    }
    
    MPI_Finalize();
    
    return 0;
}

/*************************************************************
 *              print menu
 * ask input for initial function 
 **************************************************************/
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
    fflush(stdout);
    int result;
    while(1)
    {
        result = getchar();
        if(result == '\n')
        {
            printf("Enter number:");
            fflush(stdout);
        }
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
 *              decide block boundary
 * get start row and end row of the block for current proccess
 **************************************************************/
void decideBlock()
{
    int blocks = Y_N / glbSize;
    
    glbYStart = glbRank * blocks;
    
    if( glbRank < glbSize - 1)
    {
        glbYEnd = (glbRank + 1) * blocks;
    }
    // last process do all of the rest work
    else
    {
        glbYEnd = Y_N;
    }
    
}

/*************************************************************
 *               get inital data vector
 * f: initial function
 **************************************************************/
void Ut0( double (*f)(double x, double y), double U[Y_N][X_N])
{
    for(int y = glbYStart; y < glbYEnd; y++)
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
    
    for(int y = glbYStart; y < glbYEnd; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            fprintf(file, "%g %g %g\n", x * DELTA_X , y * DELTA_Y, U[y][x]);
        }
        fprintf(file,"\n");
    }

    fclose(file);
}

