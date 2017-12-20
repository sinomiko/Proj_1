#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include "Include/Utils/logger.h"

class mc_error : public std::runtime_error {
public:
    //! ctor & dtor
    mc_error(const std::string& what, const std::string& file, std::size_t line);
    ~mc_error(void) = default;

    //! copy ctor & assignment operator
    mc_error(const mc_error&) = default;
    mc_error& operator=(const mc_error&) = default;

public:
    //! get location of the error
    const std::string& get_file(void) const;
    std::size_t get_line(void) const;

private:
    //! location of the error
    std::string m_file;
    std::size_t m_line;
};

//! macro for convenience
#define __MC_THROW(level, what)                          \
  {                                                           \
    __MC_LOG(level, (what));                             \
    throw mc_error((what), __FILE__, __LINE__); \
  }
