/*! @file
 * Sorting Onegin
*/
#pragma once

#include <algorithm>
#include <cstdio>
#include <vector>

//! @class SortStringsInFile
class Document {
public:
    /// Default constructor
    Document();
    /// Default destructor
    ~Document();

    ///
    void ReadFromInputSream();

    ///
    void SortStrFromBegin();

    ///
    void SortStrFromEnd();

    /// Dump last sorted data
    void DumpSorted() const;

    /// Dump saved source text
    void DumpSourceText() const;

private:
    /// Pointer to input stream
    FILE *input_stream;

    /// file size in bytes
    long file_size;

    /// pointers to strings beginnings
    std::vector<char *> str_begins;

    /// pointer to the beggining of the text
    char *full_text;

    /// cmp for sorting from the begging
    static int CmpStrFromBegin(const void *input_first, const void *input_second);

    /// cmp for sorting from the end
    static int CmpStrFromEnd(const void *input_first, const void *input_second);
};