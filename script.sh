#!/bin/sh
insmod /lib/modules/compat-wireless/compat.ko
insmod /lib/modules/compat-wireless/cfg80211.ko
insmod /lib/modules/compat-wireless/mac80211.ko
insmod /lib/modules/compat-wireless/wlcore.ko
insmod /lib/modules/compat-wireless/wl18xx.ko
insmod /lib/modules/compat-wireless/wlcore_sdio.ko


killall udhcpc
killall wpa_supplicant

ip link set dev wlan0 up
usleep 500

wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf

usleep 2000
ip link set dev wlan0 down; ip link set dev wlan0 up

#wpa_cli scan
usleep 3000
#udhcpc -i wlan0 &
#usleep 2000
#ifconfig wlan0 192.168.188.232





