// euler22c - Очки за имена

// Используйте names.txt (щелкнуть правой кнопкой мыши и выбрать 'Save Link/Target As...'),
// текстовый файл размером 46 КБ, содержащий более пяти тысяч имен. Начните с сортировки в алфавитном порядке.
// Затем подсчитайте алфавитные значения каждого имени и умножьте это значение на порядковый номер имени
// в отсортированном списке для получения количества очков имени.

// Например, если список отсортирован по алфавиту, имя COLIN (алфавитное значение которого 3 + 15 + 12 + 9 + 14 = 53)
// является 938-м в списке. Поэтому, имя COLIN получает 938 × 53 = 49714 очков.

// Какова сумма очков имен в файле?

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>                                                  // для isalpha()
#include <time.h>                                                   // for clock_t, clock(), CLOCKS_PER_SEC

#define NAME_FILE "euler22text.txt"
#define LEN_ARR 50000
#define NAMES 6000

int open_file(const char *name_file, char text_arr[]);
int parser_names(char text_arr[], int name_arr[], int lenght);
bool compare_names(char text_arr[], int indx_name1, int indx_name2);
int copy_arrs(int receive_arr[], int sourse_arr[], int start_indx, int lenght);
int merge_sort(char text_arr[], int name_arr[], int names);
int get_name_score(char text_arr[], int indx_name);
bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main()
{
    double time_spent = 0.0;                                        // для хранения времени выполнения кода
    clock_t begin = clock();                                        // СТАРТ таймера

    char text_arr[LEN_ARR] = {0};                                   // массив для хранения содержимого файла
    int name_arr[NAMES] = {0};                                      // массив для хранения индексов первых букв имен в массиве text_arr[]

    unsigned long long sum_point = 0;                               // сумма очков

    int lenght = open_file(NAME_FILE, text_arr);
    int names = parser_names(text_arr, name_arr, lenght);

    merge_sort(text_arr, name_arr, names);

    for (int num_name = 1; num_name <= names; num_name++)
        sum_point += num_name * get_name_score(text_arr, name_arr[num_name - 1]);

    clock_t end = clock();                                          // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;           // время работы в секундах

    printf("answer = %llu runtime = %f\n", sum_point, time_spent);  // выводим результат и время работы программы

    return 0;
}

int open_file(const char *name_file, char text_arr[])
// функция открывает файл и копирует его содержимое в массив
// параметры:   *name_file  - название / путь к файлу строкой "euler22text.txt"
//              text_arr[]  - массив в который копируем
// return:      lenght      - длина файла
{
    FILE *file;

    file = fopen(name_file, "r");   // открываем файл на чтение

    if (file == NULL)
    {
        printf("open_file(): failed to open file \"%s\".\n", name_file);
        return 0;
    }

    fgets(text_arr, LEN_ARR, file); // копируем содержимое файла в массив (до '\n'!!!)

    int lenght = ftell(file);       // получаем значение файловой позиции (конец = длина файла)

    fclose(file);                   // закрываем файл

    printf("open_file():    file \"%s\" is opened (lenght - %d) and save in array (lenght - %d)\n", name_file, lenght, LEN_ARR);

    return lenght;
}

int parser_names(char text_arr[], int name_arr[], int lenght)
// функция отмечает индексы начала слов в массиве
// параметры:   text_arr[]  - массив в который сохранены имена
//              name_arr[]  - массив в котором отмечаем индексы начала слов
//              lenght      - количество символов в массиве arr[]
// return:      name_indx   - количество слов в массиве
{
    if (more_limit("parser_names()", "lenght", lenght, "LEN_ARR", LEN_ARR - 1))   
        return 0;                                               // выход за пределы массива text_arr[]

    int name_indx = 0;
    bool start_name = false;                                    // флаг начала слова

    for (int indx = 0; indx < lenght; indx++)
    {
        if (isalpha(text_arr[indx]) && start_name == false)     // первый встреченый символ алфавита
        {
            start_name = true;                                  // является началом слова
            if (more_limit("parser_names()", "name_indx", name_indx, "NAMES", NAMES - 1)) 
                return 0;                                       // выход за пределы массива text_arr[name_indx]
            name_arr[name_indx++] = indx;                       // заносим индекс начала слова text_arr[indx] в массив name_arr[name_index]
        }

        else if (isalpha(text_arr[indx]) && start_name == true) // не первый символ слова - идем дальше
            continue;

        else
            start_name = false;                                 // слово закончилось
    }

    printf("parser_names(): is counted %d names\n", name_indx);

    return name_indx;
}

