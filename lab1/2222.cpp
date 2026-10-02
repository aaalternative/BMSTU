#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// Структура "Адрес"
struct Address {
    std::string street; // Улица
    int house_number;   // Номер дома
    int flat_number;    // Номер квартиры
};

// Структура "Житель"
struct Resident {
    std::string full_name; // ФИО
    Address address;       // Переменная структурного типа "Адрес"
    std::string gender;    // Пол ("мужской" или "женский")
    int age;               // Возраст
};

int main() {
    // Настройка локализации для корректного вывода и ввода кириллицы
    std::setlocale(LC_ALL, "Russian");

    int n;
    std::cout << "Vvidite kolichestvo zhitelei (n): ";
    std::cin >> n;

    // Используем vector для динамического массива структурного типа
    std::vector<Resident> residents(n);

    // Ввод исходных данных
    for (int i = 0; i < n; ++i) {
        std::cout << "\n-- Vvod dannih dlya zhitelya№" << i + 1 << " ---\n";
        std::cin.ignore(); // Очистка буфера после cin >>

        std::cout << "FIO: ";
        std::getline(std::cin, residents[i].full_name);

        std::cout << "Ylica: ";
        std::getline(std::cin, residents[i].address.street);

        std::cout << "Dom: ";
        std::cin >> residents[i].address.house_number;

        std::cout << "Nomer kv: ";
        std::cin >> residents[i].address.flat_number;

        std::cout << "Man/Woman: ";
        std::cin >> residents[i].gender;

        std::cout << "Age: ";
        std::cin >> residents[i].age;
    }

    // Вывод введенных данных для контроля ввода
    std::cout << "\n================ Dannie ================\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Zhitel №" << i + 1 << ": " << residents[i].full_name
                  << " | Adress " << residents[i].address.street
                  << ", Dom " << residents[i].address.house_number
                  << ", Kv " << residents[i].address.flat_number
                  << " | Pol: " << residents[i].gender
                  << " | Age: " << residents[i].age << "\n";
    }
    std::cout << "================================================\n\n";

    // Обработка запроса (Вариант 14)
    // Используем словарь (map) для группировки подсчета по каждой уникальной улице
    std::map<std::string, int> street_men_count;

    for (int i = 0; i < n; ++i) {
        // Условие: мужской пол И старше 18 И младше 60 лет
        if ((residents[i].gender == "man" || residents[i].gender == "woman") &&
            residents[i].age > 18 && residents[i].age < 60) {

            // Увеличиваем счетчик для конкретной улицы
            street_men_count[residents[i].address.street]++;
        }
    }

    // Вывод результатов
    std::cout << "--- Rezultati ---\n";
    if (street_men_count.empty()) {
        std::cout << "Man na odnoi ylice ot 18 do 60.\n";
    } else {
        std::cout << "Kolichestvo chelovek (ot 19 do 59 age) po ylicam:\n";
        for (const auto& pair : street_men_count) {
            std::cout << "Ylica \"" << pair.first << "\": " << pair.second << " chelovek.\n";
        }
    }

    return 0;
}