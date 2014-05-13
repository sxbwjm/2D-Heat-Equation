//
//  common.h
//  Project1
//
//  Created by Xiaobo Sun on 4/10/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#ifndef Project1_common_h
#define Project1_common_h

#define X_N 400
#define Y_N 600
#define DELTA_X 0.1
#define DELTA_Y 0.1

#define T_N 200000
#define DELTA_T 0.00004
#define T_STEPS_PER_FILE 500

// vector
void vector_init(double result[Y_N][X_N]);
void vector_add(double result[Y_N][X_N], double v1[Y_N][X_N],
                double v2[Y_N][X_N]);
void vector_mul_const(double result[Y_N][X_N], double v1[Y_N][X_N],
                      double k);
void vector_copy(double src[Y_N][X_N], double dest[Y_N][X_N]);

// runge kutta
void Runge_Kutta(void (*f)(double u[Y_N][X_N], double newU[Y_N][X_N]),
                 double u[Y_N][X_N], double newU[Y_N][X_N]);

// heat equation
void rhsFunc(double U[Y_N][X_N], double newU[Y_N][X_N]);

// initial conditions
double initFunc1(double x);
double initFunc2(double x);
double initFunc3(double x);
double initFunc4(double x);

// plot script
int createPlotScript(char* fileName, int type);
#endif