bool compare_names(char text_arr[], int indx_name1, int indx_name2)
// функция сортирует два имени по алфавиту
// параметры:   text_arr[]  - массив в который сохранены имена
//              indx_name1  - индекс начала первого слова (ANNA)
//              indx_name2  - индекс начала второго слова (BEN)
// return:      true        - если слова уже отсортированы верно (ANNA BEN)
{
    if (more_limit("compare_names()", "indx_name1", indx_name1, "LEN_ARR", LEN_ARR - 1))  // выход за пределы массива text_arr[]
        return true;                                                                            // прерываем функцию и ничего не меняем в массиве

    if (more_limit("compare_names()", "indx_name2", indx_name2, "LEN_ARR", LEN_ARR - 1))  // выход за пределы массива text_arr[]
        return true;                                                                            // прерываем функцию и ничего не меняем в массиве

    while (isalpha(text_arr[indx_name1]))                                                       // пока не кончилось первое слово
    {
        if (isalpha(text_arr[indx_name2]) && text_arr[indx_name1] == text_arr[indx_name2])      // и второе
        {
            indx_name1++;                                                                       // если буквы одинаковые - переходим к следующим
            indx_name2++;
            continue;
        }

        else if (isalpha(text_arr[indx_name2]) && text_arr[indx_name1] < text_arr[indx_name2]) // A (NNA) < B (EN)
            return true;                                                                       // [ANNA, BEN] -> [ANNA, BEN]

        else                    // [BEN, ANNA] -> [ANNA, BEN]; [ANNA, ANN] -> [ANN, ANNA]
            return false;       // при одинаковых начальныных буквах - первым ставить более короткое слово
    }

    return true;                                                                                // если слова одинаковы - не меняем их расположение
}

int copy_arrs(int receive_arr[], int sourse_arr[], int start_indx, int lenght)
// функция копирует один массив в другой
// параметры:   receive_arr[]   - массив в который копируем
//              sourse_arr[]    - массив из которого копируем
//              start_indx      - с какого индекса копировать
//              lenght          - количество переносимых значений
// return:                      - количество занесенных в массив чисел
{
    if (more_limit("copy_arrs()", "start_indx + lenght", start_indx + lenght, "NAMES", NAMES - 1)) // выход за пределы массива name_arr[]
        return false;

    int cnt = 0;

    for (int receive_indx = 0, source_indx = start_indx; source_indx < start_indx + lenght; receive_indx++)
    {
        receive_arr[receive_indx] = sourse_arr[source_indx++];
        cnt++;
    }

    return cnt;
}

int merge_sort(char text_arr[], int name_arr[], int names)
// Функция реализует быструю сортировку слиянием:
//      выделяет из массива name_arr[] = {..., first,...,second-1,...,second + step - 1,...};
//      два подмассива: {first,...,second-1} и {second,...,second + step - 1}; 
//      значения из первого подмассива копируются во временный массив temp_arr[];
//      массив name_arr[] заполняется из дополнительного массива и второго подмассива, параллельно сортируясь
// параметры:   text_arr[]  - массив в который сохранены имена
//              name_arr[]  - массив в котором отмечены индексы начала слов
//              names       - слов в массиве name_arr[]
{
    if (more_limit("merge_sort()", "names", names, "NAMES", NAMES - 1))           // выход за пределы массива name_arr[]
        return true;

    int len_arrs = 1;                                                                   // длина отсортированных массивов
    while (len_arrs < names)
    {
        int first = 0;                                                                  // индексы начала первого {first,...,second-1} в массиве name_arr[]
        int second = len_arrs;                                                          // и второго подмассивов {second,...,second + step - 1} в массиве name_arr[]

        for (first = 0; second < names; first += len_arrs * 2, second += len_arrs * 2)
        {
            int temp_arr[NAMES] = {0};                                                  // дополнительный массив для временного хранения списка индексов начала слов
            int ptr_temp = 0;
            int ptr_second = second;
            int max_temp = copy_arrs(temp_arr, name_arr, first, len_arrs);              // копируем в дополнительный temp_arr[] значения первого подмассива
            int max_second = (second + len_arrs < names) ? second + len_arrs : names;   // ограничиваем длину второго массива

            for (int i = first; i < first + len_arrs * 2; i++)
            {
                // если слова из обоих массивов еще не использованы, сравниваем слова из массивов
                if (ptr_temp < max_temp && ptr_second < max_second && compare_names(text_arr, temp_arr[ptr_temp], name_arr[ptr_second]))
                    name_arr[i] = temp_arr[ptr_temp++];                                 // заносим в массив name_arr[] значения из массива temp_arr[]

                // сравниваем слова из массивов - заносим из подмассива массива name_arr[ptr_second]
                else if (ptr_temp < max_temp && ptr_second < max_second && !compare_names(text_arr, temp_arr[ptr_temp], name_arr[ptr_second]))
                    name_arr[i] = name_arr[ptr_second++];                               // заносим в массив name_arr[] значения из второго подмассива

                else if (ptr_temp < max_temp)
                    name_arr[i] = temp_arr[ptr_temp++];                                 // если не закончились слова в дополнительном массиве - заносим из него

                else
                    name_arr[i] = name_arr[ptr_second++];                               // заносим слова из второго подмассива
            }
        }
        len_arrs *= 2;
    }
    return 0;
}

