/*
 * Custom Event CLass
 * Author: Scott Susanto
 */

#include "my_event.h"

Event::Event()
{
    this->event_type = -1;
}

Event::Event(int event_type)
{
    this->event_type = event_type;
}

int Event::get_event_type()
{
    return event_type;
}