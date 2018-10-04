/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * Copyright (c) 2016, SoftPLC Corporation.
 *
 ******************************************************************************/
#ifndef CIPSTER_CIPCOMMON_H_
#define CIPSTER_CIPCOMMON_H_

/** @file cipcommon.h
 * Common CIP object interface
 */

#include "typedefs.h"
#include "ciptypes.h"
#include <byte_bufs.h>


/// Binary search function template, dedicated for classes with Id() member func
template< typename T, typename IterT >
IterT vec_search( IterT begin, IterT end, T target )
{
    IterT initial_end = end;

    while( begin < end )
    {
        IterT   middle = begin + (end - begin - 1)/2;
        int     r = target - (*middle)->Id();

        if( r < 0 )
            end = middle;
        else if( r > 0 )
            begin = middle + 1;
        else
            return middle;
    }
    return initial_end;
}


/// Binary search function template, same as vec_search but returns equal or next greater
template< typename T, typename IterT >
IterT vec_search_gte( IterT begin, IterT end, T target )
{
    while( begin < end )
    {
        IterT   middle = begin + (end - begin - 1)/2;
        int     r = target - (*middle)->Id();

        if( r < 0 )
            end = middle;
        else if( r > 0 )
            begin = middle + 1;
        else
            return middle;
    }
    return end;
}


int StrPrintf( std::string* aResult, const char* aFormat, ... );

std::string StrPrintf( const char* aFormat, ... );


/** A buffer for holding the reply generated by explicit message requests
 *  or producing I/O connections. These will use this buffer in the following
 *  ways:
 *    1. Explicit messages will use this buffer to store the data generated by the request
 *    2. I/O Connections will use this buffer for the produced data
 */
extern uint8_t g_message_data_reply_buffer[CIPSTER_MESSAGE_DATA_REPLY_BUFFER];

/// Set this to other than kEIP_IoUdpPort if your system receives consumes I/O
/// messages on other than the standard port number.
extern int g_my_io_udp_port;

extern uint64_t g_current_usecs;

/// The run/idle mode sent when our producing half is kRealTimeFmt32BitHeader,
/// which is likely only when we are acting as a scanner.
extern uint32_t g_run_idle_state;

/// Return the least significant 32 bits of uint64_t g_current_usecs
inline uint32_t CurrentUSecs32()    { return uint32_t( g_current_usecs ); }


#endif    // CIPSTER_CIPCOMMON_H_
