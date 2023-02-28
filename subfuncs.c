#include "subfuncs.h"
#include <math.h>

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


void calc_coefficients(
        int n,
        double gamma_1,
        double gamma_2,
        double x[n],
        double y[n],
        double a[n-1],
        double b[n-1],
        double c[n-1],
        double d[n-1]
){
    double coefficient_matrix[4 * n - 4][4 * n - 3];
    double coefficient_vector[4 * n - 4];
    // 0)
    for (int i = 0; i < 4 * n - 4; i++)
    {
        for (int j = 0; j < 4 * n - 4; j++)
        {
            coefficient_matrix[j][i] = 0;
        }
        coefficient_vector[i] = 0;
    }

    // 1)
    for (int i = 0; i < n-1; i++)
    {
        coefficient_matrix[i][3 * (n - 1) + i] = 1;
        coefficient_matrix[i][4 * (n - 1)] = y[i];
    }

    // 2)
    double delta;
    for (int i = 0; i < n - 1; i++)
    {
        delta = x[i+1] - x[i];
        coefficient_matrix[n-1+i][0 * (n - 1) + i] = delta*delta*delta;
        coefficient_matrix[n-1+i][1 * (n - 1) + i] = delta*delta;
        coefficient_matrix[n-1+i][2 * (n - 1) + i] = delta;
        coefficient_matrix[n-1+i][3 * (n - 1) + i] = 1;
        coefficient_matrix[n-1+i][4 * (n - 1)] = y[i+1];
    }

    // 3)
    for (int i = 0; i < n - 2; i++)
    {
        delta = x[i+1] - x[i];
        coefficient_matrix[2*(n-1)+i][0 * (n - 1) + i] = 3 * delta * delta;
        coefficient_matrix[2*(n-1)+i][1 * (n - 1) + i] = 2 * delta;
        coefficient_matrix[2*(n-1)+i][2 * (n - 1) + i] = 1;
        coefficient_matrix[2*(n-1)+i][2 * (n - 1) + i + 1] = -1;

    }

    // 4)
    for (int i = 0; i < n - 2; i++)
    {
        delta = x[i+1] - x[i];
        coefficient_matrix[2*(n-1) + n - 2 +i][0 * (n - 1) + i] = 6 * delta;
        coefficient_matrix[2*(n-1) + n - 2 +i][1 * (n - 1) + i] = 2;
        coefficient_matrix[2*(n-1) + n - 2 +i][1 * (n - 1) + i + 1] = -2;
    }

    // 5)
    // gamma_1
    coefficient_matrix[2*(n-1) + 2*(n-2)][1 * (n -1)] = 2;
    coefficient_matrix[2*(n-1) + 2*(n-2)][4 * (n - 1)] = gamma_1;
    // gamma_2
    delta = x[n-1] - x[n-2];
    coefficient_matrix[2*(n-1) + 2*(n-2)+1][0 * (n - 1) + n - 2] = 6 * delta;
    coefficient_matrix[2*(n-1) + 2*(n-2)+1][1 * (n - 1) + n - 2] = 2;
    coefficient_matrix[2*(n-1) + 2*(n-2)+1][4 * (n - 1)] = gamma_2;


    gauss_algorithm(4 * n - 4, 4 * n - 3, coefficient_matrix, coefficient_vector);

    for (int i = 0; i < n-1; i++)
    {
        a[i] = coefficient_vector[0*(n-1) + i];
        b[i] = coefficient_vector[1*(n-1) + i];
        c[i] = coefficient_vector[2*(n-1) + i];
        d[i] = coefficient_vector[3*(n-1) + i];
    }
}


double calc_point_value(
        double x0,
        int n,
        double x[n],
        double a[n-1],
        double b[n-1],
        double c[n-1],
        double d[n-1]
){
    double value;
    double delta;
    for (int i = 0; i < n - 1; i++)
    {
        if ((x[i] <= x0) && (x0 <= x[i+1])){
            delta = (x0 - x[i]);
            value = a[i] * delta * delta * delta +
                    b[i] * delta * delta +
                    c[i] * delta +
                    d[i];
            return value;
        }
    }
}