#include "co_routine.h"

struct coro {
};

int co_create(struct coro* c, void* (*start_routine)(void*), void* arg) {
	return 0;
}

void co_resume(struct coro* c) {

}

void co_yield(struct coro* c) {

}

void co_destroy(struct coro* c) {

}
