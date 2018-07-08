#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "root.h"
#include "stats.h"
#include "alg.h"

int main() {
	prepare();

	for (;;) {
		algorithm();
	}

	return 0;
}

