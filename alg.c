#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include "root.h"
#include "stats.h"
#include "alg.h"

void setup_tunables() {
	STAT_AVG_SLEEP_MS = 500;
	LOAD_MULTIPLIER = 1;
	ALG_SLEEP_MS = 0;

}

void prepare() {
	set_gov(0, "userspace");

	freq_list = get_cpu_freqs();
	freq_list_size = sizeof(freq_list) + 1;
}

void algorithm() {	
	int load = get_cpu_load();
	int index = freq_list_size * (load / 100.0);
	printf("%d * (%d / %d) = index freq %d\n", freq_list_size, load, 100, index);

	// set for all cpus that it can
	for (int i = 0; i < get_present_cpus() + 1; i++) {
		set_cpu_freq(i, freq_list[index]);
	}
	
	usleep(ALG_SLEEP_MS * 1000);
}

