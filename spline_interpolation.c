#include<stdio.h>
#include<math.h>
#include "subfuncs.h"

#define MAX_FILENAME_LENGTH 256

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
                int submenu_carrier;
                printf("\n1) Point by point\n");
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
        // Не менее жестко ищем пересечение сплайнов
        else if (menu_carrier == 2){
            printf("\n");
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