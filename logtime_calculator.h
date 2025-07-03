#ifndef LOGTIME_CALCULATOR_H
# define LOGTIME_CALCULATOR_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

struct s_date {
	int year;
	int month;
	int day;
} typedef t_date;

struct s_time {
	int hours;
	int minutes;
	int seconds;
} typedef t_time;

struct s_timeData {
	t_date	*start_date;
	t_date	*current_date;
	t_time	*start_time;
	t_time	*current_time;
} typedef t_timeData;

struct s_format {
	t_date	*timeStamp_date;
	t_time	*timeStamp_time;
	t_time	*logtime;
	char	*file_name;
} typedef t_format;

struct s_print_data {
	t_date *today;
	t_time *today_logtime;
	t_time *month_logtime;
	int		days_passed;
	int		day_progress;
	int		month_progress;
	t_time	*required_hours;
} typedef t_print_data;

char	**str_split(const char *str, const char *delims);
t_date *init_date(char *date_str);
t_time *init_time(char *time_str);
t_format *init_data(char **args);
t_time *add_times(t_time *a, t_time *b);
t_time *read_time_from_file(const char *filename);

#endif
