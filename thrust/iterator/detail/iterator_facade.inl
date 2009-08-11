/*
 *  Copyright 2008-2009 NVIDIA Corporation
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

#pragma once

#include <thrust/detail/type_traits.h>
#include <thrust/iterator/iterator_categories.h>
#include <thrust/iterator/iterator_traits.h>

namespace thrust
{

namespace experimental
{

namespace detail
{

// adapted from http://www.boost.org/doc/libs/1_37_0/libs/iterator/doc/iterator_facade.html#iterator-category
//
// iterator-category(T,V,R) :=
//   if(T is convertible to input_host_iterator_tag
//      || T is convertible to output_host_iterator_tag
//      || T is convertible to input_device_iterator_tag
//      || T is convertible to output_device_iterator_tag
//   )
//     return T
//
//   else if (T is not convertible to incrementable_traversal_tag)
//     the program is ill-formed
//
//   else return a type X satisfying the following two constraints:
//
//     1. X is convertible to X1, and not to any more-derived
//        type, where X1 is defined by:
//
//        if (R is a reference type
//            && T is convertible to forward_traversal_tag)
//        {
//          if (T is convertible to random_access_traversal_tag)
//            X1 = random_access_host_iterator_tag
//          else if (T is convertible to bidirectional_traversal_tag)
//            X1 = bidirectional_host_iterator_tag
//          else
//            X1 = forward_host_iterator_tag
//        }
//        else
//        {
//          if (T is convertible to single_pass_traversal_tag
//              && R is convertible to V)
//            X1 = input_host_iterator_tag
//          else
//            X1 = T
//        }
//
//     2. category-to-traversal(X) is convertible to the most
//        derived traversal tag type to which X is also convertible,
//        and not to any more-derived traversal tag type.


template<typename Space, typename Traversal, typename ValueParam, typename Reference>
  struct iterator_facade_default_category;

//
// Convert an iterator_facade's traversal category, Value parameter,
// and ::reference type to an appropriate old-style category.
//
// If writability has been disabled per the above metafunction, the
// result will not be convertible to output_iterator_tag.
//
// Otherwise, if Traversal == single_pass_traversal_tag, the following
// conditions will result in a tag that is convertible both to
// input_iterator_tag and output_iterator_tag:
//
//    1. Reference is a reference to non-const
//    2. Reference is not a reference and is convertible to Value
//


// this is the function for host space iterators
template<typename Traversal, typename ValueParam, typename Reference>
  struct iterator_facade_default_category<thrust::experimental::space::host, Traversal, ValueParam, Reference> :
    thrust::detail::eval_if<
      thrust::detail::and_<
        thrust::detail::is_reference<Reference>,
        thrust::detail::is_convertible<Traversal, thrust::experimental::forward_traversal_tag>
      >::value,
      thrust::detail::eval_if<
        thrust::detail::is_convertible<Traversal, thrust::experimental::random_access_traversal_tag>::value,
        thrust::detail::identity<thrust::random_access_host_iterator_tag>,
        thrust::detail::eval_if<
          thrust::detail::is_convertible<Traversal, thrust::experimental::bidirectional_traversal_tag>::value,
          thrust::bidirectional_host_iterator_tag,
          thrust::forward_host_iterator_tag
        >
      >,
      thrust::detail::eval_if<
        thrust::detail::and_<
          thrust::detail::is_convertible<Traversal, thrust::experimental::single_pass_traversal_tag>,
          thrust::detail::is_convertible<Reference, ValueParam>
        >::value,
        thrust::detail::identity<thrust::input_host_iterator_tag>,
        thrust::detail::identity<Traversal>
      >
    >
{
}; // end iterator_facade_default_category


// this is the function for device space iterators
template<typename Traversal, typename ValueParam, typename Reference>
  struct iterator_facade_default_category<thrust::experimental::space::device, Traversal, ValueParam, Reference> :
    thrust::detail::eval_if<
      thrust::detail::and_<
        thrust::detail::is_device_reference<Reference>,
        thrust::detail::is_convertible<Traversal, thrust::experimental::forward_traversal_tag>
      >::value,
      thrust::detail::eval_if<
        thrust::detail::is_convertible<Traversal, thrust::experimental::random_access_traversal_tag>::value,
        thrust::detail::identity<thrust::random_access_device_iterator_tag>,
        thrust::detail::eval_if<
          thrust::detail::is_convertible<Traversal, thrust::experimental::bidirectional_traversal_tag>::value,
          thrust::bidirectional_device_iterator_tag,
          thrust::forward_device_iterator_tag
        >
      >,
      thrust::detail::eval_if<
        thrust::detail::and_<
          thrust::detail::is_convertible<Traversal, thrust::experimental::single_pass_traversal_tag>,
          thrust::detail::is_convertible<Reference, ValueParam>
        >::value,
        thrust::detail::identity<thrust::input_device_iterator_tag>,
        thrust::detail::identity<Traversal>
      >
    >
{
}; // end iterator_facade_default_category


// this is the function for any space iterators
template<typename Traversal, typename ValueParam, typename Reference>
  struct iterator_facade_default_category<thrust::experimental::space::any, Traversal, ValueParam, Reference> :
    thrust::detail::eval_if<

      thrust::detail::and_<
        thrust::detail::is_reference<Reference>,
        thrust::detail::is_convertible<Traversal, thrust::experimental::forward_traversal_tag>
      >::value,

      thrust::detail::eval_if<
        thrust::detail::is_convertible<Traversal, thrust::experimental::random_access_traversal_tag>::value,
        thrust::detail::identity<thrust::experimental::random_access_universal_iterator_tag>,

        thrust::detail::eval_if<
          thrust::detail::is_convertible<Traversal, thrust::experimental::bidirectional_traversal_tag>::value,
          thrust::experimental::bidirectional_universal_iterator_tag,
          thrust::experimental::forward_universal_iterator_tag
        >
      >,

      thrust::detail::eval_if<
        thrust::detail::and_<
          thrust::detail::is_convertible<Traversal, thrust::experimental::single_pass_traversal_tag>,
          thrust::detail::is_convertible<Reference, ValueParam>
        >::value,
        thrust::detail::identity<thrust::experimental::input_universal_iterator_tag>,
        thrust::detail::identity<Traversal>
      >
    >
{
}; // end iterator_facade_default_category


template<typename Category, typename Space, typename Traversal>
  struct iterator_category_with_space_and_traversal
    : Category, Space, Traversal
{
}; // end iterator_category_with_space_and_traversal

template<typename Space, typename Traversal, typename ValueParam, typename Reference>
  struct iterator_facade_category_impl
{
  typedef typename iterator_facade_default_category<
    Space,Traversal,ValueParam,Reference
  >::type category;

  // we must be able to deduce both Traversal & Space from category
  // otherwise, munge them all together
  typedef typename thrust::detail::eval_if<
    thrust::detail::and_<
      thrust::detail::is_same<
        Traversal,
        typename thrust::experimental::detail::iterator_category_to_traversal<category>::type
      >,
      thrust::detail::is_same<
        Space,
        typename thrust::experimental::detail::iterator_category_to_space<category>::type
      >
    >::value,
    thrust::detail::identity<category>,
    thrust::detail::identity<iterator_category_with_space_and_traversal<category,Space,Traversal> >
  >::type type;
}; // end iterator_facade_category_impl


template<typename CategoryOrSpace,
         typename CategoryOrTraversal,
         typename ValueParam,
         typename Reference>
  struct iterator_facade_category
{
  typedef typename
  thrust::detail::eval_if<
    thrust::detail::is_iterator_category<CategoryOrTraversal>::value,
    thrust::detail::identity<CategoryOrTraversal>, // categories are fine as-is
    iterator_facade_category_impl<CategoryOrSpace, CategoryOrTraversal, ValueParam, Reference>
  >::type type;
}; // end iterator_facade_category

template<typename ValueParam,
         typename CategoryOrSpace,
         typename CategoryOrTraversal,
         typename Reference,
         typename Difference>
  struct iterator_facade_types
{
  typedef typename iterator_facade_category<
    CategoryOrSpace, CategoryOrTraversal, ValueParam, Reference
  >::type iterator_category;

  typedef typename thrust::detail::remove_const<ValueParam>::type value_type;
}; // end iterator_facade_types

} // end detail

} // end experimental

} // end thrust
