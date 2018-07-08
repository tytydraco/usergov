#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "root.h"
#include "stats.h"

int compare( const void* a, const void* b)
{
   int int_a = * ( (int*) a );
   int int_b = * ( (int*) b );

   // an easy expression for comparing
   return (int_a > int_b) - (int_a < int_b);
}

int get_cpu_load() {
	return get_stat_avg();
}

int get_present_cpus() {
	char* present_str = read_file(PATH_CPU "/present");
	int min_present = atoi(&present_str[0]);
	int max_present = atoi(&present_str[2]);
	return max_present - min_present;
}

int get_stat_avg() {
	long double a[4], b[4], loadavg;
	FILE *fp;
	char dump[50];

	fp = fopen(PATH_STAT, "r");
	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
	fclose(fp);
	usleep(STAT_AVG_SLEEP_MS * 1000);

	fp = fopen(PATH_STAT, "r");
	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
	fclose(fp);

	loadavg = ((b[0]+b[1]+b[2]) - (a[0]+a[1]+a[2])) / ((b[0]+b[1]+b[2]+b[3]) - (a[0]+a[1]+a[2]+a[3]));
	loadavg *= 100;

	if (loadavg > 100)
		loadavg = 100;
	if (loadavg < 0)
		loadavg = 0;
	return (int) (loadavg);
}

int* get_cpu_freqs() {
	char* freq_list_str = read_file(PATH_CPU "/cpu0/cpufreq/" CPU_AVAIL_FREQS);
	int* freq_list = (int*) malloc(12 * sizeof(int));

	char* buf = strtok(freq_list_str, " ");
	int freq_count = 0;
	while (buf != NULL) {
		freq_list[freq_count] = atoi(buf);

		// if we run out of space in the array, alloc 4 more slots
		if (freq_count > sizeof(freq_list))
			freq_list = (int*) realloc(freq_list, (freq_count + 4) * sizeof(int*));
		
		buf = strtok(NULL, " ");
		freq_count++;
	}
	qsort(freq_list, sizeof(freq_list) + 1, sizeof(int), compare);
	
	return freq_list;
}

void set_cpu_freq(int core, int target_freq) {	
	char* path = (char*) malloc(75 * sizeof(char));
	sprintf(path, PATH_CPU "cpu%d/" CPUFREQ CPU_SET_SPEED, core);
	char target_freq_str[8] = "";
	sprintf(target_freq_str, "%d", target_freq);
	write_file(path, target_freq_str);
	free(path);
}

void set_gov(int core, char* gov) {
	char* path = (char*) malloc(75 * sizeof(char));
	sprintf(path, PATH_CPU "cpu%d/" CPUFREQ CPU_GOV, core);

	write_file(path, gov);
	free(path);
}

char* read_file(char* path) {
	FILE* f = fopen(path, "r");

	fseek(f, 0L, SEEK_END);
	long bytes = ftell(f);
	fseek(f, 0L, SEEK_SET);

	char* output = (char*) malloc(bytes * sizeof(char));
	if (!f) {
		return NULL;
	}
	
	fread(output, sizeof(char), bytes, f);
	fclose(f);
	return output;
}

void write_file(char* path, char* data) {
	FILE* f = fopen(path, "w");
	if (!f) {
		return;
	}
	fprintf(f, "%s", data);
	fclose(f);
}

