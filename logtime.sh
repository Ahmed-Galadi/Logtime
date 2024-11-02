




#!/bin/bash

# Initialize variables
accumulated_time=0
session_start=$(date +%s)

# Function to format seconds to HH:MM:SS
format_time() {
    local seconds=$1
    printf "%02d:%02d:%02d" $((seconds/3600)) $((seconds%3600/60)) $((seconds%60))
}

# Function to check if screen is locked/sleeping
is_screen_locked() {
    idle_time=$(ioreg -c IOHIDSystem | awk '/HIDIdleTime/ {print int($NF/1000000000); exit}')
    if [ "$idle_time" -gt 60 ]; then  # If idle for more than 1 minute, consider locked
        return 0
    else
        return 1
    fi
}

# Trap Ctrl+C to show final time
trap 'echo -e "\nFinal active time: $(format_time $accumulated_time)"; exit' INT

echo "Screen time tracking started. Press Ctrl+C to stop."
echo "Time will pause after 1 minute of inactivity."

is_active=true

while true; do
    current_time=$(date +%s)
    
    if is_screen_locked; then
        if $is_active; then
            # Calculate time to add to accumulated time
            session_duration=$((current_time - session_start))
            accumulated_time=$((accumulated_time + session_duration))
            is_active=false
            echo -ne "\nInactive - time paused at: $(format_time $accumulated_time)\n"
        fi
    else
        if ! $is_active; then
            # Start new session
            session_start=$current_time
            is_active=true
            echo -ne "\nActive - resuming time from: $(format_time $accumulated_time)\n"
        else
            # Calculate current total (accumulated + current session)
            session_duration=$((current_time - session_start))
            total_time=$((accumulated_time + session_duration))
            echo -ne "\rActive time: $(format_time $total_time)  \r"
        fi
    fi
    
    sleep 1
done





