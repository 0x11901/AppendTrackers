//
// Created by wangjingkai on 2021/10/20.
//

#include "except.h"
#include <stdexcept>

except::~except() = default;
except::except(const std::string &message, int errorCode) : runtime_error(message), errorCode(errorCode) {
    this->message = message;
    this->errorCode = errorCode;
}
except::except(const char *message, const std::string &message1) : runtime_error(message), message(message1) {}
