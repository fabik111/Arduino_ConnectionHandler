/*
   This file is part of ArduinoIoTCloud.
   Copyright 2020 ARDUINO SA (http://www.arduino.cc/)
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

/******************************************************************************
   INCLUDE
 ******************************************************************************/

#include "Arduino_ConnectionHandler.h"
#include "GenericConnectionHandler.h"

void GenericConnectionHandler::updateSetting(const models::NetworkSetting& s) {

    switch(s.type) {
        #if defined(BOARD_HAS_WIFI)
        case WIFI:
            _ch = new WiFiConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_ETHERNET)
        case ETHERNET:
            _ch = new EthernetConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_NB)
        case NB:
            _ch = new NBConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_GSM)
        case GSM:
            _ch = new GSMConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_CATM1_NBIOT)
        case CATM1:
            _ch = new CatM1ConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_CELLULAR)
        case CELL:
            _ch = new CellularConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_NOTECARD) // FIXME understand how to adapt it to the settings structure
        case NOTECARD:
            _ch = new NotecardConnectionHandler();
            break;
        #endif

        default:
            Debug.print(DBG_ERROR, "Network adapter not supported by this platform: %d", s.type);
            return;
    }
    _ch->updateSetting(s);
}

NetworkConnectionState GenericConnectionHandler::update_handleInit() {
    return _ch != nullptr ? _ch->update_handleInit() : INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleDisconnecting() {
    return _ch != nullptr ? _ch->update_handleDisconnecting() : INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleConnected() {
    return _ch != nullptr ? _ch->update_handleConnected() : INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleDisconnecting() {
    return _ch != nullptr ? _ch->update_handleDisconnecting() : INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleDisconnected() {
    return _ch != nullptr ? _ch->update_handleDisconnected() : INIT;
}
