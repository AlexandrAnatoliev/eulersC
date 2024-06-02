// euler59c - XOR шифровка

// Каждый символ в компьютере имеет уникальный код, предпочитаемым является стандарт ASCII
// (American Standard Code for Information Interchange - Американский стандартный код для обмена информацией).
// Для примера, A верхнего регистра = 65, звездочка (*) = 42, а k нижнего регистра = 107.

// Современный метод шифровки состоит в том, что берется текстовый файл, конвертируется в байты по ASCII,
// а потом над каждым байтом выполняется операция XOR с определенным значением, взятым из секретного ключа.
// Преимущество функции XOR состоит в том, что применяя тот же ключ к зашифрованному тексту, получается исходный;
// к примеру, 65 XOR 42 = 107, тогда 107 XOR 42 = 65.

// Для невзламываемого шифрования ключ должен быть такой же длины, что и сам текст, и ключ должен быть составлен из случайных байтов.
// Тогда, если пользователь хранит зашифрованное сообщение и ключ шифрования в разных местах, то без обеих "половинок" расшифровать сообщение просто невозможно.

// К сожалению, этот метод непрактичен для большинства пользователей, поэтому упрощенный метод использует в качестве ключа пароль.
// Если пароль короче текстового сообщения, что наиболее вероятно, то ключ циклично повторяется на протяжении всего сообщения.
// Идеальный пароль для этого метода достаточно длинный, чтобы быть надежным, но достаточно короткий, чтобы его можно было запомнить.

// Ваша задача была упрощена, так как пароль состоит из трех символов нижнего регистра.
// Используя cipher1.txt (щелкнуть правой кнопкой мыши и выбрать 'Save Link/Target As...'), содержащий зашифрованные коды ASCII, а также тот факт,
// что сообщение должно содержать распространенные английские слова, расшифруйте сообщение и найдите сумму всех значений ASCII в исходном тексте.
// 129448

#include <stdio.h>
#include <stdbool.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h>     // русский язык в printf()
#include <stdlib.h>
#include <ctype.h>

#define FILE_NAME "euler59c.txt"

typedef struct text
{
    char *arr;          // ссылка на массив
    int lenght;         // длина массива
} text_t;

text_t open_file_malloc_ar(const char *name_file);
text_t text_malloc(int lenght);
bool get_xor_text(const text_t txt, text_t *xor_txt, text_t key);
bool get_next_key(text_t *key);
bool is_text(char simb);

int main(void)
{
    setlocale(LC_ALL, "Rus");                   // русский язык в printf()

    double time_spent = 0.0;                    // для хранения времени выполнения кода
    clock_t begin = clock();                    // СТАРТ таймера

    text_t text;                                // структура для хранения исходного текста (коды в виде символов)
    text_t format_text;                         // отформатированный текст, коды в ввиде чисел
    text_t xor_text;                            // массив для xor-преобразования текста

    int answ = 0;
    int text_indx = 0;
    int format_indx = 0;
    int num = 0;

    text = open_file_malloc_ar(FILE_NAME);
    format_text = text_malloc(text.lenght);

    while (text_indx < text.lenght)             // пребразовывем ['3', '6', ',', '5, 6'] в [36, 56]
    {
        if (text.arr[text_indx] == ',')
        {
            text_indx++;
            format_text.arr[format_indx++] = num;
            num = 0;
        }

        else
        {
            num *= 10;
            num += text.arr[text_indx++] - '0'; // '0' = 48
        }
    }

    format_text.arr[format_indx] = num;         // заносим последнюю цифру (в конце нет запятой)
    format_text.lenght = format_indx + 1;       // фактическая длина текста

    free(text.arr);                             // не забыть освободить место в памяти, выделяемое под массив

    xor_text = text_malloc(format_text.lenght);             // выделяем необходимое место под XOR-преобразованный тест

    text_t key;                                             // XOR-ключ

    char key_arr[] = {'a', 'a', 'a'};
    key.arr = &key_arr[0];
    key.lenght = 3;

    bool key_fl = true;
    bool is_answer = false;

    while (key_fl && is_answer == false)                    // перебираем ключ
    {
        is_answer = get_xor_text(format_text, &xor_text, key);
        if (is_answer == false)                             // пока не будет расшифровани весь текст
            key_fl = get_next_key(&key);
    }

    for (int i = 0; i < xor_text.lenght; i++)               // считаем сумму всех ASCII значений в тесте
        answ += xor_text.arr[i];

    free(format_text.arr);
    free(xor_text.arr);

    clock_t end = clock();                                  // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;   // время работы в секундах

    printf("XOR-ключ: ");
    for (int i = 0; i < key.lenght; i++)
        printf("%c", key.arr[i]);

    printf("\nОтвет = %d время = %f\n", answ, time_spent);  // выводим результат и время работы программы

    return 0;
}

