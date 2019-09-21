/*! @file
 * Sorting Onegin
*/

#include "Document.h"

int main() {
    Document Onegin;
    Onegin.ReadFromInputSream();

    Onegin.SortStrFromBegin();
    Onegin.DumpSorted();

    Onegin.SortStrFromEnd();
    Onegin.DumpSorted();

    Onegin.DumpSourceText();
    return 0;
}
