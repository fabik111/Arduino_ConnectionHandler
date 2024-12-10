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

#include "GenericConnectionHandler.h"
#include "Arduino_ConnectionHandler.h"

static inline ConnectionHandler* instantiate_handler(NetworkAdapter adapter);

bool GenericConnectionHandler::updateSetting(const models::NetworkSetting& s) {

    if(_ch != nullptr && _ch->_current_net_connection_state != NetworkConnectionState::INIT) {
        // If the internal connection handler is already being used and not in INIT phase we cannot update the settings
        return false;
    } else if(_ch != nullptr && _ch->_current_net_connection_state == NetworkConnectionState::INIT && _interface != s.type) {
        // If the internal connection handler is already being used and in INIT phase and the interface type is being changed
        // -> we need to deallocate the previously allocated handler

        // if interface type is not being changed -> we just need to call updateSettings
        delete _ch;
        _ch = nullptr;
    }

    if(_ch == nullptr) {
        _ch = instantiate_handler(s.type);
    }

    if(_ch != nullptr) {
        _interface = s.type;
        _ch->setKeepAlive(_keep_alive);
        return _ch->updateSetting(s);
    } else {
        _interface = NetworkAdapter::NONE;

        return false;
    }
}

NetworkConnectionState GenericConnectionHandler::update_handleInit() {
    return _ch != nullptr ? _ch->update_handleInit() : NetworkConnectionState::INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleConnecting() {
    return _ch != nullptr ? _ch->update_handleConnecting() : NetworkConnectionState::INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleConnected() {
    return _ch != nullptr ? _ch->update_handleConnected() : NetworkConnectionState::INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleDisconnecting() {
    return _ch != nullptr ? _ch->update_handleDisconnecting() : NetworkConnectionState::INIT;
}

NetworkConnectionState GenericConnectionHandler::update_handleDisconnected() {
    return _ch != nullptr ? _ch->update_handleDisconnected() : NetworkConnectionState::INIT;
}

#if not (defined(BOARD_HAS_LORA) or defined(BOARD_HAS_NOTECARD))
unsigned long GenericConnectionHandler::getTime() {
    return _ch != nullptr ? _ch->getTime() : 0;
}

Client & GenericConnectionHandler::getClient() {
    return _ch->getClient(); // NOTE _ch may be nullptr
}

UDP & GenericConnectionHandler::getUDP() {
    return _ch->getUDP(); // NOTE _ch may be nullptr
}

#endif // not (defined(BOARD_HAS_LORA) or defined(BOARD_HAS_NOTECARD))

void GenericConnectionHandler::connect() {
    if(_ch!=nullptr) {
        _ch->connect();
    }
    ConnectionHandler::connect();
}

void GenericConnectionHandler::disconnect() {
    if(_ch!=nullptr) {
        _ch->disconnect();
    }
    ConnectionHandler::disconnect();
}

void GenericConnectionHandler::addCallback(NetworkConnectionEvent const event, OnNetworkEventCallback callback) {
    if(_ch!=nullptr) {
        _ch->addCallback(event, callback);
    }
}

void GenericConnectionHandler::setKeepAlive(bool keep_alive) {
    _keep_alive = keep_alive;

    if(_ch!=nullptr) {
        _ch->setKeepAlive(keep_alive);
    }
}

static inline ConnectionHandler* instantiate_handler(NetworkAdapter adapter) {
    switch(adapter) {
        #if defined(BOARD_HAS_WIFI)
        case NetworkAdapter::WIFI:
            return new WiFiConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_ETHERNET)
        case NetworkAdapter::ETHERNET:
            return new EthernetConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_NB)
        case NetworkAdapter::NB:
            return new NBConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_GSM)
        case NetworkAdapter::GSM:
            return new GSMConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_CATM1_NBIOT)
        case NetworkAdapter::CATM1:
            return new CatM1ConnectionHandler();
            break;
        #endif

        #if defined(BOARD_HAS_CELLULAR)
        case NetworkAdapter::CELL:
            return new CellularConnectionHandler();
            break;
        #endif

        default:
            Debug.print(DBG_ERROR, "Network adapter not supported by this platform: %d", adapter);
            return nullptr;
    }
}
