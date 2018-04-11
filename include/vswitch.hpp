#ifndef VSWITCH_HPP_2019
 #define VSWITCH_HPP_2019

/* 
Generate nested switches.

Inspired by LLVM's StringSwitch. 

Author: Jesse Williamson
*/

#include <utility>
#include <cassert>
#include <optional>
#include <algorithm>
#include <exception>
#include <string_view>

// Some helpers for expected situations-- users can add more types into this
// namespace:
namespace vswitch::comparitors {

// Note that we can't rely on operator overloads for non-type classes, so we
// map them:
template <typename LHS, typename RHS>
bool compare(const LHS& lhs, const RHS& rhs)
{
 return lhs == rhs;
}

template <typename LHS, typename RHS>
bool compare(const LHS&& lhs, const RHS&& rhs)
{
 return lhs == rhs;
}

// An understandably common use-case:
bool compare(const char *lhs, const char *rhs)
{
 return compare(std::string_view(lhs), std::string_view(rhs));
}

} // namespace vswitch::comparitors

namespace vswitch {

template <typename ResultT, typename MatchT>
struct vswitch_t
{
 const MatchT match;

 std::optional<ResultT> result_value;

 private:
 vswitch_t(const vswitch_t&)      = delete;
 void operator=(const vswitch_t&) = delete;

 public:
 explicit vswitch_t(const MatchT& match_)
  : match(match_)
 {}

 vswitch_t(vswitch_t&& rhs)            = default;
 vswitch_t& operator=(vswitch_t&& rhs) = default;

 public:
 template <typename ComparitorT>
 vswitch_t& result(const ResultT& value, const ComparitorT& comparitor)
 {
    if(vswitch::comparitors::compare(match, comparitor))
     result_value = value;

    return *this;
 }

 template <typename ComparitorT, typename ...ComparitorTS>
 vswitch_t& result(const ResultT& value, const ComparitorT& comparitor, const ComparitorTS& ...comparitors)
 {
	return vswitch::comparitors::compare(match, comparitor) 
			? (result_value = value, *this) 
			: result(value, comparitors...);
 }

 ResultT defaultas(const ResultT& value)
 {
    return result_value ? *result_value : value;
 }

 ResultT nodefault()
 {
	if(!result_value)
     throw std::range_error("no match");

    return *result_value;
 }
};

} // namespace vswitch

#endif
