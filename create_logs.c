#include "logtime_calculator.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("require 2 args!\n");
		return (1);
	}
	t_format *data = init_data(++argv);
	printf("%d/%d/%d\n", data->timeStamp_date->day, data->timeStamp_date->month, data->timeStamp_date->year);
	return (0);
}
