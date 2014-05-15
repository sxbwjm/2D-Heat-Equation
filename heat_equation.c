//
//  heat_equation.c
//  Heat-Equation
//
//  Created by Xiaobo Sun on 5/12/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include "common.h"

/*************************************************************
 *               One derivative
 *************************************************************/
double D1U(double u1, double u2, double delta)
{
    return (u2 - u1) / delta;
}

/*************************************************************
 *               Second derivative
 *************************************************************/
double D2U(double u_1, double u, double u1, double delta)
{
    return D1U( D1U(u_1, u, delta), D1U(u, u1, delta), delta );
}

/*************************************************************
 *               function for Runge–Kutta
 *
 * right hand side function in the following equation:
 *    u' = f(u)
 **************************************************************/
void rhsFunc(double U[Y_N][X_N], double newU[Y_N][X_N])
{
    double ux_1, ux, ux1;
    double uy_1, uy, uy1;
    
    double C = 1.0;
    
    for(int y=0; y<Y_N; y++)
    {
        for(int x=0; x<X_N; x++)
        {
            // test boundaries
            ux_1 = (x - 1 >= 0) ? U[y][x - 1] : U[y][x - 1 + X_N];
            ux = U[y][x];
            ux1 = (x + 1 < X_N) ? U[y][x + 1] : U[y][x + 1 - X_N];
       
            uy_1 = (y - 1 >= 0) ? U[y - 1][x] : U[y - 1 + Y_N][x];
            uy = U[y][x];
            uy1 = (y + 1 < Y_N) ? U[y + 1][x] : U[y + 1 - Y_N][x];
            newU[y][x] = C * ( D2U(ux_1, ux, ux1, DELTA_X) +
                               D2U(uy_1, uy, uy1, DELTA_Y) );
        }
    }
}


