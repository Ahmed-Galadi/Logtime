#include "logtime_calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

#define MONTHLY_GOAL 120

// Clear screen and move cursor to top
void clear_screen() {
    printf("\033[2J\033[H");
}

// Move cursor to specific position
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void progress_bar(int width, int duration_ms, int percentage)
{
    if (percentage < 0)   percentage = 0;
    if (percentage > 100) percentage = 100;

    int target = (percentage * width) / 100;

    for (int i = 0; i <= target; ++i) {
        printf("\r" BOLD YELLOW "Progress: [");

        for (int j = 0; j < i;   ++j) printf(GREEN "█");
        for (int j = i; j < width; ++j) printf(WHITE "░");

        printf(YELLOW "] %d%%" RESET, (i * 100) / width);
        fflush(stdout);
        usleep(duration_ms * 1000);
    }
    puts("");   /* newline after bar is complete */
}

// Matrix-style falling characters
void matrix_loader(int duration) {
    int i, j, k;
    char matrix_chars[] = "01";
    int rows = 12;
    int cols = 60;
    
    printf(BOLD GREEN "... LOADING ...\n\n" RESET);
    
    // Create the matrix display area
    for (i = 0; i < duration; i++) {
        // Move cursor up to redraw the matrix
        if (i > 0) {
            printf("\033[%dA", rows);
        }
        
        // Draw matrix rows
        for (j = 0; j < rows; j++) {
            printf(GREEN);
            for (k = 0; k < cols; k++) {
                // Add some randomness to make it look more authentic
                if (rand() % 4 == 0) {
                    printf(BOLD GREEN "%c", matrix_chars[rand() % 2]);
                } else {
                    printf(GREEN "%c", matrix_chars[rand() % 2]);
                }
            }
            printf(RESET "\n");
        }
        
        usleep(120000); // 120ms delay
    }
    
    // Clear the matrix and show completion
    printf("\033[%dA", rows);
    for (j = 0; j < rows; j++) {
        printf("\033[K\n"); // Clear each line
    }
}


// Pulse effect
void pulse_loader(int cycles) {
    char pulse_states[][20] = {
        "◐", "◓", "◑", "◒"
    };
    int i, j;
    
    for (i = 0; i < cycles; i++) {
        for (j = 0; j < 4; j++) {
            printf("\r" BOLD BLUE "Processing %s" RESET, pulse_states[j]);
            fflush(stdout);
            usleep(250000);
        }
    }
    printf("\r" GREEN "✓ Processing complete!\n" RESET);
}

// Wave animation
void wave_loader(int cycles) {
    char wave[][50] = {
        "▁▁▁▁▁▁▁▁▁▁",
        "▂▁▁▁▁▁▁▁▁▁",
        "▃▂▁▁▁▁▁▁▁▁",
        "▄▃▂▁▁▁▁▁▁▁",
        "▅▄▃▂▁▁▁▁▁▁",
        "▆▅▄▃▂▁▁▁▁▁",
        "▇▆▅▄▃▂▁▁▁▁",
        "█▇▆▅▄▃▂▁▁▁",
        "▇█▇▆▅▄▃▂▁▁",
        "▆▇█▇▆▅▄▃▂▁",
        "▅▆▇█▇▆▅▄▃▂",
        "▄▅▆▇█▇▆▅▄▃",
        "▃▄▅▆▇█▇▆▅▄",
        "▂▃▄▅▆▇█▇▆▅",
        "▁▂▃▄▅▆▇█▇▆",
        "▁▁▂▃▄▅▆▇█▇",
        "▁▁▁▂▃▄▅▆▇█",
        "▁▁▁▁▂▃▄▅▆▇",
        "▁▁▁▁▁▂▃▄▅▆",
        "▁▁▁▁▁▁▂▃▄▅",
        "▁▁▁▁▁▁▁▂▃▄",
        "▁▁▁▁▁▁▁▁▂▃",
        "▁▁▁▁▁▁▁▁▁▂"
    };
    
    int i, j;
    
    for (i = 0; i < cycles; i++) {
        for (j = 0; j < 23; j++) {
            printf("\r" BOLD CYAN "Analyzing %s" RESET, wave[j]);
            fflush(stdout);
            usleep(100000);
        }
    }
    printf("\r" GREEN "✓ Analysis complete!    \n" RESET);
}

t_time *parse_today_logtime() {
	FILE *today = fopen("sameDay", "r");
	char *data_string = NULL;
	char **splited_data = NULL;
	t_time *output = NULL;
	size_t length;

	getline(&data_string, &length, today);
	data_string = strdup(data_string);
	splited_data = str_split(data_string, " ");
	output = init_time(splited_data[1]);
	return (output);
}

t_date *get_todays_date() {

}

t_time *daily_logtime_goal(t_time *acc_logtime) {
	t_time *output = malloc(sizeof(t_time));
	
	if (acc_logtime->hours < MONTHLY_GOAL) {
		output->hours = 
	}
	return (output);
}

// print print data
void	print_data() {
	t_time *accumulated_logtime = read_time_from_file("accumulated_logtime");
	t_time *accumulated_for_today = parse_today_logtime();
	t_time *daily_goal = daily_logtime_goal(accumulated_logtime);
	int		daily_progress;
	int		monthly_progress;
	int		daily_percent;
	int		monthly_percent;
}

// Main demo function
int main() {
    clear_screen();
    
    /*printf(BOLD WHITE "╔══════════════════════════════════════╗\n");*/
    /*printf("║          ⏲  LOGTIME FARMER ⏲         ║\n");*/
    /*printf("╚══════════════════════════════════════╝\n\n" RESET);*/

    matrix_loader(10);
    clear_screen();
	print_data();
    return 0;
}
