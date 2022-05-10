#include "field.h"
#include "string.h"
#include "ip.h"



Ip::Ip(String pattern) : Field(pattern), start_adress(0), end_adress(0) { }

bool Ip::set_value(String val){

    String *cloned_ip;
    size_t ip_size = 0;

    val.split("/.", &cloned_ip, &ip_size);
    if (ip_size != 5) {
        delete[] cloned_ip;
        return false;
   }
   int ip = (cloned_ip[0].trim().to_integer() << 24) |
        (cloned_ip[1].trim().to_integer() << 16) |
        (cloned_ip[2].trim().to_integer() << 8) |
        (cloned_ip[3].trim().to_integer());

   int subnet_mask = cloned_ip[4].trim().to_integer();
   unsigned int bitmask = 0xFFFFFFFF;
   bitmask = (subnet_mask != 0 ) ? bitmask << (32 - subnet_mask) : 0;
   start_adress = ip | (~bitmask);
   end_adress = ip & bitmask;
   delete[] cloned_ip;
   return true;
}


bool Ip::match_value(String val) const {

    String *cloned_ip;
    size_t ip_size = 0;

    val.split(".", &cloned_ip, &ip_size);
    if (ip_size != 4) {
        delete[] cloned_ip;
        return false;
    }
    int ip =(cloned_ip[0].trim().to_integer() << 24) |
        (cloned_ip[1].trim().to_integer() << 16) |
        (cloned_ip[2].trim().to_integer() << 8) |
        (cloned_ip[3].trim().to_integer());
    delete[] cloned_ip;
    if((ip >= start_adress ) && (ip <= end_adress)){
      return true;
    }
    return false;

}
