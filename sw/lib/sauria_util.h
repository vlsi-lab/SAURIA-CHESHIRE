#ifndef _SAURIA_UTIL_
#define _SAURIA_UTIL_

/*
 * Copyright 2025 PoliTo
 * Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
 * SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
 *
 * Author: Tommaso Terzano <tommaso.terzano@polito.it> 
 *                         <tommaso.terzano@gmail.com>
 *  
 * Info: Utilities library for the SAURIA-Cheshire demonstrator.
 */

/* Converts a uin32_t value into a hex-formatted string for prints */
void uint32_to_hex_string(uint32_t value, char *buffer) {
    const char hex_chars[] = "0123456789ABCDEF";
    buffer[0] = '0';
    buffer[1] = 'x';  // Prefix for hex
    for (int i = 0; i < 8; i++) {
        buffer[9 - i] = hex_chars[value & 0xF];  // Get the last hex digit
        value >>= 4;  // Shift right by 4 bits (1 hex digit)
    }
    buffer[10] = '\r'; // Add carriage return
    buffer[11] = '\n'; // Add newline
    buffer[12] = '\0'; // Null terminator
}

#endif  