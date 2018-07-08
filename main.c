#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "root.h"
#include "stats.h"
#include "alg.h"

int main(int argc, char** argv) {

	// set defaults
	setup_tunables();

	// set custom argument tunables
	while (1) {
		static struct option long_options[] = {
			{"delay", required_argument, 0, 'd'},
			{"multiplier", required_argument, 0, 'm'},
			{0, 0, 0, 0}
		};
		int option_index = 0;
		int c = getopt_long(argc, argv, "d:m:", long_options, &option_index);
	       	if (c == -1)
			break;
		switch (c) {
			case 0:
				break;
			case 'd':
				STAT_AVG_SLEEP_MS = atoi(optarg);
				break;
			case 'm':
				LOAD_MULTIPLIER = atof(optarg);
				break;
			default:
				abort();
		}
	}

	// setup governor
	prepare();

	// begin algorithm loop
	while (1) {
		algorithm();
	}

	return 0;
}

