/*
* Программа  должна  формировать  несколько параллельных потоков (пусть количество зависит от архитектуры процессора). 
* Каждый поток формирует 1000000 случайных чисел  и записывает   время на их формирование  в свой файл  (номер потока.txt).
* Головная функция после завершения выводит сообщения все потоки отработали успешно. Использовать любой язык программирования
* 
* Ссылка на github: https://github.com/Laat-ain/Task_multithreading
*/

#include <iostream>
#include <thread>
#include <fstream>
using namespace std;

// Определяем и выводим на экран максимальное колличество одновременных потоков
void Number_threads() {
    cout << "Количество поддерживаемых параллельных потоков: " << thread::hardware_concurrency() << endl;
}

// Формирование 1000000 случайных чисел и определение затраченного времени
double Random() {
    srand(time(0));
    srand((unsigned int)time(NULL));
    int  random_number;
    
    for (int i = 0; i < 1000000; i++) {
        random_number = rand();
    }

    double end_time = clock()/1000.0;
    cout << "ID потока = " << this_thread::get_id() << " Время работы = " << end_time << " \n" << endl;
    return end_time;
}

// Создание и запись файлов 
void Creating_file(string file_name) {
    ofstream fout(file_name); // создаём объект класса ofstream для записи и связываем его с файлом (file_name)
    fout << "Количество затраченного времени: " << Random() << " (ID потока = " << this_thread::get_id() << " )" ;
    fout.close(); 
}

int main()
{
    setlocale(LC_ALL, "ru");
    Number_threads(); 

    thread stream_1(Creating_file, "1.txt");
    thread stream_2(Creating_file, "2.txt");
    thread stream_3(Creating_file, "3.txt");
    thread stream_4(Creating_file, "4.txt");

    stream_1.join();
    stream_2.join();
    stream_3.join();
    stream_4.join();

    cout << "Все потоки отработали успешно" << endl;
    return 0;
}
