/*
   Copyright (c) 2016, The CyanogenMod Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysinfo.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;
using android::init::property_set;

static void init_alarm_boot_properties()
{
    char const *boot_reason_file = "/proc/sys/kernel/boot_reason";
    char const *power_off_alarm_file = "/persist/alarm/powerOffAlarmSet";
    std::string boot_reason;
    std::string power_off_alarm;
    std::string tmp = GetProperty("ro.boot.alarmboot","");

    if (ReadFileToString(boot_reason_file, &boot_reason)
            && ReadFileToString(power_off_alarm_file, &power_off_alarm)) {
        /*
         * Setup ro.alarm_boot value to true when it is RTC triggered boot up
         * For existing PMIC chips, the following mapping applies
         * for the value of boot_reason:
         *
         * 0 -> unknown
         * 1 -> hard reset
         * 2 -> sudden momentary power loss (SMPL)
         * 3 -> real time clock (RTC)
         * 4 -> DC charger inserted
         * 5 -> USB charger insertd
         * 6 -> PON1 pin toggled (for secondary PMICs)
         * 7 -> CBLPWR_N pin toggled (for external power supply)
         * 8 -> KPDPWR_N pin toggled (power key pressed)
         */
        if ((Trim(boot_reason) == "3" || tmp == "true")
                && Trim(power_off_alarm) == "1")
            property_set("ro.alarm_boot", "true");
        else
            property_set("ro.alarm_boot", "false");
    }
}

bool is3GB()
{
    /*
     * Memtotal example
     * A37fs:MemTotal:        3000776 kB
     * A37f: MemTotal:        1932040 kB
     */

    struct sysinfo sys;
    sysinfo(&sys);
    return sys.totalram > 2500000000ull;
}

void set_device_properties()
{
    char const *prjversion_file = "/proc/oppoVersion/prjVersion";
    std::string prjversion;

    // fingerprint (from stock /init.prop.self_adaptive.sh)
    std::string fingerprint_A37fs_fw = "OPPO/A37fw/A37fs:5.1.1/LMY47V/1455690779:user/release-keys";
    std::string fingerprint_A37fs_f = "OPPO/A37f/A37fs:5.1.1/LMY47V/1464410042:user/release-keys";
    std::string fingerprint_A37f_fw = "OPPO/A37fw/A37f:5.1.1/LMY47V/1519717163:user/release-keys";
    std::string fingerprint_A37f_f = "OPPO/A37f/A37f:5.1.1/LMY47V/1519717078:user/release-keys";

    /*
     * RAM:
     * A37f: 2GB
     * A37fs: 3GB
     */
    property_set("ro.product.device", is3GB() ? "A37fs" : "A37f");

    if (ReadFileToString(prjversion_file, &prjversion)) {
        /*
         * Read Oppo Project ID file to get the device model
         * in order to set device infomation.
         *
         * 15392 -> A37fw
         * 15396 -> A37fw (Indonesia 3G)
         * 15399 -> A37f
         */
        if (Trim(prjversion) == "15399") {
            property_set("ro.product.model", "A37f");
            property_set("ro.product.name", "A37f");
            property_set("ro.product.device", "A37f");
            property_set("ro.build.fingerprint", is3GB() ? fingerprint_A37fs_f : fingerprint_A37f_f);
        } else if (Trim(prjversion) == "15392" || Trim(prjversion) == "15396") {
            property_set("ro.product.model", "A37fw");
            property_set("ro.product.name", "A37fw");
            property_set("ro.product.device", "A37fw");
            property_set("ro.build.fingerprint", is3GB() ? fingerprint_A37fs_fw : fingerprint_A37f_fw);
            // 15396 is 3G
            if (Trim(prjversion) == "15396") {
                property_set("ro.telephony.default_network", "0,1"); // from stock /system/build_15396.prop
            }
        }
    }
}

void vendor_load_properties()
{
    set_device_properties();
    init_alarm_boot_properties();
}
