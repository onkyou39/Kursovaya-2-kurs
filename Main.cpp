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
	std::cout << "������� ��� ����� ��� ���� � ����� ��� ������:\n";
	std::cin >> filename;
	enum Menu
	{
		Exit, //����� �� ���������
		Create, //�������� ������� �������� �� ������ ���������� �����
		Change, //��������� �������� �������� � �������� (����������) �������
		Get_value, //��������� �������� �������� ������� � �������� ���������� �������
		Delete, //�������� �������� � �������� ���������� �������
		Add, //���������� �������� � ������ 
		Get_non_empty, //��������� �������� ���������� ������� ���������
		Get_str_num, //��������� �������� ���������� �����
		Print, //����� ������� �������� �� �����
		Write //������ ������� ��������� �������� � ��������� ����
	};
	unsigned short menuSwitch;
	do
	{
		std::cout << "\n�������� ����� ������ ���������:" << std::endl;
		std::cout << "1 - �������� ������� �������� �� ������ ���������� �����" << std::endl;
		std::cout << "2 - ��������� �������� �������� � �������� (����������) �������" << std::endl;
		std::cout << "3 - ��������� �������� �������� ������� � �������� ���������� �������" << std::endl;
		std::cout << "4 - �������� �������� � �������� ���������� �������" << std::endl;
		std::cout << "5 - ���������� �������� � ������" << std::endl;
		std::cout << "6 - ��������� �������� ���������� ������� ���������" << std::endl;
		std::cout << "7 - ��������� �������� ���������� �����" << std::endl;
		std::cout << "8 - ����� ������� �������� �� �����" << std::endl;
		std::cout << "9 - ������ ������� ��������� �������� � ��������� ����" << std::endl;
		std::cout << "0 - ����� �� ���������" << std::endl;
		std::cin >> menuSwitch;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "����� � ���� �������������� ������ ������� �� 0 �� 9" << std::endl;
			continue;
		}
		unsigned int num;
		switch (menuSwitch)
		{
		case Menu::Create:
			readFile(filename);
			break;
		case Menu::Change:
			std::cout << "������� ����� ��������, �������� �������� �� ������ ��������: ";
			std::cin >> num;
			changeElement(num);
			break;
		case Menu::Get_value:
			std::cout << "������� ����� ��������, �������� �������� �� ������ ��������: ";
			std::cin >> num;
			getElement(num);
			break;
		case Menu::Delete:
			std::cout << "������� ����� ��������, ������� �� ������ �������: ";
			std::cin >> num;
			delElement(num);
			break;
		case Menu::Add:
			addElement();
			break;
		case Menu::Get_non_empty:
			std::cout << "� ������� " << getNonEmptyNumAmount() << " ������� ���������" << std::endl;
			break;
		case Menu::Get_str_num:
			std::cout << "� ������� " << getStrAmount() << " �����" << std::endl;
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
			std::cout << "����������� ������ ����� �� 0 �� 9" << std::endl;
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
		std::cout << "�������� ������ �� ����� " << filename << std::endl;
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
		std::cout << "�������� ������ � ���� " << filename << std::endl;
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
				std::cout << "���������� ������� �������� � ������� " << num << std::endl;
				std::cout << database[i].isFree << "|" << database[i].logicNumber << "|" << database[i].telNumber << "|" << database[i].name << "|" << database[i].adress << std::endl;
				std::cout << "\n������� ����� �������� ��������" << std::endl;
				std::cout << "���: ";
				std::getline(std::cin, database[i].name);
				std::cout << "�����: ";
				std::cin.ignore();
				std::getline(std::cin, database[i].adress);
				std::cin.ignore();
				std::cout << "����� ��������: ";
				std::getline(std::cin, database[i].telNumber);
				std::cout << "������ ������� ��������" << std::endl;
			}
			break;
		}
	}
	else std::cout << "������ �������� ����" << std::endl;
	
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
	std::cout << "������� � ������� " << num << " ������� �����" << std::endl;
}
void addElement()
{
	std::cout << "\n����� ���������� ��������\n";
	for (int i = 0; i < database.size(); i++) //������ �������
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
		std::cout << "������� ����� ��������, 1 - �������� �������, 0 - ����� �� �����\n";
		std::cin >> switch_on;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "����������� ������ ����� �� 0 �� 1\n" << std::endl;
			continue;
		}
		std::string input;
		int last; //������ ���������� �������� �������
		switch (switch_on)
		{
		case 1:
			std::cin.ignore();
			std::cout << "���: ";
			std::getline(std::cin, tmp.name);
			std::cout << "�����: ";
			//std::cin.ignore();
			std::getline(std::cin, tmp.adress);
			//std::cin.ignore();
			std::cout << "����� ��������: ";
			std::getline(std::cin, tmp.telNumber);
			last = database.size() - 1; //��������� ������� �������
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
			//���������� ������ �� ������ �������� �������
			if (database[i].isFree != true)
				std::cout << database[i].logicNumber << "|" << database[i].telNumber << "|" << database[i].name << "|" << database[i].adress << std::endl;
		}
	}
	else
	{
		std::cout << "������ �������� ����" << std::endl;
	}
}