#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>
#include "subfuncs.h"

#define MAX_FILENAME_LENGTH 256
#define MAX_ITERATIONS 10000
// Settings of gradient descent
#define ALPHA 0.01                    // gradient coefficient
#define SHEDULER_STEP 1000            // step after which ALPHA is reduced in SHEDULER_COEFFICIENT times
#define SHEDULER_COEFFICIENT 2        // clearly
#define OMEGA 999999                  // big number
// Post gradient descent algorithm settings
#define NEIGHBOUR 0.5                   // the vicinity of the parameter to find the intersection point
#define MICRO 0.0001                  // step of this algorithm
#define EPSILON 0.002                 // difference between the values at which we consider them to be equal


void greeting(){
    printf(" _____       _ _                                               \n");
    printf("/  ___|     | (_)                                              \n");
    printf("\\ `--. _ __ | |_ _ __   ___                                    \n");
    printf(" `--. \\ '_ \\| | | '_ \\ / _ \\                                   \n");
    printf("/\\__/ / |_) | | | | | |  __/                                   \n");
    printf("\\____/| .__/|_|_|_| |_|\\___|                                   \n");
    printf("      | |                                                      \n");
    printf("      |_|                                                      \n");
    printf(" _____      _                        _       _   _             \n");
    printf("|_   _|    | |                      | |     | | (_)            \n");
    printf("  | | _ __ | |_ ___ _ __ _ __   ___ | | __ _| |_ _  ___  _ __  \n");
    printf("  | || '_ \\| __/ _ \\ '__| '_ \\ / _ \\| |/ _` | __| |/ _ \\| '_ \\ \n");
    printf(" _| || | | | ||  __/ |  | |_) | (_) | | (_| | |_| | (_) | | | |\n");
    printf(" \\___/_| |_|\\__\\___|_|  | .__/ \\___/|_|\\__,_|\\__|_|\\___/|_| |_|\n");
    printf("                        | |                                    \n");
    printf("                        |_|                                    \n");
}