int get_name_score(char text_arr[], int indx_name)
// функция считает алфавитное значение имени
// Параметры:   text_arr[]  - массив в который сохранены имена
//              indx_name   - индекс начала слова
// return:                  - имя COLIN (алфавитное значение равно 3 + 15 + 12 + 9 + 14 = 53)
{
    if (more_limit("get_name_score()", "indx_name", indx_name, "LEN_ARR", LEN_ARR - 1))   // выход за пределы массива text_arr[]
        return false;

    if (!isalpha(text_arr[indx_name]))                                                          // если первый символ не буква
    {
        printf("get_name_score(): first simbol = %c (indx_name = %d) is not correct\n", text_arr[indx_name], indx_name);
        return 0;
    }

    int score = 0;

    while (isalpha(text_arr[indx_name]))                                                        // пока не кончилось слово
        score += text_arr[indx_name++] - 64;                                                    // код 'A' = 65

    return score;
}

bool more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
    if (input_value > limit_value)                                                              // отрабатываем превышение
    {
        printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}

// второй вариант

// #include <stdio.h>

// #define LEN_WORD 12
// #define VAL_WORDS 5163

// int get_reiting(char symb_arg)
// //возвращает рейтинг буквы от 1 до 26, '0' = 0
// {
//     return (symb_arg == 0)? 0 : (symb_arg - 64);
// }

// int main()
// {
//     char text[VAL_WORDS][LEN_WORD] = {0};           //[количество слов][количество букв]
//     char sort_buff[LEN_WORD] ={};                   //буфер

//     int name_indx = 0;
//     int ch_indx = 0;
//     int iteration = 0;

//     int name_point = 0;                             //очки имени
//     unsigned long long sum_point = 0;               //сумма очков

//     FILE *file;
//     char ch;

//     //преобразуем текст из файла во вложенный двумерный массив
//     file = fopen("euler22text.txt", "r");           //открываем файл на чтение
//     if (file == NULL)
//     {
//         printf("Failed to open file.\n");
//         return 1;
//     }
//     while ((ch = fgetc(file)) != EOF)               //пока не достигли конца файла
//     {
//         if(ch_indx == LEN_WORD)                     //если достигли конца вложенного массива
//         {
//             ch_indx = 0;
//             name_indx++;
//         }

//         if(ch == ',')                               //слова разделены запятыми
//         {
//             ch_indx = 0;
//             name_indx++;
//         }

//         else if(ch != '\"')                         //игнорируем кавычки
//             {
//                 text[name_indx][ch_indx] = ch;
//                 ch_indx++;
//             }
//     }
//     fclose(file);

//     //сортируем методом пузырька
//     while (iteration < VAL_WORDS)
//     {
//         //заносим в буфер первое имя
//         for(int ch = 0; ch < LEN_WORD; ch++)
//             sort_buff[ch] = text[0][ch];

//         //сортируем
//         for(int name = 1; name < VAL_WORDS; name++)
//         {
//             for(int ch = 0; ch < LEN_WORD; ch++)
//             //сверяем слова побуквенно
//             {
//                 if(get_reiting(sort_buff[ch]) == get_reiting(text[name][ch]))
//                 //если буквы равны - проверяем следующую
//                     continue;
//                 else if(get_reiting(sort_buff[ch]) > get_reiting(text[name][ch]))
//                 {
//                     //заносим слово из текста
//                     for(int j = 0; j < LEN_WORD; j++)
//                         text[name - 1][j] = text[name][j];
//                     break;
//                 }
//                 else
//                 {
//                     //заносим слово из буфера, обновляем буфер
//                     for(int j = 0; j < LEN_WORD; j++)
//                     {
//                         text[name - 1][j] = sort_buff[j];
//                         sort_buff[j] = text[name][j];
//                     }
//                      break;
//                 }
//             }
//         }

//         //заносим в последний элемент массива данные из буфера
//         for(int ch = 0; ch < LEN_WORD; ch++)
//             text[VAL_WORDS - 1][ch] = sort_buff[ch];

//     iteration++;
//     }

//     for(int i = 0; i < VAL_WORDS; i++)
//     //считаем сумму очков
//     {
//         name_point = 0;
//         for(int j = 0; j < LEN_WORD; j++)
//             name_point += get_reiting(text[i][j]);
//         sum_point += name_point*(i + 1);
//     }

//     printf("%llu ",sum_point);

//     return 0;
// }