/*
 * Copyright (C) 2015 The CyanogenMod Project <http://www.cyanogenmod.org>
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

#ifndef _BDROID_BUILDCFG_H
#define _BDROID_BUILDCFG_H

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
int property_get(const char *key, char *value, const char *default_value);
#ifdef __cplusplus
}
#endif

#include "osi/include/osi.h"

typedef struct {
    const char *product_name;
    const char *product_model;
} device_t;

static const device_t devices[] = {
    {"A37f", "OPPO A37f"},
    {"A37fw", "OPPO A37fw"},
};

static inline const char *BtmGetDefaultName()
{
    char product_name[92];
    property_get("ro.product.name", product_name, "");

    for (unsigned int i = 0; i < ARRAY_SIZE(devices); i++) {
        device_t device = devices[i];

        if (strcmp(device.product_name, product_name) == 0) {
            return device.product_model;
        }
    }

    // Fallback to OPPO A37
    return "OPPO A37";
}

#define BTM_DEF_LOCAL_NAME   BtmGetDefaultName()
#define BLE_VND_INCLUDED  FALSE
#endif
