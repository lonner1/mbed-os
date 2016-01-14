/*
 * Copyright (c) 2015-2016 ARM Limited. All Rights Reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __COAP_MESSAGE_HANDLER_H__
#define __COAP_MESSAGE_HANDLER_H__

#include <inttypes.h>
#include "sn_coap_header.h"
#include "sn_nsdl.h"
#include "ns_list.h"

/**
 * \brief Service message response receive callback.
 *
 * Function that handles CoAP service message receiving and parsing
 *
 * \param msg_id           Id number of the current message.
 * \param response_ptr     Pointer to CoAP header structure.
 *
 * \return 0 for success / -1 for failure
  */
typedef int coap_message_handler_response_recv(int8_t service_id, uint16_t msg_id, sn_coap_hdr_s *response_ptr);

typedef struct coap_msg_handler_s {
    void *(*sn_coap_service_malloc)(uint16_t);
    void (*sn_coap_service_free)(void *);

    uint8_t (*sn_coap_tx_callback)(uint8_t *, uint16_t, sn_nsdl_addr_s *, void *);

    struct coap_s *coap;
} coap_msg_handler_t;

typedef struct coap_transaction {
    uint8_t remote_address[16];
    uint16_t remote_port;
    uint8_t token[4];
    uint16_t msg_id;
    int8_t service_id;
    uint8_t options;
    bool client_request: 1;
    uint8_t *data_ptr;
    uint16_t data_len;
    coap_message_handler_response_recv *resp_cb;
    ns_list_link_t link;
} coap_transaction_t;


extern coap_msg_handler_t *coap_message_handler_init(void *(*used_malloc_func_ptr)(uint16_t), void (*used_free_func_ptr)(void *),
                                  uint8_t (*used_tx_callback_ptr)(uint8_t *, uint16_t, sn_nsdl_addr_s *, void *));

extern int8_t coap_message_handler_destroy(coap_msg_handler_t *handle);

extern coap_transaction_t *coap_message_handler_find_transaction(uint8_t *address_ptr, uint16_t port);

extern int16_t coap_message_handler_coap_msg_process(coap_msg_handler_t *handle, int8_t socket_id, uint8_t source_addr_ptr[static 16], uint16_t port,
                                                         uint8_t *data_ptr, uint16_t data_len, int16_t (cb)(int8_t, sn_coap_hdr_s *, coap_transaction_t *));

extern uint16_t coap_message_handler_request_send(coap_msg_handler_t *handle, int8_t service_id, uint8_t options, const uint8_t destination_addr[static 16],
                                                      uint16_t destination_port, sn_coap_msg_type_e msg_type, sn_coap_msg_code_e msg_code, const char *uri, uint8_t cont_type,
                                                      const uint8_t *payload_ptr, uint16_t payload_len, coap_message_handler_response_recv *request_response_cb);

extern int8_t coap_message_handler_response_send(coap_msg_handler_t *handle, int8_t service_id, uint8_t options, sn_coap_hdr_s *request_ptr, sn_coap_msg_code_e message_code,
                                                     int32_t content_type, const uint8_t *payload_ptr, uint16_t payload_len);

extern int8_t coap_message_handler_exec(coap_msg_handler_t *handle, uint32_t current_time);

#endif
