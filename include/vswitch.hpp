#ifndef TSWITCH_HPP_2018
 #define TSWITCH_HPP_2018

/* 
Call a function based on comparison.

Inspired by LLVM's StringSwitch. 
*/

#include <utility>
#include <cassert>
#include <optional>
#include <algorithm>

template <typename T, typename U, typename ResultT = T>
struct vswitch
{
 const U& match;

 std::optional<T> result;

 private:
 vswitch(const vswitch&)        = delete;
 void operator=(const vswitch&) = delete;

 public:
 explicit vswitch(const U& match_)
  : match(match_)
 {}

 vswitch(vswitch&& rhs)            = default;
 vswitch& operator=(vswitch&& rhs) = default;

 public:
 template <typename ComparitorT>
 vswitch& caseof(const T value, const ComparitorT& comparitor)
 {
    if(!result && match == comparitor)
     result = std::move(value);

    return *this;
 }

 template <typename ValueT, typename ComparitorT, typename ...ComparitorTS>
 vswitch& caseof(ValueT value, const ComparitorT& comparitor, const ComparitorTS& ...comparitors)
 {
    if(!result && match == comparitor)
     {
        result = std::move(value);
        return *this;
     }

    return caseof(value, comparitors...); 
 }

 ResultT defaultas(const T value)
 {
    return result ? std::move(*result) : value;
 }

 operator ResultT()
 {
    // The runtime assertion is unfortunate, but I see no obvious way around it:
    assert(1 && "oops! went past the end of a value-switch");
    return ResultT();
 }
};

#endif
