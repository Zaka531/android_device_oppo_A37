#! /vendor/bin/sh

# grep the modem partition for baseband version and set it
setprop gsm.version.baseband `strings /firmware/image/modem.b17 | grep "VENDOR" | head -1`
