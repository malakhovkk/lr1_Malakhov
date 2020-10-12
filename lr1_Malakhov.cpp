// lr1_Malakhov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <regex>
#include <string>
#include <fstream>

using namespace std;


int MAX_ID_CS = 0;
int MAX_ID_PIPE = 0;

struct Pipe
{
    int id;
    float length;
    float diam;
    bool repaired = false;
};

struct CS
{
    int id;
    string name;
    int number;
    int numberOfAvailable;
    float efficiency;
};




bool isNotNegativeFloat(const string &s)
{
    const regex digit_regex("^[\+]?[0-9]+(\,[0-9])?[0-9]*$");
    return regex_match(s, digit_regex);
}

bool isNotNegativeInteger(const string &s)
{
    const regex digit_regex("^[\+]?[0-9]+$");
    return regex_match(s, digit_regex);
    //+5 5 +25 +33 33 
}

float inputNotNegativeFloat(const string &msg)
{
    char str[100];
    bool first = true;
    do {
        if (!first) cout << "Некорректный ввод, введите еще раз >> ";
        cout << msg;
        cin >> str;
        first = false;
    } while (!isNotNegativeFloat(str));
    return atof(str);
}

int inputNotNegativeInteger(const string &msg) 
{
    char str[100];
    bool first = true;
    do
    {
        if (!first) cout << "Некорректный ввод, введите еще раз >> ";
        cout << msg;
        cin >> str;
        first = false;
    } while (!isNotNegativeInteger(str));
    return atoi(str);
}

void AddPipe(vector<Pipe>& vecPipe)
{
    Pipe pipe1;
    pipe1.id = ++MAX_ID_PIPE;
    pipe1.length = inputNotNegativeFloat("Введите длину: ");
    pipe1.diam = inputNotNegativeFloat("Введите диаметр: ");
    vecPipe.push_back(pipe1);
}


void AddCS(vector<CS>& vecCS) 
{
    CS cs1;
    cs1.id = ++MAX_ID_CS;
    cout << "Введите наименование: ";
    cin >> cs1.name;
    cs1.number = inputNotNegativeInteger("Введите количество цехов: ");
    int cur = inputNotNegativeInteger("Введите количество цехов в работе: ");
    while (cur > cs1.number)
    {
        cout << "Введенное число больше количества цехов! ";
        cur = inputNotNegativeInteger("Введите количество цехов в работе: ");
    }
    cs1.numberOfAvailable = cur;
    cs1.efficiency = inputNotNegativeFloat("Введите показатель эффективности: ");
    vecCS.push_back(cs1);
}

void DisplayCS(vector<CS>& vecCS)
{
    int i = 1;
    if (vecCS.size() == 0) cout << "Нет КС!";
    for (auto &it : vecCS)
    {
        cout << "Компрессорная станция №: " << i++ << endl;
        cout << "Наименование: " << it.name << endl;
        cout << "Количество цехов: " << it.number << endl;
        cout << "Количество цехов в работе: " << it.numberOfAvailable << endl;
        cout << "Показатель эффективности: " << it.efficiency << endl << endl;
    }
}

void DisplayPipes(vector<Pipe>& vecPipe)
{

    int i = 1;

    if (vecPipe.size() == 0) cout << "Нет труб!";
    for (auto &it: vecPipe)
    { 
        cout << "Труба №: " << i++ << endl;
        cout << "Длина: " << it.length << endl;
        cout << "Диаметр: " << it.diam << endl;
        cout << (it.repaired ? "В ремонте !" :  "Не в ремонте!");
        cout << endl;
    }
}

void EditPipes(vector<Pipe>& vecPipe)
{
    DisplayPipes(vecPipe);
    int num;
    num = inputNotNegativeInteger("Введите номер трубы: ");
    if (num > vecPipe.size() || num < 0)
    {
        cout << "Такой трубы не существует! ";
    }
    else
    {
        // ДОДЕЛАТЬ
        int isRepaired = inputNotNegativeInteger("Редактирование признака 'в ремонте' для трубы(0 - не в ремонте, 1 - в ремонте): ");
        while (!(isRepaired == 0 || isRepaired == 1))
        {
            isRepaired = inputNotNegativeInteger("Редактирование признака 'в ремонте' для трубы(0 - не в ремонте, 1 - в ремонте): ");
        }
        vecPipe[num - 1].repaired = (bool)isRepaired;

        cout << "Исправленная труба: " << endl;
        cout << "Длина: " << vecPipe[num - 1].length << endl;
        cout << "Диаметр: " << vecPipe[num - 1].diam << endl;
        cout << (vecPipe[num - 1].repaired ? "В ремонте !" : "Не в ремонте!");

        // ВЫВЕСТИ ТРУБУ, КОТОРУЮ ОТРЕДАКТИРОВАЛИ
    }
}

