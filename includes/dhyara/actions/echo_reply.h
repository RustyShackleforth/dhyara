/*
 * Copyright (c) 2020, Sunanda Bose (a.k.a. Neel Basu)
 * All rights reserved.
 * 
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef DHYARA_ACTIONS_ECHO_REPLY_H
#define DHYARA_ACTIONS_ECHO_REPLY_H

#include "dhyara/actions/action.h"
#include "dhyara/packets/echo_reply.h"
#include "dhyara/peer.h"
#include "dhyara/defs.h"

namespace dhyara{
    
struct link;
    
namespace actions{
    
/**
 * action to handle an incoming echo reply packet
 * \ingroup actions
 */
struct echo_reply: dhyara::actions::action<echo_reply, dhyara::packets::echo_reply>{
    /**
     * RTT statistics, containing min, max, total and average values observed since last reset
     */
    struct rtt_stat{
        dhyara::delay_type min = std::numeric_limits<dhyara::delay_type>::max(), max = 0, total = 0;
        double avg = 0;
        
        /**
         * reset the stat
         */
        inline void reset() { min = std::numeric_limits<dhyara::delay_type>::max(); max = 0; avg = 0.0; total = 0; }
    };
    
    /**
     * The echo_reply action is constructed using a reference to the link, so that it can relay that reply using the link if necessary
     */
    inline explicit echo_reply(dhyara::link& link): _link(link){}

    using action::operator();
    /**
     * Process an incomming echo_reply packet
     * \param addr source address 
     * \param echo_reply the received echo_reply 
     */
    void operator()(const dhyara::address& addr, const dhyara::packets::echo_reply& echo_reply);
    
    /**
     * rtt statistics
     */
    inline const rtt_stat& rtt() const { return _stat; }
    /**
     * reset statistics
     */
    inline void reset() { 
        _stat.reset();
    }
    
    private:
        dhyara::link& _link;
        rtt_stat      _stat;
};
    
}
    
}


#endif // DHYARA_ACTIONS_ECHO_REPLY_H
