// euler22c - Очки за имена

// Используйте names.txt (щелкнуть правой кнопкой мыши и выбрать 'Save Link/Target As...'), 
// текстовый файл размером 46 КБ, содержащий более пяти тысяч имен. Начните с сортировки в алфавитном порядке. 
// Затем подсчитайте алфавитные значения каждого имени и умножьте это значение на порядковый номер имени 
// в отсортированном списке для получения количества очков имени.

// Например, если список отсортирован по алфавиту, имя COLIN (алфавитное значение которого 3 + 15 + 12 + 9 + 14 = 53) 
// является 938-м в списке. Поэтому, имя COLIN получает 938 × 53 = 49714 очков.

// Какова сумма очков имен в файле?

#include <stdio.h>

#define LEN_WORD 12
#define VAL_WORDS 5163

int get_reiting(char symb_arg)
{
    switch (symb_arg)
    {
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;    
    case 'D':
        return 4;
    case 'E':
        return 5;
    case 'F':
        return 6;
    case 'G':
        return 7;
    case 'H':
        return 8;
    case 'I':
        return 9;
    case 'J':
        return 10;
    case 'K':
        return 11;
    case 'L':
        return 12;
    case 'M':
        return 13;    
    case 'N':
        return 14;
    case 'O':
        return 15;
    case 'P':
        return 16;
    case 'Q':
        return 17;
    case 'R':
        return 18;
    case 'S':
        return 19;
    case 'T':
        return 20;
    case 'U':
        return 21;
    case 'V':
        return 22;
    case 'W':
        return 23;    
    case 'X':
        return 24;
    case 'Y':
        return 25;
    case 'Z':
        return 26;
    case 0:
        return 0;
    default:
        return 30;
    }
}

int main() 
{
    char text[VAL_WORDS][LEN_WORD] = {};    //[количество слов][количество букв]
    char sort_arr[VAL_WORDS][LEN_WORD] = {};
    char sort_buff[LEN_WORD] ={};

    int i_indx = 0;
    int j_indx = 0;
    int iteration = 0;

    int name_point = 0;
    unsigned long long sum_point = 0;                           //874943365

    FILE *file;
    char ch;

    //заполняем массив 'Z'
    for(int i = 0; i < VAL_WORDS; i++)
        text[i][0] = 'Z';
    
    //преобразуем текст из файла во вложенный двумерный массив
    file = fopen("euler22text.txt", "r");
    if (file == NULL) 
    {
        printf("Failed to open file.\n");
        return 1;
    }
    while ((ch = fgetc(file)) != EOF) 
    {
        if(i_indx == VAL_WORDS)
            i_indx = 0;            
        if(j_indx == LEN_WORD)
        {
            j_indx = 0;
            i_indx++;            
        }  

        if(ch == ',')
        {
            //fl = false;
            j_indx = 0;
            i_indx++;
        }
            
        else if(ch != '\"')
            {
                text[i_indx][j_indx] = ch;
                j_indx++;
            } 
    }
    fclose(file);
    
    //сортируем методом пузырька
    while (iteration < VAL_WORDS)
    {
        //заносим в буфер первое имя
        for(int j = 0; j < LEN_WORD; j++)
            sort_buff[j] = text[0][j];
        //сортируем
        for(int i = 1; i < VAL_WORDS; i++)
        {
            if(get_reiting(sort_buff[0]) > get_reiting(text[i][0]))
            {            
                for(int j = 0; j < LEN_WORD; j++)
                    sort_arr[i - 1][j] = text[i][j];    
            } 
            else
            {
                for(int j = 0; j < LEN_WORD; j++)
                {
                    sort_arr[i - 1][j] = sort_buff[j];
                    sort_buff[j] = text[i][j];  
                }        
            }
        }
        //заносим в последний элемент массива данные из буфера
        for(int j = 0; j < LEN_WORD; j++)
            sort_arr[VAL_WORDS - 1][j] = sort_buff[j];
        //переносим отсортированный список в массив text
        for(int i = 0; i < VAL_WORDS; i++)
        {
            for(int j = 0; j < LEN_WORD; j++)
                text[i][j] = sort_arr[i][j];
        }
    iteration++;    
    }

    //сортируем методом пузырька по двум буквам
    for(int lt = 0; lt < LEN_WORD - 2; lt++)
    {
        iteration = 0;
        while (iteration < VAL_WORDS)
        {
            //заносим в буфер первое имя
            for(int j = 0; j < LEN_WORD; j++)
                sort_buff[j] = text[0][j];
            //сортируем
            for(int i = 1; i < VAL_WORDS; i++)
            {
                if(get_reiting(sort_buff[lt]) == get_reiting(text[i][lt]))
                //если первые буквы совпадают...
                {
                    if(get_reiting(sort_buff[lt + 1]) > get_reiting(text[i][lt + 1]))            
                    {            
                        for(int j = 0; j < LEN_WORD; j++)
                            sort_arr[i - 1][j] = text[i][j];    
                    } 
                    else
                    {
                        for(int j = 0; j < LEN_WORD; j++)
                        {
                            sort_arr[i - 1][j] = sort_buff[j];
                            sort_buff[j] = text[i][j];  
                        }        
                    }
                }
                else
                //заносим в текущий элемент массива данные из буфера
                    for(int j = 0; j < LEN_WORD; j++)
                    {
                        sort_arr[i - 1][j] = sort_buff[j];
                        sort_buff[j] = text[i][j]; 
                    }                   
            }

            //переносим отсортированный список в массив text
            for(int i = 0; i < VAL_WORDS; i++)
            {
                for(int j = 0; j < LEN_WORD; j++)
                    text[i][j] = sort_arr[i][j];
            }
        iteration++;    
        }
    }

    for(int i = 0; i < VAL_WORDS; i++)
    {
        name_point = 0;
        for(int j = 0; j < LEN_WORD; j++)        
            name_point += get_reiting(text[i][j]);
        sum_point += name_point*(i + 1);                        //874943365
        
    }
    char h;
    for(int j = 0; j < LEN_WORD; j++)
    {
        h = text[5162][j];
        printf("%c",h);
    }        
    return 0;
}