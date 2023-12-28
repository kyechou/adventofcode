/**
 * @file 3.cpp
 * @author Kuan-Yen Chou (kuanyenchou@gmail.com)
 * @date 2023-12-21
 *
 * --- Day 3: Gear Ratios ---
 *
 * You and the Elf eventually reach a gondola lift station; he says the gondola
 * lift will take you up to the water source, but this is as far as he can bring
 * you. You go inside.
 *
 * It doesn't take long to find the gondolas, but there seems to be a problem:
 * they're not moving.
 *
 * "Aaah!"
 *
 * You turn around to see a slightly-greasy Elf with a wrench and a look of
 * surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working
 * right now; it'll still be a while before I can fix it." You offer to help.
 *
 * The engineer explains that an engine part seems to be missing from the
 * engine, but nobody can figure out which one. If you can add up all the part
 * numbers in the engine schematic, it should be easy to work out which part is
 * missing.
 *
 * The engine schematic (your puzzle input) consists of a visual representation
 * of the engine. There are lots of numbers and symbols you don't really
 * understand, but apparently any number adjacent to a symbol, even diagonally,
 * is a "part number" and should be included in your sum. (Periods (.) do not
 * count as a symbol.)
 *
 * Here is an example engine schematic:
 *
 * 467..114..
 * ...*......
 * ..35..633.
 * ......#...
 * 617*......
 * .....+.58.
 * ..592.....
 * ......755.
 * ...$.*....
 * .664.598..
 *
 * In this schematic, two numbers are not part numbers because they are not
 * adjacent to a symbol: 114 (top right) and 58 (middle right). Every other
 * number is adjacent to a symbol and so is a part number; their sum is 4361.
 *
 * Of course, the actual engine schematic is much larger. What is the sum of all
 * of the part numbers in the engine schematic?
 *
 * To begin, [get your puzzle input](https://adventofcode.com/2023/day/3/input).
 *
 * Your puzzle answer was 528799.
 *
 * --- Part Two ---
 *
 * The engineer finds the missing part and installs it in the engine! As the
 * engine springs to life, you jump in the closest gondola, finally ready to
 * ascend to the water source.
 *
 * You don't seem to be going very fast, though. Maybe something is still wrong?
 * Fortunately, the gondola has a phone labeled "help", so you pick it up and
 * the engineer answers.
 *
 * Before you can explain the situation, she suggests that you look out the
 * window. There stands the engineer, holding a phone in one hand and waving
 * with the other. You're going so slowly that you haven't even left the
 * station. You exit the gondola.
 *
 * The missing part wasn't the only issue - one of the gears in the engine is
 * wrong. A gear is any * symbol that is adjacent to exactly two part numbers.
 * Its gear ratio is the result of multiplying those two numbers together.
 *
 * This time, you need to find the gear ratio of every gear and add them all up
 * so that the engineer can figure out which gear needs to be replaced.
 *
 * Consider the same engine schematic again:
 *
 * 467..114..
 * ...*......
 * ..35..633.
 * ......#...
 * 617*......
 * .....+.58.
 * ..592.....
 * ......755.
 * ...$.*....
 * .664.598..
 *
 * In this schematic, there are two gears. The first is in the top left; it has
 * part numbers 467 and 35, so its gear ratio is 16345. The second gear is in
 * the lower right; its gear ratio is 451490. (The * adjacent to 617 is not a
 * gear because it is only adjacent to one part number.) Adding up all of the
 * gear ratios produces 467835.
 *
 * What is the sum of all of the gear ratios in your engine schematic?
 *
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

static inline vector<string> read_schema(const string &filename) {
    vector<string> schema;
    string line;
    ifstream ifs(filename);

    while (getline(ifs, line)) {
        schema.push_back(line);
    }

    return schema;
}

static inline bool is_symbol(char c) {
    return c != '.' && !isdigit(c);
}

/**
 * @return true if any character in the specified range is a symbol.
 * @return false otherwise.
 */
static inline bool is_symbol(const vector<string> &schema,
                             vector<string>::size_type row,
                             string::size_type b,
                             string::size_type e) {
    if (row >= schema.size()) {
        return false;
    }

    for (auto i = b; i < e && i < schema[row].size(); ++i) {
        if (is_symbol(schema[row][i])) {
            return true;
        }
    }

    return false;
}

