#pragma once
#include <exception>
#include <iostream>

class ParseLineException : public std::exception {
public:
    ParseLineException(std::string&& msg, unsigned int line, const char* where) :  
    m_msg(msg), m_line(line), m_where(where) {

    }
    void print() {
        std::cout << "Error " << m_msg << ", line " << m_line << ": " << std::endl;

        for(int i = 0; m_where[i] != '\0' && m_where[i] != '\n'; i++){
            std::cout << m_where[i];
        }
        std:: cout << "\n";
    }


private:
    std::string m_msg;
    unsigned int m_line;
    const char* m_where;
};