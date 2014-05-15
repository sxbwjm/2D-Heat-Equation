//
//  heat_equation.c
//  Heat-Equation
//
//  Created by Xiaobo Sun on 5/12/14.
//  Copyright (c) 2014 Xiaobo Sun. All rights reserved.
//

#include <stdio.h>
#include <mpi.h>
#include "common.h"

double ghostCellsColLeft[Y_N];
double ghostCellsColRight[Y_N];
double ghostCellsRowTop[X_N];
double ghostCellsRowBottom[X_N];

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

void fillGhostCells(double U[Y_N][X_N])
{
    // fill ghost cells for column
    for(int y = 0; y < Y_N; y++)
    {
        // left line
        ghostCellsColLeft[y] = U[y][X_N - 1];
        // right line
        ghostCellsColRight[y] = U[y][0];
    }
    
    // fill ghost cells for rows
    int rank_above = (glbRank > 0) ? glbRank - 1 : glbSize - 1;
    int rank_below = (glbRank < glbSize - 1) ? glbRank + 1 : 0;

    // MPI_Send some interior points to this process' neighbors
    // MPI_Recv those values into ghost cells
    MPI_Request req[4];
    
    // create buffer for sending & receiving
    double* sendBuffAbove = U[glbYStart];
    double* sendBuffBelow = U[glbYEnd - 1];
    
    // receive msg
    MPI_Irecv(ghostCellsRowTop, X_N, MPI_DOUBLE, rank_above, 1111, MPI_COMM_WORLD, &req[0]);
    MPI_Irecv(ghostCellsRowBottom, X_N, MPI_DOUBLE, rank_below, 2222, MPI_COMM_WORLD, &req[1]);
    
    // send msg
    MPI_Isend(sendBuffAbove, X_N, MPI_DOUBLE, rank_above, 2222, MPI_COMM_WORLD, &req[2]);
    MPI_Isend(sendBuffBelow, X_N, MPI_DOUBLE, rank_below, 1111, MPI_COMM_WORLD, &req[3]);
    
    // wait
    MPI_Waitall(4, req, MPI_STATUSES_IGNORE);

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
    
    fillGhostCells(U);
    
    // calcuate rhs values
    for(int y=glbYStart; y<glbYEnd; y++)
    {
        for(int x=0; x<X_N; x++)
        {
            ux_1 = (x == 0) ? ghostCellsColLeft[y] : U[y][x - 1];
            ux = U[y][x];
            ux1 = (x == X_N - 1) ? ghostCellsColRight[y] : U[y][x + 1];
            
            uy_1 = (y == glbYStart) ? ghostCellsRowTop[x] : U[y - 1][x];
            uy = U[y][x];
            uy1 = (y == glbYEnd - 1) ? ghostCellsRowBottom[x] : U[y + 1][x];
            
            newU[y][x] = C * ( D2U(ux_1, ux, ux1, DELTA_X) +
                              D2U(uy_1, uy, uy1, DELTA_Y) );

            
        }
    }
}


