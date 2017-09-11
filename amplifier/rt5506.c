/*
 * Copyright (C) 2013-2015 The CyanogenMod Project
 *               2017 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "rt5506"
//#define LOG_NDEBUG 0

#include "rt5506.h"

#include <linux/rt5506.h>

#include <cutils/log.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>

static struct rt5506_reg_data rt5506_playback_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x1A, }, // gain -2dB
    { 0x02, 0x80, }, // noise gate on
    { 0x08, 0x37, }, // noise gate on
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x02, }, // noise gate setting
    { 0x0A, 0x03, }, // noise gate setting
    { 0x0B, 0xD8, }, // noise gate -4dB
    { 0x93, 0xAD, }, // de -pop noise enlarge CP Freq
    { 0x90, 0x93, }, // fix 1X mode
};

static struct rt5506_reg_data rt5506_playback_128_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x1D, }, // gain +1dB
    { 0x02, 0x80, }, // noise gate on
    { 0x08, 0x37, }, // noise gate on
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x02, }, // noise gate setting
    { 0x0A, 0x03, }, // noise gate setting
    { 0x0B, 0xD8, }, // noise gate -4dB
    { 0x93, 0xAD, }, // de -pop noise enlarge CP Freq
    { 0x90, 0x93, }, // fix 1X mode
};

static struct rt5506_reg_data rt5506_ring_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x0C, }, // gain -16dB
    { 0x02, 0x81, }, // noise gate on
    { 0x08, 0x01, }, // noise gate on
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x01, }, // noise gate setting
    { 0x0A, 0x00, }, // noise gate setting
    { 0x0B, 0xC7, }, // noise gate -35dB
};

static struct rt5506_reg_data rt5506_voice_data[] = {
    { 0x00, 0xC0, },
    { 0x01, 0x1C, }, // gain 0dB
    { 0x02, 0x00, }, // noise gate off
    { 0x07, 0x7F, }, // noise gate setting
    { 0x09, 0x01, }, // noise gate setting
    { 0x0A, 0x00, }, // noise gate setting
    { 0x0B, 0xC7, }, // noise gate setting
    { 0x93, 0xAD, }, // de -pop noise enlarge CP Freq
    { 0x90, 0x93, }, //fix 1X mode
};

int rt5506_set_mode(audio_mode_t mode) {
    struct rt5506_comm_data amp_data;
    struct rt5506_config amp_config;
    int headsetohm = HEADSET_OM_UNDER_DETECT;
    int fd;
    int rc = 0;

    /* Open the amplifier device */
    if ((fd = open(RT5506_DEVICE, O_RDWR)) < 0) {
        rc = -errno;
        ALOGE("%s: error opening amplifier device %s: %d\n",
                __func__, RT5506_DEVICE, rc);
        goto set_mode_err;
    }

    /* Get impedance of headset */
    if (ioctl(fd, AMP_QUERY_OM, &headsetohm) < 0) {
        rc = -errno;
        ALOGE("%s: error querying headset impedance: %d\n", __func__, rc);
        goto set_mode_err;
    }

    switch(mode) {
        default:
        case AUDIO_MODE_NORMAL:
            /* For headsets with a impedance between 128ohm and 1000ohm */
            if (headsetohm >= HEADSET_128OM && headsetohm <= HEADSET_1KOM) {
                ALOGI("%s: Mode: Playback 128\n", __func__);
                amp_config.reg_len = sizeof(rt5506_playback_128_data) / sizeof(struct rt5506_reg_data);
                memcpy(&amp_config.reg, rt5506_playback_128_data, sizeof(rt5506_playback_128_data));
                amp_data.out_mode = PLAYBACK_MODE_PLAYBACK128OH;
            } else {
                ALOGI("%s: Mode: Playback\n", __func__);
                amp_config.reg_len = sizeof(rt5506_playback_data) / sizeof(struct rt5506_reg_data);
                memcpy(&amp_config.reg, rt5506_playback_data, sizeof(rt5506_playback_data));
                amp_data.out_mode = PLAYBACK_MODE_PLAYBACK;
            }
            amp_data.config = amp_config;
            break;
        case AUDIO_MODE_RINGTONE:
            ALOGI("%s: Mode: Ring\n", __func__);
            amp_config.reg_len = sizeof(rt5506_ring_data) / sizeof(struct rt5506_reg_data);
            memcpy(&amp_config.reg, rt5506_ring_data, sizeof(rt5506_ring_data));
            amp_data.out_mode = PLAYBACK_MODE_RING;
            amp_data.config = amp_config;
            break;
        case AUDIO_MODE_IN_CALL:
        case AUDIO_MODE_IN_COMMUNICATION:
            ALOGI("%s: Mode: Voice\n", __func__);
            amp_config.reg_len = sizeof(rt5506_voice_data) / sizeof(struct rt5506_reg_data);
            memcpy(&amp_config.reg, rt5506_voice_data, sizeof(rt5506_voice_data));
            amp_data.out_mode = PLAYBACK_MODE_VOICE;
            amp_data.config = amp_config;
            break;
    }

    /* Set the selected config */
    if ((rc = ioctl(fd, AMP_SET_CONFIG, &amp_data)) != 0) {
        rc = -errno;
        ALOGE("%s: ioctl AMP_SET_CONFIG failed, ret = %d\n", __func__, rc);
        goto set_mode_err;
    }

set_mode_err:
    close(fd);

    return rc;
}
