/*
 * Project: include
 * File: include/wire.h
 * -----
 * File Created: Thursday, 6th May 2021 7:10:46 pm
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#ifndef INCLUDE_WIRE_H
#define INCLUDE_WIRE_H

/* Struct for data transmission. */
struct Wire
{
    /* Indicates if there is new data on the wire. */
    bool dirty;
    /* Wire data. */
    bool data;
};

#endif