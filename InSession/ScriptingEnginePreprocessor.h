#ifndef __SCRIPTING__ENGINE__PREPROCESSOR__H__
#define __SCRIPTING__ENGINE__PREPROCESSOR__H__

#include <iostream>
#include <string>  // filename
#include <vector>  // character buffer
#include <fstream> // file stream

class Preprocessor {
private:
    std::string filename;
    std::vector<char> proc_buffer; // processed file contents
    std::vector<char> orig_buffer; // original file contents

    std::vector<std::string> token_buffer; // processed token stream
    std::vector<std::string> orig_token_buffer;  // original token stream

public:
    // constructor
    Preprocessor(const std::string& filename);

    // process function
    void process(void);

    // generate tokens
    void tokenize(void);

    std::vector<std::string>* getTokenBuffer(void) {
        return &token_buffer;
    }
};

void Preprocessor::tokenize(void) {
    std::ofstream output("/tmp/output_file", std::ios::trunc | std::ios::binary);
    output.write(&proc_buffer[0], proc_buffer.size() - 1);
    output.close();

    std::ifstream input("/tmp/output_file");

    std::string tmp_input;
    while((input >> tmp_input)) {
        orig_token_buffer.push_back(tmp_input);
    }
    input.close();

    // state machine states
    const int STATE_default = 0; // looks for KEYWORD, QUOTE, COMMENT
    const int STATE_comment = 1; // comments should NOT get included in the token_buffer

    int current_state = STATE_default;
    for(std::string str : orig_token_buffer) {
        switch(current_state) {
            case STATE_default:
                if(str == "/*") { // beginning of comment
                    current_state = STATE_comment;
                } else {
                    token_buffer.push_back(str);
                }
                break;

            case STATE_comment:
                if(str == "*/") {
                    current_state = STATE_default;
                }
                break;

            default:
                std::cerr << "UNKNOWN STATE: " << current_state << std::endl;
                exit(1);
        }
    }

    for(std::string str : token_buffer) {
        std::cout << str << std::endl;
    }

}

Preprocessor::Preprocessor(const std::string& filename) {
    this->filename = filename;

    // open file and place contents in orig_buffer
    std::ifstream t;
    int length;
    t.open(filename, std::ios::in | std::ios::binary);      // open input file
    t.seekg(0, std::ios::end);    // go to the end
    length = t.tellg();           // report location (this is the length)
    t.seekg(0, std::ios::beg);    // go back to the beginning
    char* buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
    t.read(buffer, length);       // read the whole file into the buffer
    t.close();                    // close file handle

    for(int i = 0; i < length; i++) {
        orig_buffer.push_back(buffer[i]);
    }
    //orig_buffer.push_back('\0');

    delete[] buffer;
}

void Preprocessor::process(void) {
    const int STATE_default = 0;
    const int STATE_string  = 1;

    int current_state = STATE_default;

    for(int i = 0; i < orig_buffer.size(); i++) {
        char c = orig_buffer[i];

        switch(current_state) {
            case STATE_default:
                if(c == '"') {
                    proc_buffer.push_back('"');
                    current_state = STATE_string;
                } else if(c == ';') {
                    proc_buffer.push_back(' ');
                    proc_buffer.push_back(';');
                    proc_buffer.push_back(' ');
                } else {
                    proc_buffer.push_back(c);
                }
                break;
            case STATE_string:
                if(c == ' ') {
                    proc_buffer.push_back('\\');
                    proc_buffer.push_back('s');
                } else if(c == '"') {
                    proc_buffer.push_back('"');
                    current_state = STATE_default;
                } else {
                    proc_buffer.push_back(c);
                }
                break;
            default:
                std::cout << "UNKNOWN STATE" << std::endl;
                exit(1);
                break;
        }
    }

    proc_buffer.push_back('\0');
    //std::cout << &proc_buffer[0] << std::endl;
}

#endif // __SCRIPTING__ENGINE__PREPROCESSOR__H__







