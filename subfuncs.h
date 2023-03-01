#pragma once

void gauss_algorithm(int m, int n, double a[m][n], double x[n-1]);

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
        );


double calc_point_value(
        double x0,
        int n,
        double x[n],
        double a[n-1],
        double b[n-1],
        double c[n-1],
        double d[n-1]);
