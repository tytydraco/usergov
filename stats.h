#ifndef STATS_H
#define STATS_H

// tunables
int STAT_AVG_SLEEP_MS;
float LOAD_MULTIPLIER;
int ALG_SLEEP_MS;

// paths
#define PATH_CPU "/sys/devices/system/cpu/"
#define PATH_STAT "/proc/stat"

// cpu subdirs and subfiles
#define CPUFREQ "cpufreq/"
#define CPU_CUR_FREQ "scaling_cur_freq"
#define CPU_GOV "scaling_governor"
#define CPU_MAX_FREQ "scaling_max_freq"
#define CPU_MIN_FREQ "scaling_min_freq"
#define CPU_AVAIL_FREQS "scaling_available_frequencies"
#define CPU_AVAIL_GOVS "scaling_available_governors"
#define CPU_SET_SPEED "scaling_setspeed"

// commands
#define CAT "cat "
#define ECHO "echo "
#define SU "su -c "
#define CPU_PERCENT "top -bn 1 | awk '{print $9}' | tail -n +8 | awk '{s+=$1} END {print s}' "

int get_cpu_load();
int get_present_cpus();
int get_stat_avg();
int* get_cpu_freqs(int core);
void set_cpu_freq(int core, int target_freq);
void set_gov(int core, char* gov);
char* read_file(char* path);
void write_file(char* path, char* data);

#endif

