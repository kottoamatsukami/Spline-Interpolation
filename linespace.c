#include<stdio.h>
#define MAX_FILENAME_LENGTH 256



int main(){
    char FileName[MAX_FILENAME_LENGTH];
    printf("Specify the path to the file for output: ");
    scanf("%s", &FileName);
    FILE *output_file = fopen(FileName, "w");
    if (!output_file)
    {
        printf("Error: Cannot create output file!\n");
    }
    double a, b, step;
    int count;
    printf("\nEnter start point:");
    scanf("%lf", &a);
    printf("\nEnter end point:");
    scanf("%lf", &b);
    printf("\nEnter dot count:");
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
    return 0;
}