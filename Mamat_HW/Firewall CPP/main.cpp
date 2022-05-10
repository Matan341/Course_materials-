#include <iostream>
#include <stdlib.h>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"

extern int check_args(int, char**);
extern void parse_input(Field&);

using namespace std;

int main(int argc, char** argv){

    if(check_args(argc, argv) != 0 ){
        exit(1);
    }
    String *clone_rule;
    size_t rule_size = 0;
    String rule(argv[1]);
    rule.split("=", &clone_rule, &rule_size);

    String pattern = (clone_rule[0]);
    String val = (clone_rule[1]);
    delete[] clone_rule;
    if((pattern.trim().equals("src-ip")) || (pattern.trim().equals("dst-ip"))){
        Ip ip_rule(pattern);
        ip_rule.set_value(val);
        parse_input(ip_rule);
    }

    else if((pattern.equals("src-port")) || (pattern.equals("dst-port"))){
        Port port_rule(pattern);
        port_rule.set_value(val);
        parse_input(port_rule);
    }
    return 0;

}
