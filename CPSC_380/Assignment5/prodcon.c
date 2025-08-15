#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <time.h>

#include "buffer.h"

/* the buffer */
struct buffer_item buffer[BUFFER_SIZE];

/* the semaphores (full and empty) */ 
sem_t full;
sem_t empty;

/* the mutex lock */
pthread_mutex_t mutex;

/* the in and out indexes */
int in = 0;
int out = 0;


/* inserts an object into buffer -> returns 0 if successful */
int insert_item(struct buffer_item item) {
   
    // wait for at least one slot in the buffer to be empty
    sem_wait(&empty);
    
    // once a slot is open, lock the mutex lock 
    pthread_mutex_lock(&mutex);

    // insert item at the in index
    buffer[in] = item;

    // update the in position for the next insert (account for circling back)
    in = (in + 1) % BUFFER_SIZE;

    // release the mutex lock
    pthread_mutex_unlock(&mutex);

    // increase the full semaphore
    sem_post(&full);

    return 0;
    
}

/* remove an object from buffer -> returns 0 if successful */
int remove_item(struct buffer_item *item) {

    // wait for at least one slot in the buffer to be full
    sem_wait(&full);

    // once a slot is filled, lock the mutex lock 
    pthread_mutex_lock(&mutex);

    // remove an item 
    *item = buffer[out];

    // update the out position for the next remove (account for circling back)
    out = (out + 1) % BUFFER_SIZE;

    // release the mutex lock
    pthread_mutex_unlock(&mutex);

    // increase the semaphore and release
    sem_post(&empty);

    return 0;
}

/* produces items for the buffer in a loop */
void *producer(void *param) {
    struct buffer_item item;

    while(1) {
        /* sleep for a random period of time */
        sleep((rand() % 2) + 1); // between 1 and 2 seconds
        
        /* generate a random data */
        // each buffer_item has an array of 30 data numbers, each from values 0-255
        for (int i = 0; i < 30; i++) {
            item.data[i] = rand() % 256;

            // add to the item's checksum 
            // item.cksum += item.data[i];
        }

        // calculate checksum 
        for (int i = 0; i < 30; i++) {
            item.cksum += item.data[i];
        }

        if (insert_item(item)) {
            fprintf(stderr, "error: producer could not produce item %d\n", item.cksum);
        }
        else {
            printf("producer produced item %d\n", item.cksum);
        }
    }
}

/* consumes items from the buffer in a loop */
void *consumer(void *param) {
    struct buffer_item item;
    
    while(1) {
        /* sleep for a random period of time */
        sleep((rand() % 2) + 1); // between 1 and 2 seconds

        if (remove_item(&item)) {
            fprintf(stderr, "error: consumer could not consume item %d\n", item.cksum);
        }
        else {
            printf("consumer consumed item %d\n", item.cksum);

            // calculate the checksum that is expected
            uint16_t calc_cksum = 0;
            for (int i = 0; i < 30; i++) {
                calc_cksum += item.data[i];
            }

            // verify checksums are equal
            if (calc_cksum != item.cksum) {
                fprintf(stderr, "error: checksums do not match. checksum expected: %d\n", calc_cksum);
                exit(1);
            }
        }
    }
}

void initialize_buffer() {
    // 1. initialize empty and full semaphores (counting semaphores)

        // sem_init(sem_t *sem, int pshared, unsigned int value)
            // pshared -> (0) means shared between threads, (!0) means shared between processes
            // value -> value to assign to the semaphore upon initialization
    sem_init(&empty, 0, BUFFER_SIZE); // starts at buffer_size because there are n empty slots
    sem_init(&full, 0, 0); // starts at 0 because there are 0 full slots

    // 2. initialize mutex (mutex lock)
        // ...init(..._t *mutex, ...attr_t *attr) attr->null if no attributes
    pthread_mutex_init(&mutex, NULL);
}

int main(int argc, char *argv[]) {
    // ./prodcon <delay> <#producer threads> <#consumer threads>

    // 1. Get command line arguments argv[1], argv[2], argv[3] 

    // if not enough arguments provided
    if (argc != 4) { 
        fprintf(stderr, "Usage: %s <delay> <# of producer threads> <# of consumer threads>\n", argv[0]);
        return 1;
    }

    // if correct number of arguments, assign them corectly
    int delay = atoi(argv[1]);
    int num_producer_threads = atoi(argv[2]);
    int num_consumer_threads = atoi(argv[3]);

    // initialize the random generator
    srand(time(NULL));

    // 2. Initialize buffer
    initialize_buffer();

    // 3. Create producer thread(s)
    pthread_t producers[num_producer_threads]; // producer thread array

    for (int i = 0; i < num_producer_threads; i++) {
        // pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine) (void *arg), void *arg);
        // pthread_create(thread id, attributes or NULL, function to run, parameters to pass through)
        pthread_create(&producers[i], NULL, producer, NULL);
    }

    // 4. Create consumer thread(s)
    pthread_t consumers[num_consumer_threads]; // consumer thread array

    for (int i = 0; i < num_consumer_threads; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    // 5. Sleep
    sleep(delay);

    // 6. Exit 
    return 0;
    
}