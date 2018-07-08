#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "root.h"
#include "stats.h"
#include "alg.h"

int main(int argc, char** argv) {
	setup_tunables();
	prepare();

	while (1) {
		algorithm();
	}

	return 0;
}

