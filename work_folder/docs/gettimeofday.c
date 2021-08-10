// The gettimeofday() function gets the system’s clock time.
// The current time is expressed in elapsed seconds and microseconds

// int gettimeofday ( struct timeval *tp ,  struct timezone *tz )

#include <sys/time.h>
#include <stdio.h>

int main() {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  printf("seconds : %ld\nmicro seconds : %ld", 
    current_time.tv_sec, current_time.tv_usec);

  return 0;
}