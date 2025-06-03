#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main() {
	FILE *logs = fopen("logs", "r");
	char *start_time = NULL;
	char *current_time = NULL;
	size_t length = 0;

	getline(&start_time, &length, logs);
	start_time = strdup(start_time);
	return (0);
}
