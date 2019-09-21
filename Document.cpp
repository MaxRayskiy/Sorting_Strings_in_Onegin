/*! @file
 * Sorting Onegin
*/

#include "Document.h"

#include <cassert>
#include <cctype>
#include <cstdint>
#include <iostream>


Document::Document() {
    input_stream = fopen("..//Onegin.txt", "r");
    assert(input_stream != nullptr);

    fseek(input_stream, 0L, SEEK_END);
    file_size = ftell(input_stream);
    assert(file_size >= 0);

    full_text = new char[file_size];
    assert(full_text != nullptr);
    fseek(input_stream, 0L, SEEK_SET);
}

void Document::ReadFromInputSream() {
    uint64_t i = 0;
    str_begins.push_back(&full_text[0]);

    int c = fgetc(input_stream);
    assert(c != -1);
    while (c != EOF) {
        full_text[i] = (char)(c);

        if (c == '\n') {
            if (i >= 1) {
                if (full_text[i - 1] == '\n') {
                    // remove previous string if it's empty
                    str_begins.pop_back();
                }
            }
            str_begins.push_back(&full_text[i + 1]);
        }

        ++i;
        c = fgetc(input_stream);
    }
}

int Document::CmpStrFromBegin(const void *input_first, const void *input_second) {
    const char *first = *(const char**) input_first;
    const char *second = *(const char**) input_second;

    int i = -1, j = -1;

    while (true) {
        ++i;
        while (!std::isalnum(first[i])) {
            if (first[i] == '\n')
                return -1;
            ++i;
        } // first[i] is pointing to alphanumeric character now

        ++j;
        while (!(std::isalnum(second[j]))) {
            if (second[j] == '\n')
                return 1;
            ++j;
        } // second[j] is pointing to alphanumeric character now

        if (first[i] < second[j])
            return -1;
        else if (first[i] > second[j])
            return 1;
    }
}

void Document::SortStrFromBegin() {
    std::qsort(&str_begins[0], str_begins.size(), sizeof(char *), CmpStrFromBegin);
}

int Document::CmpStrFromEnd(const void *input_first, const void *input_second){
    const char *first = *(const char**) input_first;
    const char *second = *(const char**) input_second;

    int i = 0, j = 0;

    while (first[i] != '\n')
        ++i;  // moves to the end of the first string

    while (second[j] != '\n')
        ++j; // moves to the end of the second string

    while (true) {
        --i;
        while (!std::isalnum(first[i])) {
            if (first[i] == '\n')
                return -1;
            --i;
        } // first[i] is pointing to alphanumeric character now

        --j;
        while (!std::isalnum(second[j])) {
            if (second[j] == '\n')
                return 1;
            --j;
        } // second[j] is pointing to alphanumeric character now

        if (first[i] < second[j])
            return -1;
        else if (first[i] > second[j])
            return 1;
    }
}

void Document::SortStrFromEnd() {
    std::qsort(&str_begins[0], str_begins.size(), sizeof(char *), CmpStrFromEnd);
}

void Document::DumpSourceText() const{
    FILE *output;
    output = fopen("..//Output_Onegin.txt", "a");
    assert(output != nullptr);

    for (unsigned long i = 0; i < file_size; ++i)
        std::fputc(full_text[i], output);

    fclose(output);
}

Document::~Document() {
    assert(input_stream != nullptr);
    fclose(input_stream);

    delete [] full_text;
}

void Document::DumpSorted() const {
    FILE *output;
    output = fopen("..//Output_Onegin.txt", "a");
    assert (output != nullptr);

    for (const char *ch: str_begins) {
        for (int i = 0; ;++i) {
            std::fputc((int)(ch[i]), output);

            if(ch[i] == '\n' || ch[i] == EOF)
                break;
        }
    }

    for (unsigned int i = 0; i < 80; ++i)
        std::fputc('-', output);
    std::fputc('\n', output);

    fclose(output);
}