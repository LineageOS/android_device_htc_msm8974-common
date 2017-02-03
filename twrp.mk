PRODUCT_COPY_FILES += device/htc/msm8974-common/recovery/root/etc/twrp.fstab:recovery/root/etc/twrp.fstab

RECOVERY_VARIANT := twrp

TW_BRIGHTNESS_PATH := /sys/class/leds/lcd-backlight/brightness
TW_IGNORE_MAJOR_AXIS_0 := true
TW_MAX_BRIGHTNESS := 255
TW_NO_SCREEN_BLANK := true
