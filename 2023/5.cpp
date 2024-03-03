/**
 * @file 5.cpp
 * @author Kuan-Yen Chou (kuanyenchou@gmail.com)
 * @date 2024-01-04
 *
 *  --- Day 5: If You Give A Seed A Fertilizer ---
 *
 * You take the boat and find the gardener right where you were told he would
 * be: managing a giant "garden" that looks more to you like a farm.
 *
 * "A water source? Island Island is the water source!" You point out that Snow
 * Island isn't receiving any water.
 *
 * "Oh, we had to stop the water because we ran out of sand to filter it with!
 * Can't make snow with dirty water. Don't worry, I'm sure we'll get more sand
 * soon; we only turned off the water a few days... weeks... oh no." His face
 * sinks into a look of horrified realization.
 *
 * "I've been so busy making sure everyone here has food that I completely
 * forgot to check why we stopped getting more sand! There's a ferry leaving
 * soon that is headed over in that direction - it's much faster than your boat.
 * Could you please go check it out?"
 *
 * You barely have time to agree to this request when he brings up another.
 * "While you wait for the ferry, maybe you can help us with our food production
 * problem. The latest Island Island Almanac just arrived and we're having
 * trouble making sense of it."
 *
 * The almanac (your puzzle input) lists all of the seeds that need to be
 * planted. It also lists what type of soil to use with each kind of seed, what
 * type of fertilizer to use with each kind of soil, what type of water to use
 * with each kind of fertilizer, and so on. Every type of seed, soil, fertilizer
 * and so on is identified with a number, but numbers are reused by each
 * category - that is, soil 123 and fertilizer 123 aren't necessarily related to
 * each other.
 *
 * For example:
 *
 * seeds: 79 14 55 13
 *
 * seed-to-soil map:
 * 50 98 2
 * 52 50 48
 *
 * soil-to-fertilizer map:
 * 0 15 37
 * 37 52 2
 * 39 0 15
 *
 * fertilizer-to-water map:
 * 49 53 8
 * 0 11 42
 * 42 0 7
 * 57 7 4
 *
 * water-to-light map:
 * 88 18 7
 * 18 25 70
 *
 * light-to-temperature map:
 * 45 77 23
 * 81 45 19
 * 68 64 13
 *
 * temperature-to-humidity map:
 * 0 69 1
 * 1 0 69
 *
 * humidity-to-location map:
 * 60 56 37
 * 56 93 4
 *
 * The almanac starts by listing which seeds need to be planted: seeds 79, 14,
 * 55, and 13.
 *
 * The rest of the almanac contains a list of maps which describe how to convert
 * numbers from a source category into numbers in a destination category. That
 * is, the section that starts with seed-to-soil map: describes how to convert a
 * seed number (the source) to a soil number (the destination). This lets the
 * gardener and his team know which soil to use with which seeds, which water to
 * use with which fertilizer, and so on.
 *
 * Rather than list every source number and its corresponding destination number
 * one by one, the maps describe entire ranges of numbers that can be converted.
 * Each line within a map contains three numbers: the destination range start,
 * the source range start, and the range length.
 *
 * Consider again the example seed-to-soil map:
 *
 * 50 98 2
 * 52 50 48
 *
 * The first line has a destination range start of 50, a source range start of
 * 98, and a range length of 2. This line means that the source range starts at
 * 98 and contains two values: 98 and 99. The destination range is the same
 * length, but it starts at 50, so its two values are 50 and 51. With this
 * information, you know that seed number 98 corresponds to soil number 50 and
 * that seed number 99 corresponds to soil number 51.
 *
 * The second line means that the source range starts at 50 and contains 48
 * values: 50, 51, ..., 96, 97. This corresponds to a destination range starting
 * at 52 and also containing 48 values: 52, 53, ..., 98, 99. So, seed number 53
 * corresponds to soil number 55.
 *
 * Any source numbers that aren't mapped correspond to the same destination
 * number. So, seed number 10 corresponds to soil number 10.
 *
 * So, the entire list of seed numbers and their corresponding soil numbers
 * looks like this:
 *
 * seed  soil
 * 0     0
 * 1     1
 * ...   ...
 * 48    48
 * 49    49
 * 50    52
 * 51    53
 * ...   ...
 * 96    98
 * 97    99
 * 98    50
 * 99    51
 *
 * With this map, you can look up the soil number required for each initial seed
 * number:
 *
 *     Seed number 79 corresponds to soil number 81.
 *     Seed number 14 corresponds to soil number 14.
 *     Seed number 55 corresponds to soil number 57.
 *     Seed number 13 corresponds to soil number 13.
 *
 * The gardener and his team want to get started as soon as possible, so they'd
 * like to know the closest location that needs a seed. Using these maps, find
 * the lowest location number that corresponds to any of the initial seeds. To
 * do this, you'll need to convert each seed number through other categories
 * until you can find its corresponding location number. In this example, the
 * corresponding types are:
 *
 *     Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78,
 * humidity 78, location 82. Seed 14, soil 14, fertilizer 53, water 49, light
 * 42, temperature 42, humidity 43, location 43. Seed 55, soil 57, fertilizer
 * 57, water 53, light 46, temperature 82, humidity 82, location 86. Seed 13,
 * soil 13, fertilizer 52, water 41, light 34, temperature 34, humidity 35,
 * location 35.
 *
 * So, the lowest location number in this example is 35.
 *
 * What is the lowest location number that corresponds to any of the initial
 * seed numbers?
 *
 * To begin, [get your puzzle input](https://adventofcode.com/2023/day/5/input).
 *
 * Your puzzle answer was 282277027.
 *
 *  --- Part Two ---
 *
 * Everyone will starve if you only plant such a small number of seeds.
 * Re-reading the almanac, it looks like the seeds: line actually describes
 * ranges of seed numbers.
 *
 * The values on the initial seeds: line come in pairs. Within each pair, the
 * first value is the start of the range and the second value is the length of
 * the range. So, in the first line of the example above:
 *
 * seeds: 79 14 55 13
 *
 * This line describes two ranges of seed numbers to be planted in the garden.
 * The first range starts with seed number 79 and contains 14 values: 79, 80,
 * ..., 91, 92. The second range starts with seed number 55 and contains 13
 * values: 55, 56, ..., 66, 67.
 *
 * Now, rather than considering four seed numbers, you need to consider a total
 * of 27 seed numbers.
 *
 * In the above example, the lowest location number can be obtained from seed
 * number 82, which corresponds to soil 84, fertilizer 84, water 84, light 77,
 * temperature 45, humidity 46, and location 46. So, the lowest location number
 * is 46.
 *
 * Consider all of the initial seed numbers listed in the ranges on the first
 * line of the almanac. What is the lowest location number that corresponds to
 * any of the initial seed numbers?
 *
 */

