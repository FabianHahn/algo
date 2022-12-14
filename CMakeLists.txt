cmake_minimum_required(VERSION 3.1)
project(algo VERSION 0.1 LANGUAGES CXX)

enable_testing()

add_executable(find_median_k_sorted "find_median_k_sorted.cpp")
target_link_libraries(find_median_k_sorted GTest::gtest GTest::gmock)
set_property(TARGET find_median_k_sorted PROPERTY CXX_STANDARD 17)
add_test(find_median_k_sorted find_median_k_sorted)

add_executable(valid_sudoku "valid_sudoku.cpp")
target_link_libraries(valid_sudoku GTest::gtest GTest::gmock)
set_property(TARGET valid_sudoku PROPERTY CXX_STANDARD 17)
add_test(valid_sudoku valid_sudoku)

add_executable(3sum "3sum.cpp")
target_link_libraries(3sum GTest::gtest GTest::gmock)
set_property(TARGET 3sum PROPERTY CXX_STANDARD 17)
add_test(3sum 3sum)

add_executable(2sum "2sum.cpp")
target_link_libraries(2sum GTest::gtest GTest::gmock)
set_property(TARGET 2sum PROPERTY CXX_STANDARD 17)
add_test(2sum 2sum)

add_executable(2sum_sorted "2sum_sorted.cpp")
target_link_libraries(2sum_sorted GTest::gtest GTest::gmock)
set_property(TARGET 2sum_sorted PROPERTY CXX_STANDARD 17)
add_test(2sum_sorted 2sum_sorted)

add_executable(calendar_double_booking "calendar_double_booking.cpp")
target_link_libraries(calendar_double_booking GTest::gtest GTest::gmock)
set_property(TARGET calendar_double_booking PROPERTY CXX_STANDARD 17)
add_test(calendar_double_booking calendar_double_booking)

add_executable(longest_common_prefix "longest_common_prefix.cpp")
target_link_libraries(longest_common_prefix GTest::gtest GTest::gmock)
set_property(TARGET longest_common_prefix PROPERTY CXX_STANDARD 17)
add_test(longest_common_prefix longest_common_prefix)

add_executable(regex_match "regex_match.cpp")
target_link_libraries(regex_match GTest::gtest GTest::gmock)
set_property(TARGET regex_match PROPERTY CXX_STANDARD 17)
add_test(regex_match regex_match)

add_executable(mirror_reflection "mirror_reflection.cpp")
target_link_libraries(mirror_reflection GTest::gtest GTest::gmock)
set_property(TARGET mirror_reflection PROPERTY CXX_STANDARD 17)
add_test(mirror_reflection mirror_reflection)

add_executable(combination_sum4 "combination_sum.cpp")
target_link_libraries(combination_sum4 GTest::gtest GTest::gmock)
set_property(TARGET combination_sum4 PROPERTY CXX_STANDARD 17)
add_test(combination_sum4 combination_sum4)

add_executable(racecar "racecar.cpp")
target_link_libraries(racecar GTest::gtest GTest::gmock)
set_property(TARGET racecar PROPERTY CXX_STANDARD 17)
add_test(racecar racecar)

add_executable(largest_rectangle_area "largest_rectangle_area.cpp")
target_link_libraries(largest_rectangle_area GTest::gtest GTest::gmock)
set_property(TARGET largest_rectangle_area PROPERTY CXX_STANDARD 17)
add_test(largest_rectangle_area largest_rectangle_area)

add_executable(hamming_weight "hamming_weight.cpp")
target_link_libraries(hamming_weight GTest::gtest GTest::gmock)
set_property(TARGET hamming_weight PROPERTY CXX_STANDARD 17)
add_test(hamming_weight hamming_weight)

add_executable(longest_substring "longest_substring.cpp")
target_link_libraries(longest_substring GTest::gtest GTest::gmock)
set_property(TARGET longest_substring PROPERTY CXX_STANDARD 17)
add_test(longest_substring longest_substring)

add_executable(merge_k_lists "merge_k_lists.cpp")
target_link_libraries(merge_k_lists GTest::gtest GTest::gmock)
set_property(TARGET merge_k_lists PROPERTY CXX_STANDARD 17)
add_test(merge_k_lists merge_k_lists)

add_executable(longest_palindromic_substring "longest_palindromic_substring.cpp")
target_link_libraries(longest_palindromic_substring GTest::gtest GTest::gmock)
set_property(TARGET longest_palindromic_substring PROPERTY CXX_STANDARD 17)
add_test(longest_palindromic_substring longest_palindromic_substring)

