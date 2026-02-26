#define _POSIX_C_SOURCE 199309L

#include "./libtdmm/tdmm.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	// --- TESTING FIRST FIT ---
	t_init(FIRST_FIT);
	struct timespec start, end;
	double cpu_time_used;
	
	FILE *fptr;

	fptr = fopen("first_fit_data.csv", "w");

	if (fptr == NULL) {
		perror("Error creating file!");
		return 1; 
	} 

	// First fit
	for (int i = 8; i <= 8 * 1024 * 1024; i += 8) {
		if (i % 10000 == 0) fflush(fptr);
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		char* s = (char*)t_malloc(i);
		if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		cpu_time_used = (double) (end.tv_sec - start.tv_sec) * 1000000000LL + 
                (double)(end.tv_nsec - start.tv_nsec) ;
		log_state("malloc", i, cpu_time_used, fptr);
		
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		t_free(s);
		if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
			perror("clock_gettime error");
			return 1;
		}

		cpu_time_used = (double) (end.tv_sec - start.tv_sec) * 1000000000LL + 
		(double)(end.tv_nsec - start.tv_nsec) ;
		log_state("free", i, cpu_time_used, fptr);
	}
	fclose(fptr);
	// --- TESTING BEST FIT ---
	t_init(BEST_FIT);
	fptr = fopen("best_fit_data.csv", "w");

	if (fptr == NULL) {
		perror("Error creating file!");
		return 1;
	}

	// Best fit:
	for (int i = 1; i <= 8 * 1024 * 1024; i++) {
		if (i % 10000 == 0) fflush(fptr);
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		char* s = (char*)t_malloc(i);
		if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		cpu_time_used = (double) (end.tv_sec - start.tv_sec) * 1000000000LL + 
                (double)(end.tv_nsec - start.tv_nsec) ;
		log_state("malloc", i, cpu_time_used, fptr);
		
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		t_free(s);
		if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
			perror("clock_gettime error");
			return 1;
		}

		cpu_time_used = (double) (end.tv_sec - start.tv_sec) * 1000000000LL + 
		(double)(end.tv_nsec - start.tv_nsec) ;
		log_state("free", i, cpu_time_used, fptr);
	}
	fclose(fptr);

	// --- TESTING WORST FIT ---

	t_init(WORST_FIT);
	fptr = fopen("worst_fit_data.csv", "w");

	if (fptr == NULL) {
		perror("Error creating file!");
		return 1;
	}

	// Worst fit:
	for (int i = 1; i <= 8 * 1024 * 1024; i++) {
		if (i % 10000 == 0) fflush(fptr);
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		char* s = (char*)t_malloc(i);
		if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		cpu_time_used = (double) (end.tv_sec - start.tv_sec) * 1000000000LL + 
                (double)(end.tv_nsec - start.tv_nsec) ;
		log_state("malloc", i, cpu_time_used, fptr);
		
		if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
			perror("clock_gettime error");
			return 1;
		}
		t_free(s);
		if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
			perror("clock_gettime error");
			return 1;
		}

		cpu_time_used = (double) (end.tv_sec - start.tv_sec) * 1000000000LL + 
		(double)(end.tv_nsec - start.tv_nsec) ;
		log_state("free", i, cpu_time_used, fptr);
	}

	fclose(fptr);
	return 0;
}

/*
statistics gather models:
- %age memory utilization on average during a program run (that is, the amount of
memory currently allocated and not freed by the user program divided by the amount of
memory you have requested from the system.
- %age memory utilization as a function of time, where a measurement is made each time a
request is made to allocate or deallocate memory
- Actual speeds of a tmalloc() and tfree() request as they vary with memory size. That is,
you should provide a chart showing the speed of malloc as a function of size, while
varying the size of allocation from 1 byte to 8M, on a log scale.
- Actual overhead of your own data structures over a program run (size of tables, linked
lists, or whatever you use to track the allocated and free space).
*/