#include "logtime_calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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
#define ORANGE  "\033[38;2;255;165;0m"
#define LAVENDER "\033[38;5;141m"
#define HOTPINK "\033[38;2;255;105;180m"
#define GREENYELLOW "\033[38;5;190m"
#define BABYBLUE "\033[38;2;137;207;240m"
#define BLRED "\033[38;5;203m"

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

/* ── difference in whole days between two tm structs ───────────── */
static int date_diff_days(struct tm a, struct tm b)
{
    time_t ta = mktime(&a);
    time_t tb = mktime(&b);
    return (int) ((tb - ta) / 86400);          /* 86400 s = 1 day   */
}

/* ── compute how many whole days are left in the current log‑month ── */
static int days_left_in_log_month(struct tm today)
{
    struct tm end = today;

    if (today.tm_mday >= 28) {                 /* period crosses month */
        end.tm_mon += 1;                       /* ⬆ next month        */
    }
    end.tm_mday = 27;                          /* fixed end‑day       */

    return (date_diff_days(today, end) + 1);     /* +1 ⇒ count today   */
}

/* ── core: hours you must log each remaining day ─────────────────── */
int daily_hours_goal(int accumulated_hours)
{
    time_t now = time(NULL);
    struct tm today = *localtime(&now);

    int remaining  = MONTHLY_GOAL - accumulated_hours;
    if (remaining <= 0)
        return 0;                              /* already hit target  */

    int days_left  = days_left_in_log_month(today);
    return (remaining + days_left - 1) / days_left;  /* ceil div      */
}

int progress_persentage(int logtime, int goal) {
	int output = 0;
	if (logtime >= goal)
		return 100;
	else
		output = (int)(((float)logtime / (float)goal) * 100);
	return output;
}

char *format_toprint(t_time *time)
{
    char *output = malloc(20);               /* "120h 59m 59s\0" fits in 14 */
    if (!output)                             /* always check malloc */
        return NULL;
	if (!time->minutes && !time->seconds) {
		if (time->hours > 9)
			sprintf(output, "%d hours/day", time->hours);
		else
			sprintf(output, " %d hours/day", time->hours);
	}
	else
	    sprintf(output, "%02dh %02dm %02ds",     /* zero‑pad each field */
		        time->hours, time->minutes, time->seconds);
    return (output);
}

char *hpd_status_msg(int hpd) {
	char *output = malloc(255);
	
	if (hpd <= 4)
		sprintf(output, GREEN BOLD"      U ARE SAFE     "RESET);
	else if (hpd > 4 && hpd <= 8)
		sprintf(output, GREENYELLOW BOLD"      U ARE OKAY     "RESET);
	else if (hpd > 8 && hpd <= 15)
		sprintf(output, ORANGE BOLD"        U LATE       "RESET);
	else if (hpd > 15 && hpd <= 20)
		sprintf(output, HOTPINK BOLD"      IN DANGER!     "RESET);
	else
		sprintf(output, LAVENDER BOLD"       GIVE UP       "RESET);
	return (output);
}

char *hpd_status_emoji(int hpd) {
	char *output = malloc(255);
	
	if (hpd <= 4)
		sprintf(output,GREEN "     ദി(• ᴗ - )✧     "RESET);
	else if (hpd > 4 && hpd <= 8)
		sprintf(output, GREENYELLOW"        ( •᷄ᴗ•́)       "RESET);
	else if (hpd > 8 && hpd <= 15)
		sprintf(output, ORANGE"       (·•᷄‎ࡇ•᷅ )      "RESET);
	else if (hpd > 15 && hpd <= 20)
		sprintf(output, HOTPINK"      ( ˶°ㅁ°)!!     "RESET);
	else
		sprintf(output, LAVENDER"     ｡°(°¯᷄◠¯᷅°)°｡     "RESET);
	return (output);
}

