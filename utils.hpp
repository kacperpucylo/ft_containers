/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpucylo <kpucylo@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:02:47 by kpucylo           #+#    #+#             */
/*   Updated: 2022/06/20 14:10:25 by kpucylo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <stddef.h>
#include <sstream>

namespace ft
{
	//base iterator class
	template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	class iterator
	{
	public:

		//type of elements pointed to
		typedef T value_type;
		//represents difference between two iterators
		typedef Distance difference_type;
		//pointer to element pointed to
		typedef Pointer pointer;
		//reference to element pointed to
		typedef Reference reference;
		//category of the iterator
		typedef Category iterator_category;
	};

	//empty classes to identify iterator types
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};

	//struct defining iterator properties, taken from Iterator class
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <typename T>
	struct iterator_traits<T *>
	{
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T *>
	{
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	//reverse iterator to given Iterator class
	template <class Iterator>
	class reverse_iterator
	{
	public:

		typedef Iterator iterator_type;
		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

		reverse_iterator(void) : _it() {}
		explicit reverse_iterator(iterator_type it) : _it(it) {}
		template <class Iter>
			reverse_iterator(const reverse_iterator<Iter> &rev_it)
				: _it(rev_it.base()) {}
		virtual ~reverse_iterator(void) {}

		reverse_iterator &operator=(const reverse_iterator &rhs)
		{
			this->_it = rhs._it;
			return (*this);
		}

		iterator_type base(void) const
		{
			return (this->_it);
		}

		reference operator*(void) const
		{
			iterator_type temp = this->_it;
			temp--;
			return (*temp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator(this->_it - n));
		}
		reverse_iterator &operator++(void)
		{
			this->_it--;
			return (*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			++(*this);
			return (temp);
		}
		reverse_iterator &operator+=(difference_type n)
		{
			*this = *this + n;
			return (*this);
		}
		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator(this->_it + n));
		}
		reverse_iterator &operator--(void)
		{
			this->_it++;
			return (*this);
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			--(*this);
			return (temp);
		}
		reverse_iterator &operator-=(difference_type n)
		{
			*this = *this - n;
			return (*this);
		}
		pointer operator->(void) const
		{
			return(&(operator*()));
		}
		reference operator[](difference_type n) const
		{
			return (this->base()[-n - 1]);
		}

	private:

		iterator_type _it;
	};
	//non-member overloads for reverse_iterator
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template <class Iterator_L, class Iterator_R>
	bool operator==(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template <class Iterator_L, class Iterator_R>
	bool operator!=(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template <class Iterator_L, class Iterator_R>
	bool operator<(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template <class Iterator_L, class Iterator_R>
	bool operator<=(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template <class Iterator_L, class Iterator_R>
	bool operator>(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs,
					const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	//for comparisons between reverse_iterator and const_reverse_iterator
	template <class Iterator_L, class Iterator_R>
	bool operator>=(const reverse_iterator<Iterator_L> &lhs,
					const reverse_iterator<Iterator_R> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
										const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs,
																const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	// //convert n to std::string
	template <typename T>
	std::string to_str(T n)
	{
		std::ostringstream oss;
		oss << n;
		return (oss.str());
	}

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			first++;
			n++;
		}
		return (n);
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return (false);
			else if (comp(*first1, *first2))
				return (true);
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	//holds a pair of values
	template <class T1, class T2>
	class pair
	{
	public:

		typedef T1 first_type;
		typedef T2 second_type;

		pair(void) : first(), second() {}
		//init with given values
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		template <class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

		~pair(void) {}

		const pair &operator=(const pair &rhs)
		{
			this->first = rhs.first;
			this->second = rhs.second;
			return (*this);
		}

		first_type first;
		second_type second;

	private:
	};

	//logical operators for ft::pair
	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (!(lhs < rhs));
	}

	//constructs and returns a pair of x and y values
	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	//enable_if is used to decide whether a template type substition should be valid with current type
	template <bool, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	//used to decide whether passed type is of integral type
	template <class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	typedef integral_constant<bool, false> false_type;
	typedef integral_constant<bool, true> true_type;

	//non-itegral types
	template <class T> struct is_integral : false_type {};

	//integral types
	template <> struct is_integral<bool> : true_type {};
	template <> struct is_integral<char> : true_type {};
	template <> struct is_integral<char16_t> : true_type {};
	template <> struct is_integral<char32_t> : true_type {};
	template <> struct is_integral<wchar_t> : true_type {};
	template <> struct is_integral<signed char> : true_type {};
	template <> struct is_integral<short int> : true_type {};
	template <> struct is_integral<int> : true_type {};
	template <> struct is_integral<long int> : true_type {};
	template <> struct is_integral<long long int> : true_type {};
	template <> struct is_integral<unsigned char> : true_type {};
	template <> struct is_integral<unsigned short int> : true_type {};
	template <> struct is_integral<unsigned int> : true_type {};
	template <> struct is_integral<unsigned long int> : true_type {};
	template <> struct is_integral<unsigned long long int> : true_type {};
}

#endif
