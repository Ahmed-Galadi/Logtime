#!/bin/bash

log_start_date=$(who -u | awk '{print $3}')
log_start_hour=$(who -u | awk '{print $4}')

while true
do
	current_date=$(date "+%Y-%m-%d");
	current_time=$(date "+%H:%M:%S");

	echo "$log_start_date|$log_start_hour" > logs;
	echo "$current_date|$current_time" >> logs;	

	logtime=$(./calculate);
	timestamp=$(date "+%Y-%m-%d %H:%M:%S");
	current_month=$(date "+%Y-%m");
	echo "$timestamp|$logtime" >> logs;
	./addLogtime "$timestamp" "$logtime" "$current_month";
	sleep 5;
done

