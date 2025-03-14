#include "ladder.h"

void error(string word1, string word2, string word3) {
cerr << "Error: " << word1 << " " << word2 << " " << word3 << endl;
}

//used this pseudocode from https://en.wikipedia.org/wiki/Levenshtein_distance
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int lenStr1 = str1.size();
    int lenStr2 = str2.size();

    if (std::abs(lenStr1 - lenStr2) > d) return false;

    std::vector<std::vector<int>> d_matrix(lenStr1 + 1, std::vector<int>(lenStr2 + 1));

    for (int i = 0; i <= lenStr1; ++i) d_matrix[i][0] = i;
    for (int j = 0; j <= lenStr2; ++j) d_matrix[0][j] = j;

    for (int i = 1; i <= lenStr1; ++i) {
        for (int j = 1; j <= lenStr2; ++j) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            d_matrix[i][j] = std::min({d_matrix[i - 1][j] + 1,d_matrix[i][j - 1] + 1,d_matrix[i - 1][j - 1] + cost});
        }
    }

    int edit_distance = d_matrix[lenStr1][lenStr2];
    return edit_distance <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!visited.contains(word)) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream ifs(file_name);
    string word;
    while (ifs >> word) {
        word_list.insert(word);
    }
    ifs.close();
}

void print_word_ladder(const vector<string>& ladder) {
    for (string x : ladder) {
        cout << x << " ";
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}