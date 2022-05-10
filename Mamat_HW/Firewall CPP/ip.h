#ifndef IP_H
#define IP_H

#include "string.h"
#include "field.h"


class Ip : public Field {
int start_adress, end_adress;

public:
    Ip(String pattern);
    bool match_value(String val) const;
    bool set_value(String val);

};

#endif
