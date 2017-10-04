/*
    Tokenizer takes in raw file and produces a stream of
    tokens useful for executing

    We do not generate an Abstract Syntax Tree. Instead,
    the validity of programs is determined at execution
    after tokenizing
*/

#ifndef __JJC__ICCC__TOKENIZER__H__
#define __JJC__ICCC__TOKENIZER__H__

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

// commonly used types in IcccTokenizer
typedef const std::string& STRING_REF;
typedef std::vector<char>  CHAR_VEC;

class TokenStream {
private:
    // actual token stream
    std::vector<std::string> tokenVector;

    // iterate through string and perform ops:
    // 1.) replace every whitespace char in
    //     strings with escape sequences (space = \s, tab = \t)
    // 2.) replace every semicolon w/
    //     space + semicolon
    std::string preprocess(STRING_REF raw_data);

    // generate tokens from preprocessed data
    // done with a simple stringstream
    void tokenize(STRING_REF proc_data);

public:
    // default constructor
    TokenStream() { ; }

    // constructor takes file containing Iccc script
    TokenStream(STRING_REF filename);

    // after this method returns, a complete
    // token stream has been generated
    void parseFile(STRING_REF filename);

    // tokens in token stream
    int length(void) { return tokenVector.size(); }

    // access tokens like they're in an array
    std::string& operator[](const int index);
};

// ============================================================================
// Method definitions
// ============================================================================

std::string& TokenStream::operator[](const int index) {
    return tokenVector[index];
}

TokenStream::TokenStream(STRING_REF filename) {
    parseFile(filename);
}

void TokenStream::parseFile(STRING_REF filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);

    file.seekg(0, file.end);
    uint32_t file_length = file.tellg();
    file.seekg(0, file.beg);

    char* file_contents = new char[file_length+1] { 0 };

    file.read(file_contents, file_length);
    file.close();

    std::string proc = preprocess(file_contents);
    std::cout << proc << std::endl;
    tokenize(proc);
}

void TokenStream::tokenize(STRING_REF proc_data) {
    std::stringstream strs(proc_data);
    tokenVector.clear();

    std::string str;
    while(strs >> str)
        tokenVector.push_back(str);
}

std::string TokenStream::preprocess(STRING_REF raw_data) {
    std::vector<char> proc_data_vec;
    int s = raw_data.length();

    const int STATE_default = 0;
    const int STATE_comment = 1;
    const int STATE_string  = 2;

    int current_state = STATE_default;

    for(int i = 0; i < s; i++) {
        switch(current_state) {
        case STATE_default:
            switch(raw_data[i]) {
                case ';': // add " ; "
                    proc_data_vec.push_back(' ');
                    proc_data_vec.push_back(';');
                    proc_data_vec.push_back(' ');
                    break;
                case '/': // start of comment
                    if(raw_data[i+1] == '/')
                        current_state = STATE_comment;
                    break;
                case '"':
                    //std::cerr << "Begin STRING" << std::endl;
                    proc_data_vec.push_back('"');
                    current_state = STATE_string;
                    break;
                default:
                    proc_data_vec.push_back(raw_data[i]);
                    break;
            }
            break;
        case STATE_comment:
            if(raw_data[i] == '\n') {
                proc_data_vec.push_back('\n');
                current_state = STATE_default;
            }
            break;
        case STATE_string:
            switch(raw_data[i]) {
                case ' ':
                    proc_data_vec.push_back('\\');
                    proc_data_vec.push_back('s');
                    break;
                case '\t':
                    proc_data_vec.push_back('\\');
                    proc_data_vec.push_back('t');
                    break;
                case '"':
                    //std::cerr << "End STRING" << std::endl;
                    proc_data_vec.push_back('"');
                    current_state = STATE_default;
                    break;
                case '\n':
                    proc_data_vec.push_back('\\');
                    proc_data_vec.push_back('n');
                    break;
                default:
                    proc_data_vec.push_back(raw_data[i]);
                    break;
            }
            break;
        default:
            // should never happen
            std::cerr << "========PREPROCCESSOR ERROR (UNKNOWN STATE)========" << std::endl;
            std::cerr << " == state: " << current_state << std::endl;
            std::cerr.write(&proc_data_vec[0], proc_data_vec.size());
            exit(1);
            break;
        }
    }

    proc_data_vec.push_back('\0');
    return std::string(&proc_data_vec[0]);

    // data in proc_data_vec is automatically deleted
}

#endif // __JJC__ICCC__TOKENIZER__H__





