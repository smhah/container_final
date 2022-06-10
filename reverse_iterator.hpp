/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 02:30:58 by smhah             #+#    #+#             */
/*   Updated: 2022/06/10 08:32:11 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include <iostream>
#include <cstddef>
#include "utils/utils.hpp"
#include "utils/iterator_traits.hpp"

namespace ft
{
    template<typename Iterator>
    class reverse_iterator
    {
        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<iterator_type>::value_type value_type;
            typedef typename iterator_traits<iterator_type>::difference_type difference_type;
            typedef typename iterator_traits<iterator_type>::pointer pointer;
            typedef typename iterator_traits<iterator_type>::reference reference;
            typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

            reverse_iterator(): _iter() {}
            explicit reverse_iterator(iterator_type it) : _iter(it) {
            }
            template<class Iter>
            reverse_iterator(const reverse_iterator<Iter>& it) : _iter(it.base()) {}

            iterator_type base() const 
            {
                return _iter;
            }

            reference operator*() const
            {
                iterator_type tmp = _iter;
                return *--tmp;
            }

            pointer operator->() const
            {
                iterator_type tmp(_iter);
                --tmp;
                return tmp.operator->();
            }

            reverse_iterator& operator++()
            {
                --_iter;
                return *this;
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator tmp = *this;
                --_iter;
                return tmp;
            }

            reverse_iterator& operator--()
            {
                ++_iter;
                return *this;
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator tmp = *this;
                ++_iter;
                return tmp;
            }

            reverse_iterator	operator+(difference_type n) const
			{
				reverse_iterator	tmp(this->base());
				tmp._iter -= n;
				return tmp; 
			}

            reverse_iterator& operator+=(difference_type n)
            {
                _iter -= n;
                return *this;
            }

			reverse_iterator operator- (difference_type n) const
			{
				reverse_iterator	tmp(this->base());
				tmp._iter += n;
				return (tmp);
			}

            reverse_iterator& operator-=(difference_type n)
            {
                _iter += n;
                return *this;
            }

            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }

            bool operator==(const reverse_iterator& it) const
            {
                return _iter == it._iter;
            }


            bool operator!=(const reverse_iterator& it) const
            {
                return _iter != it._iter;
            }

            bool operator<(const reverse_iterator& it) const
            {
                return _iter > it._iter;
            }

            bool operator>(const reverse_iterator& it) const
            {
                return _iter < it._iter;
            }

            bool operator<=(const reverse_iterator& it) const
            {
                return _iter >= it._iter;
            }

            bool operator>=(const reverse_iterator& it) const
            {
                return _iter <= it._iter;
            }

        private:
            iterator_type _iter;
};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it)
	{
		return it + n;
	}

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

	template<class Iterator>
	bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template<class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template<class Iterator>
	bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template<class Iterator>
	bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template<class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template<class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
}
#endif
