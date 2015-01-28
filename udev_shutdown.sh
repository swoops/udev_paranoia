#!/bin/bash
### BEGIN INIT INFO
# Provides:          udev_shutdown
# Required-Start:    
# Required-Stop:     
# Default-Start:     
# Default-Stop:      0 6
# Short-Description: fix udev rules for next boot
# Description:  
#	This init script should be run before every shutdown or reboot
#	so that the udev rule that blocks all USB devices will be removed
#	before the next boot up.
### END INIT INFO

rule="/etc/udev/rules.d/11-to_rule_all.rules"
if ! [ $1 == "stop" ]; then
	echo
	echo "============================================================"
	echo "$0 was called without stop... that should not happen"
	echo "============================================================"
	echo
	exit 1
elif [ -e $rule ]; then
	echo "removing udev_paranoia rule"
	rm $rule
	exit 0
else
	echo "$rule DNE already"
	exit 0
fi

	
