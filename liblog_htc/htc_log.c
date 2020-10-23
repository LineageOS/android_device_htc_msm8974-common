/*
 * Copyright (C) 2015 The CyanogenMod Project
 * Copyright (C) 2020 Android Ice Cold Project
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

#ifndef __unused
#define __unused  __attribute__((__unused__))
#endif

//#define LOG_NDEBUG 0

#define HTC_LOGLEVEL_VERBOSE 1
#define HTC_LOGLEVEL_DEBUG (1 << 1)
#define HTC_LOGLEVEL_INFO (1 << 2)
#define HTC_LOGLEVEL_WARN (1 << 3)
#define HTC_LOGLEVEL_ERROR (1 << 4)
#define HTC_LOGLEVEL_FATAL (1 << 5)

#define HTC_LOGMASK_DEFAULT (HTC_LOGLEVEL_INFO | HTC_LOGLEVEL_WARN | HTC_LOGLEVEL_ERROR | HTC_LOGLEVEL_FATAL)
#define HTC_LOGMASK_ALL 0xFFFFFFFF

#include <log/log.h>
#include <cutils/properties.h>

#if LOG_NDEBUG
#define HTC_LOGMASK HTC_LOGMASK_DEFAULT
#else
#define HTC_LOGMASK HTC_LOGMASK_ALL
#endif

signed int __htclog_read_masks(char *buf __unused, signed int len __unused)
{
    return 0;
}

int __htclog_init_mask(const char *a1 __unused, unsigned int a2 __unused, int a3 __unused)
{
    return property_get_int32("debug.htc.logmask", property_get_int32("persist.debug.htc.logmask", HTC_LOGMASK));
}

int __htclog_print_private(int a1 __unused, const char *a2 __unused, const char *fmt __unused, ...)
{
    return 0;
}
