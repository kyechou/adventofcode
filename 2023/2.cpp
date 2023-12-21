/**
 * @file 2.cpp
 * @author Kuan-Yen Chou (kuanyenchou@gmail.com)
 * @date 2023-12-20
 *
 * --- Day 2: Cube Conundrum ---
 *
 * You're launched high into the atmosphere! The apex of your trajectory just
 * barely reaches the surface of a large island floating in the sky. You gently
 * land in a fluffy pile of leaves. It's quite cold, but you don't see much
 * snow. An Elf runs over to greet you.
 *
 * The Elf explains that you've arrived at Snow Island and apologizes for the
 * lack of snow. He'll be happy to explain the situation, but it's a bit of a
 * walk, so you have some time. They don't get many visitors up here; would you
 * like to play a game in the meantime?
 *
 * As you walk, the Elf shows you a small bag and some cubes which are either
 * red, green, or blue. Each time you play this game, he will hide a secret
 * number of cubes of each color in the bag, and your goal is to figure out
 * information about the number of cubes.
 *
 * To get information, once a bag has been loaded with cubes, the Elf will reach
 * into the bag, grab a handful of random cubes, show them to you, and then put
 * them back in the bag. He'll do this a few times per game.
 *
 * You play several games and record the information from each game (your puzzle
 * input). Each game is listed with its ID number (like the 11 in Game 11: ...)
 * followed by a semicolon-separated list of subsets of cubes that were revealed
 * from the bag (like 3 red, 5 green, 4 blue).
 *
 * For example, the record of a few games might look like this:
 *
 * Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
 * Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
 * Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
 * Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
 * Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
 *
 * In game 1, three sets of cubes are revealed from the bag (and then put back
 * again). The first set is 3 blue cubes and 4 red cubes; the second set is 1
 * red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green
 * cubes.
 *
 * The Elf would first like to know which games would have been possible if the
 * bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?
 *
 * In the example above, games 1, 2, and 5 would have been possible if the bag
 * had been loaded with that configuration. However, game 3 would have been
 * impossible because at one point the Elf showed you 20 red cubes at once;
 * similarly, game 4 would also have been impossible because the Elf showed you
 * 15 blue cubes at once. If you add up the IDs of the games that would have
 * been possible, you get 8.
 *
 * Determine which games would have been possible if the bag had been loaded
 * with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of
 * the IDs of those games?
 *
 * To begin, [get your puzzle input](https://adventofcode.com/2023/day/2/input).
 *
 * Your puzzle answer was 2278.
 *
 * --- Part Two ---
 *
 * The Elf says they've stopped producing snow because they aren't getting any
 * water! He isn't sure why the water stopped; however, he can show you how to
 * get to the water source to check it out for yourself. It's just up ahead!
 *
 * As you continue your walk, the Elf poses a second question: in each game you
 * played, what is the fewest number of cubes of each color that could have been
 * in the bag to make the game possible?
 *
 * Again consider the example games from earlier:
 *
 * Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
 * Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
 * Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
 * Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
 * Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
 *
 * In game 1, the game could have been played with as few as 4 red, 2 green, and
 * 6 blue cubes. If any color had even one fewer cube, the game would have been
 * impossible. Game 2 could have been played with a minimum of 1 red, 3 green,
 * and 4 blue cubes. Game 3 must have been played with at least 20 red, 13
 * green, and 6 blue cubes. Game 4 required at least 14 red, 3 green, and 15
 * blue cubes. Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in
 * the bag.
 *
 * The power of a set of cubes is equal to the numbers of red, green, and blue
 * cubes multiplied together. The power of the minimum set of cubes in game 1
 * is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up
 * these five powers produces the sum 2286.
 *
 * For each game, find the minimum set of cubes that must have been present.
 * What is the sum of the power of these sets
 *
 */

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

class Cubes {
public:
    int reds = 0;
    int greens = 0;
    int blues = 0;

    Cubes() = default;
    Cubes(int _r, int _g, int _b) : reds(_r), greens(_g), blues(_b) {}

    explicit Cubes(const string &s) {
        istringstream iss(s);
        string color_str;

        while (getline(iss, color_str, ',')) {
            if (auto pos = color_str.find("red"); pos != string::npos) {
                reds = stoi(color_str.substr(0, pos));
            }
            if (auto pos = color_str.find("green"); pos != string::npos) {
                greens = stoi(color_str.substr(0, pos));
            }
            if (auto pos = color_str.find("blue"); pos != string::npos) {
                blues = stoi(color_str.substr(0, pos));
            }
        }
    }

    bool exceeds(const Cubes &other) const {
        return reds > other.reds || greens > other.greens ||
               blues > other.blues;
    }

    void expand(const Cubes &other) {
        if (reds < other.reds) {
            reds = other.reds;
        }
        if (greens < other.greens) {
            greens = other.greens;
        }
        if (blues < other.blues) {
            blues = other.blues;
        }
    }

    unsigned long power() const {
        return static_cast<unsigned long>(reds) *
               static_cast<unsigned long>(greens) *
               static_cast<unsigned long>(blues);
    }
};

ostream &operator<<(ostream &os, const Cubes &cubes) {
    os << cubes.reds << " red, " << cubes.greens << " green, " << cubes.blues
       << " blue";
    return os;
}

// Returns the game ID and also removes the prefix until the first colon.
unsigned long get_game_id(string &line) {
    unsigned long space_pos = line.find(' ');
    unsigned long colon_pos = line.find(':');
    unsigned long game_id =
        stoul(line.substr(space_pos + 1, colon_pos - space_pos - 1));
    line.erase(0, colon_pos + 1);
    return game_id;
}

unsigned long part_one(const string &filename) {
    unsigned long sum = 0;
    string line;
    ifstream ifs(filename);

    // 12 red cubes, 13 green cubes, and 14 blue cubes
    static const Cubes max_cubes(12, 13, 14);

    while (getline(ifs, line)) {
        bool game_is_possible = true;
        unsigned long game_id = get_game_id(line);
        string round_str;
        istringstream iss(line);

        while (getline(iss, round_str, ';')) {
            Cubes round_cubes(round_str);
            if (round_cubes.exceeds(max_cubes)) {
                game_is_possible = false;
            }
        }

        if (game_is_possible) {
            sum += game_id;
        }
    }

    return sum;
}

unsigned long part_two(const string &filename) {
    unsigned long sum = 0;
    string line;
    ifstream ifs(filename);

    while (getline(ifs, line)) {
        unsigned long game_id [[maybe_unused]] = get_game_id(line);
        string round_str;
        istringstream iss(line);
        Cubes min_cubes;

        while (getline(iss, round_str, ';')) {
            Cubes round_cubes(round_str);
            min_cubes.expand(round_cubes);
        }

        sum += min_cubes.power();
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
