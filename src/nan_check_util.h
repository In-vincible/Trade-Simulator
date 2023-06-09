//
// Created by Bikram Bharti on 09-06-2023.
//

#ifndef CMAKE_TEMPLATE_NAN_CHECK_UTIL_H
#define CMAKE_TEMPLATE_NAN_CHECK_UTIL_H

#include <iostream>
#include <cmath>
#include <type_traits>

// Template function to check if a value is NaN
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, bool>::type
isNaN(const T& value) {
    return std::isnan(value);
}

// Overload for std::string (not required)
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, bool>::type
isNaN(const T&) {
    // NaN check for std::string is not applicable
    return false;
}

#endif //CMAKE_TEMPLATE_NAN_CHECK_UTIL_H
