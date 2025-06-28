#!/bin/bash

log_start_date=$(who -u | awk '{print $3}')
log_start_hour=$(who -u | awk '{print $4}')


cat accumulated_logtime > ".logtime_tracker_1";
cat sameDay > ".logtime_tracker_2";

while true
do
	current_date=$(date "+%Y-%m-%d");
	current_time=$(date "+%H:%M:%S");

	echo "$log_start_date|$log_start_hour" > logs;
	echo "$current_date|$current_time" >> logs;	

	logtime=$(./calculate);
	timestamp=$(date "+%Y-%m-%d %H:%M:%S");
	echo "$timestamp|$logtime" >> logs;
	./addLogtime "$timestamp" "$logtime" ".logtime_tracker_1";
	./createLogs "$timestamp" "$logtime";

	sleep 5;
done