#include <algorithm>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
using num_t = unsigned long;
using seeds_t = vector<num_t>;
using map_t = map<num_t, pair<num_t, num_t>>; // src -> (dst, len)

constexpr unsigned int num_maps = 7;

class Input {
public:
    seeds_t seeds;
    map_t maps[num_maps];
};

void print_map_entry(map_t::const_iterator it) {
    cerr << "src: " << it->first << ", dst: " << it->second.first
         << ", len: " << it->second.second << endl;
}

void print_map(const map_t &map) {
    for (auto it = map.begin(); it != map.end(); ++it) {
        print_map_entry(it);
    }
}

static inline void strip_colon(string &line) {
    unsigned long colon_pos = line.find(':');
    line.erase(0, colon_pos + 1);
}

static inline seeds_t read_seeds(const string_view line) {
    seeds_t seeds;
    string num_str;
    istringstream iss{string{line}};

    while (getline(iss, num_str, ' ')) {
        if (num_str.empty()) {
            continue;
        }
        seeds.push_back(stoul(num_str));
    }

    return seeds;
}

static inline map_t read_map(ifstream &ifs) {
    map_t map;
    string line;

    while (getline(ifs, line)) {
        if (line.empty() || line.find("map") != string::npos) {
            break;
        }

        seeds_t numbers = read_seeds(line);
        if (numbers.size() != 3) {
            throw invalid_argument("Failed reading the input at line: '" +
                                   line + "'");
        }

        auto [_, inserted] =
            map.try_emplace(numbers[1], numbers[0], numbers[2]);
        if (!inserted) {
            throw invalid_argument(
                "Failed inserting the map entry for line: '" + line + "'");
        }
    }

    return map;
}

static inline Input read_input(const string_view filename) {
    Input input;
    string line;
    ifstream ifs(string{filename});

    // Read the seeds
    getline(ifs, line);
    strip_colon(line);
    input.seeds = read_seeds(line);

    while (getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.find("map") == string::npos) {
            throw invalid_argument("Failed reading the input at line: '" +
                                   line + "'");
        }

        if (line.starts_with("seed-to-soil")) {
            input.maps[0] = read_map(ifs);
        } else if (line.starts_with("soil-to-fertilizer")) {
            input.maps[1] = read_map(ifs);
        } else if (line.starts_with("fertilizer-to-water")) {
            input.maps[2] = read_map(ifs);
        } else if (line.starts_with("water-to-light")) {
            input.maps[3] = read_map(ifs);
        } else if (line.starts_with("light-to-temperature")) {
            input.maps[4] = read_map(ifs);
        } else if (line.starts_with("temperature-to-humidity")) {
            input.maps[5] = read_map(ifs);
        } else if (line.starts_with("humidity-to-location")) {
            input.maps[6] = read_map(ifs);
        } else {
            throw invalid_argument("Failed reading the input at line: '" +
                                   line + "'");
        }
    }

    return input;
}

static inline num_t map_look_up(num_t src, const map_t &map) {
    auto it = map.lower_bound(src);

    // If src is in range, find the dst.
    if (it != map.end() && src >= it->first &&
        src < it->first + it->second.second) {
        return it->second.first + (src - it->first);
    }

    // If src is in range of the previous map entry, find the dst.
    if (it != map.begin()) {
        --it;
        if (src >= it->first && src < it->first + it->second.second) {
            return it->second.first + (src - it->first);
        }
    }

    // Otherwise, src is not explicitly mapped. Use the same number as the dst.
    return src;
}

