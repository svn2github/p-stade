#ifndef PSTADE_LIBS_OVEN_TEST_OVEN_ALL_HPP
#define PSTADE_LIBS_OVEN_TEST_OVEN_ALL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>


#include "pstade/oven/adapted_to_base.hpp"
#include "pstade/oven/adjacent_filtered.hpp"
#include "pstade/oven/adjacent_transformed.hpp"
#include "pstade/oven/advance_from.hpp"
#include "pstade/oven/algorithm.hpp"
#include "pstade/oven/always.hpp"
#include "pstade/oven/any_iterator.hpp"
#include "pstade/oven/any_output_iterator.hpp"
#include "pstade/oven/any_range.hpp"
#include "pstade/oven/applied.hpp"
#include "pstade/oven/applier.hpp"
#include "pstade/oven/array_range.hpp"
#include "pstade/oven/as_array.hpp"
#include "pstade/oven/as_c_str.hpp"
#include "pstade/oven/as_literal.hpp"
#include "pstade/oven/at.hpp"
#include "pstade/oven/back.hpp"
#include "pstade/oven/begin_end.hpp"
#include "pstade/oven/block.hpp"
#include "pstade/oven/broken_into.hpp"
#include "pstade/oven/checked.hpp"
#include "pstade/oven/cleared.hpp"
#include "pstade/oven/comprehension.hpp"
#include "pstade/oven/concatenated.hpp"
#include "pstade/oven/concepts.hpp"
#include "pstade/oven/const_refs.hpp"
#include "pstade/oven/constants.hpp"
#include "pstade/oven/converted.hpp"
#include "pstade/oven/converter.hpp"
#include "pstade/oven/copied_to.hpp"
#include "pstade/oven/copied.hpp"
#include "pstade/oven/copier.hpp"
#include "pstade/oven/copy_range.hpp"
#include "pstade/oven/counting.hpp"
#include "pstade/oven/cycled.hpp"
#include "pstade/oven/delimited.hpp"
#include "pstade/oven/directory_range.hpp"
#include "pstade/oven/distance.hpp"
#include "pstade/oven/do_iter_swap.hpp"
#include "pstade/oven/dropped.hpp"
#include "pstade/oven/dropped_while.hpp"
#include "pstade/oven/elements.hpp"
#include "pstade/oven/empty_range.hpp"
#include "pstade/oven/equals.hpp"
#include "pstade/oven/exists.hpp"
#include "pstade/oven/expression.hpp"
#include "pstade/oven/extension.hpp"
#include "pstade/oven/file_range.hpp"
#include "pstade/oven/filtered.hpp"
#include "pstade/oven/filterer.hpp"
#include "pstade/oven/forall.hpp"
#include "pstade/oven/foreach.hpp"
#include "pstade/oven/front.hpp"
#include "pstade/oven/generation.hpp"
#include "pstade/oven/hetero.hpp"
#include "pstade/oven/identities.hpp"
#include "pstade/oven/indexing.hpp"
#include "pstade/oven/indirected.hpp"
#include "pstade/oven/indirecter.hpp"
#include "pstade/oven/initial_ptrs.hpp"
#include "pstade/oven/initial_values.hpp"
#include "pstade/oven/io.hpp"
#include "pstade/oven/is_heap.hpp"
#include "pstade/oven/is_sorted.hpp"
#include "pstade/oven/iter_range.hpp"
#include "pstade/oven/iteration.hpp"
#include "pstade/oven/iterator_base.hpp"
#include "pstade/oven/jointed.hpp"
#include "pstade/oven/lines.hpp"
#include "pstade/oven/lower_chars.hpp"
#include "pstade/oven/make_range.hpp"
#include "pstade/oven/map_keys.hpp"
#include "pstade/oven/map_values.hpp"
#include "pstade/oven/matches.hpp"
#include "pstade/oven/matrix.hpp"
// #include "pstade/oven/mb_decoded.hpp"
// #include "pstade/oven/mb_encoded.hpp"
#include "pstade/oven/memoized.hpp"
#include "pstade/oven/merged.hpp"
#include "pstade/oven/moved.hpp"
#include "pstade/oven/narrow_chars.hpp"
#include "pstade/oven/offset.hpp"
#include "pstade/oven/optional.hpp"
#include "pstade/oven/outdirected.hpp"
#include "pstade/oven/outplaced.hpp"
#include "pstade/oven/parallel_copy.hpp"
#include "pstade/oven/parallel_equals.hpp"
#include "pstade/oven/parallel_for_each.hpp"
#include "pstade/oven/parallel_reduce.hpp"
#include "pstade/oven/parallel_sort.hpp"
#include "pstade/oven/partitioned.hpp"
#include "pstade/oven/permuted.hpp"
#include "pstade/oven/permuter.hpp"
#include "pstade/oven/pointed.hpp"
#include "pstade/oven/popped.hpp"
#include "pstade/oven/ptr_container.hpp"
#include "pstade/oven/range_category.hpp"
#include "pstade/oven/range_constant_iterator.hpp"
#include "pstade/oven/range_difference.hpp"
#include "pstade/oven/range_iterator.hpp"
#include "pstade/oven/range_mutable_iterator.hpp"
#include "pstade/oven/range_pointer.hpp"
#include "pstade/oven/range_reference.hpp"
#include "pstade/oven/range_transformer.hpp"
#include "pstade/oven/range_traversal.hpp"
#include "pstade/oven/range_value.hpp"
#include "pstade/oven/read.hpp"
#include "pstade/oven/recursion.hpp"
#include "pstade/oven/regex.hpp"
#include "pstade/oven/regular.hpp"
#include "pstade/oven/reverse_iterator.hpp"
#include "pstade/oven/reversed.hpp"
#include "pstade/oven/rotated.hpp"
#include "pstade/oven/rvalues.hpp"
#include "pstade/oven/scanned.hpp"
#include "pstade/oven/set_cap.hpp"
#include "pstade/oven/set_cup.hpp"
#include "pstade/oven/set_delta.hpp"
#include "pstade/oven/set_minus.hpp"
#include "pstade/oven/shared.hpp"
#include "pstade/oven/shared_regular.hpp"
#include "pstade/oven/shared_single.hpp"
#include "pstade/oven/shared_values.hpp"
#include "pstade/oven/single.hpp"
#include "pstade/oven/sliced.hpp"
#include "pstade/oven/sorted.hpp"
#include "pstade/oven/spanned.hpp"
#include "pstade/oven/split_at.hpp"
#include "pstade/oven/steps.hpp"
#include "pstade/oven/stream_lines.hpp"
#include "pstade/oven/stream_read.hpp"
#include "pstade/oven/stream_writer.hpp"
#include "pstade/oven/string_found.hpp"
#include "pstade/oven/string_split.hpp"
#include "pstade/oven/sub_range.hpp"
#include "pstade/oven/sub_set.hpp"
#include "pstade/oven/successors.hpp"
#include "pstade/oven/sugar.hpp"
#include "pstade/oven/tab_expanded.hpp"
#include "pstade/oven/tab_unexpanded.hpp"
#include "pstade/oven/tagged.hpp"
#include "pstade/oven/taken.hpp"
#include "pstade/oven/taken_while.hpp"
#include "pstade/oven/tokenized.hpp"
#include "pstade/oven/transformed.hpp"
#include "pstade/oven/transformer.hpp"
#include "pstade/oven/traversal_tags.hpp"
#include "pstade/oven/tuple.hpp"
#include "pstade/oven/typeof.hpp"
#include "pstade/oven/unfold.hpp"
#include "pstade/oven/uniqued.hpp"
#include "pstade/oven/unrolled_copy.hpp"
#include "pstade/oven/unrolled_foreach.hpp"
#include "pstade/oven/unrolled_reduce.hpp"
#include "pstade/oven/unzipped.hpp"
#include "pstade/oven/upper_chars.hpp"
#include "pstade/oven/utf8_decoded.hpp"
#include "pstade/oven/utf8_encoded.hpp"
#include "pstade/oven/utf8_encoder.hpp"
#include "pstade/oven/utf16_decoded.hpp"
#include "pstade/oven/utf16_encoded.hpp"
#include "pstade/oven/utf16_encoder.hpp"
#include "pstade/oven/wide_chars.hpp"
#include "pstade/oven/window.hpp"
#include "pstade/oven/with_data.hpp"
#include "pstade/oven/with_line_number.hpp"
#include "pstade/oven/with_position.hpp"
#include "pstade/oven/write.hpp"
#include "pstade/oven/xpressive.hpp"
#include "pstade/oven/xpressive_matches.hpp"
#include "pstade/oven/xpressive_tokenized.hpp"
#include "pstade/oven/zipped.hpp"
#include "pstade/oven/zipped_with.hpp"

#if BOOST_VERSION >= 103500
    #include "pstade/oven/fuzipped.hpp"
    #include "pstade/oven/unfuzipped.hpp"
#endif


#endif
