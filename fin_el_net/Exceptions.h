//
// Created by liza on 27.09.2021.
//
#ifndef FIN_EL_NET_EXCEPTIONS_H
#define FIN_EL_NET_EXCEPTIONS_H
#include <exception>
#include <string>
class FileNotFoundException : public std::exception {
    std::string error;
public:
    FileNotFoundException() {
        error.assign("Cannot open file or it does not exist!");
    }

    const char *what() const noexcept override {
        return error.c_str();
    }
};

#endif //FIN_EL_NET_EXCEPTIONS_H
