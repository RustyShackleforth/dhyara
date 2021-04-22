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

#include "dhyara/neighbourhood.h"

const dhyara::neighbour& dhyara::neighbourhood::add(const dhyara::neighbour& p){
    auto inserted = _neighbours.insert(std::make_pair(p.addr(), p));
    esp_now_add_peer(p.raw());
    return inserted.first->second;
}

const dhyara::neighbour& dhyara::neighbourhood::add(const dhyara::address& addr, uint8_t ch, bool enc){
    return add(dhyara::neighbour(addr));
}

const dhyara::neighbour& dhyara::neighbourhood::add(const std::string& addr, std::uint8_t ch, bool enc){
    return add(dhyara::address(addr), ch, enc);
}

bool dhyara::neighbourhood::exists(const std::string& addr) const {
    return _neighbours.find(dhyara::address(addr)) != _neighbours.end();
}

bool dhyara::neighbourhood::exists(const dhyara::address& addr) const{
    return _neighbours.find(addr) != _neighbours.end();
}

std::size_t dhyara::neighbourhood::size() const{
    return _neighbours.size();
}


dhyara::neighbour& dhyara::neighbourhood::neighbour(const dhyara::address& addr){
    neighbour_collection_type::iterator it = _neighbours.find(addr);
    return it->second;
}
