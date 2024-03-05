// euler54c - Покерные ставки

// В карточной игре покер ставка состоит из пяти карт и оценивается от самой младшей до самой старшей в следующем порядке:

// Старшая карта: Карта наибольшего достоинства.
// Одна пара: Две карты одного достоинства.
// Две пары: Две различные пары карт
// Тройка: Три карты одного достоинства.
// Стрейт: Все пять карт по порядку, любые масти.
// Флаш: Все пять карт одной масти.
// Фул-хаус: Три карты одного достоинства и одна пара карт.
// Каре: Четыре карты одного достоинства.
// Стрейт-флаш: Любые пять карт одной масти по порядку.
// Роял-флаш: Десятка, валет, дама, король и туз одной масти.
// Достоинство карт оценивается по порядку:
// 2, 3, 4, 5, 6, 7, 8, 9, 10, валет, дама, король, туз.

// Если у двух игроков получились ставки одного порядка, то выигрывает тот, у кого карты старше:
// к примеру, две восьмерки выигрывают две пятерки (см. пример 1 ниже).
// Если же достоинства карт у игроков одинаковы, к примеру, у обоих игроков пара дам, то сравнивают карту наивысшего достоинства (см. пример 4 ниже);
// если же и эти карты одинаковы, сравнивают следующие две и т.д.

// Допустим, два игрока сыграли 5 ставок следующим образом:

// Ставка   1-й игрок               2-й игрок	 	        Победитель
// 1        5♥ 5♣ 6♠ 7♠ K♦          2♣ 3♠ 8♠ 8♦ T♦
//          Пара пятерок            Пара восьмерок          2-й игрок

// 2	 	5♦ 8♣ 9♠ J♠ A♣          2♣ 5♣ 7♦ 8♠ Q♥
//          Старшая карта туз       Старшая карта дама      1-й игрок

// 3	 	2♦ 9♣ A♠ A♥ A♣          3♦ 6♦ 7♦ T♦ Q♦
//          Три туза                Флаш, бубны             2-й игрок

// 4	 	4♦ 6♣ 9♥ Q♥ Q♣          3♦ 6♦ 7♥ Q♦ Q♠
//          Пара дам                Пара дам
//          Старшая карта девятка   Старшая карта семерка   1-й игрок

// 5	 	2♥ 2♦ 4♣ 4♦ 4♠          3♣ 3♦ 3♠ 9♠ 9♦
//          Фул-хаус                Фул-хаус
//          Три четверки            Три тройки              1-й игрок

// Файл poker.txt содержит одну тысячу различных ставок для игры двух игроков.

// В каждой строке файла приведены десять карт (отделенные одним пробелом): первые пять - карты 1-го игрока, оставшиеся пять - карты 2-го игрока.
// Можете считать, что все ставки верны (нет неверных символов или повторов карт), ставки каждого игрока не следуют в определенном порядке,
// и что при каждой ставке есть безусловный победитель.

// Сколько ставок выиграл 1-й игрок?

// Примечание: карты в текстовом файле обозначены в соответствии с английскими наименованиями достоинств и мастей:
// T - десятка, J - валет, Q - дама, K - король, A - туз; S - пики, C - трефы, H - червы, D - бубны.

#include <stdio.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <locale.h> // русский язык в printf()
#include <stdbool.h>
#include <ctype.h>

#define NAME_FILE "euler54text.txt"
#define LEN_ARR 32000 // 1000 ставок по 10 карт (из двух букв) и 10 пробелов + запас

typedef enum poker_combinations
{
    high_card,
    one_pair,
    two_pairs,
    three_kind,
    straight,
    flush,
    full_house,
    four_kind,
    straight_flush,
    royal_flush,

} comb_t; // комбинации в покере

typedef struct hand
{
    char cnt_values[15];   // храним количество карт в ставке по их индексу
                           // arr[2] = 3; - три двойки
                           // arr[11] = 1; - один валет
                           // T - десятка[10], J - валет[11], Q - дама[12], K - король[13], A - туз[14];
    char cnt_suits[5];     // храним масти по индексу
                           // S - пики[1], C - трефы[2], H - червы[3], D - бубны[4]
    char max_value;        // значение старшей карты
    char four_kind_value;  // значение четырех карт
    char three_kind_value; // значение трех карт
    char two_kind_max;     // значение старшей пары карт
    char two_kind_min;     // значение младшей пары карт
} hand_t;

int open_file(const char *name_file, char text_arr[]);
void hand_init(hand_t *Hand1);
int get_hand(hand_t *Hand, char *hands_arr, int indx_hands, char values_suits[]);
comb_t get_comb(hand_t *Hand);
bool compare_hands(hand_t *Hand1, hand_t *Hand2, comb_t comb);

// bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value);

