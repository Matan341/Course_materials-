#include "string.h"
#include "field.h"
#include "port.h"


Port::Port(String pattern) : Field(pattern), port{0, 0} { }

bool Port::set_value(String val) {

    String *cloned_port;
    size_t port_size = 0;
    val.split("-", &cloned_port, &port_size);

    if(port_size != 2){
      delete[] cloned_port;
      return false;
    }

    int port_begin = cloned_port[0].trim().to_integer();
    int port_end = cloned_port[1].trim().to_integer();
    delete[] cloned_port;

    port[0] = (port_begin < port_end) ? port_begin : port_end;
    port[1] = (port_end > port_begin) ? port_end : port_begin;
    return true;

}


bool Port::match_value(String val) const {

    int cloned_port = val.trim().to_integer();
    if((cloned_port >= port[0]) && (cloned_port <= port[1])){
        return true;
    }
    return false;

}
