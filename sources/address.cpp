/*
 * Copyright (c) 2021, <copyright holder> <email>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "dhyara/address.h"
#include <cstring>

dhyara::address::address(const dhyara::address::container_type& addr): _bytes(addr){}
dhyara::address::address(std::uint8_t b1, std::uint8_t b2, std::uint8_t b3, std::uint8_t b4, std::uint8_t b5, std::uint8_t b6){
    _bytes[0] = b1;
    _bytes[1] = b2;
    _bytes[2] = b3;
    _bytes[3] = b4;
    _bytes[4] = b5;
    _bytes[5] = b6;
}
dhyara::address::address(const std::uint8_t* bytes){
    std::copy(bytes, bytes + 6, _bytes.begin());
}

dhyara::address::address(const std::string& addr){
    std::uint32_t b[6];
    if (std::sscanf(addr.c_str(), "%02x:%02x:%02x:%02x:%02x:%02x", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]) != 6){
        std::cerr << "Invalid Address" << std::endl;
    }
    std::copy(b, b+6, _bytes.begin());
}

std::string dhyara::address::to_string() const{
    char buff[18];
    std::memset(buff, 0, sizeof(buff));
    snprintf(buff, sizeof(buff), "%02x:%02x:%02x:%02x:%02x:%02x", _bytes[0], _bytes[1], _bytes[2], _bytes[3], _bytes[4], _bytes[5]);
    return std::string(buff);
}


std::uint64_t dhyara::address::hash() const{
    return
        std::uint64_t(_bytes[0]) << 40 |
        std::uint64_t(_bytes[1]) << 32 | ( 
            std::uint32_t(_bytes[2]) << 24 | 
            std::uint32_t(_bytes[3]) << 16 |
            std::uint32_t(_bytes[4]) << 8 |
            std::uint32_t(_bytes[5])
        );
}
bool dhyara::address::operator<(const dhyara::address& other) const{
    return hash() < other.hash();
}
bool dhyara::address::operator==(const dhyara::address& other) const{
    // return hash() == other.hash();
    return (b1() == other.b1())
        && (b2() == other.b2())
        && (b3() == other.b3())
        && (b4() == other.b4())
        && (b5() == other.b5())
        && (b6() == other.b6());
}

bool dhyara::address::operator==(const std::string& addr) const{
    return operator==(dhyara::address(addr));
}

void dhyara::address::set(const std::uint8_t* bytes){
    std::copy(bytes, bytes + 6, _bytes.begin());
}

std::ostream& dhyara::operator<<(std::ostream& os, const dhyara::address& address){
    os << "Addr< " << address.to_string() << " >";
    return os;
}
