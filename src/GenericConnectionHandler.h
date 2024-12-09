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

#ifndef ARDUINO_GENERIC_CONNECTION_HANDLER_H_
#define ARDUINO_GENERIC_CONNECTION_HANDLER_H_

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

    GenericConnectionHandler(bool const keep_alive=true): ConnectionHandler(keep_alive), _ch(nullptr) {}

    #if defined(BOARD_HAS_NOTECARD) || defined(BOARD_HAS_LORA)
      virtual bool available() = 0;
      virtual int read() = 0;
      virtual int write(const uint8_t *buf, size_t size) = 0;
    #else
      unsigned long getTime() override;

      /*
       * NOTE: The following functions have a huge risk of returning a reference to a non existing memory location
       * It is important to make sure that the internal connection handler is already allocated before calling them
       * When updateSettings is called and the internal connectionHandler is reallocated the references to TCP and UDP
       * handles should be deleted.
       */
      Client & getClient() override;
      UDP & getUDP() override;
    #endif

    bool updateSetting(const models::NetworkSetting& s) override;

    void connect() override;
    void disconnect() override;
    void addCallback(NetworkConnectionEvent const event, OnNetworkEventCallback callback) override;

    void setKeepAlive(bool keep_alive=true) override;

  protected:

    NetworkConnectionState update_handleInit         () override;
    NetworkConnectionState update_handleConnecting   () override;
    NetworkConnectionState update_handleConnected    () override;
    NetworkConnectionState update_handleDisconnecting() override;
    NetworkConnectionState update_handleDisconnected () override;

  private:

    ConnectionHandler* _ch;
};

#endif /* ARDUINO_GENERIC_CONNECTION_HANDLER_H_ */
