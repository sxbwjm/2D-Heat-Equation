//
//  Runge_Kutta.c
//  Project1
//
//  Created by Xiaobo Sun on 4/5/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include "common.h"

/*************************************************************
 *          Runge–Kutta 4th-Order Method
 *
 * solve the following ordinary differential equations:
 *    u' = f(u)
 *
 * f:  function pointer of f in the above equation
 * u:  initial value (array)
 * h:  step size
 *
 * returns next frame of u
 *************************************************************/
void Runge_Kutta(void (*f)(double u[], double newU[]),
                   double u[], double newU[])
{
    double h = DELTA_T;
    
    double k1[X_N], k2[X_N], k3[X_N], k4[X_N];
    double tmp1[X_N], tmp2[X_N];

    // k1 = f(u)
    (*f)(u, k1);
    
    // k2 = f(u + k1 * h / 2)
    vector_mul_const(tmp1, k1, h / 2, X_N);
    vector_add(tmp2, u, tmp1, X_N);
    (*f)(tmp2, k2);
    
    // k3 = f(u + k2 * h / 2)
    vector_mul_const(tmp1, k2, h / 2, X_N);
    vector_add(tmp2, u, tmp1, X_N);
    (*f)(tmp2, k3);
    
    // k4 = f(u + k3 * h)
    vector_mul_const(tmp1, k3, h, X_N);
    vector_add(tmp2, u, tmp1, X_N);
    (*f)(tmp2, k4);
        
    vector_init(newU, X_N);
    
    vector_mul_const(k2,  k2, 2, X_N);    // k2 = 2 * k2
    vector_mul_const(k3,  k3, 2, X_N);    // k3 = 2 * k3

    vector_add(tmp1, k1, k2, X_N);        // k1 + 2 * k2
    vector_add(tmp1, tmp1, k3, X_N);      // k1 + 2 * k2 + 2 * k3
    vector_add(tmp1, tmp1, k4, X_N);      // k1 + 2 * k2 + 2 * k3 + k4
    
    // tmp1 = (k1 + 2 * k2 + 2 * k3 + k4) * h / 6
    h = h / 6;
    vector_mul_const(tmp1, tmp1, h, X_N);
    
    vector_add(newU, u, tmp1, X_N);

}