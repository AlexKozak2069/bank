#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Структура для користувачів банку
struct Users {
    string name;
    string phonenumber;
    string password;
    string birthdate;
    string cardNumber;
    vector<string> accounts;
};

// Структура для адміністраторів банку
struct AdminStr {
    string adminame;
    string adminpassword;
};

// Клас для роботи з меню користувача
class Menu {
public:
    void showMenu() {
        string response;
        do {
            cout << "Бажаєте побачити меню нашого банку? (Так/Ні): ";
            cin >> response;
            tolower(response[0]); // переведення першого символу у нижній регістр

            if (response == "так") {
                displayOptions();
            }
            else if (response != "ні") {
                cout << "Невірна відповідь. Спробуйте ще раз." << endl;
            }
        } while (response != "ні");
    }
private:
    int choice;
    string card;
    string account;
    string limit;
    string number;

    void displayOptions() {
        do {
            cout << "0) Огляд балансу" << endl;
            cout << "1) Переказ коштів на інший рахунок" << endl;
            cout << "2) Оплата рахунків" << endl;
            cout << "3) Управління лімітами транзакцій" << endl;
            cout << "4) Оновлення особистих даних або пароля" << endl;
            cout << "5) Контактна інформація банку" << endl;
            cout << "6) Зв'язок з представником банку" << endl;
            cout << "7) Вихід з меню" << endl;
            cout << "Виберіть розділ меню (0-7): ";
            cin >> choice;
            switch (choice) {
            case 0:
                cout << "Ваш баланс: ****" << endl;
                break;
            case 1:
                cout << "На який номер карти буде здійснений переказ?" << endl;
                cin >> card;
                cout << "Переказ здійснений, дякую!" << endl;
                break;
            case 2:
                cout << "На який рахунок буде здійснений переказ?" << endl;
                cin >> account;
                cout << "Переказ здійснений, дякую!" << endl;
                break;
            case 3:
                cout << "Який ліміт хочете встановити?" << endl;
                cin >> limit;
                cout << "Ліміт встановлено." << endl;
                break;
            case 4:
                cout << "Оновлення особистих даних або пароля" << endl;
                break;
            case 5:
                cout << "Номер телефону: +380501234567" << endl;
                cout << "Номер електронної пошти: bankio2024@gmail.com" << endl;
                break;
            case 6:
                cout << "На який номер вам подзвонити?" << endl;
                cin >> number;
                cout << "Ми вам скоро зателефонуємо." << endl;
                break;
            case 7:
                cout << "Дякую за використання наших послуг!" << endl;
                exit(0);
                break;
            default:
                cout << "Невірний вибір. Спробуйте знову." << endl;
                cin.clear(); // очистка помилки
                cin.ignore(1000, '\n'); // очистка введеного рядка
                break;
            }
        } while (false); // нескінченний цикл до вибору виходу
    }
};

// Клас для користувача
class User {
public:
    static vector<Users> user_db;

    bool login() {
        string phoneNumber;
        string password;

        cout << "Бажаєте увійти в акаунт? (Так/Ні)" << endl;
        string loginChoice;
        cin >> loginChoice;

        // Переводимо вхідну відповідь до нижнього регістру
        for (char& c : loginChoice) {
            c = tolower(c);
        }

        while (loginChoice == "так") {
            cout << "Введіть номер телефону +38";
            cin >> phoneNumber;
            cout << "Введіть пароль: ";
            cin >> password;

            // Перевірка введених даних з даними реєстрації
            for (const auto& user : User::user_db) {
                if (user.phonenumber == phoneNumber && user.password == password) {
                    cout << "Вхід успішний!" << endl;
                    // Викликаємо функцію показу меню тут
                    Menu m;
                    m.showMenu();

                    return true;
                }
            }
            cout << "Невірні дані! Спробуйте ще раз (Так/Ні): ";
            cin >> loginChoice;

            // Переводимо вхідну відповідь до нижнього регістру
            for (char& c : loginChoice) {
                c = tolower(c);
            }
        }
        cout << "Для продовження потрібно зареєструватися." << endl;
        return false;
    }

