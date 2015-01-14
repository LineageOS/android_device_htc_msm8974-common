#!/bin/sh
# loggy.sh.

date=`date +%F_%H-%M-%S`
logcat -v time -f  /storage/sdcard0/cm121logcat_${date}.txt