static inline num_t
location_look_up(num_t src, unsigned int map_index, const Input &input) {
    num_t dst = map_look_up(src, input.maps[map_index]);
    if (map_index < num_maps - 1) {
        return location_look_up(dst, map_index + 1, input);
    } else {
        return dst;
    }
}

num_t part_one(const Input &input) {
    num_t min_location = numeric_limits<num_t>::max();

    for (auto seed : input.seeds) {
        auto loc = location_look_up(seed, /*map_index=*/0, input);
        if (loc < min_location) {
            min_location = loc;
        }
    }

    return min_location;
}

class Range {
public:
    num_t first, second; // inclusive: [first, second]
    Range(num_t lb, num_t ub) : first(lb), second(ub) {}
};

template <class T>
inline void hash_combine(size_t &seed, const T &value) {
    seed ^= hash<T>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

class RangeHash {
public:
    size_t operator()(const Range &range) const {
        hash<num_t> hasher;
        size_t hash_value = 0;
        hash_combine(hash_value, hasher(range.first));
        hash_combine(hash_value, hasher(range.second));
        return hash_value;
    }
};

class RangeEq {
public:
    bool operator()(const Range &a, const Range &b) const {
        return a.first == b.first && a.second == b.second;
    }
};

// map_index -> (src_range -> min_loc)
static unordered_map<unsigned int,
                     unordered_map<Range, num_t, RangeHash, RangeEq>>
    min_loc_cache;

num_t location_look_up_from_range(const Range &src_range,
                                  unsigned int map_index,
                                  const Input &input) {
    if (map_index >= num_maps) {
        return src_range.first;
    }

    // TODO: Use the cache for dynamic programming.

    // Cache lookup
    {
        auto it = min_loc_cache.find(map_index);
        if (it != min_loc_cache.end()) {
            auto range_it = it->second.find(src_range);
            if (range_it != it->second.end()) {
                return range_it->second;
            }
        }
    }

    const map_t &map = input.maps[map_index];
    num_t min_location = numeric_limits<num_t>::max();

    // Find the lower bound (no smaller than src_range.first).
    auto lb = map.lower_bound(src_range.first);
    if ((lb == map.end() || src_range.first < lb->first) && lb != map.begin()) {
        --lb;
        if (src_range.first > lb->first + lb->second.second - 1) {
            ++lb;
        }
    }

    // Find the upper bound (greater than src_range.second).
    auto ub = map.upper_bound(src_range.second);

    // Populate dst_ranges.
    if (lb != map.end()) {
        if (src_range.first < lb->first) {
            num_t loc = location_look_up_from_range(
                {src_range.first, min(lb->first - 1, src_range.second)},
                map_index + 1, input);
            min_location = min(min_location, loc);
        }
    } else {
        num_t loc =
            location_look_up_from_range(src_range, map_index + 1, input);
        min_location = min(min_location, loc);
    }
    for (auto it = lb; it != ub; ++it) {
        // Get the mapping of the intersection of map_entry_range and
        // src_range.
        pair<num_t, num_t> map_entry_range{it->first,
                                           it->first + it->second.second - 1};
        num_t loc = location_look_up_from_range(
            {max(map_entry_range.first, src_range.first) + it->second.first -
                 it->first,
             min(map_entry_range.second, src_range.second) + it->second.first -
                 it->first},
            map_index + 1, input);
        min_location = min(min_location, loc);
        // Get the mapping of the following unmapped region if it's
        // non-empty.
        auto next_it = it;
        next_it++;
        pair<num_t, num_t> unmapped_range{it->first + it->second.second,
                                          next_it->first - 1};
        if (unmapped_range.first <= unmapped_range.second) {
            num_t loc = location_look_up_from_range(
                {max(unmapped_range.first, src_range.first),
                 min(unmapped_range.second, src_range.second)},
                map_index + 1, input);
            min_location = min(min_location, loc);
        }
    }

    // Cache update
    { min_loc_cache[map_index][src_range] = min_location; }

    return min_location;
}

unsigned long part_two(const Input &input) {
    num_t min_location = numeric_limits<num_t>::max();

    for (auto it = input.seeds.begin(); it != input.seeds.end(); it += 2) {
        auto loc = location_look_up_from_range({*it, *it + *(it + 1) - 1},
                                               /*map_index=*/0, input);
        min_location = min(min_location, loc);
    }

    return min_location;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "There must be exactly 3 arguments." << endl;
        return -1;
    }

    int mode = stoi(argv[1]);
    string filename(argv[2]);
    Input input = read_input(filename);

    if (mode == 1) {
        cout << part_one(input) << endl;
    } else if (mode == 2) {
        cout << part_two(input) << endl;
    } else {
        cerr << "Unknown mode (must be either 1 or 2): " << mode << endl;
        return -1;
    }

    return 0;
}
