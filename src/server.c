// Copyright (c) 2016 Brian Barto
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the MIT License. See LICENSE for more details.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "main.h"

int startup(char *hostname, char *portno) {
	int mainsockfd;
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	
	// Initializing serv_addr memory footprint to all integer zeros ('\0')
	memset((char *) &hints, 0, sizeof(struct addrinfo));
	
	// Get one or more arrdinfo structures that conforms with that provided by 'hints'
	hints.ai_family = AF_UNSPEC;              // Return IPv4 and IPv6 choices
	hints.ai_socktype = SOCK_STREAM;          // We want a TCP socket
	hints.ai_flags = AI_PASSIVE;              // All interfaces
	if (getaddrinfo(hostname, portno, &hints, &result) != 0) {
		fprintf(stderr, "server: Could not obtain internet address info.\n");
		return -1;
	}

	// Loop over results from getaddrinfo() and try to bind. Exit loop on first successful bind.
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		mainsockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (mainsockfd == -1)
			continue;

		if (bind(mainsockfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                           // Successful binding

		close(mainsockfd);
	}
	
	// Error if we didn't bind to any sockets
	if (rp == NULL) {
		fprintf(stderr, "server: Could not bind to socket %i\n", mainsockfd);
		return -1;
	}

	// Free the result structure we don't need anymore
	freeaddrinfo(result);
	
	// Mark socket as accepting connections, up to 5 backlogged connections
	listen(mainsockfd, 5);
	
	return mainsockfd;

}

void periodic(void) {
	printf("server periodic code\n");
}

void comp_cleanup(void) {
	// component cleanup here
}

int comp_type(void) {
	return SERVER;
}
