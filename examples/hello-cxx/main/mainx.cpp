#include "mainx.h"
#include <dhyara/network.h>
#include <iostream>
#include <freertos/FreeRTOS.h>
#include <dhyara/link.h>
#include "esp_wifi.h"
#include <dhyara/dhyara.h>
#include "esp_log.h"
#include <dhyara/tools/ping.h>
#include <dhyara/tools/traceroute.h>
#include <dhyara/packets/data.h>
#include <dhyara/utils/http.h>

void mainx(){
    dhyara::utils::http server(dhyara_link());
    
    dhyara::network network(dhyara_link());
    dhyara_set_default_network(&network);
    
    dhyara::address sink("4c:11:ae:9c:a6:85"), source("4c:11:ae:71:0f:4d");
    
    dhyara_start_default_network();
    
//     For experimental purpose 
//     Optionally ban direct communication between the source and the target
//     Force the source and target to communicate via one or more intermediate nodes
    network.isolate(source, sink);
    
    dhyara::address local = dhyara_local();
    dhyara::address other = (local == source) ? sink : ((local == sink) ? source : dhyara::address::null());
    
    // The anonymous function will be called once all chunks of a data packet is received
    dhyara_receive_data([](const dhyara::address& source, const dhyara::packets::data& data){
        std::cout << "received data " << " originating from " << data.source() << " via " << source << " of size " << data.length() << std::endl;
    });
    
    while(1){
        if(!other.is_null()){
            dhyara_ping(other, 1, 10);
            dhyara_traceroute(other);
            std::string buffer = "Hello World";
            dhyara_send(other, buffer.begin(), buffer.end());
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
} 
