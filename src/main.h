#ifndef MAIN_H
#define MAIN_H 1

#include <sys/select.h>

#define DEFAULT_PORT        51717
#define DEFAULT_HOST        NULL
#define BUFFER_SIZE         1024
#define COMMAND_SIZE        4
#define COMMAND_LIMIT       10
#define PERIODIC_SECONDS    5
#define SERVER              1
#define CLIENT              2

// Function prototypes defined in server.c and client.c
void load_commands(void);
int periodic(void);
int comp_type(void);

// Globals
int mainsockfd;
fd_set active_fd_set;

#endif
