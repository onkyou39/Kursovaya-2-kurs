#define NOMINMAX

#include <locale>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <Windows.h>

void readFile(std::string filename);
void writeFile(std::string filename);
void changeElement(unsigned int num);
void getElement(unsigned int num);
void delElement(unsigned int num);
void addElement();
unsigned int getNonEmptyNumAmount();
unsigned int getStrAmount();
void printDB();

struct People
{
	bool isFree = true;
	unsigned int logicNumber = 1;
	std::string telNumber;
	std::string name;
	std::string adress;
};
std::vector<People> database;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string filename = "Database.txt";
	std::cout << "Введите имя файла или путь к файлу для работы:\n";
	std::cin >> filename;
	enum Menu
	{
		Exit, //выход из программы
		Create, //создание массива структур из данных текстового файла
		Change, //изменение значения элемента с заданным (логическим) номером
		Get_value, //получение значения элемента матрицы с заданным логическим номером
		Delete, //удаление элемента с заданным логическим номером
		Add, //добавление элемента в массив 
		Get_non_empty, //получение текущего количества занятых элементов
		Get_str_num, //получение текущего количества строк
		Print, //вывод массива структур на экран
		Write //запись занятых элементов структур в текстовый файл
	};
	unsigned short menuSwitch;
	do
	{
		std::cout << "\nВыберите режим работы программы:" << std::endl;
		std::cout << "1 - создание массива структур из данных текстового файла" << std::endl;
		std::cout << "2 - изменение значения элемента с заданным (логическим) номером" << std::endl;
		std::cout << "3 - получение значения элемента матрицы с заданным логическим номером" << std::endl;
		std::cout << "4 - удаление элемента с заданным логическим номером" << std::endl;
		std::cout << "5 - добавление элемента в массив" << std::endl;
		std::cout << "6 - получение текущего количества занятых элементов" << std::endl;
		std::cout << "7 - получение текущего количества строк" << std::endl;
		std::cout << "8 - вывод массива структур на экран" << std::endl;
		std::cout << "9 - запись занятых элементов структур в текстовый файл" << std::endl;
		std::cout << "0 - выход из программы" << std::endl;
		std::cin >> menuSwitch;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Выбор в меню осуществляется только цифрами от 0 до 9" << std::endl;
			continue;
		}
		unsigned int num;
		switch (menuSwitch)
		{
		case Menu::Create:
			readFile(filename);
			break;
		case Menu::Change:
			std::cout << "Введите номер элемента, значение которого вы хотите изменить: ";
			std::cin >> num;
			changeElement(num);
			break;
		case Menu::Get_value:
			std::cout << "Введите номер элемента, значение которого вы хотите получить: ";
			std::cin >> num;
			getElement(num);
			break;
		case Menu::Delete:
			std::cout << "Введите номер элемента, который вы хотите удалить: ";
			std::cin >> num;
			delElement(num);
			break;
		case Menu::Add:
			addElement();
			break;
		case Menu::Get_non_empty:
			std::cout << "В массиве " << getNonEmptyNumAmount() << " занятых элементов" << std::endl;
			break;
		case Menu::Get_str_num:
			std::cout << "В массиве " << getStrAmount() << " строк" << std::endl;
			break;
		case Menu::Print:
			printDB();
			break;
		case Menu::Write:
			writeFile(filename);
			break;
		case Menu::Exit:
			return 0;
		default:
			std::cout << "Допускаются только цифры от 0 до 9" << std::endl;
			break;
		}
	} while (menuSwitch != 0);
	return 0;
}
void readFile(std::string filename)
{
	std::ifstream file;
	try
	{
		file.open(filename);
		if (!file) throw std::invalid_argument("error opening file");
		People tmp;
		tmp.logicNumber = 0;
		std::string tmpstr;
		while (true)
		{
			if (!std::getline(file, tmpstr, '|')) break;
			tmp.isFree = std::stoi(tmpstr);
			std::getline(file, tmpstr, '|');
			tmp.logicNumber = std::stoi(tmpstr);
			std::getline(file, tmpstr, '|');
			tmp.telNumber = tmpstr;
			std::getline(file, tmpstr, '|');
			tmp.name = tmpstr;
			std::getline(file, tmpstr, '\n');
			tmp.adress = tmpstr;
			database.push_back(tmp);
		}
		file.close();
		std::cout << "Успешное чтение из файла " << filename << std::endl;
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
void writeFile(std::string filename)
{
	std::ofstream file;
	try
	{
		file.open(filename);
		if (!file) throw std::invalid_argument("error opening file");
		for (int i = 0; i < database.size(); i++)
		{
			file << database[i].isFree << "|" << database[i].logicNumber << "|" << database[i].telNumber << "|" << database[i].name << "|" << database[i].adress << std::endl;
		}
		file.close();
		std::cout << "Успешная запись в файл " << filename << std::endl;
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
void changeElement(unsigned int num)
{
	if (database.size() != 0)
	{
		for (int i = 0; i < database.size(); i++)
		{
			if (database[i].logicNumber == num)
			{
				database[i].isFree = true;
				std::cout << "Предыдущее значеие элемента с номером " << num << std::endl;
				std::cout << database[i].isFree << "|" << database[i].logicNumber << "|" << database[i].telNumber << "|" << database[i].name << "|" << database[i].adress << std::endl;
				std::cout << "\nВведите новое значение элемента" << std::endl;
				std::cout << "ФИО: ";
				std::getline(std::cin, database[i].name);
				std::cout << "Адрес: ";
				std::cin.ignore();
				std::getline(std::cin, database[i].adress);
				std::cin.ignore();
				std::cout << "Номер телефона: ";
				std::getline(std::cin, database[i].telNumber);
				std::cout << "Данные успешно изменены" << std::endl;
			}
			break;
		}
	}
	else std::cout << "Массив структур пуст" << std::endl;
	
}
void getElement(unsigned int num)
{
	std::cout << std::endl;
	for (int i = 0; i < database.size(); i++)
	{
		if (database[i].logicNumber == num)
		{
			std::cout << database[i].logicNumber << "|" << database[i].telNumber << "|" << database[i].name << "|" << database[i].adress << std::endl;
			break;
		}
	}
}
void delElement(unsigned int num)
{
	std::cout << std::endl;
	for (int i = 0; i < database.size(); i++)
	{
		if (database[i].logicNumber == num)
		{
			database[i].isFree = true;
			break;
		}
	}
	std::cout << "Элемент с номером " << num << " успешно удалён" << std::endl;
}
void addElement()
{
	std::cout << "\nРежим добавления элемента\n";
	for (int i = 0; i < database.size(); i++) //сжатие массива
	{
		if (database[i].isFree)
		{
			database.erase(database.begin() + i);
		}
	}
	People tmp;
	bool switch_on = true;
	while (switch_on)
	{
		std::cout << "Введите номер операции, 1 - добавить элемент, 0 - выход из цикла\n";
		std::cin >> switch_on;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Допускаются только цифры от 0 до 1\n" << std::endl;
			continue;
		}
		std::string input;
		int last; //индекс последнего элемента массива
		switch (switch_on)
		{
		case 1:
			std::cin.ignore();
			std::cout << "ФИО: ";
			std::getline(std::cin, tmp.name);
			std::cout << "Адрес: ";
			//std::cin.ignore();
			std::getline(std::cin, tmp.adress);
			//std::cin.ignore();
			std::cout << "Номер телефона: ";
			std::getline(std::cin, tmp.telNumber);
			last = database.size() - 1; //последний элемент массива
			if (database.size() != 0) tmp.logicNumber = database[last].logicNumber + 1;
			tmp.isFree = false;
			database.push_back(tmp);
			break;
		default:
			break;
		}
	}
}
unsigned int getNonEmptyNumAmount()
{
	unsigned int counter = 0;
	for (int i = 0; i < database.size(); i++)
	{
		if (!database[i].isFree)
		{
			counter++;
		}
	}
	return counter;
}
unsigned int getStrAmount()
{
	return database.size();
}
void printDB()
{
	if (database.size() != 0)
	{
		for (int i = 0; i < database.size(); i++)
		{
			//печатаются только не пустые элементы массива
			if (database[i].isFree != true)
				std::cout << database[i].logicNumber << "|" << database[i].telNumber << "|" << database[i].name << "|" << database[i].adress << std::endl;
		}
	}
	else
	{
		std::cout << "Массив структур пуст" << std::endl;
	}
}