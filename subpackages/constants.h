// Settings of file environment
#define MAX_FILENAME_LENGTH 256
#define MAX_ITERATIONS 3000

// Settings of gradient descent algorithms
#define GRADIENT_COEFFICIENT 0.0001  // if normalized mode use 0.0001 else use 0.0005
#define ACCUMULATED_SPEED_COEFFICIENT 0.9
#define SHEDULER_STEP 1000
#define SHEDULER_COEFFICIENT 2
#define OMEGA 999999                 // Just a big number
#define EARLY_STOP 0                 // If the error increases, the algorithm terminates
#define SKIP_COUNT 10                // If the gradient does not change its SKIP_COUNT value once, the algorithm terminates
#define OMICRON 0.0000001            // Coefficient for derivatives

// Settings of post-gradient descent algorithm
#define NEIGHBOUR 0.01                // (t-NEIGHBOUR; t+NEIGHBOUR) for some parameter t
#define MICRO 0.00001                 // Approximation step
#define EPSILON 0.0001               // The difference at which the two numbers are considered equal

// Version
#define VERSION "release-1.0"

// Echo settings
#define ECHO_ARROW "echo: "
#define ECHO_MSG_MISSED_KEY "Missed the key, don't upset please!"
#define ECHO_MSG_EXIT "Bye"
#define ECHO_MSG_INPUT_FILE_REQ "Specify the path to the file for input:"
#define ECHO_MSG_OUTPUT_FILE_REQ "Specify the path to the file for output:"
#define ECHO_MSG_ERROR_FILE "Error: Cannot open file!"


/*
 * ----------------------------------------------
 * Last modified at 01.03.2023 by Kottoamatsukami
 * ----------------------------------------------
 */