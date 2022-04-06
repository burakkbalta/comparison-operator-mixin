#ifndef COMPARISON_OPERATOR_MIXIN_H
#define COMPARISON_OPERATOR_MIXIN_H

#include <type_traits>

namespace bb {

/**
 * Traits which can be used to check whether type T has a less than operator function overload.
 * If it has , a member variable named as value is set to true,otherwise false.
 * In compile time, check operations can be processed with using this member.
 */
template<typename T>
struct has_less_than_operator
{
	using Type = typename std::remove_reference<typename std::remove_cv<typename std::remove_all_extents<T>::type>::type>::type;
	
	template<typename U>
	static constexpr decltype(std::declval<Type>().operator <(std::declval<Type>()), bool())
	test_less_than(int)
	{
		return true;
	}
	
	template<typename U>
	static constexpr bool test_less_than(...) {
		return false;
	}
	
	static constexpr bool value = test_less_than<T>(int());
};
/**
 * In below, CRTP is used. The aim is to ensure all operator overloading function should be implemented 
 * for derived class given template parameter. 
 * To use the following structure, the one pre-condition that derived class should implement 
 * less than operator overloading function should be provided.  
 */
template<typename CRTP>
struct ComparisonOperatorMixin {

	bool operator==(const ComparisonOperatorMixin &rhs) const noexcept {
        static_assert(has_less_than_operator<CRTP>::value, "Less than operator function should be implemented.");
		return !(static_cast<const CRTP &>(*this) < static_cast<const CRTP&>(rhs) 
		 || static_cast<const CRTP &>(rhs) < static_cast<const CRTP&>(*this)); 
	}
	
	bool operator!=(const ComparisonOperatorMixin &rhs) const noexcept {
		return !(*this == rhs);
	}
	
	bool operator>(const ComparisonOperatorMixin &rhs) const noexcept {
        static_assert(has_less_than_operator<CRTP>::value, "Less than operator function should be implemented.");
		return !(static_cast<const CRTP &>(*this) < static_cast<const CRTP&>(rhs)
			|| (*this == rhs));
	}
	
	bool operator>=(const ComparisonOperatorMixin &rhs) const noexcept {
        static_assert(has_less_than_operator<CRTP>::value, "Less than operator function should be implemented.");
		return !(static_cast<const CRTP &>(*this) < static_cast<const CRTP&>(rhs));
	}
	
	bool operator<=(const ComparisonOperatorMixin &rhs) const noexcept {
		return !(*this > rhs);
	}
};

}

#endif /* COMPARISON_OPERATOR_MIXIN_H */

