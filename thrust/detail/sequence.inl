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


/*! \file sequence.inl
 *  \brief Inline file for sequence.h.
 */

#include <thrust/detail/config.h>
#include <thrust/sequence.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/sequence.h>
#include <thrust/system/detail/adl/sequence.h>

namespace thrust
{


template<typename System, typename ForwardIterator>
  void sequence(thrust::detail::dispatchable_base<System> &system,
                ForwardIterator first,
                ForwardIterator last)
{
  using thrust::system::detail::generic::sequence;
  return sequence(system.derived(), first, last);
} // end sequence()


template<typename System, typename ForwardIterator, typename T>
  void sequence(thrust::detail::dispatchable_base<System> &system,
                ForwardIterator first,
                ForwardIterator last,
                T init)
{
  using thrust::system::detail::generic::sequence;
  return sequence(system.derived(), first, last, init);
} // end sequence()


template<typename System, typename ForwardIterator, typename T>
  void sequence(thrust::detail::dispatchable_base<System> &system,
                ForwardIterator first,
                ForwardIterator last,
                T init,
                T step)
{
  using thrust::system::detail::generic::sequence;
  return sequence(system.derived(), first, last, init, step);
} // end sequence()


namespace detail
{


template<typename System, typename ForwardIterator>
  void strip_const_sequence(const System &system,
                            ForwardIterator first,
                            ForwardIterator last)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::sequence(non_const_system, first, last);
} // end sequence()


template<typename System, typename ForwardIterator, typename T>
  void strip_const_sequence(const System &system,
                            ForwardIterator first,
                            ForwardIterator last,
                            T init)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::sequence(non_const_system, first, last, init);
} // end sequence()


template<typename System, typename ForwardIterator, typename T>
  void strip_const_sequence(const System &system,
                            ForwardIterator first,
                            ForwardIterator last,
                            T init,
                            T step)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::sequence(non_const_system, first, last, init, step);
} // end sequence()


} // end detail


template<typename ForwardIterator>
  void sequence(ForwardIterator first,
                ForwardIterator last)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<ForwardIterator>::type System;

  System system;

  return thrust::detail::strip_const_sequence(select_system(system), first, last);
} // end sequence()


template<typename ForwardIterator, typename T>
  void sequence(ForwardIterator first,
                ForwardIterator last,
                T init)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<ForwardIterator>::type System;

  System system;

  return thrust::detail::strip_const_sequence(select_system(system), first, last, init);
} // end sequence()


template<typename ForwardIterator, typename T>
  void sequence(ForwardIterator first,
                ForwardIterator last,
                T init,
                T step)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<ForwardIterator>::type System;

  System system;

  return thrust::detail::strip_const_sequence(select_system(system), first, last, init, step);
} // end sequence()


} // end namespace thrust

