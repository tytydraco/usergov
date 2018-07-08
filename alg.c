#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "root.h"
#include "stats.h"
#include "alg.h"

void setup_tunables() {
	STAT_AVG_SLEEP_MS = 1000;
	LOAD_MULTIPLIER = 1;
	ALG_SLEEP_MS = 0;
}

void prepare() {
	for (int i = 0; i < get_present_cpus() + 1; i++) {
		set_gov(i, "userspace");
	}
}

void algorithm() {	
	

	// set for all cpus that it can
	for (int i = 0; i < get_present_cpus() + 1; i++) {
		freq_list = get_cpu_freqs(i);
		freq_list_size = sizeof(freq_list) + 1;

		int load = get_cpu_load();
		int index = freq_list_size * (load * LOAD_MULTIPLIER / 100.0);
		printf("%d * (%d / %d) = index freq %d\n", freq_list_size, (int) (load * LOAD_MULTIPLIER), 100, index);

		set_cpu_freq(i, freq_list[index]);
	}
	
	usleep(ALG_SLEEP_MS * 1000);
}

