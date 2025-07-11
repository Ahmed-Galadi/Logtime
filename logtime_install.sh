#!/bin/bash

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
GRAY='\033[0;37m'
BOLD='\033[1m'
NC='\033[0m' # No Color

init_logtime() {
	echo "Hi $USER To get started, please enter the number of hours you've already logged this month (as shown in your Discord):

Example: If your current logtime is \"42h\", enter it as: 42

This helps me initialize your progress accurately. Press Enter when you're ready
Your Logtime this Month is: "
read init_logtime
echo "${init_logtime}h 0m 0s" > accumulated_logtime
}

install() {
    git clone https://github.com/Ahmed-Galadi/Logtime.git $HOME/logtime
	cd $HOME/logtime
	cc logtime_calculator.c str_split.c logtime_utils.c  -o calculate
	cc add_logtime.c logtime_utils.c str_split.c -o addLogtime
	cc  logtime_print.c logtime_utils.c str_split.c -o logtimePrint 
	init_logtime
	mkdir ~/.config/autostart
	cat > ~/.config/autostart/logtime.desktop <<EOF
[Desktop Entry]
Type=Application
Exec=$HOME/logtime/logtime.sh
Path=$HOME/logtime
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name=Logtime Tracker
Comment=Start logtime tracker at login
EOF
	echo "alias logtime=\"$HOME/logtime/logtimePrint\"" >> $HOME/.zshrc
	echo "alias logtime=\"$HOME/logtime/logtimePrint\"" >> $HOME/.bashrc
	echo "Logtime has been successfully installed!

Please restart your session (log out and log back in) so Logtime can start automatically in the background.

Here’s how to use it:

    Type logtime to view your current progress.

    Type logtime_help to see available commands and usage tips.

    Type logtime_edit to manually edit your logged data.

You’re all set — happy logging! "
}

loading_install() {
    local duration=${1:-5}
    local width=40
    local percentage=0

    export LC_ALL=en_US.UTF-8

    # Choose characters
    local fill_char="█"
    local empty_char="░"

    echo -e "$YELLOW Loading...$NC"
    while [ $percentage -le 100 ]; do
        local filled=$((percentage * width / 100))
        local empty=$((width - filled))
        
        local bar=""
        for ((i = 0; i < filled; i++)); do
            bar+="$fill_char"
        done
        for ((i = 0; i < empty; i++)); do
            bar+="$empty_char"
        done
        
        printf "\r${GREEN}[%s] %d%%%s" $bar $percentage 
        sleep $(echo "scale=2; $duration/100" | bc)
        percentage=$((percentage + 1))
    done
	install
    echo -e "\n${GREEN}Success!${NC}"
}

loading_install
