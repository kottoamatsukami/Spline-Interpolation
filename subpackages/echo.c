#include "echo.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * =================-< GREETING >-=================
 *
 */
void greeting()
{
    puts(" _____       _ _                                                      ");
    puts("/  ___|     | (_)                                                     ");
    puts("\\ `--. _ __ | |_ _ __   ___                                          ");
    puts(" `--. \\ '_ \\| | | '_ \\ / _ \\                                      ");
    puts("/\\__/ / |_) | | | | | |  __/                                         ");
    puts("\\____/| .__/|_|_|_| |_|\\___|                                        ");
    puts("      | |                                                             ");
    puts("      |_|                                                             ");
    puts(" _____      _                        _       _   _                    ");
    puts("|_   _|    | |                      | |     | | (_)                   ");
    puts("  | | _ __ | |_ ___ _ __ _ __   ___ | | __ _| |_ _  ___  _ __         ");
    puts("  | || '_ \\| __/ _ \\ '__| '_ \\ / _ \\| |/ _` | __| |/ _ \\| '_ \\  ");
    puts(" _| || | | | ||  __/ |  | |_) | (_) | | (_| | |_| | (_) | | | |       ");
    puts(" \\___/_| |_|\\__\\___|_|  | .__/ \\___/|_|\\__,_|\\__|_|\\___/|_| |_|");
    puts("                        | |                                           ");
    puts("                        |_|                                           ");
    puts(VERSION);
}

/*
 * =================-< MAIN MENU >-=================
 *
 */
int main_menu()
{
    int menu_carrier = 0;
    while (1) {
        puts("1) Interpolate data");
        puts("2) Find the intersection or distance of two splines");
        puts("3) Generate line-space");
        puts("4) Credits");
        puts("0) exit");
        puts(ECHO_ARROW);
        scanf("%d", &menu_carrier);
        if ((menu_carrier > 3) || (menu_carrier < 0)) {
            puts(ECHO_MSG_MISSED_KEY);
            continue;
        }
        return menu_carrier;
    }
}

/*
 * =================-< FIRST SUB MENU >-=================
 *
 */
int first_submenu()
{
    int menu_carrier = 0;
    while (1) {
        puts("1) Normalized argument");
        puts("2) Argument in [0, num_of_dots]");
        puts("0) Go to the main menu");
        puts(ECHO_ARROW);
        scanf("%d", &menu_carrier);
        if ((menu_carrier > 2) || (menu_carrier < 0)) {
            puts(ECHO_MSG_MISSED_KEY);
            continue;
        }
        return menu_carrier;
    }
}

int second_submenu()
{
    int menu_carrier = 0;
    while (1)
    {
        puts("1) Point by point");
        puts("2) Load file");
        puts("0) Back");
        puts(ECHO_ARROW);
        scanf("%d", &menu_carrier);
        if ((menu_carrier > 2) || (menu_carrier < 0)) {
            puts(ECHO_MSG_MISSED_KEY);
            continue;
        }
        return menu_carrier;
    }
}

int third_submenu()
{
    int menu_carrier = 0;
    while (1)
    {
        puts("1) Gradient Descent with approximation <FAST>");
        puts("2) Parameter search                    <VERY SLOW>");
        puts("0) Back");
        puts("echo: ");
        scanf("%d", &menu_carrier);
        if ((menu_carrier > 2) || (menu_carrier < 0)) {
            puts(ECHO_MSG_MISSED_KEY);
            continue;
        }
        return menu_carrier;
    }
}

int fourth_submenu()
{
    int menu_carrier = 0;
    while (1)
    {
        puts("1) Mean Squared Error (MSE) <HIGHLY UNSTABLE>");
        puts("2) Module                   <RECOMMENDED>");
        puts("0) Back");
        puts("echo: ");
        scanf("%d", &menu_carrier);
        if ((menu_carrier > 2) || (menu_carrier < 0)) {
            puts(ECHO_MSG_MISSED_KEY);
            continue;
        }
        return menu_carrier;
    }
}
/*
 * =============-< EXIT HANDLER >-===============
 *
 */
void exit_handler()
{
    puts(ECHO_MSG_EXIT);
    exit(0);
}

/*
 * =============-< FILE PATH REQUEST >-============
 *
 */
void filepath_request(int is_input)
{
    if (is_input)
    {
        puts(ECHO_MSG_INPUT_FILE_REQ);
    }
    else
    {
        puts(ECHO_MSG_OUTPUT_FILE_REQ);
    }
    puts(ECHO_ARROW);
}