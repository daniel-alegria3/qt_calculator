#pragma once
#include <string>
#include <vector>
#include <regex>

// using std::vector;
// using std::string;
// using std::regex;

using namespace std;

class Tokenizer {
private:
    regex regex_whitespace;
    regex regex_pattern;

    string create_regex_pattern_string(const vector<string> delimiters);

public:
    string regex_pattern_string;

    Tokenizer();
    Tokenizer(const vector<string> delimiters);
    Tokenizer(string pattern);
    vector<string> tokenize(string input);
    void update_regex_pattern(const vector<string> delimiters);
    bool is_tokenizable(string input);
    string get_regex_pattern();
};

