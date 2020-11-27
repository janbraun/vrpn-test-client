/*
 * Wrapper for the VRPN interface without lab. Not lab specific.
 * Copyright (C) 2019  Jan-Matthias Braun <j-mb@mmmi.sdu.dk>
 *               2018  DPZ
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "vrpn_client.h"
#include <iostream>

using namespace VRPN;

VRPNClient::VRPNClient ( const std::string& tracker_name )
    : m_text_receiver{tracker_name.c_str() } {

    m_text_receiver.register_message_handler ( this, handle_message );
}


void VRPN_CALLBACK VRPNClient::handle_message ( void *self, const vrpn_TEXTCB msg ) {
    VRPNClient* _this = reinterpret_cast<VRPNClient*> ( self );

    std::cout << "Received message " << msg.message << std::endl;
    _this->m_message_buffer.push_back( msg );
}
