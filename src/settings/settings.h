/*
 * This file is part of ArduinoIoTCloud.
 *
 * Copyright 2019 ARDUINO SA (http://www.arduino.cc/)
 *
 * This software is released under the GNU General Public License version 3,
 * which covers the main part of arduino-cli.
 * The terms of this license can be found at:
 * https://www.gnu.org/licenses/gpl-3.0.en.html
 *
 * You can be released from the requirements of the above licenses by purchasing
 * a commercial license. Buying such a license is mandatory if you want to modify or
 * otherwise use the software for commercial activities involving the Arduino
 * software without disclosing the source code of your own applications. To purchase
 * a commercial license, send an email to license@arduino.cc.
 */

#pragma once

#include "Arduino_ConnectionHandlerDefinitions.h"
#include <stdint.h>

namespace models {
  struct WiFiSetting {
    char ssid[33]; // Max length of ssid is 32 + \0
    char pwd[64];  // Max length of password is 63 + \0
  };

  struct EthernetSetting {
    IPAddress     ip;
    IPAddress     dns;
    IPAddress     gateway;
    IPAddress     netmask;
    unsigned long timeout;
    unsigned long response_timeout;
  };

  struct CellularSetting {
    char pin[8];
    char apn[101]; // Max length of apn is 100 + \0
    char login[32];
    char pass[32];
  };

  typedef CellularSetting GSMSetting;
  typedef CellularSetting NBSetting;
  typedef CellularSetting CATM1Setting;

  struct LoraSetting {
    char          appeui[17];    // appeui is 8 octets * 2 (hex format) + \0
    char          appkey[33];    // appeui is 16 octets * 2 (hex format) + \0
  };

  struct NetworkSetting {
    NetworkAdapter type;
    union {
      WiFiSetting   wifi;
      CATM1Setting  catM1;
      GSMSetting    gsm;
      NBSetting     nb;
      LoraSetting   lora;
    } values;
  };
}
