/*
   This file is part of ArduinoIoTCloud.

   Copyright 2019 ARDUINO SA (http://www.arduino.cc/)

   This software is released under the GNU General Public License version 3,
   which covers the main part of arduino-cli.
   The terms of this license can be found at:
   https://www.gnu.org/licenses/gpl-3.0.en.html

   You can be released from the requirements of the above licenses by purchasing
   a commercial license. Buying such a license is mandatory if you want to modify or
   otherwise use the software for commercial activities involving the Arduino
   software without disclosing the source code of your own applications. To purchase
   a commercial license, send an email to license@arduino.cc.
*/

#ifndef ARDUINO_WIFI_CONNECTION_HANDLER_H_
#define ARDUINO_WIFI_CONNECTION_HANDLER_H_

/******************************************************************************
   INCLUDE
 ******************************************************************************/

#include "ConnectionHandlerInterface.h"

/******************************************************************************
   CLASS DECLARATION
 ******************************************************************************/

/** GenericConnectionHandler class
 * This class aims to wrap a connectionHandler and provide a generic way to
 * instantiate a specific connectionHandler type
 */
class GenericConnectionHandler : public ConnectionHandler
{
  public:

    GenericConnectionHandler(): _ch(nullptr) {}

    unsigned long getTime() override;
    Client & getClient() override;
    UDP & getUDP() override;

    void updateSetting(const models::NetworkSetting& s) override;

  protected:

    NetworkConnectionState update_handleInit         () override;
    NetworkConnectionState update_handleConnecting   () override;
    NetworkConnectionState update_handleConnected    () override;
    NetworkConnectionState update_handleDisconnecting() override;
    NetworkConnectionState update_handleDisconnected () override;

  private:

    ConnectionHandler* _ch;
};

#endif /* ARDUINO_WIFI_CONNECTION_HANDLER_H_ */
