#include "logtime_calculator.h"
#define FILE_NAME "sameDay"

bool	is_sameDay(t_date *savedDate, t_date *currentDate) {
	if (!savedDate || !currentDate)
		return (false);
	if (savedDate->day == currentDate->day 
		&& savedDate->month == currentDate->month 
		&& savedDate->year == currentDate->year)
		return (true);
	return (false);
}

char *read_file(FILE *file) {
	char *output = malloc(1025);

	return (output);
}

t_date *get_savedDate(t_date *dateStamp) {
	FILE	*sameDay_file;
	t_date	*output_date = NULL;

    if (access(FILE_NAME, F_OK) == 0) {
		sameDay_file = fopen(FILE_NAME, "r");
	    char buffer[256];
		fgets(buffer, sizeof(buffer), sameDay_file);
		char **splited_buffer = str_split(buffer, " ");
		output_date = init_date(splited_buffer[1]);
		fclose(sameDay_file);
		return (output_date);
	} 
	sameDay_file = fopen(FILE_NAME, "w");
	fprintf(sameDay_file, "%d-%d-%d 0:0:0", dateStamp->day, dateStamp->month, ```dateStamp->year);
	fclose(sameDay_file);
	return (dateStamp);
}

void	save_logs(t_format *data) {
	FILE	*logs_file = fopen("Detailed_logs.txt", "a");
	FILE	*sameDay = fopen(FILE_NAME, "r");
	FILE	*tracker_file = fopen(".logtime_tracker_2", "r"); // this file has the first data saved in sameDay file.. soo it keeps track of the changing loging time session .
	t_date	*savedDate = get_savedDate(data->timeStamp_date);
	t_time	*added_logtime = NULL;

	if (is_sameDay(savedDate, data->timeStamp_date)) {
		
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("require 2 args!\n");
		return (1);
	}
	t_format *data = init_data(++argv);
	printf("date: %d/%d/%d ==> logtime: %d:%d:%d\n", data->timeStamp_date->day, data->timeStamp_date->month, data->timeStamp_date->year,
				data->logtime->hours, data->logtime->minutes, data->logtime->seconds);
	save_logs(data);
	return (0);
}
