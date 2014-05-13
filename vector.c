//
//  vector.c
//  Project1
//
//  Created by Xiaobo Sun on 4/10/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>

void vector_init(double result[Y_N][X_N])
{
    for(int i=0; i < Y_N; i++)
    {
        for(int j=0; j < X_N; j++)
        {
            result[i] = 0.0;
        }
    }
}
void vector_add(double result[], double v1[], double v2[], int size)
{
    for(int i=0; i < size; i++)
    {
        result[i] = v1[i] + v2[i];
    }
}

void vector_mul_const(double result[], double v1[], double k, int size)
{
    for(int i=0; i < size; i++)
    {
        result[i] = v1[i] * k;
    }
}

void vector_copy(double src[], double dest[], int size)
{
    for(int i=0; i < size; i++)
    {
        dest[i] = src[i];
    }
}