add_executable(trie "trie.cpp")
target_link_libraries(trie GTest::gtest GTest::gmock)
set_property(TARGET trie PROPERTY CXX_STANDARD 17)
add_test(trie trie)

add_executable(num_islands "num_islands.cpp")
target_link_libraries(num_islands GTest::gtest GTest::gmock)
set_property(TARGET num_islands PROPERTY CXX_STANDARD 17)
add_test(num_islands num_islands)

add_executable(tree_max_path_sum "tree_max_path_sum.cpp")
target_link_libraries(tree_max_path_sum GTest::gtest GTest::gmock)
set_property(TARGET tree_max_path_sum PROPERTY CXX_STANDARD 17)
add_test(tree_max_path_sum tree_max_path_sum)

add_executable(k_closest "k_closest.cpp")
target_link_libraries(k_closest GTest::gtest GTest::gmock)
set_property(TARGET k_closest PROPERTY CXX_STANDARD 17)
add_test(k_closest k_closest)

add_executable(reduce_array_size "reduce_array_size.cpp")
target_link_libraries(reduce_array_size GTest::gtest GTest::gmock)
set_property(TARGET reduce_array_size PROPERTY CXX_STANDARD 17)
add_test(reduce_array_size reduce_array_size)

add_executable(insert_interval "insert_interval.cpp")
target_link_libraries(insert_interval GTest::gtest GTest::gmock)
set_property(TARGET insert_interval PROPERTY CXX_STANDARD 17)
add_test(insert_interval insert_interval)

add_executable(k_largest "k_largest.cpp")
target_link_libraries(k_largest GTest::gtest GTest::gmock)
set_property(TARGET k_largest PROPERTY CXX_STANDARD 17)
add_test(k_largest k_largest)

add_executable(network_delay_time "network_delay_time.cpp")
target_link_libraries(network_delay_time GTest::gtest GTest::gmock)
set_property(TARGET network_delay_time PROPERTY CXX_STANDARD 17)
add_test(network_delay_time network_delay_time)

add_executable(minimum_window_substring "minimum_window_substring.cpp")
target_link_libraries(minimum_window_substring GTest::gtest GTest::gmock)
set_property(TARGET minimum_window_substring PROPERTY CXX_STANDARD 17)
add_test(minimum_window_substring minimum_window_substring)

add_executable(word_ladder "word_ladder.cpp")
target_link_libraries(word_ladder GTest::gtest GTest::gmock)
set_property(TARGET word_ladder PROPERTY CXX_STANDARD 17)
add_test(word_ladder word_ladder)

add_executable(stock_trading "stock_trading.cpp")
target_link_libraries(stock_trading GTest::gtest GTest::gmock)
set_property(TARGET stock_trading PROPERTY CXX_STANDARD 17)
add_test(stock_trading stock_trading)

add_executable(lru_cache "lru_cache.cpp")
target_link_libraries(lru_cache GTest::gtest GTest::gmock)
set_property(TARGET lru_cache PROPERTY CXX_STANDARD 17)
add_test(lru_cache lru_cache)

add_executable(reconstruct_itinerary "reconstruct_itinerary.cpp")
target_link_libraries(reconstruct_itinerary GTest::gtest GTest::gmock)
set_property(TARGET reconstruct_itinerary PROPERTY CXX_STANDARD 17)
add_test(reconstruct_itinerary reconstruct_itinerary)

