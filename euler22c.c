// euler22c - Очки за имена

// Используйте names.txt (щелкнуть правой кнопкой мыши и выбрать 'Save Link/Target As...'), 
// текстовый файл размером 46 КБ, содержащий более пяти тысяч имен. Начните с сортировки в алфавитном порядке. 
// Затем подсчитайте алфавитные значения каждого имени и умножьте это значение на порядковый номер имени 
// в отсортированном списке для получения количества очков имени.

// Например, если список отсортирован по алфавиту, имя COLIN (алфавитное значение которого 3 + 15 + 12 + 9 + 14 = 53) 
// является 938-м в списке. Поэтому, имя COLIN получает 938 × 53 = 49714 очков.

// Какова сумма очков имен в файле?

//второй вариант

#include <stdio.h>

#define LEN_WORD 12
#define VAL_WORDS 5163

int get_reiting(char symb_arg)
//возвращает рейтинг буквы от 1 до 26, '0' = 0
{    
    return (symb_arg == 0)? 0 : (symb_arg - 64);
}

int main() 
{
    char text[VAL_WORDS][LEN_WORD] = {0};           //[количество слов][количество букв]    
    char sort_buff[LEN_WORD] ={};                   //буфер

    int name_indx = 0;
    int ch_indx = 0;
    int iteration = 0;

    int name_point = 0;                             //очки имени
    unsigned long long sum_point = 0;               //сумма очков          

    FILE *file;
    char ch;
   
    //преобразуем текст из файла во вложенный двумерный массив
    file = fopen("euler22text.txt", "r");           //открываем файл на чтение
    if (file == NULL) 
    {
        printf("Failed to open file.\n");
        return 1;
    }
    while ((ch = fgetc(file)) != EOF)               //пока не достигли конца файла
    {         
        if(ch_indx == LEN_WORD)                     //если достигли конца вложенного массива
        {
            ch_indx = 0;
            name_indx++;            
        }  

        if(ch == ',')                               //слова разделены запятыми
        {
            ch_indx = 0;
            name_indx++;
        }
            
        else if(ch != '\"')                         //игнорируем кавычки
            {
                text[name_indx][ch_indx] = ch;
                ch_indx++;
            } 
    }
    fclose(file);
    
    //сортируем методом пузырька
    while (iteration < VAL_WORDS)
    {
        //заносим в буфер первое имя
        for(int ch = 0; ch < LEN_WORD; ch++)        
            sort_buff[ch] = text[0][ch];

        //сортируем
        for(int name = 1; name < VAL_WORDS; name++)
        {
            for(int ch = 0; ch < LEN_WORD; ch++)
            //сверяем слова побуквенно
            {
                if(get_reiting(sort_buff[ch]) == get_reiting(text[name][ch]))
                //если буквы равны - проверяем следующую
                    continue;
                else if(get_reiting(sort_buff[ch]) > get_reiting(text[name][ch]))
                {
                    //заносим слово из текста
                    for(int j = 0; j < LEN_WORD; j++)
                        text[name - 1][j] = text[name][j];  
                    break;  
                }
                else
                {
                    //заносим слово из буфера, обновляем буфер
                    for(int j = 0; j < LEN_WORD; j++)
                    {
                        text[name - 1][j] = sort_buff[j];
                        sort_buff[j] = text[name][j];  
                    }
                     break;     
                }
            }
        }
              
        //заносим в последний элемент массива данные из буфера
        for(int ch = 0; ch < LEN_WORD; ch++)
            text[VAL_WORDS - 1][ch] = sort_buff[ch];        
 
    iteration++;    
    }
 
    for(int i = 0; i < VAL_WORDS; i++)
    //считаем сумму очков
    {
        name_point = 0;
        for(int j = 0; j < LEN_WORD; j++)        
            name_point += get_reiting(text[i][j]);
        sum_point += name_point*(i + 1);
    }

    printf("%llu ",sum_point);                                   //верный ответ - 871198282
  
    return 0;
}