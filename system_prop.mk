#
# Common system properties for msm8974
#

# Audio
PRODUCT_PROPERTY_OVERRIDES += \
    audio.offload.buffer.size.kb=32 \
    audio.offload.gapless.enabled=true \
    av.offload.enable=true \
    av.streaming.offload.enable=true \
    audio.offload.pcm.16bit.enable=true \
    audio.offload.pcm.24bit.enable=true \
    tunnel.audio.encode=true \
    use.voice.path.for.pcm.voip=false

# fluencetype can be "fluence" or "fluencepro" or "none"
PRODUCT_PROPERTY_OVERRIDES += \
    ro.qc.sdk.audio.fluencetype=fluence

PRODUCT_PROPERTY_OVERRIDES += \
    persist.audio.fluence.voicecall=true \
    persist.audio.fluence.speaker=true

# Graphics
PRODUCT_PROPERTY_OVERRIDES += \
    debug.egl.hw=1 \
    debug.mdpcomp.logs=0 \
    debug.sf.hw=1 \
    dev.pm.dyn_samplingrate=1 \
    persist.hwc.mdpcomp.enable=true \
    ro.opengles.version=196608 \
    ro.sf.lcd_density=480

# GPS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.gps.qc_nlp_in_use=0 \
    ro.gps.agps_provider=1 \
    ro.qc.sdk.izat.premium_enabled=0 \
    ro.qc.sdk.izat.service_mask=0x0

# Input
PRODUCT_PROPERTY_OVERRIDES += \
    ro.input.noresample=1

# Media
PRODUCT_PROPERTY_OVERRIDES += \
    media.aac_51_output_enabled=true \
    mm.enable.smoothstreaming=true

# MTP and USB-OTG
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.usb.config=mtp \
    persist.sys.isUsbOtgEnabled=true

# NFC
PRODUCT_PROPERTY_OVERRIDES += \
    debug.nfc.fw_download=true \
    debug.nfc.fw_boot_download=false

# NITZ
PRODUCT_PROPERTY_OVERRIDES += \
    persist.rild.nitz_plmn="" \
    persist.rild.nitz_long_ons_0="" \
    persist.rild.nitz_long_ons_1="" \
    persist.rild.nitz_long_ons_2="" \
    persist.rild.nitz_long_ons_3="" \
    persist.rild.nitz_short_ons_0="" \
    persist.rild.nitz_short_ons_1="" \
    persist.rild.nitz_short_ons_2="" \
    persist.rild.nitz_short_ons_3=""

# Qualcomm
PRODUCT_PROPERTY_OVERRIDES += \
    com.qc.hardware=true \
    persist.thermal.monitor=true \
    ro.qc.sdk.sensors.gestures=true \
    ro.vendor.extension_library=/vendor/lib/libqc-opt.so \
    ro.qualcomm.perf.cores_online=2

# RIL
PRODUCT_PROPERTY_OVERRIDES += \
    rild.libpath=/vendor/lib/libril-qc-qmi-1.so \
    ril.subscription.types=NV,RUIM \
    ro.baseband.arch=msm \
    ro.data.large_tcp_window_size=true \
    ro.ril.hsupa.category=6 \
    ro.ril.hsxpa=4 \
    ro.ril.disable.cpc=1 \
    ro.ril.def.agps.mode=1 \
    ro.telephony.call_ring.multiple=false \
    ro.use_data_netmgrd=true \
    persist.data.netmgrd.qos.enable=true \
    persist.radio.apm_sim_not_pwdn=1 \
    persist.radio.jbims=1 \
    DEVICE_PROVISIONED=1

# Wifi
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0
