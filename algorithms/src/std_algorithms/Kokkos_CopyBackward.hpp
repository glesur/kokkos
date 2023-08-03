//@HEADER
// ************************************************************************
//
//                        Kokkos v. 4.0
//       Copyright (2022) National Technology & Engineering
//               Solutions of Sandia, LLC (NTESS).
//
// Under the terms of Contract DE-NA0003525 with NTESS,
// the U.S. Government retains certain rights in this software.
//
// Part of Kokkos, under the Apache License v2.0 with LLVM Exceptions.
// See https://kokkos.org/LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//@HEADER

#ifndef KOKKOS_STD_ALGORITHMS_COPY_BACKWARD_HPP
#define KOKKOS_STD_ALGORITHMS_COPY_BACKWARD_HPP

#include "impl/Kokkos_CopyBackward.hpp"
#include "Kokkos_BeginEnd.hpp"

namespace Kokkos {
namespace Experimental {

//
// overload set accepting execution space
//
template <typename ExecutionSpace, typename IteratorType1, typename IteratorType2,
std::enable_if_t<::Kokkos::is_execution_space_v<ExecutionSpace>, int> = 0>
IteratorType2 copy_backward(const ExecutionSpace& ex, IteratorType1 first, IteratorType1 last,
              IteratorType2 d_last) {
  return Impl::copy_backward_exespace_impl(
      "Kokkos::copy_backward_iterator_api_default", ex, first, last, d_last);
}

template <typename ExecutionSpace, typename IteratorType1, typename IteratorType2
std::enable_if_t<::Kokkos::is_execution_space_v<ExecutionSpace>, int> = 0>
IteratorType2 copy_backward(const std::string& label, const ExecutionSpace& ex,
              IteratorType1 first, IteratorType1 last, IteratorType2 d_last) {
  return Impl::copy_backward_exespace_impl(label, ex, first, last, d_last);
}

template <typename ExecutionSpace, typename DataType1, typename... Properties1,
          typename DataType2, typename... Properties2,
          std::enable_if_t<::Kokkos::is_execution_space_v<ExecutionSpace>, int> = 0>
auto copy_backward(const ExecutionSpace& ex,
                   const ::Kokkos::View<DataType1, Properties1...>& source,
                   ::Kokkos::View<DataType2, Properties2...>& dest) {
  Impl::static_assert_is_admissible_to_kokkos_std_algorithms(source);
  Impl::static_assert_is_admissible_to_kokkos_std_algorithms(dest);

  return Impl::copy_backward_exespace_impl(
      "Kokkos::copy_backward_view_api_default", ex, cbegin(source),
      cend(source), end(dest));
}

template <typename ExecutionSpace, typename DataType1, typename... Properties1,
          typename DataType2, typename... Properties2,
          std::enable_if_t<::Kokkos::is_execution_space_v<ExecutionSpace>,
                           int> = 0>
auto copy_backward(const std::string& label, const ExecutionSpace& ex,
                   const ::Kokkos::View<DataType1, Properties1...>& source,
                   ::Kokkos::View<DataType2, Properties2...>& dest) {
  Impl::static_assert_is_admissible_to_kokkos_std_algorithms(source);
  Impl::static_assert_is_admissible_to_kokkos_std_algorithms(dest);

  return Impl::copy_backward_exespace_impl(label, ex, cbegin(source),
                                           cend(source), end(dest));
}

//
// overload set accepting team handle
//
template <typename TeamHandleType, typename IteratorType1, typename IteratorType2,
std::enable_if_t<::Kokkos::is_team_handle_v<TeamHandleType>, int> = 0>
KOKKOS_FUNCTION
IteratorType2 copy_backward(const TeamHandleType& teamHandle, IteratorType1 first,
              IteratorType1 last, IteratorType2 d_last) {
  return Impl::copy_backward_team_impl(teamHandle, first, last, d_last);
}

template <
    typename TeamHandleType, typename DataType1, typename... Properties1,
    typename DataType2, typename... Properties2,
    std::enable_if_t<::Kokkos::is_team_handle_v<TeamHandleType>, int> = 0>
KOKKOS_FUNCTION auto copy_backward(
    const TeamHandleType& teamHandle,
    const ::Kokkos::View<DataType1, Properties1...>& source,
    ::Kokkos::View<DataType2, Properties2...>& dest) {
  Impl::static_assert_is_admissible_to_kokkos_std_algorithms(source);
  Impl::static_assert_is_admissible_to_kokkos_std_algorithms(dest);

  return Impl::copy_backward_team_impl(teamHandle, cbegin(source), cend(source),
                                       end(dest));
}

}  // namespace Experimental
}  // namespace Kokkos

#endif
