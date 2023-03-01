#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "subpackages/echo.h"
#include "subpackages/subfuncs.h"
#include "subpackages/constants.h"


int main(){
    // Start echo
    while (1){
        /*
         * ==============-<SCRIPT MENU>-==============
         */
        greeting();
        int user_choice = main_menu();

        // Exit handler
        if (user_choice == 0)
        {
            exit_handler();
        }

        // Interpolate data handler
        if (user_choice == 1)
        {
            // Determine the mode for spline (normalized)
            int normalized;
            user_choice = first_submenu();
            if (user_choice == 0)
            {
                break;
            }
            if (user_choice == 1)
            {
                normalized = 1;
            }
            if (user_choice == 2)
            {
                normalized = 0;
            }

            /*
             * =============-<File processing>-=============
             *
             */
            char FileName[MAX_FILENAME_LENGTH];
            filepath_request(1);
            scanf("%s", &FileName);
            FILE *target_file = fopen(FileName, "r");
            if (!target_file){puts(ECHO_MSG_ERROR_FILE);continue;}

            int n;                   // number of dots
            double gamma_1, gamma_2; // value of the second derivatives at the ends of the spline
            fscanf(target_file, "%d %lf %lf", &n, &gamma_1, &gamma_2);
            double x[n], y[n], index[n];
            for (int i = 0; i < n;i++)
            {
                fscanf(target_file, "%lf %lf", &x[i], &y[i]);
                if (normalized){index[i] = (double)i/n;}
                else           {index[i] = i;}
            }
            if (normalized) {index[n-1]=1;}
            fclose(target_file);

            /*
             * =============-< Spline Calculation >-=============
             *
             */
            Spline splineX;
            initialize_spline(&splineX, n, index, x, gamma_1, gamma_2);
            calc_coefficients(&splineX);


            Spline splineY;
            initialize_spline(&splineY, n, index, y, gamma_1, gamma_2);
            calc_coefficients(&splineY);

            /*
             * ============-< NEXT MENU >-============
             *
             * */
            while (1){
                user_choice = second_submenu();

                // Come back handler
                if (user_choice == 0){
                    break;
                }

                /*
                 * ============-< Point by point interpolation >-============
                 *
                 * */
                if (user_choice == 1){
                    double t;
                    puts("Hint: put -1 to come back");

                    // New echo
                    while (1){
                        printf("echo <Argument in [%lf, %lf]>:\n", index[0], index[n-1]);
                        scanf("%lf", &t);
                        if (t == -1){printf("\n"); break;}
                        printf("Approximately: %lf %lf\n",
                               calc_point_value(splineX, t),
                               calc_point_value(splineY, t)
                        );
                    }
                }

                /*
                * ============-< File interpolation >-============
                *
                * */
                else if (user_choice == 2){
                    char FileName[MAX_FILENAME_LENGTH];

                    /*
                     * --------------------------------
                     * Input file
                     * --------------------------------
                     * */
                    filepath_request(1);
                    scanf("%s", &FileName);
                    FILE *input_file = fopen(FileName, "r");
                    if (!input_file){puts(ECHO_MSG_ERROR_FILE);continue;}

                    /*
                     * --------------------------------
                     * Output file
                     * --------------------------------
                     * */
                    filepath_request(0);
                    scanf("%s", &FileName);
                    FILE *output_file = fopen(FileName, "w");
                    if (!output_file){puts(ECHO_MSG_ERROR_FILE);continue;}

                    /*
                     * --------------------------------
                     * Calculation
                     * --------------------------------
                     * */
                    int N;        // number of dots in file
                    double t;     // argument
                    fscanf(input_file, "%d", &N);
                    for (int j=0;j<N;j++)
                    {
                        fscanf(input_file, "%lf", &t);
                        fprintf(output_file,"%lf %lf\n",
                               calc_point_value(splineX, t),
                               calc_point_value(splineY, t)
                        );
                    }
                    fclose(input_file);
                    fclose(output_file);
                    puts("Successfully!");
                }
            }
        }

        // Third submenu
        else if (user_choice == 2){
            // Determine the mode for spline (normalized)
            int normalized;
            user_choice = first_submenu();
            if (user_choice == 0){break;}
            if (user_choice == 1){normalized=1;}
            if (user_choice == 2){normalized = 0;}

            char FileName[MAX_FILENAME_LENGTH];
            /*
             *  Calculate coefficients for first spline
             *
             * */
            filepath_request(1);
            scanf("%s", &FileName);
            FILE *first_spline = fopen(FileName, "r");
            if (!first_spline){puts(ECHO_MSG_ERROR_FILE);continue;}

            int first_n;
            double first_gamma_1, first_gamma_2;
            fscanf(first_spline, "%d %lf %lf", &first_n, &first_gamma_1, &first_gamma_2);
            double first_x[first_n], first_y[first_n], first_index[first_n];
            for (int i = 0; i < first_n;i++)
            {
                fscanf(first_spline, "%lf %lf", &first_x[i], &first_y[i]);
                if (normalized){first_index[i] = (double)i/first_n;}
                else           {first_index[i] = i;}
            }
            if (normalized) {first_index[first_n-1]=1;}
            fclose(first_spline);

            Spline firstX;
            initialize_spline(&firstX, first_n, first_index, first_x, first_gamma_1, first_gamma_2);
            calc_coefficients(&firstX);

            Spline firstY;
            initialize_spline(&firstY, first_n, first_index, first_y, first_gamma_1, first_gamma_2);
            calc_coefficients(&firstY);

            /*
             *  Calculate coefficients for second spline
             *
             * */
            filepath_request(1);
            scanf("%s", &FileName);
            FILE *second_spline = fopen(FileName, "r");
            if (!second_spline){
                puts(ECHO_MSG_ERROR_FILE);
                free_spline(&firstX);
                free_spline(&firstY);
                continue;
            }

            int second_n;
            double second_gamma_1, second_gamma_2;
            fscanf(second_spline, "%d %lf %lf", &second_n, &second_gamma_1, &second_gamma_2);
            double second_x[second_n], second_y[second_n], second_index[second_n];
            for (int i = 0; i < second_n;i++)
            {
                fscanf(second_spline, "%lf %lf", &second_x[i], &second_y[i]);
                if (normalized){second_index[i] = (double)i/second_n;}
                else           {second_index[i] = i;}
            }
            if (normalized) {second_index[second_n-1]=1;}
            fclose(second_spline);

            Spline secondX;
            initialize_spline(&secondX, second_n, second_index, second_x, second_gamma_1, second_gamma_2);
            calc_coefficients(&secondX);

            Spline secondY;
            initialize_spline(&secondY, second_n, second_index, second_y, second_gamma_1, second_gamma_2);
            calc_coefficients(&secondY);

            // Third submenu
            while (1) {
                user_choice = third_submenu();
                if (user_choice == 0) {
                    break;
                }
                if (user_choice == 1) {
                    /*
                     *  Gradient Descent
                     *
                     * */

                    double f1t, g1t, f2c, g2c;
                    double t=first_index[first_n/2], c=second_index[second_n/2], min_t=OMEGA, min_c=OMEGA;
                    double distance=OMEGA;
                    double gradient_t, gradient_c, last_gradient_t=0, last_gradient_c=0;
                    double function_value=0, last_function_value=OMEGA, min_function_value=OMEGA;
                    double alpha = GRADIENT_COEFFICIENT, beta = ACCUMULATED_SPEED_COEFFICIENT;
                    int hot_stops = 0;

                    user_choice = fourth_submenu();
                    if (user_choice == 0){break;}

                    for (int i=1; i < MAX_ITERATIONS+1; i++){
                        if (user_choice == 1){
                            /*
                             * MSE
                             */
                            gradient_t = (
                                    MSE(t+OMICRON, t, firstX, firstY, secondX, secondY)
                                    -
                                    MSE(t, t, firstX, firstY, secondX, secondY)
                            )/OMICRON;

                            gradient_c = (
                                     MSE(t, t+OMICRON, firstX, firstY, secondX, secondY)
                                     -
                                     MSE(t, t, firstX, firstY, secondX, secondY)
                            )/OMICRON;

                            f1t = calc_point_value(firstX, t);
                            g1t = calc_point_value(firstY, t);
                            f2c = calc_point_value(secondX, c);
                            g2c = calc_point_value(secondY, c);

                            function_value = (
                                    (f1t - f2c)*(f1t - f2c)
                                    +
                                    (g1t - g2c)*(g1t - g2c)
                            );
                        }
                        if (user_choice == 2){
                            /*
                             * Module
                             * */
                            /*
                             * MSE
                             */
                            gradient_t = (
                                    MSE(t+OMICRON, c, firstX, firstY, secondX, secondY)
                                    -
                                    MSE(t, c, firstX, firstY, secondX, secondY)
                            )/OMICRON;

                            gradient_c = (
                                    MODULE(t, c+OMICRON, firstX, firstY, secondX, secondY)
                                    -
                                    MODULE(t, c, firstX, firstY, secondX, secondY)
                            )/OMICRON;

                            f1t = calc_point_value(firstX, t);
                            g1t = calc_point_value(firstY, t);
                            f2c = calc_point_value(secondX, c);
                            g2c = calc_point_value(secondY, c);

                            function_value = (
                                    (f1t - f2c)*(f1t - f2c)
                                    +
                                    (g1t - g2c)*(g1t - g2c)
                            );
                        }

                        t = t - alpha * (beta*last_gradient_t + (1-beta)*gradient_t);
                        c = c - alpha * (beta*last_gradient_c + (1-beta)*gradient_c);

                        // Projection on set
                        // t
                        if (t < 0){t = 0;}
                        else if (t > first_index[first_n-1]){t = first_index[first_n-1];}
                        // c
                        if (c < 0){c = 0;}
                        else if (c > second_index[second_n-1]){c = second_index[second_n-1];}
                        // Hot stop
                        if (function_value>=last_function_value){
                            hot_stops++;
                            if (EARLY_STOP || (hot_stops >= SKIP_COUNT)) {
                                printf("(f1(t):=%lf >< g1(t):=%lf)   (f2(t):=%lf >< g2(t):=%lf)\n", f1t, g1t, f2c, g2c);
                                break;
                            }
                        }
                        if (function_value <= min_function_value){
                            min_function_value = function_value;
                            min_t = t;
                            min_c = c;
                        }
                        else{
                            hot_stops=0;
                        }
                        printf("Iteration[%d]: t:=%lf c:=%lf F(t, c):=%lf >< cur_alpha:=%lf hot_stops:=%d\n", i, t, c, function_value, alpha, hot_stops);


                        // Scheduler
                        if (i % SHEDULER_STEP == 0){
                            alpha /= SHEDULER_COEFFICIENT;
                        }

                        last_function_value = function_value;
                        last_gradient_t = gradient_t;
                        last_gradient_c = gradient_c;
                    }
                    printf("min F(t, c):=%lf t:=%lf c:=%lf\n", min_function_value, min_t, min_c);
                    // Post gradient descent algorithm
                    for (double new_t = fmax(0, min_t-NEIGHBOUR); new_t<fmin(first_index[first_n-1],min_t+NEIGHBOUR); new_t+=MICRO){
                        f1t = calc_point_value(firstX, new_t);
                        g1t = calc_point_value(firstY, new_t);
                        for (double new_c = fmax(0, min_c-NEIGHBOUR); new_c<fmin(second_index[second_n-1],min_c+NEIGHBOUR); new_c+=MICRO){
                            f2c = calc_point_value(secondX, new_c);
                            g2c = calc_point_value(secondY, new_c);
                            distance = fmin(
                                    distance,
                                    sqrt(
                                            (f1t - f2c)*(f1t - f2c) +
                                            (g1t - g2c)*(g1t - g2c)
                                    )
                            );
                            if ((fabs(g1t - g2c) < EPSILON) && (fabs(f1t - f2c) < EPSILON)){
                                distance = 0;
                                printf("Intersection: t:=%lf c:=%lf -> (%lf %lf)  (%lf %lf)\n", t, c, f1t, g1t, f2c, g2c);
                                break;
                            }
                        }

                        if (distance == 0){
                            break;
                        }
                    }
                    if (distance != 0){
                        printf("Splines do not overlap, min distance: %lf\n", distance);
                    }
                }

                else if (user_choice == 2){
                    /*
                     *  Parameter search
                     *
                     * */
                    puts("Starting, please wait...");
                    double f1t, g1t, f2c, g2c;
                    double distance=OMEGA;
                    for (double t = 0; t<first_index[first_n-1]; t+=MICRO){
                        f1t = calc_point_value(firstX, t);
                        g1t = calc_point_value(firstY, t);
                        for (double c = 0; c<second_index[second_n-1]; c+=MICRO){
                            f2c = calc_point_value(secondX, c);
                            g2c = calc_point_value(secondY, c);
                            distance = fmin(
                                    distance,
                                    sqrt(
                                            (f1t - f2c)*(f1t - f2c) +
                                            (g1t - g2c)*(g1t - g2c)
                                    )
                            );

                            if ((fabs(g1t - g2c) < EPSILON) && (fabs(f1t - f2c) < EPSILON)){
                                distance = 0;
                                printf("Intersection: t:=%lf c:=%lf -> (%lf %lf)  (%lf %lf)\n", t, c, f1t, g1t, f2c, g2c);
                                break;
                            }
                        }

                        if (distance == 0){
                            break;
                        }
                    }
                    if (distance != 0){
                        printf("Splines do not overlap, min distance: %lf\n", distance);
                    }
                }
            }
        }

        // Linespace gen
        else if (user_choice == 3)
        {
            char FileName[MAX_FILENAME_LENGTH];
            filepath_request(0);
            scanf("%s", &FileName);
            FILE *output_file = fopen(FileName, "w");
            if (!output_file){puts(ECHO_MSG_ERROR_FILE);}

            double a, b, step;
            int count;
            puts("Enter start point");
            scanf("%lf", &a);
            puts("Enter end point:");
            scanf("%lf", &b);
            puts("Enter dot count:");
            scanf("%d", &count);
            step = (b - a) / (double)(count-1);
            int iterations = 0;
            if (a >= b){
                return -1;
            }
            if (step <= 0){
                return -2;
            }

            fprintf(output_file, "%d\n", count);
            while (a <= b){
                fprintf(output_file, "%lf\n", a);
                a += step;
                iterations += 1;
            }
            if (iterations != count){
                fprintf(output_file, "%lf\n", b);
            }
            fclose(output_file);
            puts("Completed!");
        }

        else if (user_choice == 4){
            /*
             * ------------------------
             * Credits
             * ------------------------
             * */
            puts("https://github.com/kottoamatsukami");
        }
    }
}