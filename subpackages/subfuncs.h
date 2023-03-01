#pragma once
#include "constants.h"

// Structures
typedef struct {
    int n;                  // number of dots
    double *a;              // array of coefficients <a>
    double *b;              // array of coefficients <b>
    double *c;              // array of coefficients <c>
    double *d;              // array of coefficients <d>
    double *x;              // x array
    double *y;              // y array
    double gamma_1, gamma_2;// value of the second derivatives at the ends of the spline
} Spline;

void print_array(int n, double arr[n]);

void gauss_algorithm(int m, int n, double a[m][n], double x[n-1]);

void calc_coefficients(Spline *spline);

double calc_point_value(Spline spline, double x0);

void initialize_spline(Spline *spline, int n, double x_array[n], double y_array[n], double gamma_1, double gamma_2);

void free_spline(Spline *spline);

double MSE(double t, double c, Spline spline_TX, Spline spline_TY, Spline spline_CX, Spline spline_CY);

double MODULE(double t, double c, Spline spline_TX, Spline spline_TY, Spline spline_CX, Spline spline_CY);