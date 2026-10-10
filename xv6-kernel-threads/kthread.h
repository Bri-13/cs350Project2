#ifndef XV6_PUBLIC_KTHREAD_H
#define XV6_PUBLIC_KTHREAD_H

#define NTHREAD			16
#define MAX_MUTEXES     64

// prototypes for pt 1 - Zara
int kthread_create(void*(*start_func)(), void* stack, int stack_size);
int kthread_id();
void kthread_exit();
int kthread_join(int thread_id);

// prototypes for pt 2 - Huynh
int kthread_mutex_alloc();
int kthread_mutex_dealloc(int mutex_id);
int kthread_mutex_lock(int mutex_id);
int kthread_mutex_unlock(int mutex_id);

#endif