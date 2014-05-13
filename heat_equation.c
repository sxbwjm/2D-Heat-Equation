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
    int sizeX = X_N;
    int sizeY = Y_N;
    int i, j;
    
    double C = 1.0;
    
    for(i=0; i<sizeX; i++)
    {
        for(j=0; j<sizeY; j++)
        {
            // test boundaries
            ux_1 = (j - 1 >= 0) ? U[i][j - 1] : U[i][j - 1 + sizeX];
            ux = U[i][j];
            ux1 = (j + 1 < sizeX) ? U[i][j + 1] : U[i][j + 1 - sizeX];
       
            uy_1 = (i - 1 >= 0) ? U[i - 1][j] : U[i - 1 + sizeY][j];
            uy = U[i][j];
            uy1 = (i + 1 < sizeY) ? U[i + 1][j] : U[i + 1 - sizeY][j];
            newU[i][j] = C * ( D2U(ux_1, ux, ux1, DELTA_X) +
                               D2U(uy_1, uy, uy1, DELTA_Y) );
        }
    }
}


