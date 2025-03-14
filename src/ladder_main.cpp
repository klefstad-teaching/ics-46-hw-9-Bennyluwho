#include "ladder.h"

using namespace std;

int main() {

    // std::cout << std::boolalpha;
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    // cout << word_list.size() << endl;

    // cout << is_adjacent("code", "cade") << endl;
    // cout << is_adjacent("cade", "cate") << endl;
    // cout << is_adjacent("cate", "date") << endl;
    // cout << is_adjacent("date", "data") << endl;
    // cout << generate_word_ladder("sleep", "awake", word_list).size() << endl;

   // verify_word_ladder();
    print_word_ladder(generate_word_ladder("sleep", "awake", word_list));


}