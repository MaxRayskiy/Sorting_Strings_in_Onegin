/*
 *
*/
#include <algorithm>
#include <iostream>
#include <vector>

class SortStringsInFile {
    FILE *input_text;
    long file_size;
    std::vector<char*> str_begins;
    std::vector<char *> str_ends;
    char *full_text;

    inline static bool IsAlphaOrNum(const char symbol); // true, если буква или цифра
    static int CmpInOrder(const void *f, const void *s);
    static int CmpFromEnd(const void *f, const void *s);

public:
    SortStringsInFile();
    void ReadText();
    void SortInOrder();
    void SortFromEnd();

    ~SortStringsInFile();
};

int main() {
    SortStringsInFile Onegin;
    Onegin.ReadText();
    Onegin.SortInOrder();
    Onegin.SortFromEnd();

    return 0;
}

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
        full_text[i++] = static_cast<char>(c);

        if (c == 10) {// 10 == (int)'\n'
            str_begins.push_back(&full_text[i]);

            if (i > 1) {
                str_ends.push_back(&full_text[i - 2]);
            }
        }

        c = fgetc(input_text);
    }
    str_ends.push_back(&full_text[file_size - 2]);
}

inline bool SortStringsInFile::IsAlphaOrNum(const char symbol) {  // true, если буква или цифра
    return (('a' <= symbol && symbol <= 'z') || ( 'A' <= symbol && symbol <= 'Z') || ('0' <= symbol && symbol <= '9'));
}


int SortStringsInFile::CmpInOrder(const void *f, const void *s) {
    const char *first = *(const char**) f;
    const char *second = *(const char**) s;

    int i = -1, j = -1;

    while (true) {
        ++i;
        while (!IsAlphaOrNum(first[i])) {
            if (first[i] == '\n')
                return -1;
            ++i;
        }

        ++j;
        while (!IsAlphaOrNum(second[j])) {
            if (second[j] == '\n')
                return 1;
            ++j;
        }
        if (first[i] < second[j])
            return -1;
        else if (first[i] > second[j])
            return 1;
        else
            continue;
    }
}

void SortStringsInFile::SortInOrder() {
    std::qsort(&str_begins[0], str_begins.size(), sizeof(char *), CmpInOrder);

    FILE *output = fopen("..//Sorted_In_Order.txt", "w+");
    for (const char *ch: str_begins) {
        for (int i = 0; ;++i) {
            std::fputc(static_cast<int>(ch[i]), output);

            if(ch[i] == '\n' || ch[i] == EOF)
                break;
        }
    }
    fclose(output);
}

int SortStringsInFile::CmpFromEnd(const void *f, const void *s){
    const char *first = *(const char**) f;
    const char *second = *(const char**) s;

    int i = 1, j = 1;

    while (true) {
        --i;
        while (!IsAlphaOrNum(first[i])) {
            if (first[i] == '\n')
                return -1;
            --i;
        }

        --j;
        while (!IsAlphaOrNum(second[j])) {
            if (second[j] == '\n')
                return 1;
            --j;
        }
        if (first[i] < second[j])
            return -1;
        else if (first[i] > second[j])
            return 1;
        else
            continue;
    }
}

void SortStringsInFile::SortFromEnd() {
    std::qsort(&str_ends[0], str_begins.size(), sizeof(char *), CmpFromEnd);

    FILE *output = fopen("..//Sorted_From_the_end.txt", "w+");
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
    } //работает. страшно.
    fclose(output);
}

SortStringsInFile::~SortStringsInFile() {
    fclose(input_text);
    delete [] full_text;
}