char *month_status_emoji(int month_progress) {
	char *output = malloc(255);
	
	if (month_progress <= 25)
		sprintf(output, HOTPINK BOLD"     LOW "RESET BLRED"(·•᷄_•᷅ )     "RESET);
	else if (month_progress > 25 && month_progress <= 50)
		sprintf(output, CYAN BOLD"    MEDIUM"RESET GREENYELLOW" (•̀ᴗ•́ )و   "RESET);
	else if (month_progress > 50 && month_progress <= 75)
		sprintf(output, BABYBLUE BOLD"  ALMOST "RESET GREEN"ᕙ( •̀ ᗜ •́ )ᕗ "RESET);
	else if (month_progress > 75 && month_progress <= 99)
		sprintf(output,LAVENDER BOLD" SO CLOSE "RED" ৻(•̀ ᗜ •́ ৻) "RESET);
	else if (month_progress >= 100)
		sprintf(output,YELLOW BOLD" CONGRATS!"RESET ORANGE"ヾ(˃ᴗ˂)◞"RESET LAVENDER"•"RESET BABYBLUE"*"HOTPINK"✰"RESET);
	return (output);
}

char *today_status(t_time *todays_time, int daily_goal, int month_progress) {
	char *output = malloc(1024);
	t_time *accumulated_logtime = read_time_from_file("accumulated_logtime");
    time_t now = time(NULL);
    struct tm today = *localtime(&now);

	if (todays_time->hours < 4) {

		sprintf(output, "  "YELLOW"│"RESET CYAN"   WE JUST STARTED"RESET YELLOW"   │   │   "RESET MAGENTA" DAYS LEFT:"RESET RED BOLD" %02d"RESET YELLOW"    │   │"RESET"%s"YELLOW"│\n  \
"YELLOW"│       "RESET LAVENDER "ᕕ( ᐛ )ᕗ"RESET YELLOW"       │   │"RESET"%s"YELLOW"│   │"RESET"%s"YELLOW"│\n"RESET, days_left_in_log_month(today), hpd_status_msg(daily_goal), month_status_emoji(month_progress), hpd_status_emoji(daily_goal));
	}
	else if (todays_time->hours >= 4 && todays_time->hours < 8) {
		sprintf(output, YELLOW"  │      "RESET ORANGE"GOOD WORK"RESET YELLOW"      │   │   "RESET MAGENTA" DAYS LEFT:"RESET RED BOLD" %02d"RESET YELLOW"    │   │"RESET"%s"YELLOW"│\n  \
│       "RESET HOTPINK"(ദി˙ᗜ ˙)"RESET YELLOW"      │   │"RESET"%s"YELLOW"│   │"RESET"%s"YELLOW"│\n"RESET, days_left_in_log_month(today), hpd_status_msg(daily_goal), month_status_emoji(month_progress), hpd_status_emoji(daily_goal));
	}
	else if (todays_time->hours >= 8 && todays_time->hours < 15) {
		sprintf(output, YELLOW"  │     "RESET GREENYELLOW"HARD WORKER"RESET YELLOW"     │   │    "RESET MAGENTA"DAYS LEFT:"RESET RED BOLD" %02d"RESET YELLOW"    │   │"RESET"%s"YELLOW"│\n  \
│        "RESET GREEN"ᕙ(⇀‸↼‶)ᕗ "RESET YELLOW"    │   │"RESET"%s"YELLOW"│   │"RESET"%s"YELLOW"│\n"RESET, days_left_in_log_month(today), hpd_status_msg(daily_goal), month_status_emoji(month_progress), hpd_status_emoji(daily_goal));
	}
	else if (todays_time->hours >= 15 && todays_time->hours < 20)
		sprintf(output, YELLOW"  │    "RESET ORANGE"SLEEP DESERVED"RESET YELLOW"   │   │    "RESET MAGENTA"DAYS LEFT:"RESET RED BOLD" %02d"RESET YELLOW"    │   │"RESET"%s"YELLOW"│\n  \
│        "RESET BABYBLUE"(ᴗ˳ᴗ)ᶻ𝗓𐰁 "RESET YELLOW"    │   │"RESET"%s"YELLOW"│   │"RESET"%s"YELLOW"│\n"RESET, days_left_in_log_month(today), hpd_status_msg(daily_goal), month_status_emoji(month_progress), hpd_status_emoji(daily_goal));
	else
		sprintf(output, YELLOW"  │     "RESET BLRED"BRAIN DAMAGE"RESET YELLOW"    │   │    "RESET MAGENTA"DAYS LEFT:"RESET RED BOLD" %02d "RESET YELLOW"   │   │"RESET"%s"YELLOW"│\n  \
│         "RESET BLRED"☉ ‿ ⚆ "RESET YELLOW"      │   │"RESET"%s"YELLOW"│   │"RESET"%s"YELLOW"│\n"RESET, days_left_in_log_month(today), hpd_status_msg(daily_goal), month_status_emoji(month_progress), hpd_status_emoji(daily_goal));
	return (output);
}

