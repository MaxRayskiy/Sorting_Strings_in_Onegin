/*! @file
 * Sorting Onegin
*/

#include "SortStringsInFile.h"

int main() {
    SortStringsInFile Onegin;
    Onegin.ReadText();
    Onegin.SortFromBegin();
    Onegin.SortFromEnd();
    Onegin.ReturnText();

    return 0;
}
