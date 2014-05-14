//
//  plot_script.c
//  Project1
//
//  Created by Xiaobo Sun on 4/12/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include "common.h"

int createPlotScript(char* fileName, int type)
{
    FILE* f = fopen(fileName, "w");
    if(f == NULL)
    {
        return -1;
    }
    
    // y range when ploting
    float yRange = 0.35;
    switch(type)
    {
        case 0:
            yRange = 2.5;
            break;
        case 1:
            yRange = 5;
            break;
        case 2:
            yRange = 10;
            break;
        case 3:
            yRange = 6;
            break;
        default:
            break;
    }
    
    // file number
    int fileNum = T_N / T_STEPS_PER_FILE - 1;
    fprintf(f, "if (exist(\"n\")==0 || n<0) n=0\n");
    fprintf(f, "splot [0:%f] [0:%f] [0:%f] sprintf(\"output/data-%%d\", n) with pm3d", X_N * DELTA_X, Y_N * DELTA_Y, yRange);
    fprintf(f, " title sprintf(\"time:%%f\", n * %f)\n",  DELTA_T * T_STEPS_PER_FILE);
    fprintf(f,"if (n<%d) n=n+1; pause 0.01; reread\n", fileNum);
    fprintf(f,"n=-1\n");
    
    fclose(f);
    
    return 0;
    
    
}