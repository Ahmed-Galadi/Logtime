#include "logtime_calculator.h"

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
	if (splited_data[1])
		output->minutes = atoi(splited_data[1]);
	else
		output->seconds = 0;

	if (splited_data[2])
		output->seconds = atoi(splited_data[2]);
	else
		output->seconds = 0;
	return (output);

}

t_format *init_data(char **args) {
	t_format *output = (t_format *)malloc(sizeof(t_format));
	char **splited_timestamp = str_split(args[0], " ");
	output->timeStamp_date = init_date(splited_timestamp[0]);
	output->timeStamp_time = init_time(splited_timestamp[1]);
	output->logtime = init_time(args[1]);
	output->file_name = args[2];
	return (output);	
}