    void saveUsersToFile(const string& filename) {
        ofstream file(filename); // Відкриваємо файл для запису
        if (file.is_open()) {
            for (const auto& user : user_db) {
                file << user.name << "," << user.phonenumber << "," << user.password << "," << user.birthdate << "," << user.cardNumber << "\n";
            }
            cout << "Користувачі збережені у файлі " << filename << endl;
            file.close(); // Закриваємо файл після запису
        }
        else {
            cout << "Помилка: не вдалося відкрити файл для запису." << endl;
        }
    }
    void loadUsersFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, phonenumber, password, birthdate, cardNumber;
                getline(ss, name, ',');
                getline(ss, phonenumber, ',');
                getline(ss, password, ',');
                getline(ss, birthdate, ',');
                getline(ss, cardNumber, ',');
                Users user = { name, phonenumber, password, birthdate, cardNumber, {} };
                user_db.push_back(user);
            }
            file.close(); // Закриваємо файл після завантаження
        }
        else {
            cout << "Помилка: не вдалося відкрити файл для читання." << endl;
        }
    }
    // Додано функції для редагування та видалення користувача
    void editUser(const string& phoneNumber) {
        for (auto& user : user_db) {
            if (user.phonenumber == phoneNumber) {
                cout << "Введіть нове ім'я: ";
                cin >> user.name;
                cout << "Введіть новий пароль: ";
                cin >> user.password;
                cout << "Введіть нову дату народження: ";
                cin >> user.birthdate;
                cout << "Дані користувача оновлено." << endl;
                return;
            }
        }
        cout << "Користувача з таким номером телефону не знайдено." << endl;
    }
    void deleteUser(const string& phoneNumber) {
        for (auto it = user_db.begin(); it != user_db.end(); ++it) {
            if (it->phonenumber == phoneNumber) {
                user_db.erase(it);
                cout << "Користувача видалено." << endl;
                return;
            }
        }
        cout << "Користувача з таким номером телефону не знайдено." << endl;
    }
};
class Sort {
public:
    static string convertBirthdate(const string& birthdate) {
        string day = birthdate.substr(0, 2);
        string month = birthdate.substr(3, 2);
        string year = birthdate.substr(6, 4);
        return year + month + day;
    }
    static bool compareBirthdates(const Users& a, const Users& b) {
        return convertBirthdate(a.birthdate) < convertBirthdate(b.birthdate);
    }
    void printSortedUsers() {
        vector<Users> sorted_users = User::user_db;
        sort(sorted_users.begin(), sorted_users.end(), Sort::compareBirthdates);
        for (const auto& user : sorted_users) {
            cout << "Ім'я: " << user.name << ", Дата народження: " << user.birthdate << endl;
        }
    }
};
// Клас для адміністратора
class Admin {
public:
    static vector<AdminStr> admins_db;
    void menuAdmin() {
        int otvetAdmin;
        while (true) {
            cout << "0) Список користувачів" << endl;
            cout << "1) Видалення або редагування користувача" << endl;
            cout << "2) Змінити ліміт транзакцій" << endl;
            cout << "3) Зв'язок з користувачем" << endl;
            cout << "4) Вивести звіт по датам народження" << endl;
            cout << "-1) Вихід" << endl;
            cout << "Виберіть розділ меню (-1, 0-4): ";
            cin >> otvetAdmin;
            if (otvetAdmin == -1) {
                cout << "Вихід з меню адміністратора." << endl;
                break;
            }
            switch (otvetAdmin) {
            case 0:
                cout << "Список користувачів:" << endl;
                cout << "Кількість користувачів: " << User::user_db.size() << endl;
                for (const auto& user : User::user_db) {
                    cout << "Ім'я: " << user.name << ", Номер телефона: " << user.phonenumber << ", Пароль: " << user.password << ", Дата народження: " << user.birthdate << ", Номер карти: " << user.cardNumber << endl;
                }
                break;
            case 1: {
                string phoneNumber;
                cout << "Введіть номер телефону користувача для редагування або видалення: ";
                cin >> phoneNumber;
                int action;
                cout << "Виберіть дію (1 - редагувати, 2 - видалити): ";
                cin >> action;
                User user;
                if (action == 1) {
                    user.editUser(phoneNumber);
                }
                else if (action == 2) {
                    user.deleteUser(phoneNumber);
                }
                else {
                    cout << "Невірна дія." << endl;
                }
                break;
            }
            case 2:
                cout << "Який ліміт бажаєте встановити ?" << endl;
                int limit;
                cin >> limit;
                cout << "Ліміт встановленно" << endl;
                break;
            case 3:
                cout << "Функція зв'язку з користувачем недоступна." << endl;
                break;
            case 4:
                Sort s;
                s.printSortedUsers();
                break;
            default:
                cout << "Невірний вибір. Спробуйте знову." << endl;
                break;
            }
        }
    }
    void saveAdminsToFile(const string& filename) {
        ofstream file(filename); // Відкриваємо файл для запису

        if (file.is_open()) {
            for (const auto& admin : admins_db) {
                file << admin.adminame << "," << admin.adminpassword << "\n";
            }
            cout << "Адміністратори збережені у файлі " << filename << endl;
            file.close(); // Закриваємо файл після запису
        }
        else {
            cout << "Помилка: не вдалося відкрити файл для запису." << endl;
        }
    }
    void loadAdminsFromFile(const string& filename) {
        ifstream file(filename);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string adminame, adminpassword;
                getline(ss, adminame, ',');
                getline(ss, adminpassword, ',');
                AdminStr admin = { adminame, adminpassword };
                admins_db.push_back(admin);
            }
            file.close(); // Закриваємо файл після завантаження
        }
        else {
            cout << "Помилка: не вдалося відкрити файл для читання." << endl;
        }
    }
};
vector<AdminStr> Admin::admins_db; // Ініціалізація статичного списку адміністраторів
vector<Users> User::user_db; // Ініціалізація статичного списку користувачів
// Клас для привітання та реєстрації
class Vhid {
public:
    Vhid() {
        cout << "\n Доброго дня, Вас вітає банк ЄО!" << endl;
    }
    void Zapros() {
        string voprosAdmin;
        bool validInput = false;

        while (!validInput) {
            cout << "Реєстрація буде від імені адміна чи користувача? (a - адмін, k - користувач)" << endl;
            cin >> voprosAdmin;
            if (voprosAdmin == "a" || voprosAdmin == "A" || voprosAdmin == "а" || voprosAdmin == "А") {
                AdminStr newAdmin;
                cout << "Введіть ваше ім'я: ";
                cin >> newAdmin.adminame;
                cout << "Введіть пароль: ";
                cin >> newAdmin.adminpassword;
                Admin::admins_db.push_back(newAdmin);
                cout << "Адміністратор успішно увійшов." << endl;
                Admin a;
                a.menuAdmin(); // Викликати метод menuAdmin з об'єкта Admin
                validInput = true; // Завершити цикл при успішному введенні
            }
            else if (voprosAdmin == "k" || voprosAdmin == "K" || voprosAdmin == "к" || voprosAdmin == "К") {
                registerUser(); // Викликаємо функцію реєстрації користувача
                User u;
                u.login();
                validInput = true; // Завершити цикл при успішному введенні
            }
            else {
                cout << "Невірний вибір. Спробуйте ще раз." << endl;
            }
        }
    }
private:
    // Функція реєстрації користувача
    void registerUser() {
        string phoneNumber;
        cout << "Введіть номер телефону +38";
        cin >> phoneNumber;
        // Перевіряємо, чи користувач з таким номером вже існує
        for (const auto& user : User::user_db) {
            if (user.phonenumber == phoneNumber) {
                cout << "Користувач з таким номером телефону вже існує. Будь ласка, використайте інший номер." << endl;
                return; // Виходимо з функції, не додаючи нового користувача
            }
        }
        Users newUser; // Оголошення нового користувача
        // Цикл, щоб дату народження вводили до введення коректних даних
        while (true) {
            cout << "Введіть дату народження (у форматі день.місяць.рік): ";
            cin >> newUser.birthdate; // Зчитуємо дату народження
            // Перевіряємо правильність формату дати
            int day, month, year;
            char dot;
            stringstream ss(newUser.birthdate);
            ss >> day >> dot >> month >> dot >> year;
            if (ss.fail() || dot != '.' || ss.peek() != EOF) {
                cout << "Некоректний формат дати. Будь ласка, введіть дату у форматі день.місяць.рік." << endl;
                continue;
            }
            // Перевірка на правильність введених дат
            if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
                cout << "Некоректна дата народження. Будь ласка, перевірте правильність введених даних." << endl;
                continue;
            }
            // Якщо дата введена коректно, виходимо з циклу
            break;
        }
        cout << "Введіть ваше ім'я: ";
        cin >> newUser.name;
        newUser.phonenumber = phoneNumber; // Зберігаємо номер телефону
        cout << "Введіть пароль: ";
        cin >> newUser.password;
        // Генеруємо випадковий номер карти
        newUser.cardNumber = generateRandomCardNumber();
        newUser.accounts.push_back(newUser.cardNumber);
        User::user_db.push_back(newUser); // Додати користувача до вектора
        cout << "Користувач успішно зареєстрований." << endl;
    }
    string generateRandomCardNumber() {
        string cardNumber = "4"; // Початкові 4 цифри для Visa
        for (int i = 0; i < 15; ++i) {
            cardNumber += to_string(rand() % 10); // Додаємо випадкові цифри
        }
        return cardNumber;
    }
};
// Головна функція програми
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(nullptr)); // Ініціалізуємо генератор випадкових чисел
    User user;
    user.loadUsersFromFile("users.txt");
    Admin admin;
    admin.loadAdminsFromFile("admins.txt");
    Vhid vh;
    vh.Zapros();

    // Зберегти користувачів та адміністраторів у файли перед закриттям програми
    user.saveUsersToFile("users.txt");
    admin.saveAdminsToFile("admins.txt");
    return 0;
}