text_t open_file_malloc_ar(const char *name_file)
// Функция, которая открывает файл, выделяет место под массив и копирует содержимое в него
// Параметры:   *name_file  - название / путь к файлу строкой "euler59c.txt"
// return:      txt      	- структура, содержащая ссылку на массив и длину массива
{
    text_t txt;

    FILE *file;
    file = fopen(name_file, "r");                       // открываем файл на чтение

    if (file == NULL)
        printf("file_open_malloc_ar(): ошибка при открытии файла \"%s\".\n", name_file);

    fseek(file, 0, SEEK_END);                           // устанавливаем файловую позицию в конец файла
    txt.lenght = ftell(file);                           // получаем значение файловой позиции (конец = длина файла)
    txt.arr = malloc(txt.lenght);                       // выделяем место под массив
    fseek(file, 0, SEEK_SET);                           // устанавливаем файловую позицию в начало файла

    while (fgets(txt.arr, txt.lenght, file) != NULL)    // до конца файла
        fputs(txt.arr, file);                           // копируем содержимое файла в массив (ставит в конце ноль!)

    fseek(file, -1, SEEK_END);                          // fgets() ставит в последнюю ячейку ноль '\000'
    txt.arr[txt.lenght - 1] = fgetc(file);              // заменяем ноль последним символом файла перед EOF

    fclose(file);                                       // закрываем файл

    return txt;
}

text_t text_malloc(int lenght)
// Функция, которая выделяет место под структуру
// Параметры:   lenght  - длина массива
// return:      txt    - структура, содержащая ссылку на массив и длину массива
{
    text_t txt;

    txt.arr = malloc(lenght);   // выделяем место под массив
    txt.lenght = lenght;

    return txt;
}

bool get_xor_text(const text_t txt, text_t *xor_txt, text_t key)
// Функция для расшифровки текста
// Параметры:   txt     - исходный (отредактированный) текст
//              xor_txt - расшифрованный текст
//              key     - ключ для расшифровки
// return:      true    - текст успешно расшифрован
{
    for (int i = 0, key_indx = 0; i < txt.lenght; i++)
    {
        if (key_indx == key.lenght)                             // перебираем элементы ключа
            key_indx = 0;

        if (is_text(txt.arr[i] ^ key.arr[key_indx]))
            xor_txt->arr[i] = txt.arr[i] ^ key.arr[key_indx++]; // расшифровываем по-символьно текст
        else
            return false;                                       // прерываем, если расшифрованный символ не может быть текстом
    }

    return true;
}

bool get_next_key(text_t *key)
// Функция для получения следующего ключа
// перебирает ключи от aaa дол zzz
// Параметры:   key     - ключ
// return:      true    - ключ успешно получен
{
    for (int i = 0; i < key->lenght; i++)
    {
        if (key->arr[i] == 'z')
            key->arr[i] = 'a';

        else
        {
            key->arr[i]++;
            return true;
        }
    }

    return false;
}

bool is_text(char simb)
// Функция для проверки допустимости значений символов
// Параметры:   simb    - символ
// return:      false   - символ не может быть использован в тексте
{
    if (isalnum(simb))  // буквы и цифры
        return true;

    else if (simb == ',' || simb == ' ' || simb == ':' || simb == '!' || simb == '?' || simb == ';' || simb == '.')
        return true;    // знаки препинания

    else if (simb == '\"' || simb == '-' || simb == '\'' || simb == '[' || simb == ']' || simb == '+' || simb == '/' || simb == '(' || simb == ')')
        return true;    // скобки и прочие знаки

    return false;
}