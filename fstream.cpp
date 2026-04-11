#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <string>

const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

class Actions {
    std::ifstream read_from;
    std::ofstream write_to;
public:
    void write() {
        try {
            write_to.open("numbers.txt",std::ios::app);
        } catch (const std::exception& exc) {
            std::cerr << RED << "Ошибка открытия файла: " << exc.what() << RESET << std::endl;
        }
        int number = 0, write_every = 0;
        while(write_every < 5) {
            std::cin >> number;
            write_to << number << " ";
            write_every++;
        }
        write_to.close();
    }
    void read_or_filter() {
        try {
            read_from.open("numbers.txt");
        } catch (const std::exception& exc) {
            std::cerr << RED << "Ошибка открытия файла: " << exc.what() << RESET << std::endl;
        }
        bool read = 0;
        std::size_t select_operation = 0;
        std::cout << "1) Прочитать числа и вывести сумму\n2) Фильтровать числа на четные" << std::endl;
        std::cout << "Выберите операцию: ";
        std::cin >> select_operation;

        if(select_operation == 1) read = 1;
        if(select_operation != 1 && select_operation != 2) return;


        std::string get_number = "";
        std::size_t sum = 0, filtered_number = 0;

        if(read) {

            while(read_from >> get_number) {
                sum += std::stoi(get_number);
            }

            std::cout << "Сумма всех чисел из файла 'numbers.txt':" << sum << std::endl;
            read_from.close();
            return;
        }

        try {
            write_to.open("even.txt");
        } catch (const std::exception& exc) {
            std::cerr << RED << "Ошибка открытия файла: " << exc.what() << RESET << std::endl;
        }

        while(read_from >> get_number) {
            filtered_number = std::stoi(get_number);
            if(filtered_number % 2 == 0) {
                write_to << filtered_number << " ";
            }
        }

        write_to.close();
    }
    void strings() {
        try {
            write_to.open("input.txt");
            if (!write_to.is_open()) {
                throw std::runtime_error("Не удалось открыть input.txt");
            }
        } catch (const std::exception& exc) {
            std::cerr << RED << "Ошибка открытия файла input.txt: " << exc.what() << RESET << std::endl;
            return;
        }

        std::cin.ignore();
        std::string text = "";
        std::cout << "Напишите текст: ";
        std::getline(std::cin, text);
        write_to << text;
        write_to.close();

        try {
            read_from.open("input.txt");
            if (!read_from.is_open()) {
                throw std::runtime_error("Не удалось открыть input.txt для чтения");
            }
        } catch (const std::exception& exc) {
            std::cerr << RED << "Ошибка открытия файла input.txt: " << exc.what() << RESET << std::endl;
            return;
        }

        int line_count = 0;
        int word_count = 0;
        std::string line;

        while (std::getline(read_from, line)) {
            line_count++;

            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                word_count++;
            }
        }
        read_from.close();

        try {
            write_to.open("output.txt");
            if (!write_to.is_open()) {
                throw std::runtime_error("Не удалось открыть output.txt");
            }
        } catch (const std::exception& exc) {
            std::cerr << RED << "Ошибка открытия файла output.txt: " << exc.what() << RESET << std::endl;
            return;
        }

        write_to << "Количество строк: " << line_count << std::endl;
        write_to << "Количество слов: " << word_count << std::endl;
        write_to.close();

        std::cout << "Результат записан в output.txt" << std::endl;
        std::cout << "Строк: " << line_count << ", Слов: " << word_count << std::endl;
    }
};

void launch() {
    Actions actions;
    std::size_t select_option = 0;

    std::cout << "1) Записать числа\n2) Прочитать числа и вывести сумму или фильтровать числа\n3) Работа с текстом\n" << std::endl;

    while(true) {
        std::cout << "Выберите опцию: " << std::endl;
        std::cin >> select_option;

        switch(select_option) {
        case 1:
            actions.write();
            break;
        case 2:
            actions.read_or_filter();
            break;
        case 3:
            actions.strings();
            break;
        default:
            std::cerr << "Нет такой опции" << std::endl;
            break;
        }

        std::size_t continue_or_not = 0;
        std::cout << "Хотите продолжить работать с файлами, напишите 1, иначе выход из программы" << std::endl;
        std::cin >> continue_or_not;

        if(continue_or_not != 1) break;

    }
}

int main() {
    std::setlocale(LC_ALL,"Rus");
    launch();
    return 0;
}
