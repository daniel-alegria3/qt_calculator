#include "rpn/tokenizer.h"

// using std::vector;
// using std::string;
// using std::regex;
// using std::regex_replace;
// using std::sregex_token_iterator;

using namespace std;


Tokenizer::Tokenizer()
{
    whitespace_pattern = regex(R"(\s+)");
}

Tokenizer::Tokenizer(const vector<string> delimiters)
{
    regex_pattern_string = create_regex_pattern_string(delimiters);
    regex_pattern = regex(regex_pattern_string);
    whitespace_pattern = regex(R"(\s+)");
}

vector<string> Tokenizer::tokenize(string input)
{
    // input = regex_replace(input, whitespace_pattern, "");

    sregex_token_iterator iter(input.begin(), input.end(), regex_pattern);
    sregex_token_iterator end;

    vector<string> tokens;
    for (; iter != end; ++iter) {
        string token = regex_replace(iter->str(), whitespace_pattern, "");
        tokens.push_back(token);
    }

    return tokens;
}

string Tokenizer::create_regex_pattern_string(const vector<string> delimiters)
{
    // TODO: this regular expression doesnt allow 'sqrt' to be placed
    string delimiter_pattern = R"(\s*([0-9]*\.[0-9]+|[0-9]+|)";

    for (const auto& delim : delimiters) {
        delimiter_pattern += regex_replace(delim, regex(R"([\^$.|?*+(){}[\]])"), R"(\$&)") + "|";
    }

    // Remove the last '|'
    if (!delimiter_pattern.empty()) {
        delimiter_pattern.pop_back();
    }

    return delimiter_pattern + R"()\s*)";
}

void Tokenizer::update_regex_pattern(const vector<string> delimiters)
{
    regex_pattern_string = create_regex_pattern_string(delimiters);
    regex_pattern = regex(regex_pattern_string);
}

bool Tokenizer::is_tokenizable(string input) {
    return regex_match(input, regex_pattern);
}