static inline bool is_part_number(const vector<string> &schema,
                                  vector<string>::size_type row,
                                  string::size_type b,
                                  string::size_type e) {
    // Check the previous row.
    if (row > 0) {
        auto check_b = b > 0 ? b - 1 : b;
        auto check_e = e < schema[row - 1].size() ? e + 1 : e;
        if (is_symbol(schema, row - 1, check_b, check_e)) {
            return true;
        }
    }

    // Check the current row (left and right).
    if (b > 0 && is_symbol(schema[row][b - 1])) {
        return true;
    }
    if (e < schema[row].size() && is_symbol(schema[row][e])) {
        return true;
    }

    // Check the next row.
    if (row < schema.size() - 1) {
        auto check_b = b > 0 ? b - 1 : b;
        auto check_e = e < schema[row + 1].size() ? e + 1 : e;
        if (is_symbol(schema, row + 1, check_b, check_e)) {
            return true;
        }
    }

    return false;
}

unsigned long part_one(const vector<string> &schema) {
    unsigned long sum = 0;

    for (vector<string>::size_type row = 0; row < schema.size(); ++row) {
        for (string::size_type col = 0; col < schema[row].size(); ++col) {
            if (!isdigit(schema[row][col]) ||
                (col > 0 && isdigit(schema[row][col - 1]))) {
                continue;
            }

            // schema[row][col] is a digit. Find the entire number.
            string::size_type b = col;
            string::size_type e = col + 1;
            while (e < schema[row].size() && isdigit(schema[row][e])) {
                ++e;
            }

            // Add to the sum if <row, b, e> is a part number.
            if (is_part_number(schema, row, b, e)) {
                sum += stoul(schema[row].substr(b, e - b));
            }
        }
    }

    return sum;
}

static inline tuple<int, int, int>
find_number_from_digit(const vector<string> &schema,
                       vector<string>::size_type row,
                       string::size_type col) {
    // Find the adjacent number
    auto b = col;
    while (b > 0 && isdigit(schema[row][b - 1])) {
        --b;
    }
    auto e = col + 1;
    while (e < schema[row].size() && isdigit(schema[row][e])) {
        ++e;
    }
    return {row, b, e};
}

static inline bool is_gear(const vector<string> &schema,
                           vector<string>::size_type row,
                           string::size_type col,
                           unsigned long &gear_product) {
    set<tuple<int, int, int>> adjacent_numbers;
    auto row_b = row > 0 ? row - 1 : row;
    auto row_e = row < schema.size() - 1 ? row + 2 : row + 1;
    auto col_b = col > 0 ? col - 1 : col;
    auto col_e = col < schema[row].size() - 1 ? col + 2 : col + 1;

    for (auto i = row_b; i < row_e; ++i) {
        for (auto j = col_b; j < col_e; ++j) {
            if (isdigit(schema[i][j])) {
                adjacent_numbers.insert(find_number_from_digit(schema, i, j));
            }
        }
    }

    if (adjacent_numbers.size() != 2) {
        return false;
    }

    // Compute the gear product
    gear_product = 1;
    for (auto [r, b, e] : adjacent_numbers) {
        auto num = stoul(schema[r].substr(b, e - b));
        gear_product *= num;
    }

    return true;
}

unsigned long part_two(const vector<string> &schema) {
    unsigned long sum = 0;
    for (vector<string>::size_type row = 0; row < schema.size(); ++row) {
        for (string::size_type col = 0; col < schema[row].size(); ++col) {
            if (schema[row][col] != '*') {
                continue;
            }

            unsigned long gear_product = 0;
            if (is_gear(schema, row, col, gear_product)) {
                sum += gear_product;
            }
        }
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
    vector<string> schema = read_schema(filename);

    if (mode == 1) {
        cout << part_one(schema) << endl;
    } else if (mode == 2) {
        cout << part_two(schema) << endl;
    } else {
        cerr << "Unknown mode (must be either 1 or 2): " << mode << endl;
        return -1;
    }

    return 0;
}
