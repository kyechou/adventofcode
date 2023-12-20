/**
 * @file 1.cpp
 * @author Kuan-Yen Chou (kuanyenchou@gmail.com)
 * @date 2023-12-19
 *
 * --- Day 1: Trebuchet?! ---
 *
 * Something is wrong with global snow production, and you've been selected to
 * take a look. The Elves have even given you a map; on it, they've used stars
 * to mark the top fifty locations that are likely to be having problems.
 *
 * You've been doing this long enough to know that to restore snow operations,
 * you need to check all fifty stars by December 25th.
 *
 * Collect stars by solving puzzles. Two puzzles will be made available on each
 * day in the Advent calendar; the second puzzle is unlocked when you complete
 * the first. Each puzzle grants one star. Good luck!
 *
 * You try to ask why they can't just use a weather machine ("not powerful
 * enough") and where they're even sending you ("the sky") and why your map
 * looks mostly blank ("you sure ask a lot of questions") and hang on did you
 * just say the sky ("of course, where do you think snow comes from") when you
 * realize that the Elves are already loading you into a trebuchet ("please hold
 * still, we need to strap you in").
 *
 * As they're making the final adjustments, they discover that their calibration
 * document (your puzzle input) has been amended by a very young Elf who was
 * apparently just excited to show off her art skills. Consequently, the Elves
 * are having trouble reading the values on the document.
 *
 * The newly-improved calibration document consists of lines of text; each line
 * originally contained a specific calibration value that the Elves now need to
 * recover. On each line, the calibration value can be found by combining the
 * first digit and the last digit (in that order) to form a single two-digit
 * number.
 *
 * For example:
 *
 * 1abc2
 * pqr3stu8vwx
 * a1b2c3d4e5f
 * treb7uchet
 *
 * In this example, the calibration values of these four lines are 12, 38, 15,
 * and 77. Adding these together produces 142.
 *
 * Consider your entire calibration document. What is the sum of all of the
 * calibration values?
 *
 * To begin, get your [puzzle input](https://adventofcode.com/2023/day/1/input).
 *
 * Your puzzle answer was 54159.
 *
 * --- Part Two ---
 *
 * Your calculation isn't quite right. It looks like some of the digits are
 * actually spelled out with letters: one, two, three, four, five, six, seven,
 * eight, and nine also count as valid "digits".
 *
 * Equipped with this new information, you now need to find the real first and
 * last digit on each line. For example:
 *
 * two1nine
 * eightwothree
 * abcone2threexyz
 * xtwone3four
 * 4nineeightseven2
 * zoneight234
 * 7pqrstsixteen
 *
 * In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76.
 * Adding these together produces 281.
 *
 * What is the sum of all of the calibration values?
 *
 */

#include <cctype>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

unsigned long part_one(const string &filename) {
    unsigned long sum = 0;
    unsigned long line_value;
    string line;
    ifstream ifs(filename);

    while (getline(ifs, line)) {
        string_view line_view = line;

        // Starting from the beginning to find the first digit
        auto it = line_view.begin();
        for (; it != line_view.end(); ++it) {
            if (isdigit(*it)) {
                line_value = (*it - '0') * 10;
                break;
            }
        }

        if (it == line_view.end()) {
            cerr << "Failed to find the first digit for line: " << line_view
                 << endl;
            return -1;
        }

        // Starting from the end to find the last digit
        auto rit = line_view.rbegin();
        for (; rit != line_view.rend(); ++rit) {
            if (isdigit(*rit)) {
                line_value += (*rit - '0');
                break;
            }
        }

        if (rit == line_view.rend()) {
            cerr << "Failed to find the last digit for line: " << line_view
                 << endl;
            return -1;
        }

        sum += line_value;
    }

    return sum;
}

struct StringHash {
    using is_transparent = void; // enables heterogenous lookup
    size_t operator()(string_view sv) const { return hash<string_view>()(sv); }
};

static const unordered_map<string_view, int, StringHash, equal_to<>>
    letter_digit_map = {
        {"one",   1},
        {"two",   2},
        {"three", 3},
        {"four",  4},
        {"five",  5},
        {"six",   6},
        {"seven", 7},
        {"eight", 8},
        {"nine",  9},
};

// Returns the numerical value if it is a digit or a letter digit in the forward
// direction. Returns -1 otherwise.
int fwd_digit(const string_view::iterator &it, const string_view &line) {
    if (isdigit(*it)) {
        return *it - '0';
    }

    unsigned long pos = it - line.begin();
    for (unsigned len = 3; len <= 5 && pos + len <= line.size(); ++len) {
        string_view word = line.substr(pos, len);
        if (auto map_it = letter_digit_map.find(word);
            map_it != letter_digit_map.end()) {
            return map_it->second;
        }
    }

    return -1;
};

// Returns the numerical value if it is a digit or a letter digit in the reverse
// direction. Returns -1 otherwise.
int rev_digit(const string_view::reverse_iterator &it,
              const string_view &line) {
    if (isdigit(*it)) {
        return *it - '0';
    }

    unsigned long pos = it - line.rbegin();
    for (unsigned len = 3; len <= 5 && pos + len <= line.size(); ++len) {
        string_view word = line.substr(line.size() - pos - len, len);
        if (auto map_it = letter_digit_map.find(word);
            map_it != letter_digit_map.end()) {
            return map_it->second;
        }
    }

    return -1;
};

unsigned long part_two(const string &filename) {
    unsigned long sum = 0;
    unsigned long line_value;
    string line;
    ifstream ifs(filename);

    while (getline(ifs, line)) {
        string_view line_view = line;

        // Starting from the beginning to find the first digit
        auto it = line_view.begin();
        for (; it != line_view.end(); ++it) {
            if (int digit = fwd_digit(it, line_view); digit >= 0) {
                line_value = digit * 10;
                break;
            }
        }

        if (it == line_view.end()) {
            cerr << "Failed to find the first digit for line: " << line_view
                 << endl;
            return -1;
        }

        // Starting from the end to find the last digit
        auto rit = line_view.rbegin();
        for (; rit != line_view.rend(); ++rit) {
            if (int digit = rev_digit(rit, line_view); digit >= 0) {
                line_value += digit;
                break;
            }
        }

        if (rit == line_view.rend()) {
            cerr << "Failed to find the last digit for line: " << line_view
                 << endl;
            return -1;
        }

        sum += line_value;
    }

    return sum;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "There must be exactly 3 arguments." << endl;
        return -1;
    }

    int mode = stoi(argv[1]);
    string filename(argv[2]);

    if (mode == 1) {
        cout << part_one(filename) << endl;
    } else if (mode == 2) {
        cout << part_two(filename) << endl;
    } else {
        cerr << "Unknown mode (must be either 1 or 2): " << mode << endl;
        return -1;
    }

    return 0;
}
