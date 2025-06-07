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


char	**str_split(const char *str, const char *delims);

#endif
