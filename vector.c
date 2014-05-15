//
//  vector.c
//  Project1
//
//  Created by Xiaobo Sun on 4/10/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include "common.h"

void vector_init(double result[Y_N][X_N])
{
    for(int y = glbYStart; y < glbYEnd; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            result[y][x] = 0.0;
        }
    }
}

void vector_add(double result[Y_N][X_N], double v1[Y_N][X_N], double v2[Y_N][X_N])
{
    for(int y = glbYStart; y < glbYEnd; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            result[y][x] = v1[y][x] + v2[y][x];
        }
    }
    
}

void vector_mul_const(double result[Y_N][X_N], double v1[Y_N][X_N], double k)
{
    for(int y = glbYStart; y < glbYEnd; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            result[y][x] = v1[y][x] * k;
        }
    }
}

void vector_copy(double src[Y_N][X_N], double dest[Y_N][X_N])
{
    for(int y = glbYStart; y < glbYEnd; y++)
    {
        for(int x = 0; x < X_N; x++)
        {
            dest[y][x] = src[y][x];
        }
    }

}
