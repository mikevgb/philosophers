// int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)

// Creates a mutex, referenced by mutex, with attributes specified by attr. If attr is NULL, the default mutex 
// attribute (NONRECURSIVE) is used.
// Returned value
// If successful, pthread_mutex_init() returns 0, and the state of the mutex becomes initialized and unlocked.
// If unsuccessful, pthread_mutex_init() returns -1.