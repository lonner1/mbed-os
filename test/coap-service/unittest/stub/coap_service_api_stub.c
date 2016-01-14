/*
 * Copyright (c) 2015-2016 ARM Limited. All Rights Reserved.
 */


#include "config.h"
#ifdef HAVE_THREAD
#include <string.h>

#include "ns_types.h"
#include "ns_list.h"
#include "ns_trace.h"
#include "nsdynmemLIB.h"
#include "sn_nsdl.h"
#include "sn_coap_header.h"
#include "coap_service_api.h"
#include "coap_message_handler.h"
#include "eventOS_event.h"
#include "eventOS_scheduler.h"
#include "eventOS_event_timer.h"
#include "common_functions.h"
#include "net_interface.h"

int8_t coap_service_initialize(int8_t interface_id, uint16_t listen_port, uint8_t service_options,
                                 coap_service_security_start_cb *start_ptr, coap_service_security_done_cb *security_done_cb)
{
    return 0;
}

void coap_service_delete(int8_t service_id)
{
}

int16_t coap_service_virtual_socket_recv(int8_t service_id, uint8_t source_addr_ptr[static 16], uint16_t port, uint8_t *data_ptr, uint16_t data_len)
{
    return 0;
}

int16_t coap_service_virtual_socket_set_cb(int8_t service_id, coap_service_virtual_socket_send_cb *send_method_ptr)
{
    return 0;
}

int8_t coap_service_register_uri(int8_t service_id, const char *uri, uint8_t allowed_method, coap_service_request_recv_cb *request_recv_cb)
{
    return 0;
}

int8_t coap_service_unregister_uri(int8_t service_id, const char *uri)
{
    return 0;
}

uint16_t coap_service_request_send(int8_t service_id, uint8_t options, const uint8_t destination_addr[static 16], uint16_t destination_port, sn_coap_msg_type_e msg_type, sn_coap_msg_code_e msg_code, const char *uri,
                                  uint8_t cont_type, const uint8_t *payload_ptr, uint16_t payload_len, coap_message_handler_response_recv *request_response_cb){
    return 0;
}

int8_t coap_service_response_send(int8_t service_id, uint8_t options, sn_coap_hdr_s *request_ptr, sn_coap_msg_code_e message_code, int32_t content_type, const uint8_t *payload_ptr,uint16_t payload_len){
    return 0;
}

#endif
