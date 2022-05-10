#include "string.h"
#include "field.h"


Field::Field(String pattern) : pattern(pattern) { }

Field::~Field() {}

bool Field::match(String packet) {

    String *packet_fields; // this should be packet
    size_t packet_size;
    packet.split(",", &packet_fields, &packet_size);
    for(size_t i = 0; i < packet_size; i++){

        String *current_field;
        size_t field_size;
        packet_fields[i].trim();
        packet_fields[i].split("=", &current_field, &field_size);

        String rule = current_field[0].trim();
        String value = current_field[1].trim();
        if(rule.equals(pattern) && match_value(value)) {

            delete[] current_field;
            delete[] packet_fields;
            return true;
        }
        delete[] current_field;
    }
    
    if(packet_size != 0){
      delete[] packet_fields;
    }
    return false;
}
