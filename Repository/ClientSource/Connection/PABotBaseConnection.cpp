/*  Pokemon Automation Bot Base - Client Example
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include "ClientSource/CommonFramework/CRC32.h"
#include "ClientSource/CommonFramework/MessageProtocol.h"
#include "ClientSource/Libraries/Logging.h"
#include "ClientSource/Libraries/MessageConverter.h"
#include "PABotBaseConnection.h"

namespace PokemonAutomation{

MessageSniffer null_sniffer;

PABotBaseConnection::PABotBaseConnection(std::unique_ptr<StreamConnection> connection)
    : m_connection(std::move(connection))
    , m_sniffer(&null_sniffer)
{
    m_connection->add_listener(*this);
}
PABotBaseConnection::~PABotBaseConnection(){
    if (m_connection){
        safely_stop();
    }
}
void PABotBaseConnection::safely_stop(){
    m_connection->stop();
    m_connection.reset();
}


void PABotBaseConnection::set_sniffer(MessageSniffer* sniffer){
    if (sniffer == nullptr){
        sniffer = &null_sniffer;
    }
    m_sniffer = sniffer;
}


void PABotBaseConnection::send_zeros(uint8_t bytes){
    char ch = 0;
    for (uint8_t c = 0; c < bytes; c++){
        m_connection->send(&ch, 1);
//        Sleep(10);
    }
}
void PABotBaseConnection::send_message(uint8_t type, const std::string& msg, bool is_retransmit){
//    log("Sending: " + message_to_string(type, msg));
    m_sniffer->on_send(type, msg, is_retransmit);

    size_t total_bytes = SERIAL_MESSAGE_OVERHEAD + msg.size();
    if (total_bytes > PABB_MAX_MESSAGE_SIZE){
        throw "Message is too long.";
    }

    std::string buffer;
    buffer += ~(uint8_t)total_bytes;
    buffer += type;
    buffer += msg;
    buffer += std::string(sizeof(uint32_t), 0);
    pabb_crc32_write_to_message(&buffer[0], buffer.size());

    m_connection->send(&buffer[0], buffer.size());
}


void PABotBaseConnection::on_recv(const void* data, size_t bytes){
    //  Push into receive buffer.
    for (size_t c = 0; c < bytes; c++){
        m_recv_buffer.emplace_back(((const char*)data)[c]);
    }

    while (!m_recv_buffer.empty()){
        uint8_t length = ~m_recv_buffer[0];

        if (m_recv_buffer[0] == 0){
            m_sniffer->log("Skipping zero byte.");
            m_recv_buffer.pop_front();
            continue;
        }

        //  Message is too short.
        if (length < SERIAL_MESSAGE_OVERHEAD){
            m_sniffer->log("Message is too short: bytes = " + std::to_string(length));
            m_recv_buffer.pop_front();
            continue;
        }

        //  Message is too long.
        if (length > PABB_MAX_MESSAGE_SIZE){
            m_sniffer->log("Message is too long: bytes = " + std::to_string(length));
            m_recv_buffer.pop_front();
            continue;
        }

        //  Message is incomplete.
        if (length > m_recv_buffer.size()){
            return;
        }

        std::string message(m_recv_buffer.begin(), m_recv_buffer.begin() + length);

        //  Verify checksum
        {
            //  Calculate checksum.
            uint32_t checksumA = pabb_crc32(0xffffffff, &message[0], length - sizeof(uint32_t));

            //  Read the checksum from the message.
            uint32_t checksumE = ((uint32_t*)(&message[0] + length))[-1];

            //  Compare
//            std::cout << checksumA << " / " << checksumE << std::endl;
            if (checksumA != checksumE){
                m_sniffer->log("Invalid Checksum: bytes = " + std::to_string(length));
//                std::cout << checksumA << " / " << checksumE << std::endl;
//                log(message_to_string(message[1], &message[2], length - SERIAL_MESSAGE_OVERHEAD));
                m_recv_buffer.pop_front();
                continue;
            }
        }
        m_recv_buffer.erase(m_recv_buffer.begin(), m_recv_buffer.begin() + length);

        uint8_t type = message[1];
        std::string body(&message[2], length - SERIAL_MESSAGE_OVERHEAD);
        m_sniffer->on_recv(type, body);
        on_recv_message(type, body);
    }
}


}
