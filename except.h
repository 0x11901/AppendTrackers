//
// Created by wangjingkai on 2021/10/20.
//

#ifndef APPENDTRACKERS_EXCEPT_H
#define APPENDTRACKERS_EXCEPT_H

#include <stdexcept>

class except final : public std::runtime_error {
  public:
    except(const std::string &message, int errorCode);
    except(const char *message, const std::string &message1);
    ~except() final;

  private:
    std::string message;
    int errorCode;
};

#endif // APPENDTRACKERS_EXCEPT_H
