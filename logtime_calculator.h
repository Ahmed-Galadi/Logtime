#ifndef LOGTIME_CALCULATOR_H
# define LOGTIME_CALCULATOR_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

char	**str_split(const char *str, const char *delims);

#endif
