/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file for_each.inl
 *  \brief Inline file for for_each.h.
 */

#include <thrust/detail/config.h>
#include <thrust/for_each.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/for_each.h>
#include <thrust/system/detail/adl/for_each.h>

namespace thrust
{


template<typename System,
         typename InputIterator,
         typename UnaryFunction>
  InputIterator for_each(thrust::detail::dispatchable_base<System> &system,
                         InputIterator first,
                         InputIterator last,
                         UnaryFunction f)
{
  using thrust::system::detail::generic::for_each;

  return for_each(system.derived(), first, last, f);
}


namespace detail
{

template<typename System, typename InputIterator, typename UnaryFunction>
  InputIterator strip_const_for_each(const System &system, InputIterator first, InputIterator last, UnaryFunction f)
{
  return thrust::for_each(const_cast<System&>(system), first, last, f);
}

}


template<typename InputIterator,
         typename UnaryFunction>
InputIterator for_each(InputIterator first,
                       InputIterator last,
                       UnaryFunction f)
{
  using thrust::system::detail::generic::select_system;
  typedef typename thrust::iterator_system<InputIterator>::type System;

  System system;
  return detail::strip_const_for_each(select_system(system), first, last, f);
} // end for_each()


template<typename System, typename InputIterator, typename Size, typename UnaryFunction>
  InputIterator for_each_n(thrust::detail::dispatchable_base<System> &system,
                           InputIterator first,
                           Size n,
                           UnaryFunction f)
{
  using thrust::system::detail::generic::for_each_n;

  return for_each_n(system.derived(), first, n, f);
} // end for_each_n()


namespace detail
{

template<typename System, typename InputIterator, typename Size, typename UnaryFunction>
  InputIterator strip_const_for_each_n(const System &system, InputIterator first, Size n, UnaryFunction f)
{
  return thrust::for_each_n(const_cast<System&>(system), first, n, f);
}

}


template<typename InputIterator,
         typename Size,
         typename UnaryFunction>
InputIterator for_each_n(InputIterator first,
                         Size n,
                         UnaryFunction f)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<InputIterator>::type System;

  System system;
  return detail::strip_const_for_each_n(select_system(system), first, n, f);
} // end for_each_n()


} // end namespace thrust