void EditCS(vector<CS>& vecCS) 
{
    DisplayCS(vecCS);
    int num;
    num = inputNotNegativeInteger("Введите номер КС: ");
    if (num > vecCS.size() || num < 0 )
    {
        cout << "Такой станции не существует! ";
    }
    else
    {
        int Add = inputNotNegativeInteger("Запуск и останов цеха в КС(1 - добавить, 0 - остановить): ");
        while (!(Add == 0 || Add == 1))
        {
            Add = inputNotNegativeInteger("Запуск и останов цеха в КС(1 - добавить, 0 - остановить): ");
        }
        int res;
        if (Add == 0)
        {
            res = -1;
        }
        else
        {
            res = 1;
        }

        if (vecCS[num - 1].numberOfAvailable + res >= 0 && vecCS[num - 1].numberOfAvailable + res <= vecCS[num - 1].number)
        {
            vecCS[num - 1].numberOfAvailable += res;

            cout << "Измененная компрессорная станция: " << endl;
            cout << "Наименование: " << vecCS[num - 1].name << endl;
            cout << "Количество цехов: " << vecCS[num - 1].number << endl;
            cout << "Количество цехов в работе: " << vecCS[num - 1].numberOfAvailable << endl;
            cout << "Показатель эффективности: " << vecCS[num - 1].efficiency << endl << endl;

        }
        else
        {
            cout << "Невозможно выполнить действие";
        }
    }
}

void OutputToFile(const vector<CS>& vecCS, const vector<Pipe>& vecPipe)
{
  
    ofstream fout;
    fout.open("output.txt");
    int i = 1;
    if (vecCS.size() == 0) fout << "Нет КС!";
    for (auto& it : vecCS)
    {
        fout << "Компрессорная станция №: " << i++ << endl;
        fout << "Наименование: " << it.name << endl;
        fout << "Количество цехов: " << it.number << endl;
        fout << "Количество цехов в работе: " << it.numberOfAvailable << endl;
        fout << "Показатель эффективности: " << it.efficiency << endl << endl;
    }
   

    if (vecPipe.size() == 0) fout << "Нет труб!";
    for (auto& it : vecPipe)
    {
        fout << "Труба №: " << i++ << endl;
        fout << "Длина: " << it.length << endl;
        fout << "Диаметр: " << it.diam << endl;
        fout << (it.repaired ? "В ремонте !" : "Не в ремонте!");
        fout << endl;
    }
    cout << "Вывели трубы и КС в файл output.txt";

    fout.close();
}

void InputFromFile( vector<CS>& vecCS,  vector<Pipe>& vecPipe)
{
    ifstream fin("input.txt");
    if (!fin.is_open()) 
        cout << "Файл не может быть открыт!\n"; 
    else
    {
        vecPipe.clear();
        MAX_ID_PIPE = 0;
        vecCS.clear();
        MAX_ID_CS = 0;
        Pipe pipe1;
        CS cs1;
        string buff;
        while (fin >> buff)
        {
            if (buff == "pipe")
            {
                pipe1.id = ++MAX_ID_PIPE;
                fin >> pipe1.length;
                fin >> pipe1.diam;
                vecPipe.push_back(pipe1);
            }
            else
            {
                CS cs1;
                cs1.id = ++MAX_ID_CS;
                fin >> cs1.name;
                fin >> cs1.number;
                fin >> cs1.numberOfAvailable;
                fin >> cs1.efficiency;
                vecCS.push_back(cs1);
            }
        }
    }
    cout << "Ввели из файла данные";
    fin.close();
}

int main()
{


    setlocale(LC_ALL, "Russian");
    vector<CS> vecCS;
    vector<Pipe> vecPipe;
    for (;;)
    {
        system ("CLS");
        int command;
        cout << "1. Добавить трубу" << endl <<
            "2. Добавить КС" << endl <<
            "3. Просмотр всех объектов" << endl <<
            "4. Редактировать трубу" << endl <<
            "5. Редактировать КС" << endl <<
            "6. Сохранить" << endl <<
            "7. Загрузить" << endl <<
            "0. Выход" << endl;
        command = inputNotNegativeInteger("Введите номер команды: ");
        while (command > 7)
        {
            cout << "Введенное число больше 7! ";
            command = inputNotNegativeInteger("Введите номер команды: ");
        }

        switch (command)
        {
            case 1:
            {
                AddPipe(vecPipe);
                break;
            }
            case 2:
            {
                AddCS(vecCS);
                break;
            }
            case 3:
            {
                DisplayCS(vecCS);
                DisplayPipes(vecPipe);
                system("pause");
                break;
            }
            case 4:
            {
                EditPipes(vecPipe);
                system("pause");
                // Доделать
                break;
            }
            case 5:
            {
                EditCS(vecCS);
                system("pause");
                break;
            }
            case 6:
            {
                OutputToFile(vecCS, vecPipe);
                system("pause");
                break;
            }
            case 7:
            {
                InputFromFile(vecCS, vecPipe);
                system("pause");
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
                break;
        }
    }
}





// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
