#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

// write a multithreaded varion of the monte carlo simulation

// create global variables 
int totalPoints = 0;
int pointsInCircle = 0;
pthread_mutex_t threadLock;

// read in the number of points that should be generated

// create a function that creates a random precision number
double random_double() {
    return random() / ((double)RAND_MAX + 1);
}

// create a function that each thread will follow 
void* monteCarloThread(void *pointsPerThread) {
    int pointsForThread = *((int *)pointsPerThread); // num of points this thread will generate
    int threadPointsInCircle = 0; // num of points generated in the circle

    // generate a number of random points
    for (int i = 0; i < pointsForThread; i++) {
        double x = random_double() * 2.0 - 1.0;
        double y = random_double() * 2.0 - 1.0;

        // count the number of points that occur within the circle
        if (sqrt(x*x + y*y) < 1.0) {
            ++threadPointsInCircle;
        }
    }

    // store the result in the global variable
    pthread_mutex_lock(&threadLock); // lock the variables
    pointsInCircle += threadPointsInCircle;
    totalPoints += pointsForThread;
    pthread_mutex_unlock(&threadLock); // unlock the variables

    pthread_exit(NULL);
}
    
int main(int argc, char* argv[]) {
    // ERROR HANDLING: verify the input & parameters are valid
    // check if user included a parameter
    if (argc != 2) {
        printf("no parameter detected.\n");
        return 1;
    }
    
    // read in the parameter and convert to an integer
    int userNumPoints = atoi(argv[1]);
    // check if user included a valid integer parameter
    if (userNumPoints <= 0) {
        printf("invalid number of points entered as a parameter.\n");
        return 1;
    }

    // initialize the random number generator
    srand(time(NULL));

    // create two threads
    pthread_t threadOne;
    pthread_t threadTwo;

    // calculate the number of points each thread should execute
    int pointsForFirstThread = userNumPoints / 2;
    int pointsForSecThread;

    if (userNumPoints % 2 == 0) { // if total points is even
        pointsForSecThread = userNumPoints / 2;   
    }
    else {
        pointsForSecThread = (userNumPoints / 2) + 1;
    }

    // initialize each thread
    pthread_create(&threadOne, NULL, &monteCarloThread, &pointsForFirstThread);
    pthread_create(&threadTwo, NULL, &monteCarloThread, &pointsForSecThread);

    // wait for both threads to exit
    pthread_join(threadOne, NULL);
    pthread_join(threadTwo, NULL);

    // calculate and output the estimated value of pi
    // pi = 4 * (num of points in circle)/(total num of points)
    double piEstimation = 4.0 * pointsInCircle / totalPoints;
    printf("Total Points: %d\n", totalPoints);
    printf("Total Points in Circle: %d\n", pointsInCircle);
    printf("Estimate of Pi: %lf\n", piEstimation);

    // destroy the thread lock
    pthread_mutex_destroy(&threadLock);

    return 0;
}

