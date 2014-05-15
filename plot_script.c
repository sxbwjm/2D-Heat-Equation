//
//  plot_script.c
//  Project1
//
//  Created by Xiaobo Sun on 4/12/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include "common.h"

/*************************************************************
 *   create gnuplot script for ploting result in animation
 **************************************************************/
int createPlotScript(char* fileName, int type)
{
    FILE* f = fopen(fileName, "w");
    if(f == NULL)
    {
        return -1;
    }
    
    // range when ploting
    float xRange = X_N * DELTA_X;
    float yRange = Y_N * DELTA_Y;
    float zRange = 2.5;
    switch(type)
    {
        case 0:
            zRange = 2.5;
            break;
        case 1:
            zRange = 5;
            break;
        case 2:
            zRange = 10;
            break;
        default:
            break;
    }
    
    // file number
    int fileNum = T_N / T_STEPS_PER_FILE - 1;
    float deltaTime = DELTA_T * T_STEPS_PER_FILE;
    
    // init
    fprintf(f, "if (exist(\"n\")==0 || n<0) n=0\n");
    // set ranges
    fprintf(f, "set xrange [0:%f]\n", xRange);
    fprintf(f, "set yrange [0:%f]\n", yRange);
    fprintf(f, "set zrange [0:%f]\n", zRange);
    fprintf(f, "set cbrange [0:%f]\n", zRange);
    // plot
    
    fprintf(f, "splot sprintf(\"< cat ");
    for(int i = 0; i < glbSize; i++)
    {
        fprintf(f, "output/data-%d-%%d ", i);
    }
    
    fprintf(f, "\"");
    
    for(int i = 0; i < glbSize; i++)
    {
        fprintf(f, ",n");
    }
    
    fprintf(f, ") with pm3d");
    fprintf(f, " title sprintf(\"time:%%f\", n * %f)\n", deltaTime);
    
    // loop
    fprintf(f,"if (n<%d) n=n+1; pause 0.01; reread\n", fileNum);
    fprintf(f,"n=-1\n");
    
    fclose(f);
    
    return 0;
    
    
}