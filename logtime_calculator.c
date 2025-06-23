#include "logtime_calculator.h"
#include <stdlib.h>
#include <time.h>

time_t to_timestamp(t_date *date, t_time *time) {
	struct tm timeinfo = {0};

	timeinfo.tm_year = date->year - 1900;
	timeinfo.tm_mon  = date->month - 1;
	timeinfo.tm_mday = date->day;
	timeinfo.tm_hour = time->hours;
	timeinfo.tm_min  = time->minutes;
	timeinfo.tm_sec  = time->seconds;

	return mktime(&timeinfo);
}

int	calculate(t_timeData *data) {
	time_t start = to_timestamp(data->start_date, data->start_time);
	time_t end   = to_timestamp(data->current_date, data->current_time);

	int output = difftime(end, start);

	return (output);
}

void	print_logtime(int logtime_in_seconds) {
	int seconds = logtime_in_seconds;
	int hours = seconds / 3600;
	int minutes = (seconds % 3600) / 60;
	int secs = seconds % 60;
	
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("%d:%d:%d\n", hours, minutes, secs);
	fflush(stdout);
}

int main() {
	FILE *logs = fopen("logs", "r");
	char *start_time = NULL;
	char *current_time = NULL;
	size_t length = 0;
	t_date *date_start;
	t_date *date_now;
	t_time *time_start;
	t_time *time_now;
	t_timeData *data;

	// getting data from file and format it
	getline(&start_time, &length, logs);
	start_time = strdup(start_time);
	date_start = init_date(str_split(start_time, "|")[0]);
	time_start = init_time(str_split(start_time, "|")[1]);

	getline(&current_time, &length, logs);
	current_time = strdup(current_time);
	time_now = init_time(str_split(current_time, "|")[1]);
	date_now = init_date(str_split(current_time, "|")[0]);
	
	data = (t_timeData *)malloc(sizeof(t_timeData));
	data->start_date = date_start;
	data->start_time = time_start;
	data->current_date = date_now;
	data-> current_time = time_now;

	print_logtime(calculate(data));

	free(start_time);
	free(current_time);
	fclose(logs);
	return (0);
}
