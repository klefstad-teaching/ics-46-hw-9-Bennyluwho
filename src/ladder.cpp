#include "ladder.h"

void error(string word1, string word2, string word3) {
cerr << "Error: " << word1 << " " << word2 << " " << word3 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();

    if (abs(len1 - len2) > d) return false;

    int edits = 0;
    int i = 0, j = 0;

    if (len1 == len2) {
        for (int k = 0; k < len1; ++k) {
            if (str1[k] != str2[k]) {
                if (++edits > d) return false;
            }
        }
    }
    else {
        while (i < len1 && j < len2) {
            if (str1[i] != str2[j]) {
                if (++edits > d) return false;
                (len1 > len2) ? ++i : ++j;
            } else {
                ++i, ++j;
            }
        }
        if (i < len1 || j < len2) ++edits;
        return edits <= d;
    }

    return edits <= d;
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word){
        return {};
    }
    // if (!word_list.contains(begin_word) || !word_list.contains(end_word)) {
    //     return {};
    // }

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
    if (!ladder.empty()) {
        cout << "Word ladder found: ";
        for (string x : ladder) {
            cout << x << " ";
        }
        cout << endl;
    } else {
        cout << "No word ladder found.\n";
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