#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "root.h"
#include "stats.h"
#include "alg.h"

void prepare() {
	set_gov(0, "userspace");

	freq_list = get_cpu_freqs();
	freq_list_size = sizeof(freq_list) + 1;
}

void algorithm() {	
	int load = get_cpu_load();
	int index = freq_list_size * (load / 100.0);
	printf("%d * (%d / %d) = index freq %d\n", freq_list_size, load, 100, index);
	set_cpu_freq(0, freq_list[index]);
	usleep(ALG_SLEEP_MS * 1000);
}