int main(void)
{
    double time_spent = 0.0; // для хранения времени выполнения кода
    clock_t begin = clock(); // СТАРТ таймера

    setlocale(LC_ALL, "Rus"); // русский язык в printf()

    int answ = 0;
    static char hands_arr[LEN_ARR] = {0}; // массив для хранения содержимого файла
    char values_suits[] = {['2'] = 2, ['3'] = 3, ['4'] = 4, ['5'] = 5, ['6'] = 6, ['7'] = 7, ['8'] = 8, ['9'] = 9, ['T'] = 10, ['J'] = 11, ['Q'] = 12, ['K'] = 13, ['A'] = 14, ['S'] = 1, ['C'] = 2, ['H'] = 3, ['D'] = 4};

    hand_t Hand1; // структуры для хранения ставок
    hand_t Hand2;

    int lenght = open_file(NAME_FILE, hands_arr);
    int indx_hands = 0;

    while (indx_hands < lenght)
    {
        hand_init(&Hand1); // обнуляем значения
        hand_init(&Hand2);

        indx_hands = get_hand(&Hand1, hands_arr, indx_hands, values_suits);
        indx_hands = get_hand(&Hand2, hands_arr, indx_hands, values_suits);

        comb_t comb1 = get_comb(&Hand1);
        comb_t comb2 = get_comb(&Hand2);

        if (comb1 == comb2)
            answ += compare_hands(&Hand1, &Hand2, comb1);

        else
            answ += comb1 > comb2;
        
    }

    clock_t end = clock();                                // СТОП таймера
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; // время работы в секундах

    printf("Ответ = %d время = %f\n", answ, time_spent); // выводим результат и время работы программы
    return 0;
}

int open_file(const char *name_file, char hands_arr[])
// функция открывает файл и копирует его содержимое в массив
// параметры:   *name_file  - название / путь к файлу строкой "euler22text.txt"
//              text_arr[]  - массив в который копируем
// return:      lenght      - длина файла
{
    FILE *file;

    file = fopen(name_file, "r"); // открываем файл на чтение

    if (file == NULL)
    {
        printf("open_file(): ошибка при открытии файла \"%s\".\n", name_file);
        return 0;
    }
    char ch;
    int indx = 0;

    while ((ch = fgetc(file)) != EOF)
        hands_arr[indx++] = ch; // копируем содержимое файла в массив (до EOF)

    int lenght = ftell(file); // получаем значение файловой позиции (конец = длина файла)

    fclose(file); // закрываем файл

    printf("open_file(): файл \"%s\" (длиной %d) открыт и сохранен в массив (длиной %d)\n", name_file, lenght, LEN_ARR);

    return lenght;
}

void hand_init(hand_t *Hand)
// Функция, которая обнуляет значения ставки
{
    Hand->max_value = 0;
    Hand->four_kind_value = 0;
    Hand->three_kind_value = 0;
    Hand->two_kind_max = 0;
    Hand->two_kind_min = 0;

    for (int i = 0; i < 15; i++)
        Hand->cnt_values[i] = 0;

    for (int i = 0; i < 5; i++)
        Hand->cnt_suits[i] = 0;
}

int get_hand(hand_t *Hand, char *hands_arr, int indx_hands, char values_suits[])
// игроки получают свои ставки
// return: индекс символа разделяющего ставки '\n'
{
    while (hands_arr[indx_hands] == '\n')
        indx_hands++;

    for (int card = 0; card < 5; card++) // считаем карты первой ставки
    {
        while (hands_arr[indx_hands] == ' ')
            indx_hands++;

        Hand->cnt_values[values_suits[hands_arr[indx_hands++]]]++;
        Hand->cnt_suits[values_suits[hands_arr[indx_hands++]]]++;
    }

    for (int value = 0; value < 15; value++)
    {
        if (Hand->cnt_values[value])
            Hand->max_value = value; // и сохраняем значение старшей карты

        if (Hand->cnt_values[value] == 4)
            Hand->four_kind_value = value;

        else if (Hand->cnt_values[value] == 3)
            Hand->three_kind_value = value;

        else if (Hand->cnt_values[value] == 2 && Hand->two_kind_min) // если одна пара уже есть
            Hand->two_kind_max = value;

        else if (Hand->cnt_values[value] == 2)
            Hand->two_kind_min = value;
    }

    return indx_hands;
}
comb_t get_comb(hand_t *Hand)
// функция принимает ставку и возвращает комбинацию
//      Старшая карта: Карта наибольшего достоинства.
//      Одна пара: Две карты одного достоинства.
//      Две пары: Две различные пары карт
//      Тройка: Три карты одного достоинства.
//      Стрейт: Все пять карт по порядку, любые масти.
//      Флаш: Все пять карт одной масти.
//      Фул-хаус: Три карты одного достоинства и одна пара карт.
//      Каре: Четыре карты одного достоинства.
//      Стрейт-флаш: Любые пять карт одной масти по порядку.
//      Роял-флаш: Десятка, валет, дама, король и туз одной масти.
// T - десятка[10], J - валет[11], Q - дама[12], K - король[13], A - туз[14];
{
    bool same_suit_fl = false;   // пять карт одной масти
    bool consecutive_fl = false; // все карты по порядку
    bool four_fl = false;        // четыре карты одного достоинства
    bool three_fl = false;       // три карты одного достоинства
    int pair_cnt = 0;            // количество пар карт

    for (int suit = 0; suit < 5; suit++)
    {
        if (Hand->cnt_suits[suit] == 5)
        {
            same_suit_fl = true; // пять карт одной масти
            break;
        }
    }

    for (int value = 0, cnt = 0; value < 15; value++)
    {
        if (Hand->cnt_values[value])
            cnt++;                             // считаем карты идущие подряд
        else if (Hand->cnt_values[value] == 0) // обнуляем счетчик при прерывании серии карт
            cnt = 0;

        if (cnt == 5)
        {
            consecutive_fl = true; // все карты по порядку
            break;                 // все карты посчитаны
        }

        if (Hand->cnt_values[value] == 4)
        {
            four_fl = true;
            break;
        }

        else if (Hand->cnt_values[value] == 3)
            three_fl = true;

        else if (Hand->cnt_values[value] == 2)
            pair_cnt++;
    }

    if (same_suit_fl && consecutive_fl && Hand->max_value == 14) // пять карт одной масти, идут подряд, старшая - туз
        return royal_flush;                                      // Роял-флаш: Десятка, валет, дама, король и туз одной масти.

    else if (same_suit_fl && consecutive_fl) // пять карт одной масти, идут подряд
        return straight_flush;               // Стрейт-флаш: Любые пять карт одной масти по порядку.

    else if (four_fl)
        return four_kind; // Каре: Четыре карты одного достоинства.

    else if (three_fl && pair_cnt)
        return full_house; // Фул-хаус: Три карты одного достоинства и одна пара карт.

    else if (same_suit_fl)
        return flush; // Флаш: Все пять карт одной масти.

    else if (consecutive_fl)
        return straight; // Стрейт: Все пять карт по порядку, любые масти.

    else if (three_fl)
        return three_kind; // Тройка: Три карты одного достоинства.

    else if (pair_cnt == 2)
        return two_pairs; // Две пары: Две различные пары карт

    else if (pair_cnt)
        return one_pair; // Одна пара: Две карты одного достоинства.

    else
        return high_card; // Старшая карта: Карта наибольшего достоинства.
}

