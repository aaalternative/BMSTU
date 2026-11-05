#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Структура "подразделение организации" (Вариант 14)
struct Department {
    string name;
    string manager;
    int total_employees;
    int employees_on_vacation;
};

// Функция для записи вектора структур в файл
void writeToFile(const vector<Department>& deps, const string& filename, bool isBinary) {
    if (isBinary) {
        ofstream out(filename, ios::binary);
        if (!out) { cout << "Ошибка записи!" << endl; return; }
        int size = deps.size();
        out.write((char*)&size, sizeof(size));
        for (const auto& d : deps) {
            int nameLen = d.name.size();
            out.write((char*)&nameLen, sizeof(nameLen));
            out.write(d.name.c_str(), nameLen);
            
            int managerLen = d.manager.size();
            out.write((char*)&managerLen, sizeof(managerLen));
            out.write(d.manager.c_str(), managerLen);
            
            out.write((char*)&d.total_employees, sizeof(d.total_employees));
            out.write((char*)&d.employees_on_vacation, sizeof(d.employees_on_vacation));
        }
        cout << "Записано в бинарный файл." << endl;
    } else {
        ofstream out(filename);
        if (!out) { cout << "Ошибка записи!" << endl; return; }
        out << deps.size() << "\n";
        for (const auto& d : deps) {
            out << d.name << "\n" << d.manager << "\n" 
                << d.total_employees << " " << d.employees_on_vacation << "\n";
        }
        cout << "Записано в текстовый файл." << endl;
    }
}

// Функция для чтения вектора структур из файла
vector<Department> readFromFile(const string& filename, bool isBinary) {
    vector<Department> deps;
    if (isBinary) {
        ifstream in(filename, ios::binary);
        if (!in) { cout << "Ошибка чтения!" << endl; return deps; }
        int size;
        if (in.read((char*)&size, sizeof(size))) {
            deps.resize(size);
            for (int i = 0; i < size; ++i) {
                int len;
                in.read((char*)&len, sizeof(len));
                deps[i].name.resize(len);
                in.read((char*)&deps[i].name[0], len);
                
                in.read((char*)&len, sizeof(len));
                deps[i].manager.resize(len);
                in.read((char*)&deps[i].manager[0], len);
                
                in.read((char*)&deps[i].total_employees, sizeof(deps[i].total_employees));
                in.read((char*)&deps[i].employees_on_vacation, sizeof(deps[i].employees_on_vacation));
            }
        }
    } else {
        ifstream in(filename);
        if (!in) { cout << "Ошибка чтения!" << endl; return deps; }
        int size;
        if (in >> size) {
            in.ignore();
            deps.resize(size);
            for (int i = 0; i < size; ++i) {
                getline(in, deps[i].name);
                getline(in, deps[i].manager);
                in >> deps[i].total_employees >> deps[i].employees_on_vacation;
                in.ignore();
            }
        }
    }
    return deps;
}

// Функция для вывода размера файла
void printFileSize(const string& filename) {
    ifstream in(filename, ios::binary | ios::ate);
    if (in) {
        cout << "Размер '" << filename << "': " << in.tellg() << " байт." << endl;
    } else {
        cout << "Не удалось узнать размер файла." << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Использование:\n"
             << "-w text/bin <имя_файла> (запись)\n"
             << "-r text/bin <имя_файла> (чтение)\n"
             << "-compare <txt> <bin> (сравнение размеров)\n";
        return 1;
    }

    string mode = argv[1];
    string type = argv[2];
    string filename = argv[3];

    if (mode == "-w") {
        vector<Department> deps = {
            {"Отдел разработки", "Иванов И.И.", 50, 5},
            {"Бухгалтерия", "Петрова А.С.", 10, 2},
            {"Отдел кадров", "Сидоров В.В.", 5, 0}
        };
        writeToFile(deps, filename, type == "bin");
    } 
    else if (mode == "-r") {
        vector<Department> deps = readFromFile(filename, type == "bin");
        for (const auto& d : deps) {
            cout << d.name << " | " << d.manager << " | Всего: " << d.total_employees << " | В отпуске: " << d.employees_on_vacation << endl;
        }
    }
    else if (mode == "-compare") {
        printFileSize(type);     // type = txt_file
        printFileSize(filename); // filename = bin_file
    }

    return 0;
}
