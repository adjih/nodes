APPLICATION = plant_node
#include ../Makefile.tests_common

BOARD ?= samr21-xpro
# #to avoid flooding the RAM
#RPL_MAX_ROUTING_ENTRIES = 4
RIOTBASE ?= $(CURDIR)/../../RIOT
FEATURES_REQUIRED = periph_adc periph_gpio
CFLAGS += -DDEVELHELP -DMICROCOAP_DEBUG -DRPL_MAX_ROUTING_ENTRIES=4

ifneq (,$(filter iot-lab_M3,$(BOARD)))
  FEATURES_REQUIRED += periph_i2c
  USEMODULE += lsm303dlhc
endif

USEPKG = microcoap

USEMODULE += vtimer
USEMODULE += rpl
USEMODULE += udp
USEMODULE += defaulttransceiver

include $(RIOTBASE)/Makefile.include