bool compare_hands(hand_t *Hand1, hand_t *Hand2, comb_t comb)
// Функция сравнивает две ставки с одниаковыми комбинациями
//      Старшая карта: Карта наибольшего достоинства.

// high_card,
//     one_pair,

{
    if (comb == royal_flush) // Роял-флаш: Десятка, валет, дама, король и туз одной масти.
        return Hand1->max_value > Hand2->max_value;

    else if (comb == straight_flush) // Стрейт-флаш: Любые пять карт одной масти по порядку.
        return Hand1->max_value > Hand2->max_value;

    else if (comb == four_kind) // Каре: Четыре карты одного достоинства.
    {
        if (Hand1->four_kind_value == Hand2->four_kind_value)
            return Hand1->max_value > Hand2->max_value;

        return Hand1->four_kind_value > Hand2->four_kind_value;
    }

    else if (comb == full_house) // Фул-хаус: Три карты одного достоинства и одна пара карт.
    {
        if (Hand1->three_kind_value == Hand2->three_kind_value)
            return Hand1->two_kind_min > Hand2->two_kind_min;

        return Hand1->three_kind_value > Hand2->three_kind_value;
    }

    else if (comb == flush) //      Флаш: Все пять карт одной масти.
        return Hand1->max_value > Hand2->max_value;

    else if (comb == straight) // Стрейт: Все пять карт по порядку, любые масти.
        return Hand1->max_value > Hand2->max_value;

    else if (comb == three_kind) //      Тройка: Три карты одного достоинства.
    {
        if (Hand1->three_kind_value == Hand2->three_kind_value)
            return Hand1->max_value > Hand2->max_value;

        return Hand1->three_kind_value > Hand2->three_kind_value;
    }

    else if (comb == two_pairs) //      Две пары: Две различные пары карт
    {
        if (Hand1->two_kind_max == Hand2->two_kind_max)
            return Hand1->two_kind_min > Hand2->two_kind_min;

        return Hand1->two_kind_max > Hand2->two_kind_max;
    }

    else if (comb == one_pair) //      Одна пара: Две карты одного достоинства.
    {
        if (Hand1->two_kind_min == Hand2->two_kind_min)
            return Hand1->max_value > Hand2->max_value;
        return Hand1->two_kind_min > Hand2->two_kind_min;
    }

    else
        return Hand1->max_value > Hand2->max_value;
}

bool input_more_limit(const char *name_func, const char *name_input, int input_value, const char *name_limit, int limit_value)
// функция определяет превышение переменной своего предельного значения и выводит предупреждение
// параметры:   *name_func  - название функции
//              input_value - значение переменной
//              *name_input - название переменной
//              limit_value - предельное значение
//              *name_limit - название предельного значения
// return:      true        - при превышении
{
    if (input_value > limit_value) // обрабатываем превышение
    {
        printf("%s: %s = %d more %s = %d\n", name_func, name_input, input_value, name_limit, limit_value);
        return true;
    }

    return false;
}
