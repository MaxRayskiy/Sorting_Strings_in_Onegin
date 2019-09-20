/*! @file
 * Sorting Onegin
*/
#pragma once

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

//! @class SortStringsInFile
class SortStringsInFile {
    /// Указатель на входной поток
    FILE *input_text;

    /// размер файла в байтах
    long file_size;

    /// Вектор указателей на начала  строк
    std::vector<char *> str_begins;

    /// Вектор указателей на начала  строк
    std::vector<char *> str_ends;

    /// Указатель на начало текста
    char *full_text;

    ///Метод, проверяющий, что символ является латинской буквой или цифрой
    ///@warning только латинские символы!
    ///@todo добавить кириллицу
    ///@param symbol Анализируемый символ
    ///@return true, если символ является латинской буквой или цифрой
    inline static bool IsAlphaOrNum(const char &symbol);

    /// Компаратор для сортировки с начала
    static int CmpFromBegin(const void *input_first, const void *input_second);

    /// Компаратор для сортировки с конца
    static int CmpFromEnd(const void *input_first, const void *input_second);

public:
    /// Конструктор по умолчанию
    SortStringsInFile();

    /// Считываем текст из потока
    void ReadText();

    /// Сортируем и выводим строки с начала
    void SortFromBegin();

    /// Сортируем и выводим строки с конца
    void SortFromEnd();

    /// Возвращаем исходный текст
    void ReturnText();

    /// Деструктор по умолчанию
    ~SortStringsInFile();
};