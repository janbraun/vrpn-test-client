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

#pragma once

#include "vrpn_Connection.h"
#include "vrpn_Text.h"

#include <string>
#include <vector>


namespace VRPN {

//! Convert the timestamp to a double value in seconds.
inline constexpr double timestamp_from_message ( const vrpn_TEXTCB& msg ) {
    return msg.msg_time.tv_sec + msg.msg_time.tv_usec * 1E-6;
}


class VRPNClient {
public:
    using buffer_t = std::vector<vrpn_TEXTCB>;

    VRPNClient ( const std::string& tracker_name );

    void mainloop() {
        m_text_receiver.mainloop();
    }

    void swap_buffer ( buffer_t& ext_buffer ) {
        ext_buffer.resize ( 0 );
        std::swap ( m_message_buffer, ext_buffer );
    }

private: // Methods
    // Callbacks
    static void VRPN_CALLBACK handle_message ( void *self, const vrpn_TEXTCB msg );

private: // Members
    vrpn_Text_Receiver m_text_receiver;
    buffer_t m_message_buffer;

}; // class VRPNClient

} // namespace VRPN
