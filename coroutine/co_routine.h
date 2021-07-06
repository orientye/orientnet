#ifdef _CO_ROUTINE_H_

struct coro;

int co_create(struct coro* c, void* (*start_routine)(void*), void* arg);
void co_resume(struct coro* c);
void co_yield(struct coro* c);
void co_destroy(struct coro* c);

#endif //_CO_ROUTINE_H_