add_executable(min_interval "min_interval.cpp")
target_compile_definitions(min_interval PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(min_interval GTest::gtest GTest::gmock)
set_property(TARGET min_interval PROPERTY CXX_STANDARD 17)
add_test(min_interval min_interval)

add_executable(sliding_window_max "sliding_window_max.cpp")
target_compile_definitions(sliding_window_max PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(sliding_window_max GTest::gtest GTest::gmock)
set_property(TARGET sliding_window_max PROPERTY CXX_STANDARD 17)
add_test(sliding_window_max sliding_window_max)

add_executable(longest_dictionary_word "longest_dictionary_word.cpp")
target_compile_definitions(longest_dictionary_word PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(longest_dictionary_word GTest::gtest GTest::gmock)
set_property(TARGET longest_dictionary_word PROPERTY CXX_STANDARD 17)
add_test(longest_dictionary_word longest_dictionary_word)

add_executable(max_points_on_line "max_points_on_line.cpp")
target_compile_definitions(max_points_on_line PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(max_points_on_line GTest::gtest GTest::gmock)
set_property(TARGET max_points_on_line PROPERTY CXX_STANDARD 17)
add_test(max_points_on_line max_points_on_line)

add_executable(group_anagrams "group_anagrams.cpp")
target_compile_definitions(group_anagrams PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(group_anagrams GTest::gtest GTest::gmock)
set_property(TARGET group_anagrams PROPERTY CXX_STANDARD 17)
add_test(group_anagrams group_anagrams)

add_executable(median_of_stream "median_of_stream.cpp")
target_compile_definitions(median_of_stream PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(median_of_stream GTest::gtest GTest::gmock)
set_property(TARGET median_of_stream PROPERTY CXX_STANDARD 17)
add_test(median_of_stream median_of_stream)

add_executable(character_stream "character_stream.cpp")
target_compile_definitions(character_stream PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(character_stream GTest::gtest GTest::gmock)
set_property(TARGET character_stream PROPERTY CXX_STANDARD 17)
add_test(character_stream character_stream)

add_executable(word_search "word_search.cpp")
target_compile_definitions(word_search PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(word_search GTest::gtest GTest::gmock)
set_property(TARGET word_search PROPERTY CXX_STANDARD 17)
add_test(word_search word_search)

add_executable(word_search2 "word_search2.cpp")
target_compile_definitions(word_search2 PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(word_search2 GTest::gtest GTest::gmock)
set_property(TARGET word_search2 PROPERTY CXX_STANDARD 17)
add_test(word_search2 word_search2)

add_executable(coin_piles "coin_piles.cpp")
target_compile_definitions(coin_piles PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(coin_piles GTest::gtest GTest::gmock)
set_property(TARGET coin_piles PROPERTY CXX_STANDARD 17)
add_test(coin_piles coin_piles)

add_executable(speed_limits "speed_limits.cpp")
target_compile_definitions(speed_limits PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(speed_limits GTest::gtest GTest::gmock)
set_property(TARGET speed_limits PROPERTY CXX_STANDARD 17)
add_test(speed_limits speed_limits)

add_executable(word_pattern "word_pattern.cpp")
target_compile_definitions(word_pattern PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(word_pattern GTest::gtest GTest::gmock)
set_property(TARGET word_pattern PROPERTY CXX_STANDARD 17)
add_test(word_pattern word_pattern)

add_executable(maximum_multiplication_score "maximum_multiplication_score.cpp")
target_compile_definitions(maximum_multiplication_score PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(maximum_multiplication_score GTest::gtest GTest::gmock)
set_property(TARGET maximum_multiplication_score PROPERTY CXX_STANDARD 17)
add_test(maximum_multiplication_score maximum_multiplication_score)

add_executable(happy_number "happy_number.cpp")
target_compile_definitions(happy_number PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(happy_number GTest::gtest GTest::gmock)
set_property(TARGET happy_number PROPERTY CXX_STANDARD 17)
add_test(happy_number happy_number)

add_executable(course_schedule "course_schedule.cpp")
target_compile_definitions(course_schedule PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(course_schedule GTest::gtest GTest::gmock)
set_property(TARGET course_schedule PROPERTY CXX_STANDARD 17)
add_test(course_schedule happy_number)

add_executable(first_missing_positive "first_missing_positive.cpp")
target_compile_definitions(first_missing_positive PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(first_missing_positive GTest::gtest GTest::gmock)
set_property(TARGET first_missing_positive PROPERTY CXX_STANDARD 17)
add_test(first_missing_positive first_missing_positive)

add_executable(serialize_binary_tree "serialize_binary_tree.cpp")
target_compile_definitions(serialize_binary_tree PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(serialize_binary_tree GTest::gtest GTest::gmock)
set_property(TARGET serialize_binary_tree PROPERTY CXX_STANDARD 17)
add_test(serialize_binary_tree serialize_binary_tree)

add_executable(binary_concat "binary_concat.cpp")
target_compile_definitions(binary_concat PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(binary_concat GTest::gtest GTest::gmock)
set_property(TARGET binary_concat PROPERTY CXX_STANDARD 17)
add_test(binary_concat binary_concat)

add_executable(equality_satisfiability "equality_satisfiability.cpp")
target_compile_definitions(equality_satisfiability PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(equality_satisfiability GTest::gtest GTest::gmock)
set_property(TARGET equality_satisfiability PROPERTY CXX_STANDARD 17)
add_test(equality_satisfiability equality_satisfiability)

add_executable(min_eating_speed "min_eating_speed.cpp")
target_compile_definitions(min_eating_speed PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(min_eating_speed GTest::gtest GTest::gmock)
set_property(TARGET min_eating_speed PROPERTY CXX_STANDARD 17)
add_test(min_eating_speed min_eating_speed)

add_executable(dominoes "dominoes.cpp")
target_compile_definitions(dominoes PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(dominoes GTest::gtest GTest::gmock)
set_property(TARGET dominoes PROPERTY CXX_STANDARD 17)
add_test(dominoes dominoes)

add_executable(cat_mouse "cat_mouse.cpp")
target_compile_definitions(cat_mouse PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(cat_mouse GTest::gtest GTest::gmock)
set_property(TARGET cat_mouse PROPERTY CXX_STANDARD 17)
add_test(cat_mouse cat_mouse)

add_executable(trapping_rain_water "trapping_rain_water.cpp")
target_compile_definitions(trapping_rain_water PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(trapping_rain_water GTest::gtest GTest::gmock)
set_property(TARGET trapping_rain_water PROPERTY CXX_STANDARD 17)
add_test(trapping_rain_water trapping_rain_water)

add_executable(producer_consumer "producer_consumer.cpp")
target_compile_definitions(producer_consumer PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(producer_consumer GTest::gtest GTest::gmock)
set_property(TARGET producer_consumer PROPERTY CXX_STANDARD 17)
add_test(producer_consumer producer_consumer)

add_executable(find_k_closest "find_k_closest.cpp")
target_compile_definitions(find_k_closest PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(find_k_closest GTest::gtest GTest::gmock)
set_property(TARGET find_k_closest PROPERTY CXX_STANDARD 17)
add_test(find_k_closest find_k_closest)

add_executable(skyline "skyline.cpp")
target_compile_definitions(skyline PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(skyline GTest::gtest GTest::gmock)
set_property(TARGET skyline PROPERTY CXX_STANDARD 17)
add_test(skyline skyline)

add_executable(colorful_balloons "colorful_balloons.cpp")
target_compile_definitions(colorful_balloons PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(colorful_balloons GTest::gtest GTest::gmock)
set_property(TARGET colorful_balloons PROPERTY CXX_STANDARD 17)
add_test(colorful_balloons colorful_balloons)

add_executable(path_sum "path_sum.cpp")
target_compile_definitions(path_sum PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(path_sum GTest::gtest GTest::gmock)
set_property(TARGET path_sum PROPERTY CXX_STANDARD 17)
add_test(path_sum path_sum)

add_executable(semaphore "semaphore.cpp")
target_compile_definitions(semaphore PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(semaphore GTest::gtest GTest::gmock)
set_property(TARGET semaphore PROPERTY CXX_STANDARD 17)
add_test(semaphore semaphore)

add_executable(target_sum "target_sum.cpp")
target_compile_definitions(target_sum PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(target_sum GTest::gtest GTest::gmock)
set_property(TARGET target_sum PROPERTY CXX_STANDARD 17)
add_test(target_sum target_sum)

add_executable(cheapest_flight "cheapest_flight.cpp")
target_compile_definitions(cheapest_flight PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(cheapest_flight GTest::gtest GTest::gmock)
set_property(TARGET cheapest_flight PROPERTY CXX_STANDARD 17)
add_test(cheapest_flight cheapest_flight)

add_executable(decode_ways "decode_ways.cpp")
target_compile_definitions(decode_ways PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(decode_ways GTest::gtest GTest::gmock)
set_property(TARGET decode_ways PROPERTY CXX_STANDARD 17)
add_test(decode_ways decode_ways)

add_executable(first_bad_version "first_bad_version.cpp")
target_compile_definitions(first_bad_version PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(first_bad_version GTest::gtest GTest::gmock)
set_property(TARGET first_bad_version PROPERTY CXX_STANDARD 17)
add_test(first_bad_version first_bad_version)

add_executable(continuous_subarray_sum "continuous_subarray_sum.cpp")
target_compile_definitions(continuous_subarray_sum PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(continuous_subarray_sum GTest::gtest GTest::gmock)
set_property(TARGET continuous_subarray_sum PROPERTY CXX_STANDARD 17)
add_test(continuous_subarray_sum continuous_subarray_sum)

add_subdirectory(thirdparty)
