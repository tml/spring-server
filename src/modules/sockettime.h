#ifndef SOCKETTIME_H
#define SOCKETTIME_H 1

void sockettime_init(void);
void sockettime_set(int);
int sockettime_get(int);
int sockettime_elapsed(int);

#endif