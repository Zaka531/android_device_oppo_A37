# Copyright (C) 2015-2017 The CyanogenMod Project
# Copyright (C) 2017, The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_l_mr1.mk)
$(call inherit-product, device/oppo/A37/device.mk)
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

# Assert
TARGET_OTA_ASSERT_DEVICE := A37,A37f,A37fw,A37fs

# Must define platform variant before including any common things
TARGET_BOARD_PLATFORM_VARIANT := msm8916

PRODUCT_DEVICE := A37
PRODUCT_NAME := lineage_A37
PRODUCT_BRAND := OPPO
PRODUCT_MODEL := A37
PRODUCT_MANUFACTURER := OPPO

# Build fingerprint
PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="msm8916_64-user 5.1.1 LMY47V eng.root.20190711.032745 release-keys"

# GMS
PRODUCT_GMS_CLIENTID_BASE := android-oppo
