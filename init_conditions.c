//
//  InitConditions.c
//  Project1
//
//  Created by Xiaobo Sun on 4/11/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "common.h"

/*************************************************************
 *               functions for inital condition
 **************************************************************/

// u(x,y,0) = (c/2)/cosh^2(√c/2 * (x-2.5))
double initFunc1(double x, double y)
{
    double c = 5 ;
    double tmp = cosh( sqrt(c) * (x-2.5) / 2);
    return c / (tmp * tmp) / 2;
}

// u(x,y,0) = (c/2)/cosh^2(√c/2 * (r-2.5))
double initFunc2(double x, double y)
{
    x = x - 2.5;
    y = y - 2.5;
    
    double r = sqrt( x * x + y * y);
    double c = 10 ;
    double tmp = cosh( sqrt(c) * r / 2);
    return c / (tmp * tmp) / 2;
}

double initFunc3(double x, double y)
{
    double x1 = x - 1.5;
    double y1 = y - 1.5;
    
    double x2 = x - 3.0;
    double y2 = y - 3.0;
    
    double r1 = sqrt( x1 * x1 + y1 * y1);
    double c1 = 20 ;
    double tmp1 = cosh( sqrt(c1) * r1 / 2);
    
    double r2 = sqrt( x2 * x2 + y2 * y2);
    double c2 = 10 ;
    double tmp2 = cosh( sqrt(c2) * r2 / 2);

    return c1 / (tmp1 * tmp1) / 2 +
           c2 / (tmp2 * tmp2) / 2;
}