int main(){
    srand(time(NULL));
    // Start echo
    while (1){
        // greeting
        greeting();
        // Call script menu
        int menu_carrier;
        printf("1) interpolate data\n");
        printf("2) find the intersection or distance of two splines\n");
        printf("3) credits\n");
        printf("0) exit\n");
        printf("echo: ");
        scanf("%d", &menu_carrier);

        // User error handler
        if ((menu_carrier > 3) || (menu_carrier < 0)){
            printf("\nMissed the key, don't upset please!\n");
        }

        // Exit handler
        else if (menu_carrier == 0){
            printf("\nBye!");
            return 0;
        }

        // Interpolate data handler
        else if (menu_carrier == 1) {
            char FileName[MAX_FILENAME_LENGTH];
            printf("\nSpecify the path to the file\n");
            printf("echo: ");
            scanf("%s", &FileName);
            FILE *target_file = fopen(FileName, "r");
            if (!target_file)
            {
                printf("Error: Cannot open your file!\n");
            }
            printf("\n");
            int n;
            double gamma_1, gamma_2;
            fscanf(target_file, "%d %lf %lf", &n, &gamma_1, &gamma_2);
            double x[n], y[n], index[n];
            for (int i = 0; i < n;i++)
            {
                fscanf(target_file, "%lf %lf", &x[i], &y[i]);
                index[i] = i;
            }
            fclose(target_file);

            // x
            double a_x[n-1], b_x[n-1], c_x[n-1], d_x[n-1];
            calc_coefficients(
                    n,
                    gamma_1,
                    gamma_2,
                    index,
                    x,
                    a_x,
                    b_x,
                    c_x,
                    d_x);

            //y
            double a_y[n-1], b_y[n-1], c_y[n-1], d_y[n-1];
            calc_coefficients(
                    n,
                    gamma_1,
                    gamma_2,
                    index,
                    y,
                    a_y,
                    b_y,
                    c_y,
                    d_y);

            while (1){
                printf("\n");
                printf("1) Point by point\n");
                printf("2) Load file\n");
                printf("0) exit\n");
                printf("echo: ");
                scanf("%d", &menu_carrier);

                // User error handler
                if ((menu_carrier > 2) || (menu_carrier < 0)){
                    printf("\nMissed the key, don't upset please!\n");
                }

                // Exit handler
                else if (menu_carrier == 0){
                    break;
                }

                // Interpolate points
                else if (menu_carrier == 1){
                    printf("Hint: put 0.123456789666 to come back\n");
                    double x0;
                    double point_x;
                    double point_y;

                    // New echo
                    while (1){
                        // take argument and calculate point
                        printf("echo <Argument in [%lf, %lf]>: ", index[0], index[n-1]);
                        scanf("%lf", &x0);
                        if (x0 == 0.123456789666){printf("\n"); break;}
                        printf("\nAprox: %lf %lf\n",
                               calc_point_value(
                                       x0,
                                       n,
                                       index,
                                       a_x,
                                       b_x,
                                       c_x,
                                       d_x
                                       ),
                               calc_point_value(
                                       x0,
                                       n,
                                       index,
                                       a_y,
                                       b_y,
                                       c_y,
                                       d_y
                                       )
                               );
                    }
                }

                // Interpolate points in file
                else if (menu_carrier == 2){
                    char FileName[MAX_FILENAME_LENGTH];
                    printf("\nSpecify the path to the file for input: ");
                    printf("\necho: ");
                    scanf("%s", &FileName);
                    FILE *input_file = fopen(FileName, "r");
                    if (!input_file)
                    {
                        printf("Error: Cannot open your file!\n");
                    }

                    printf("\nSpecify the path to the file for output: ");
                    printf("\necho: ");
                    scanf("%s", &FileName);
                    FILE *output_file = fopen(FileName, "w");
                    if (!output_file)
                    {
                        printf("Error: Cannot create output file!\n");
                    }

                    int N;
                    double t;
                    fscanf(input_file, "%d", &N);
                    for (int j=0;j<N;j++)
                    {
                        fscanf(input_file, "%lf", &t);
                        fprintf(output_file,"%lf %lf\n",
                               calc_point_value(
                                       t,
                                       n,
                                       index,
                                       a_x,
                                       b_x,
                                       c_x,
                                       d_x
                               ),
                               calc_point_value(
                                       t,
                                       n,
                                       index,
                                       a_y,
                                       b_y,
                                       c_y,
                                       d_y
                               )
                        );
                    }
                    fclose(input_file);
                    fclose(output_file);
                }
                else{
                    printf("\nI don`t know how you got here :(. Maybe i should continue...\n");
                    continue;
                }
            }




        }

        // Second submenu
        else if (menu_carrier == 2){
            printf("\n");
            char FileName[MAX_FILENAME_LENGTH];

            // Calculate coefficients for first spline
            printf("\nSpecify the path to the dots for first spline\n");
            printf("echo: ");
            scanf("%s", &FileName);
            FILE *first_spline = fopen(FileName, "r");
            if (!first_spline)
            {
                printf("Error: Cannot open your file!\n");
            }
            printf("\n");

            int first_n;
            double first_gamma_1, first_gamma_2;
            fscanf(first_spline, "%d %lf %lf", &first_n, &first_gamma_1, &first_gamma_2);
            double first_x[first_n], first_y[first_n], first_index[first_n];
            for (int i = 0; i < first_n;i++)
            {
                fscanf(first_spline, "%lf %lf", &first_x[i], &first_y[i]);
                first_index[i] = i;
            }
            fclose(first_spline);
            // x
            double first_a_x[first_n-1], first_b_x[first_n-1], first_c_x[first_n-1], first_d_x[first_n-1];
            calc_coefficients(
                    first_n,
                    first_gamma_1,
                    first_gamma_2,
                    first_index,
                    first_x,
                    first_a_x,
                    first_b_x,
                    first_c_x,
                    first_d_x);

            //y
            double first_a_y[first_n-1], first_b_y[first_n-1], first_c_y[first_n-1], first_d_y[first_n-1];
            calc_coefficients(
                    first_n,
                    first_gamma_1,
                    first_gamma_2,
                    first_index,
                    first_y,
                    first_a_y,
                    first_b_y,
                    first_c_y,
                    first_d_y);

            // Calculate coefficients for second spline
            printf("\nSpecify the path to the dots for second spline\n");
            printf("echo: ");
            scanf("%s", &FileName);
            FILE *second_spline = fopen(FileName, "r");
            if (!second_spline)
            {
                printf("Error: Cannot open your file!\n");
            }
            printf("\n");

            int second_n;
            double second_gamma_1, second_gamma_2;
            fscanf(second_spline, "%d %lf %lf", &second_n, &second_gamma_1, &second_gamma_2);
            double second_x[second_n], second_y[second_n], second_index[second_n];
            for (int i = 0; i < second_n; i++)
            {
                fscanf(second_spline, "%lf %lf", &second_x[i], &second_y[i]);
                second_index[i] = i;
            }
            fclose(second_spline);
            // x
            double second_a_x[second_n-1], second_b_x[second_n-1], second_c_x[second_n-1], second_d_x[second_n-1];
            calc_coefficients(
                    second_n,
                    second_gamma_1,
                    second_gamma_2,
                    second_index,
                    second_x,
                    second_a_x,
                    second_b_x,
                    second_c_x,
                    second_d_x);


            //y
            double second_a_y[second_n-1], second_b_y[second_n-1], second_c_y[second_n-1],second_d_y[second_n-1];
            calc_coefficients(
                    second_n,
                    second_gamma_1,
                    second_gamma_2,
                    second_index,
                    second_y,
                    second_a_y,
                    second_b_y,
                    second_c_y,
                    second_d_y);

            // start new echo
            while (1) {
                printf("\n");
                printf("1) start\n");
                printf("0) exit\n");
                printf("echo: ");
                scanf("%d", &menu_carrier);

                if ((menu_carrier > 1) || (menu_carrier < 0)) {
                    printf("\nMissed the key, don't upset please!\n");
                } else if (menu_carrier == 0) {
                    break;
                } else if (menu_carrier == 1) {
                    // Distance between splines

                    // Gradient Descent
                    // F(t, c) = |f1t - f2c| + |g1t - g2c|
                    double f1t, g1t, f2c, g2c;
                    double t=first_n/2.0, c=second_n/2.0;
                    double distance=OMEGA;
                    double gradient_t, gradient_c;
                    double function_value=0, last_function_value=OMEGA;
                    double alpha = ALPHA;
                    for (int i=1; i < MAX_ITERATIONS+1; i++){
                        f1t = calc_point_value(
                                t,
                                first_n,
                                first_index,
                                first_a_x,
                                first_b_x,
                                first_c_x,
                                first_d_x
                        );
                        g1t = calc_point_value(
                                t,
                                first_n,
                                first_index,
                                first_a_y,
                                first_b_y,
                                first_c_y,
                                first_d_y
                        );
                        f2c = calc_point_value(
                                c,
                                second_n,
                                second_index,
                                second_a_x,
                                second_b_x,
                                second_c_x,
                                second_d_x
                        );
                        g2c = calc_point_value(
                                c,
                                second_n,
                                second_index,
                                second_a_y,
                                second_b_y,
                                second_c_y,
                                second_d_y
                        );

                        gradient_t = (
                                (f1t - f2c + g1t - g2c)
                                /
                                fabs(f1t - f2c)
                                );

                        gradient_c = (
                                (f2c - f1t +  g2c - g1t)
                                /
                                fabs(g1t - g2c)
                                );
                        t += alpha * gradient_t;
                        c += alpha * gradient_c;
                        // Projection on set
                        // t
                        if (t < 0){
                            t = 0;
                        }
                        else if (t > first_index[first_n-1]){
                            t = first_index[first_n-1];
                        }
                        // c
                        if (c < 0){
                            c = 0;
                        }
                        else if (c > second_index[second_n-1]){
                            c = second_index[second_n-1];
                        }

                        // Calc func value
                        // F(t, c) = |f1t - f2c| + |g1t - g2c|
                        function_value = (
                                fabs(f1t - f2c)
                                +
                                fabs(g1t - g2c)
                                         );
                        // Hot stop
                        if (function_value>last_function_value){
                            printf("(f1(t):=%lf >< g1(t):=%lf)   (f2(t):=%lf >< g2(t):=%lf)\n", f1t, g1t, f2c, g2c);
                            break;
                        }
                        printf("Iteration[%d]: t:=%lf c:=%lf function(t, c):=%lf ><Scheduler: alpha=%lf\n", i, t, c, function_value, alpha);


                        // Scheduler
                        if (i % SHEDULER_STEP == 0){
                            alpha /= SHEDULER_COEFFICIENT;
                        }


                        last_function_value = function_value;
                    }

                    // Post gradient descent algorithm
                    for (double new_t = fmax(0, t-NEIGHBOUR); new_t<fmin(first_index[first_n-1],t+NEIGHBOUR); new_t+=MICRO){
                        f1t = calc_point_value(
                                new_t,
                                first_n,
                                first_index,
                                first_a_x,
                                first_b_x,
                                first_c_x,
                                first_d_x
                        );
                        g1t = calc_point_value(
                                new_t,
                                first_n,
                                first_index,
                                first_a_y,
                                first_b_y,
                                first_c_y,
                                first_d_y
                        );
                        for (double new_c = fmax(0, c-NEIGHBOUR); new_c<fmin(second_index[second_n-1],c+NEIGHBOUR); new_c+=MICRO){
                            f2c = calc_point_value(
                                    new_c,
                                    second_n,
                                    second_index,
                                    second_a_x,
                                    second_b_x,
                                    second_c_x,
                                    second_d_x
                            );
                            g2c = calc_point_value(
                                    new_c,
                                    second_n,
                                    second_index,
                                    second_a_y,
                                    second_b_y,
                                    second_c_y,
                                    second_d_y
                            );
                            distance = fmin(
                                    distance,
                                    sqrt(
                                            (f1t - f2c)*(f1t - f2c) +
                                            (g1t - g2c)*(g1t - g2c)
                                    )
                            );
                            if (fabs(g1t - g2c) < EPSILON){
                                if (fabs(f1t - f2c) < EPSILON){
                                    distance = 0;
                                    printf("Intersection: t:=%lf c:=%lf -> (%lf %lf)  (%lf %lf)\n", t, c, f1t, g1t, f2c, g2c);
                                    break;
                                }
                            }
                            if (distance == 0){
                                break;
                            }
                        }
                    }


                    if (distance != 0){
                        printf("Splines do not overlap, min distance: %lf\n", distance);
                    }
                }
                else {
                    printf("\nI don`t know how you got here :(. Maybe i should continue...\n");
                    continue;
                }
            }
        }

        // халява
        else if (menu_carrier == 3){
            printf("\n");
            printf("https://github.com/kottoamatsukami\n");
        }
        else{
            printf("\nI don`t know how you got here :(. Maybe i should continue...\n");
            continue;
        }
    }
}