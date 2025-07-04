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

t_time *add_times(t_time *a, t_time *b) {
	t_time *res = malloc(sizeof(t_time));
	int total_seconds = a->seconds + b->seconds;
	int total_minutes = a->minutes + b->minutes + (total_seconds / 60);
	int total_hours = a->hours + b->hours + (total_minutes / 60);

	res->seconds = total_seconds % 60;
	res->minutes = total_minutes % 60;
	res->hours = total_hours;
	return (res);
}

t_time *read_time_from_file(const char *filename) {
	FILE *file = fopen(filename, "r");
	int h = 0, m = 0, s = 0;
	
	if (!file)
		return NULL;
	fscanf(file, "%dh %dm %ds", &h, &m, &s);
	fclose(file);

	t_time *result = malloc(sizeof(t_time));
	result->hours = h;
	result->minutes = m;
	result->seconds = s;
	return result;
}

static int	nbr_len(int nbr)
{
	int		count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		count++;
	while (nbr)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*nbr_str;
	int		len_nbr;
	long	nbr;

	nbr = n;
	len_nbr = nbr_len(nbr);
	nbr_str = malloc(len_nbr + 1);
	nbr_str[len_nbr] = '\0';
	if (nbr < 0)
	{
		nbr_str[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
	{
		nbr_str[0] = '0';
		return (nbr_str);
	}
	while (nbr)
	{
		nbr_str[--len_nbr] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (nbr_str);
}
