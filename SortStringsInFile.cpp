/*! @file
 * Sorting Onegin
*/
#include "SortStringsInFile.h"

SortStringsInFile::SortStringsInFile() {
    if ((input_text = fopen("..//Onegin.txt", "r")) == nullptr) {
        std::cout << "no such file" << std::endl;
        return;
    }

    fseek(input_text, 0L, SEEK_END);
    file_size = ftell(input_text);
    full_text = new char [file_size];
    fseek(input_text, 0L, SEEK_SET);
}

void SortStringsInFile::ReadText() {
    unsigned long i = 0;
    str_begins.push_back(&full_text[0]);

    int c = fgetc(input_text);
    while ( c != EOF) {
        full_text[i] = static_cast<char>(c);

        if (c == 10) {// 10 == (int)'\n'
            if (i >= 1) {
                if (full_text[i - 1] == '\n') {
                    // если предыдущая строка пуста, уберем
                    str_begins.pop_back();
                }

                if (full_text[i - 1] != '\n') {
                    // если предыдущая строка не пуста
                    str_ends.push_back(&full_text[i - 1]);
                }
            }

            str_begins.push_back(&full_text[i + 1]);
        }

        ++i;
        c = fgetc(input_text);
    }
    str_ends.push_back(&full_text[file_size - 2]);
}

inline bool SortStringsInFile::IsAlphaOrNum(const char &symbol) {  // true, если буква или цифра
    return (('a' <= symbol && symbol <= 'z') ||
            ('A' <= symbol && symbol <= 'Z') ||
            ('0' <= symbol && symbol <= '9'));
}


int SortStringsInFile::CmpFromBegin(const void *input_first, const void *input_second) {
    const char *first = *(const char**) input_first;
    const char *second = *(const char**) input_second;

    int i = -1, j = -1;

    while (true) {
        ++i;
        while (!IsAlphaOrNum(first[i])) {
            if (first[i] == '\n')
                return -1;
            ++i;
        } // теперь first[i] указывает на букву илли цифру

        ++j;
        while (!IsAlphaOrNum(second[j])) {
            if (second[j] == '\n')
                return 1;
            ++j;
        } // теперь second[j] указывает на букву илли цифру

        if (first[i] < second[j])
            return -1;
        else if (first[i] > second[j])
            return 1;
        else
            continue; // строки совпали, смотрим дальше
    }
}

void SortStringsInFile::SortFromBegin() {
    std::qsort(&str_begins[0], str_begins.size(), sizeof(char *), CmpFromBegin);

    FILE *output;
    output = fopen("..//Sorted_From_the_beginning.txt", "w+");
    if (output == nullptr)
        return;

    for (const char *ch: str_begins) {
        for (int i = 0; ;++i) {
            std::fputc(static_cast<int>(ch[i]), output);

            if(ch[i] == '\n' || ch[i] == EOF)
                break;
        }
    }
    fclose(output);
}

int SortStringsInFile::CmpFromEnd(const void *input_first, const void *input_second){
    const char *first = *(const char**) input_first;
    const char *second = *(const char**) input_second;

    int i = 1, j = 1;

    while (true) {
        --i;
        while (!IsAlphaOrNum(first[i])) {
            if (first[i] == '\n')
                return -1;
            --i;
        } // теперь first[i] указывает на букву илли цифру

        --j;
        while (!IsAlphaOrNum(second[j])) {
            if (second[j] == '\n')
                return 1;
            --j;
        } // теперь second[j] указывает на букву илли цифру

        if (first[i] < second[j])
            return -1;
        else if (first[i] > second[j])
            return 1;
        else
            continue; // строки совпали, смотрим дальше
    }
}

void SortStringsInFile::SortFromEnd() {
    std::qsort(&str_ends[0], str_begins.size(), sizeof(char *), CmpFromEnd);

    FILE *output;
    output = fopen("..//Sorted_From_the_end.txt", "w+");
    if (output == nullptr)
        return;

    for (const char *ch: str_ends) {
        for(int i = 0; ; --i) {
            if(ch[i] == '\n' || ch[i] == EOF) { //отматали на начало строки
                while (true) {
                    ++i;
                    std::fputc(static_cast<int>(ch[i]), output); // и записываем в файл строку
                    if (ch[i] == '\n' || ch[i] == EOF) // пока она не закончится
                        break;
                }
                break;
            }
        }
    }
    fclose(output);
}

void SortStringsInFile::ReturnText() {
    FILE *output;
    output = fopen("..//Onegin_after_sort.txt", "w+");

    for (unsigned long i = 0; i < file_size; ++i)
        std::fputc(full_text[i], output);

    fclose(output);
}

SortStringsInFile::~SortStringsInFile() {
    fclose(input_text);
    delete [] full_text;
}


