#include "logtime_calculator.h"
#include <stdlib.h>
#include <time.h>

t_date *init_date(char *date_str) {
	t_date *output = (t_date *)malloc(sizeof(t_date));
	char **splited_date = str_split(date_str, "-");

	output->year = atoi(splited_date[0]);
	output->month = atoi(splited_date[1]);
	output->day = atoi(splited_date[2]);
	return (output);
}

t_time *init_time(char *time_str) {
	t_time *output = (t_time *)malloc(sizeof(t_time));
	char **splited_data = str_split(time_str, ":");

	output->hours = atoi(splited_data[0]);
	output->minutes = atoi(splited_data[1]);
	if (splited_data[2])
		output->seconds = atoi(splited_data[2]);
	else
		output->seconds = 0;
	return (output);
}


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

int main() {
	FILE *logs = fopen("logs", "r");
	char *start_time = NULL;
	char *current_time = NULL;
	size_t length = 0;
	t_date *date_start;
	t_time *time_start;

	getline(&start_time, &length, logs);
	start_time = strdup(start_time);
	date_start = init_date(str_split(start_time, "|")[0]);

	printf("%d/%d/%d\n", date_start->day, date_start->month, date_start->year);

	getline(&current_time, &length, logs);
	current_time = strdup(current_time);
	time_start = init_time(str_split(start_time, "|")[1]);

	printf("%d:%d\n", time_start->hours,time_start->minutes);

	printf("\nstart_time ===> %s\n", start_time);
	printf("current_time ===> %s\n", current_time);

	free(start_time);
	free(current_time);
	fclose(logs);
	return (0);
}
