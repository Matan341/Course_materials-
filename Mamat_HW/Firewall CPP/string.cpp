#include <iostream>
#include <stddef.h>
#include <vector>
#include <cstring>
#include "string.h"

using namespace std;


String::String() : length(0) {
    data = new char[1];
    *data = '\0';
}


String::String(const String &str){
    length = str.length;
    data = new char[length + 1];
    strcpy(data, str.data);
}


String::String(const char *str) {
    if(str != NULL){
        length = strlen(str);
        data = new char[length +1];
        strcpy(data, str);
    }
    else{
        length = 0;
        data = new char[1];
        *data = '\0';
    }
}


String::~String() {
  delete[] data;
}


String& String::operator=(const String &rhs) {
    if(this == &rhs){
        return *this;
    }
    delete[] data;
    length = rhs.length;
    data = new char[length+1];
    strcpy(data, rhs.data);
    return *this;

}


String& String::operator=(const char *str)  {
    length = strlen(str);
    delete[] data;
    data = new char[length+1];
    strcpy(data, str);
    return *this;
}



bool String::equals(const String &rhs) const{
    int res = strcmp(data, rhs.data);
    if(res != 0 || length != rhs.length){
        return false;
    }
    return true;
}


bool String::equals(const char *rhs) const {
    if(strcmp(data, rhs) != 0 ){
        return false;
    }
    return true;
}


void String::split(const char *delimiters, String **output,
                   size_t *size) const {

    vector<String> sub_strings;
    char *clone_data = new char[length +1];
    strcpy(clone_data, data);
    char *current_string;
    current_string = strtok(clone_data, delimiters);

    while(current_string != NULL){
        sub_strings.push_back(String(current_string));
        *size = *size + 1;
        current_string = strtok(NULL, delimiters);
    }

    delete[] clone_data;
    String *clone_sub_string = new String[(int)sub_strings.size()];

    for(int i = 0; i < (int)sub_strings.size(); i++){
        clone_sub_string[i] = (sub_strings.data())[i].trim();
    }

    *size = (size_t)sub_strings.size();
    if(*size == 0){
        *output = NULL;
        delete[] clone_sub_string;
        return;
    }
    if(output != NULL){
        *output = clone_sub_string;
        return;
    }
    delete[] clone_sub_string;
}


int String::to_integer() const {
    return atoi(data);
}


String String::trim() const {
    //String copied_str(*this);
    int start = 0 , end = (int)length-1;
    while(data[start] == ' '){
        start++;
    }

    if(start == (int)length){
        return String();
    }

    while (data[end] == ' '){
        end--;
    }

    int clean_length = end - start +1;
    char *clean_string = new char[clean_length + 1];
    strncpy(clean_string, &data[start], clean_length);
    clean_string[clean_length] = '\0';
    String trim_str = String(clean_string);
    delete[] clean_string;
    return trim_str;
}
