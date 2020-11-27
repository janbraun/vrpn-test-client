/*
 *
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

#include <unistd.h>
#include <iostream>

void parse_message ( const vrpn_TEXTCB& msg ) {
    // User other find?
    std::string _text{msg.message};
    std::cout << "Message: ---------------------------\n"
              << "\tTime: " << msg.msg_time.tv_sec + msg.msg_time.tv_usec * 1E-6
              << "\tType: " << msg.type << std::endl;
    std::cout << "\tContent: " << msg.message << std::endl;

    auto pos = _text.find ( ',' );
    std::cerr << "Pos: " << pos << std::endl;
    if ( pos == std::string::npos )
        return;

    std::string key ( _text, 0, pos );
    std::string value ( _text, pos + 1 );

    std::cout << "\tKey: " << key << ", Value: " << value << std::endl;
    if ( key == "TRIAL" )
        std::cout << " !!!!!!!!!! NEW TRIAL of type " << value << std::endl;
    else if ( key == "STAGE" )
        std::cout << "\t\t -> New stage " << value << std::endl;
    else
        std::cout << "?????????????????? Unknown key" << std::endl;
}


int main(int argc, char** argv) {

    // Tracker address, e.g., Tracker0@172.17.3.125:6666
    std::string tracker_address = "Tracker10@127.0.0.1";

    if ( argc > 1 )
        tracker_address = argv[1];

    VRPN::VRPNClient::buffer_t buffer;
    VRPN::VRPNClient client ( tracker_address );

    while ( true ) {
        client.mainloop();
        client.swap_buffer ( buffer );      // Fetches more than one message, if available.
        if ( buffer.size() )
            std::cout << "Received non-empty buffer. Size: " << buffer.size() << std::endl;
        for ( const auto& msg : buffer )
            parse_message ( msg );
        usleep ( 100*1000 );
    }

    return 0;
}
