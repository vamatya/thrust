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


/*! \file adjacent_difference.inl
 *  \brief Inline file for adjacent_difference.h
 */

#include <thrust/detail/config.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/adjacent_difference.h>
#include <thrust/system/detail/adl/adjacent_difference.h>

namespace thrust
{


template <typename System, typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(thrust::detail::dispatchable_base<System> &system,
                                   InputIterator first, InputIterator last, 
                                   OutputIterator result)
{
  using thrust::system::detail::generic::adjacent_difference;

  return adjacent_difference(system.derived(), first, last, result);
} // end adjacent_difference()


template <typename System, typename InputIterator, typename OutputIterator, typename BinaryFunction>
OutputIterator adjacent_difference(thrust::detail::dispatchable_base<System> &system,
                                   InputIterator first, InputIterator last, 
                                   OutputIterator result,
                                   BinaryFunction binary_op)
{
  using thrust::system::detail::generic::adjacent_difference;

  return adjacent_difference(system.derived(), first, last, result, binary_op);
} // end adjacent_difference()


namespace detail
{


template <typename System, typename InputIterator, typename OutputIterator>
OutputIterator strip_const_adjacent_difference(const System &system,
                                               InputIterator first, InputIterator last, 
                                               OutputIterator result)
{
  System &non_const_system = const_cast<System&>(system);

  return thrust::adjacent_difference(non_const_system, first, last, result);
} // end adjacent_difference()


template <typename System, typename InputIterator, typename OutputIterator, typename BinaryFunction>
OutputIterator strip_const_adjacent_difference(const System &system,
                                               InputIterator first, InputIterator last, 
                                               OutputIterator result,
                                               BinaryFunction binary_op)
{
  System &non_const_system = const_cast<System&>(system);

  return thrust::adjacent_difference(non_const_system, first, last, result, binary_op);
} // end adjacent_difference()


} // end detail


template <typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, 
                                   OutputIterator result)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<InputIterator>::type  System1;
  typedef typename thrust::iterator_system<OutputIterator>::type System2;

  System1 system1;
  System2 system2;

  return thrust::detail::strip_const_adjacent_difference(select_system(system1, system2), first, last, result);
} // end adjacent_difference()


template <typename InputIterator, typename OutputIterator, typename BinaryFunction>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
                                   OutputIterator result,
                                   BinaryFunction binary_op)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<InputIterator>::type  System1;
  typedef typename thrust::iterator_system<OutputIterator>::type System2;

  System1 system1;
  System2 system2;

  return thrust::detail::strip_const_adjacent_difference(select_system(system1, system2), first, last, result, binary_op);
} // end adjacent_difference()


} // end namespace thrust