/*void progress_bar(int day_progress, int month progress) {*/
/**/
/*}*/

// print print data
void	print_data() {
	t_time *accumulated_logtime = read_time_from_file("accumulated_logtime");
	t_time *accumulated_for_today = parse_today_logtime();
	int		daily_goal = daily_hours_goal(accumulated_logtime->hours);
	int		daily_percent = progress_persentage(accumulated_for_today->hours, daily_goal); 
	int		monthly_percen = progress_persentage(accumulated_logtime->hours, MONTHLY_GOAL);


	printf(YELLOW "╭─────────────────────────────────────────────────────────────────────────────╮\n\
│                        "RESET ORANGE BOLD"⏱  TIME TRACKER STATS ⏱ "RESET YELLOW"                             │\n\
╰─────────────────────────────────────────────────────────────────────────────╯"RESET"\n\
\n\
  "YELLOW"╭─────────────────────╮   ╭─────────────────────╮   ╭─────────────────────╮\n\
  │                     │   │                     │   │                     │\n\
  │       "RESET CYAN BOLD"TODAY"RESET YELLOW"         │   │       "RESET GREEN BOLD"MONTH"RESET YELLOW"         │   │	  "YELLOW BOLD"HOURSE PER DAY"RESET YELLOW"    │\n\
  │                     │   │                     │   │                     │\n\
  │ "RESET CYAN"┌─────────────────┐"RESET YELLOW" │   │ "RESET GREEN"┌─────────────────┐"RESET YELLOW" │   │ "RESET ORANGE"┌─────────────────┐"RESET YELLOW" │\n");
	t_time th = {daily_goal, 0, 0};
	printf("  │ "RESET CYAN"│   "BOLD"%s"RESET CYAN"   │"RESET YELLOW" │   │ "RESET GREEN"│"BOLD"   %s   │"RESET YELLOW" │   │ "RESET ORANGE"│"BOLD"  %s   │"RESET YELLOW" │\n",
		format_toprint(accumulated_for_today), format_toprint(accumulated_logtime), format_toprint(&th));
	printf("  │ "RESET CYAN"└─────────────────┘"RESET YELLOW" │   │ "RESET GREEN"└─────────────────┘"RESET YELLOW" │   │ "RESET ORANGE"└─────────────────┘"RESET YELLOW" │\n");
	printf("  │                     │   │                     │   │                     │"RESET"\n");
	printf("%s", today_status(accumulated_for_today, daily_goal, monthly_percen));
	printf(YELLOW"  │                     │   │                     │   │                     │\n");
	printf("  ╰─────────────────────╯   ╰─────────────────────╯   ╰─────────────────────╯"RESET);
}

// Main demo function
int main() {
    clear_screen();
    matrix_loader(10);
    clear_screen();
	print_data();
    return (1);
}
