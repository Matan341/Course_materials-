#ifndef PORT_H
#define PORT_H


#include "string.h"
#include "field.h"


class Port : public Field {
int port[2];

public:

  Port(String pattern);
  bool match_value(String val) const;
  bool set_value(String val);

};

#endif
