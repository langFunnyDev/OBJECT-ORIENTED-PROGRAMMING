#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define DB_FileName "employers.db"

std::ifstream ReadDB;
std::ofstream WriteDB;

class employer{
private:
    std::string _surname;
    std::string _name;
    std::string _patronymic;
    std::string _position;
    int _age;
    int _salary;

public:
    employer(const std::string surname, const std::string name, const std::string patronymic,
             const std::string position, int age, int salary) : _surname(surname), _name(name),
                                                                 _patronymic(patronymic), _position(position),
                                                                 _age(age), _salary(salary) {}

    const std::string &getSurname() const {
        return _surname;
    }

    const std::string &getName() const {
        return _name;
    }

    const std::string &getPatronymic() const {
        return _patronymic;
    }

    const std::string &getPosition() const {
        return _position;
    }

    int getAge() const {
        return _age;
    }

    int getSalary() const {
        return _salary;
    }
};

std::vector <employer> office;

float average(std::vector <employer> &v){
    int sum = 0;
    for (auto & i : v) {
        sum += i.getSalary();
    }
    return (float) sum / (float) v.size();
}

void readDB(){
    std::string surname;
    std::string name;
    std::string patronymic;
    std::string position;
    int age;
    int salary;

    ReadDB.open(DB_FileName);
    if(!ReadDB.is_open()) {
        WriteDB.open(DB_FileName);
        if (!WriteDB.is_open()) return;
    }
    if(ReadDB.peek() != EOF) {
        do{
            ReadDB >> surname >> name >> patronymic >> age >> position >> salary;
            office.emplace_back(employer(surname, name, patronymic, position, age, salary));
        } while (!ReadDB.eof());
    }
    ReadDB.close();
}

void updateDB(){
    WriteDB.open(DB_FileName);
    if (!WriteDB.is_open()) return;
    for (int i = 0; i < office.size(); ++i) {
        WriteDB << office[i].getSurname() << " " << office[i].getName() << " " << office[i].getPatronymic() << " " << office[i].getAge() << " " << office[i].getPosition() << " " << office[i].getSalary();
        if (i != office.size() - 1) WriteDB << " ";
    }
    WriteDB.close();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int state = 0;

    readDB();

    std::cout << "Вас приветствует система учета сотрудников." << std::endl;
    do {
        std::cout << "Выберите действие:" << std::endl
        << "    1) Добавить нового сотрудника в офис" << std::endl
        << "    2) Просмотреть список сотрудников" << std::endl
        << "    3) Просмотреть данные о конкретном сотруднике (по его id)" << std::endl
        << "    4) Просмотреть данные о конкретном сотруднике (по его фамилии)" << std::endl
        << "    5) Подсчитать среднюю заработную плату по офису" << std::endl
        << "    6) Удалить сотрудника" << std::endl << std::endl
        << "    -1) Завершить работу с программой" << std::endl
        << "Для выбора действия введите число соответствующее его номеру: ";
        std::cin >> state;
        std::string surname;
        std::string name;
        std::string patronymic;
        std::string position;
        int age;
        int salary;
        int id = -1;
        switch (state) {
            case 1:

                std::cout << "Вы выбрали функция добавления нового сотрудника. Теперь вам необходимо ввести его данные." << std::endl;
                std::cout << "    Фамилия: "; std::cin >> surname;
                std::cout << "    Имя: "; std::cin >> name;
                std::cout << "    Отчество: "; std::cin >> patronymic;
                std::cout << "    Возраст: "; std::cin >> age;
                std::cout << "    Должность: "; std::cin >> position;
                std::cout << "    Заработная плата: "; std::cin >> salary;
                office.emplace_back(surname, name, patronymic, position, age, salary);
                std::cout << "Вы успешно добавили нового сотрудника." << std::endl;
                updateDB();
                break;
            case 2:
                if (office.empty()) {
                    std::cout << "В офисе пусто :(" << std::endl;
                } else {
                    std::cout << "В офисе работают следующие люди:" << std::endl;
                    for (int i = 0; i < office.size(); ++i) {
                        std::cout << "    " << i+1 << ") " << office[i].getSurname() << " " << office[i].getName() << " " << office[i].getPatronymic() << std::endl;
                    }
                }
                break;
            case 3:
                std::cout << "Для поиска сотрудника введите его ID: "; std::cin >> id;
                std::cout << "    " << id << ") " << office[id-1].getSurname() << " " << office[id-1].getName() << " " << office[id-1].getPatronymic() << std::endl;
                std::cout << "    " << "    " << "Возраст: " << office[id-1].getAge() << std::endl;
                std::cout << "    " << "    " << "Должность: " << office[id-1].getPosition() << std::endl;
                std::cout << "    " << "    " << "Заработная плата: " << office[id-1].getSalary() << std::endl;
                break;
            case 4:
                std::cout << "Для поиска сотрудника введите его фамилию: "; std::cin >> surname;
                for (int i = 0; i < office.size(); ++i) {
                    if (surname == office[i].getSurname()) id = i + 1;
                }
                if (id != -1){
                    std::cout << "    " << id << ") " << office[id-1].getSurname() << " " << office[id-1].getName() << " " << office[id-1].getPatronymic() << std::endl;
                    std::cout << "    " << "    " << "Возраст: " << office[id-1].getAge() << std::endl;
                    std::cout << "    " << "    " << "Должность: " << office[id-1].getPosition() << std::endl;
                    std::cout << "    " << "    " << "Заработная плата: " << office[id-1].getSalary() << std::endl;
                } else {
                    std::cout << "Сожалеем, сотрудника с такой фамилией не существует." << std::endl;
                }
                break;
            case 5:
                std::cout << "Средняя зарплата по офису составляет: " << average(office) << " руб." << std::endl;
                break;
            case 6:
                std::cout << "Для удаления сотрудника введите его ID и фамилию (через пробел): "; std::cin >> id >> surname;
                if(office[id - 1].getSurname() == surname) office.erase(office.begin() + id - 1);
                std::cout << "Сотрудник успешно удалён.";
                updateDB();
                break;
            default:
                break;
        }
    } while (state != -1);
    return 0;
}
