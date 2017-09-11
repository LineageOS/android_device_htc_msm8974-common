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

#ifndef _RT5506_H_
#define _RT5506_H_

#define RT5506_DEVICE "/dev/rt5501"
#define RT5506_MAX_REG_DATA 15

struct rt5506_reg_data {
    unsigned char addr;
    unsigned char val;
};

struct rt5506_config {
    unsigned int reg_len;
    struct rt5506_reg_data reg[RT5506_MAX_REG_DATA];
};

struct rt5506_comm_data {
    unsigned int out_mode;
    struct rt5506_config config;
};

enum {
    AMP_INIT = 0,
    AMP_MUTE,
    AMP_MAX_FUNC
};

enum PLAYBACK_MODE {
    PLAYBACK_MODE_OFF = AMP_MAX_FUNC,
    PLAYBACK_MODE_PLAYBACK,
    PLAYBACK_MODE_PLAYBACK8OH,
    PLAYBACK_MODE_PLAYBACK16OH,
    PLAYBACK_MODE_PLAYBACK32OH,
    PLAYBACK_MODE_PLAYBACK64OH,
    PLAYBACK_MODE_PLAYBACK128OH,
    PLAYBACK_MODE_PLAYBACK256OH,
    PLAYBACK_MODE_PLAYBACK500OH,
    PLAYBACK_MODE_PLAYBACK1KOH,
    PLAYBACK_MODE_VOICE,
    PLAYBACK_MODE_TTY,
    PLAYBACK_MODE_FM,
    PLAYBACK_MODE_RING,
    PLAYBACK_MODE_MFG,
    PLAYBACK_MODE_BEATS_8_64,
    PLAYBACK_MODE_BEATS_128_500,
    PLAYBACK_MODE_MONO,
    PLAYBACK_MODE_MONO_BEATS,
    PLAYBACK_MAX_MODE
};

enum HEADSET_OM {
    HEADSET_8OM = 0,
    HEADSET_16OM,
    HEADSET_32OM,
    HEADSET_64OM,
    HEADSET_128OM,
    HEADSET_256OM,
    HEADSET_500OM,
    HEADSET_1KOM,
    HEADSET_MONO,
    HEADSET_OM_UNDER_DETECT,
};

#define AMP_IOCTL_MAGIC 'g'
#define AMP_SET_CONFIG   _IOW(RT5501_IOCTL_MAGIC, 0x01, unsigned)
#define AMP_READ_CONFIG  _IOW(RT5501_IOCTL_MAGIC, 0x02, unsigned)
#define AMP_SET_MODE     _IOW(RT5501_IOCTL_MAGIC, 0x03, unsigned)
#define AMP_SET_PARAM    _IOW(RT5501_IOCTL_MAGIC, 0x04, unsigned)
#define AMP_WRITE_REG    _IOW(RT5501_IOCTL_MAGIC, 0x07, unsigned)
#define AMP_QUERY_OM     _IOW(RT5501_IOCTL_MAGIC, 0x08, unsigned)

int rt5506_set_mode(audio_mode_t mode);

#endif
