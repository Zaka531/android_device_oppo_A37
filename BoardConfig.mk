#
# Copyright (C) 2016 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

BOARD_VENDOR := oppo

DEVICE_PATH := device/oppo/A37

FORCE_32_BIT := true

# Inherit from msm8916-common
-include device/cyanogen/msm8916-common/BoardConfigCommon.mk

# Assertions
TARGET_BOARD_INFO_FILE ?= $(DEVICE_PATH)/board-info.txt

# Kernel
BOARD_KERNEL_OFFSET := 0x00008000
BOARD_KERNEL_CMDLINE += androidboot.selinux=permissive
BOARD_KERNEL_IMAGE_NAME := Image
TARGET_KERNEL_SOURCE := kernel/oppo/msm8916
BOARD_KERNEL_SEPARATED_DT := true
TARGET_KERNEL_ARCH := arm64
TARGET_CUSTOM_DTBTOOL := dtbToolOppo
TARGET_KERNEL_CONFIG := lineageos_a37f_defconfig

# File System
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 33554432
BOARD_CACHEIMAGE_PARTITION_SIZE := 126877696
BOARD_PERSISTIMAGE_PARTITION_SIZE := 33554432
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 33554432
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 2859466752
BOARD_USERDATAIMAGE_PARTITION_SIZE := 11632902144
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.qcom

# Dexpreopt
ifeq ($(HOST_OS),linux)
  ifneq ($(TARGET_BUILD_VARIANT),eng)
      WITH_DEXPREOPT := true
      WITH_DEXPREOPT_BOOT_IMG_AND_SYSTEM_SERVER_ONLY := true
      DONT_DEXPREOPT_PREBUILTS := true
      USE_DEX2OAT_DEBUG := false
      WITH_DEXPREOPT_DEBUG_INFO := false
  endif
endif

# Init
TARGET_INIT_VENDOR_LIB := libinit_msm8916
TARGET_PLATFORM_DEVICE_BASE := /devices/soc.0/
TARGET_RECOVERY_DEVICE_MODULES := libinit_msm8916

# Security Patch Level
VENDOR_SECURITY_PATCH := 2018-03-01

# HIDL
DEVICE_MANIFEST_FILE += $(DEVICE_PATH)/manifest.xml

# Display
TARGET_SCREEN_DENSITY := 280

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth

# Charger
BOARD_CHARGER_ENABLE_SUSPEND := true
BOARD_CHARGER_DISABLE_INIT_BLANK := true
BACKLIGHT_PATH := /sys/class/leds/lcd-backlight/brightness

# Encryption
TARGET_LEGACY_HW_DISK_ENCRYPTION := true
TARGET_KEYMASTER_WAIT_FOR_QSEE := true

# Camera
BOARD_GLOBAL_CFLAGS += -DCONFIG_OPPO_CAMERA_51
TARGET_NEEDS_PLATFORM_TEXT_RELOCATIONS := true
TARGET_HAS_LEGACY_CAMERA_HAL1 := true
TARGET_PROCESS_SDK_VERSION_OVERRIDE += \
	/system/bin/mediaserver=23

# GPS
TARGET_NO_RPC := true

# Releasetools
TARGET_RECOVERY_UPDATER_LIBS := librecovery_updater_oppo
TARGET_RELEASETOOLS_EXTENSIONS := device/oppo/common

# Shim
TARGET_LD_SHIM_LIBS += \
    /system/vendor/lib/libmmcamera2_stats_modules.so|libshim_camera.so \
    /system/vendor/lib/libmmcamera2_stats_algorithm.so|libcamera_shim.so \
    /system/vendor/lib/hw/camera.vendor.msm8916.so|libshim_camera.so

# SEpolicy
#BOARD_SEPOLICY_DIRS += \
#    $(PLATFORM_PATH)/sepolicy

# Wi-Fi
TARGET_PROVIDES_WCNSS_QMI := true

# Proprietary Prebuilt
-include vendor/oppo/A37/BoardConfigVendor.mk
