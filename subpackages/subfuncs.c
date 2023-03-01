#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "subfuncs.h"
#include "constants.h"

void gauss_algorithm(int m, int n, double a[m][n], double x[n-1])
{
    int i,j,k;
    for(i=0;i<m-1;i++){
        for(k=i+1;k<m;k++){
            if(fabs(a[i][i])<fabs(a[k][i])){
                for(j=0;j<n;j++){
                    double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
        for(k=i+1;k<m;k++){
            double  term=a[k][i]/ a[i][i];
            for(j=0;j<n;j++){
                a[k][j]=a[k][j]-term*a[i][j];
            }
        }

    }
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++){
            x[i]=x[i]-a[i][j]*x[j];
        }
        x[i]=x[i]/a[i][i];
    }
}


void calc_coefficients(Spline *spline)
{
    double coefficient_matrix[4 * spline->n - 4][4 * spline->n - 3];
    double coefficient_vector[4 * spline->n - 4];
    /*
     * ================-<FILL THE COEFFICIENT MATRIX>-===================
     * */
    /*
     * 0)
     * Zeroing the matrix and solution vector
     * */
    for (int i = 0; i < 4 * spline->n - 4; i++)
    {
        for (int j = 0; j < 4 * spline->n - 4; j++)
        {
            coefficient_matrix[j][i] = 0;
        }
        coefficient_vector[i] = 0;
    }

    /*
     * 1)
     * The first condition of passing a left point with a spline
     * */
    for (int i = 0; i < spline->n-1; i++)
    {
        coefficient_matrix[i][3 * (spline->n - 1) + i] = 1;
        coefficient_matrix[i][4 * (spline->n - 1)] = spline->y[i];
    }

    /*
     * 2)
     * The condition of passing a right point with a spline
     * */
    double delta;
    for (int i = 0; i < spline->n - 1; i++)
    {
        delta = spline->x[i+1] - spline->x[i];
        coefficient_matrix[spline->n-1+i][0 * (spline->n - 1) + i] = delta*delta*delta;
        coefficient_matrix[spline->n-1+i][1 * (spline->n - 1) + i] = delta*delta;
        coefficient_matrix[spline->n-1+i][2 * (spline->n - 1) + i] = delta;
        coefficient_matrix[spline->n-1+i][3 * (spline->n - 1) + i] = 1;
        coefficient_matrix[spline->n-1+i][4 * (spline->n - 1) + 0] = spline->y[i+1];
    }

    /*
     * 3)
     * Equality of first derivatives
     * */
    for (int i = 0; i < spline->n - 2; i++)
    {
        delta = spline->x[i+1] - spline->x[i];
        coefficient_matrix[2*(spline->n-1)+i][0 * (spline->n - 1) + i + 0] = 3 * delta * delta;
        coefficient_matrix[2*(spline->n-1)+i][1 * (spline->n - 1) + i + 0] = 2 * delta;
        coefficient_matrix[2*(spline->n-1)+i][2 * (spline->n - 1) + i + 0] = 1;
        coefficient_matrix[2*(spline->n-1)+i][2 * (spline->n - 1) + i + 1] = -1;

    }

    /*
     * 4)
     * Equality of second derivatives
     * */
    for (int i = 0; i < spline->n - 2; i++)
    {
        delta = spline->x[i+1] - spline->x[i];
        coefficient_matrix[2*(spline->n-1) + spline->n - 2 +i][0 * (spline->n - 1) + i + 0] = 6 * delta;
        coefficient_matrix[2*(spline->n-1) + spline->n - 2 +i][1 * (spline->n - 1) + i + 0] = 2;
        coefficient_matrix[2*(spline->n-1) + spline->n - 2 +i][1 * (spline->n - 1) + i + 1] = -2;
    }

    /*
     * 5)
     * The value of the second derivatives of 0-cubic and n-1-cubic
     * */
    // gamma_1
    coefficient_matrix[2*(spline->n-1) + 2*(spline->n-2)][1 * (spline->n - 1)] = 2;
    coefficient_matrix[2*(spline->n-1) + 2*(spline->n-2)][4 * (spline->n - 1)] = spline->gamma_1;
    // gamma_2
    delta = spline->x[spline->n-1] - spline->x[spline->n-2];
    coefficient_matrix[2*(spline->n-1) + 2*(spline->n-2)+1][0 * (spline->n - 1) + spline->n - 2] = 6 * delta;
    coefficient_matrix[2*(spline->n-1) + 2*(spline->n-2)+1][1 * (spline->n - 1) + spline->n - 2] = 2;
    coefficient_matrix[2*(spline->n-1) + 2*(spline->n-2)+1][4 * (spline->n - 1)] = spline->gamma_2;

    // Calculate coefficients by Gauss
    gauss_algorithm(4 * spline->n - 4, 4 * spline->n - 3, coefficient_matrix, coefficient_vector);

    // Move the coefficients
    for (int i = 0; i < spline->n-1; i++)
    {
        spline->a[i] = coefficient_vector[0*(spline->n-1) + i];
        spline->b[i] = coefficient_vector[1*(spline->n-1) + i];
        spline->c[i] = coefficient_vector[2*(spline->n-1) + i];
        spline->d[i] = coefficient_vector[3*(spline->n-1) + i];
    }
}

void print_array(int n, double arr[n])
{
    for (int i = 0; i < n; i++){
        printf("%lf ", arr[i]);
    }
    printf("\n");
}

double calc_point_value(Spline spline, double x0)
{
    double value;
    double delta;
    for (int i = 0; i < spline.n - 1; i++)
    {
        if ((spline.x[i] <= x0) && (x0 <= spline.x[i+1])){

            delta = (x0 - spline.x[i]);
            value = spline.a[i] * delta * delta * delta +
                    spline.b[i] * delta * delta +
                    spline.c[i] * delta +
                    spline.d[i];
            return value;
        }
    }
}


void initialize_spline(Spline *spline, int n, double x_array[n], double y_array[n], double gamma_1, double gamma_2)
{
    spline->n = n;
    spline->gamma_1 = gamma_1;
    spline->gamma_2 = gamma_2;

    spline->a = (double*)calloc(n-1, sizeof(double));
    spline->b = (double*)calloc(n-1, sizeof(double));
    spline->c = (double*)calloc(n-1, sizeof(double));
    spline->d = (double*)calloc(n-1, sizeof(double));

    spline->x = (double*)calloc(n, sizeof(double));
    spline->y = (double*)calloc(n, sizeof(double));

    spline->x = x_array;
    spline->y = y_array;
}

void free_spline(Spline *spline)
{
    free(spline->a);
    free(spline->b);
    free(spline->c);
    free(spline->d);
    free(spline->x);
    free(spline->y);
}

double MSE(double t, double c, Spline spline_TX, Spline spline_TY, Spline spline_CX, Spline spline_CY)
{
    return (
            (calc_point_value(spline_TX, t) - calc_point_value(spline_CX, c))*(calc_point_value(spline_TX, t) - calc_point_value(spline_CX, c))
            +
            (calc_point_value(spline_TY, t) - calc_point_value(spline_CY, c))*(calc_point_value(spline_TY, t) - calc_point_value(spline_CY, c))
            );

}

double MODULE(double t, double c, Spline spline_TX, Spline spline_TY, Spline spline_CX, Spline spline_CY)
{
    return (
            fabs(calc_point_value(spline_TX, t) - calc_point_value(spline_CX, c))
            +
            fabs(calc_point_value(spline_TY, t) - calc_point_value(spline_CY, c))
            );
}

/*
 * ----------------------------------------------
 * Last modified at 01.03.2023 by Kottoamatsukami
 * ----------------------------------------------
 */