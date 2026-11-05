C++
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BankAccount {
protected:
    string fio;
    double summa;
    double stavka;
    double let;

public:
    BankAccount(string f, double s, double st, double l) {
        fio = f;
        summa = s;
        stavka = st;
        let = l;
    }

    virtual ~BankAccount() {}

    virtual double get_total() {
        return summa + (summa * (stavka / 100) * let);
    }

    virtual void print() {
        cout << "Владелец: " << fio << endl;
        cout << "Сумма: " << summa << endl;
        cout << "Ставка: " << stavka << endl;
        cout << "Года: " << let << endl;
        cout << "Итого: " << get_total() << endl;
    }
};

class PrivilegedAccount : public BankAccount {
private:
    double kredit_proc;

public:
    PrivilegedAccount(string f, double s, double st, double l, double kp) 
        : BankAccount(f, s, st, l) {
        kredit_proc = kp;
    }

    double get_total() override {
        double base = BankAccount::get_total();
        return base + (base * (kredit_proc / 100));
    }

    void print() override {
        cout << "--- Привилегированный счет ---" << endl;
        BankAccount::print();
        cout << "Процент кредита: " << kredit_proc << endl;
        cout << "Итого с кредитом: " << get_total() << endl;
    }
};

// Статический полиморфизм (шаблон)
template <typename T>
void print_static(T obj) {
    obj.print();
}

// Динамический полиморфизм
void print_dynamic(BankAccount* acc) {
    acc->print();
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем объекты
    BankAccount acc1("Иванов И.И.", 10000, 5, 2);
    PrivilegedAccount acc2("Петров П.П.", 20000, 7, 3, 15);

    cout << "Простой счет:" << endl;
    acc1.print();
    cout << endl;

    cout << "Привилегированный счет:" << endl;
    acc2.print();
    cout << endl;

    cout << "=== Статический полиморфизм ===" << endl;
    print_static(acc1);
    print_static(acc2);

    cout << "=== Динамический полиморфизм ===" << endl;
    print_dynamic(&acc1);
    print_dynamic(&acc2);

    cout << "=== Вектор указателей ===" << endl;
    vector<BankAccount*> vec;
    vec.push_back(&acc1);
    vec.push_back(&acc2);

    double total_sum = 0;

    for(int i = 0; i < vec.size(); i++) {
        vec[i]->print();
        total_sum += vec[i]->get_total();
        cout << "------------------" << endl;
    }

    cout << "Общая сумма на всех счетах: " << total_sum << endl;

    return 0;
}