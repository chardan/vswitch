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

namespace vswitch::detail::comparitors {

// Note that we can't rely on operator overloads for non-type classes, so we
// map them:
template <typename LHS, typename RHS>
bool eq(const LHS& lhs, const RHS& rhs)
{
 return lhs == rhs;
}

template <typename LHS, typename RHS>
bool eq(const LHS&& lhs, const RHS&& rhs)
{
 return lhs == rhs;
}

// An understandably common non-class use-case:
bool eq(const char *lhs, const char *rhs)
{
 return eq(std::string_view(lhs), std::string_view(rhs));
}

} // namespace vswitch::detail::comparitors

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
 vswitch_t& result(const ResultT& value, const MatchT& comparitor)
 {
    if(vswitch::detail::comparitors::eq(match, comparitor))
     result_value = value;

    return *this;
 }

 template <typename ...ComparitorTS>
 vswitch_t& result(const ResultT& value, const MatchT& comparitor, const ComparitorTS& ...comparitors)
 {
	return vswitch::detail::comparitors::eq(match, comparitor) 
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
