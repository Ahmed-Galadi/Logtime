#include "logtime_calculator.h"

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

/*t_time *add_times(t_time *a, t_time *b) {*/
/*	t_time *res = malloc(sizeof(t_time));*/
/*	int total_seconds = a->seconds + b->seconds;*/
/*	int total_minutes = a->minutes + b->minutes + (total_seconds / 60);*/
/*	int total_hours = a->hours + b->hours + (total_minutes / 60);*/
/**/
/*	res->seconds = total_seconds % 60;*/
/*	res->minutes = total_minutes % 60;*/
/*	res->hours = total_hours;*/
/*	return res;*/
/*}*/

void write_time_to_file(const char *filename, t_time *time) {
	FILE *file = fopen(filename, "w");
	if (!file)
		return;

	fprintf(file, "%dh %dm %ds\n", time->hours, time->minutes, time->seconds);
	fclose(file);
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		perror("Logtime Addition Failed!\n");
		return (1);
	}
	t_format *data = init_data(++argv);

	t_time *existing_logtime = read_time_from_file(data->file_name);
	if (!existing_logtime) {
		perror("Failed to read input file\n");
		return (1);
	}

	t_time *new_total = add_times(existing_logtime, data->logtime);
	write_time_to_file("accumulated_logtime", new_total);

	// Free allocated memory
	free(existing_logtime);
	free(new_total);
	// Also free t_format and its contents if needed

	return 0;
}
