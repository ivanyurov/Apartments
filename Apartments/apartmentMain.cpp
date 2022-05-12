#include<iostream>
#include<fstream>
#include"apartment.h"

void menu(char*& x)
{
	std::cout << "Use one of the following commands:" << std::endl;
	std::cout << "-load" << std::endl;
	std::cout << "-save" << std::endl;
	std::cout << "-add" << std::endl;
	std::cout << "-del ID" << std::endl;
	std::cout << "-print" << std::endl;
	std::cout << "-export" << std::endl;
	std::cout << "-find ID" << std::endl;
	std::cout << "-exit" << std::endl;
	char action[64];
	std::cin >> action;
	for (int i = 0; i < 64; ++i)
	{
		x[i] = action[i];
	}
}
int main()
{
	dataBase base;
	int act;
	do
	{
		act = 0;
		char* action=new char[64];
		menu(action);
		if ((action[0] == 'l') && (action[1] == 'o') && (action[2] == 'a') && (action[3] == 'd')) act = 1;
		if ((action[0] == 's') && (action[1] == 'a') && (action[2] == 'v') && (action[3] == 'e')) act = 2;
		if ((action[0] == 'a') && (action[1] == 'd') && (action[2] == 'd')) act = 3;
		if ((action[0] == 'd') && (action[1] == 'e') && (action[2] == 'l')) act = 4;
		if ((action[0] == 'p') && (action[1] == 'r') && (action[2] == 'i') && (action[3] == 'n') && (action[4] == 't')) act = 5;
		if ((action[0] == 'e') && (action[1] == 'x') && (action[2] == 'p') && (action[3] == 'o') && (action[4] == 'r') && (action[5] == 't')) act = 6;
		if ((action[0] == 'f') && (action[1] == 'i') && (action[2] == 'n') && (action[3] == 'd')) act = 7;
		if ((action[0] == 'e') && (action[1] == 'x') && (action[2] == 'i') && (action[3] == 't')) act = 8;
		if (act == 0)
		{
			std::cout << "Unknown command: ";
			for (int i = 0; i < 16; ++i)
			{
				if ((action[i] >= 'a') && (action[i] <= 'z')) { std::cout << action[i]; }
				else { break; }
			}
			std::cout << std::endl;
			continue;
		}
		if (act == 1) 
		{
			//read database from .dat file 
			char fileName[64];
			std::cout << "Enter file name:\n";
			std::cin >> fileName;
			std::ifstream file(fileName, std::ios_base::binary);
			if (!file)
			{
				std::cout << "Wrong file name.\n";
			}
			else
			{
				file >> base;
				file.close();
			}
		}
		if (act == 2) 
		{
			//write database in .dat file
			char fileName[64];
			std::cout << "Enter file name:\n";
			std::cin >> fileName;
			std::ofstream file(fileName);
			file << base;
		}
		if (act == 3)
		{
			//add apartment to database
			apartment tmp;
			std::cin >> tmp;
			dataBase tmpBase(base.getSize() + 1);
			for (int i = 0; i < base.getSize(); ++i)
			{
				tmpBase[i] = base[i];
			}
			tmpBase[tmpBase.getSize() - 1] = tmp;
			base = tmpBase;
		}

		if (act == 4) //delete apartment by ID
		{
			int ID_;
			std::cout << "Enter apartment ID\n";
			std::cin >> ID_;
			int num=-1;
			for (int i = 0; i < base.getSize(); ++i)
			{
				if (base[i].getID() == ID_)
				{
					num = i;
				}
			}
			if (num != -1)
			{
				dataBase tmpBase(base.getSize() - 1);
				int j = 0;
				for (int i = 0; i < base.getSize(); ++i)
				{
					if (i != num) { tmpBase[j] = base[i]; }
					else { --j; }
					++j;
				}
				base = tmpBase;
			}
			else { std::cout << "Wrong ID\n"; }
		}
		if (act == 5) //print database (full / with selected room count)
		{
			int num;
			std::cout << "Enter the number of rooms, if any, enter 0\n";
			std::cin >> num;
			if (num > 0)
			{
				int count = 0;
				for (int i = 0; i < base.getSize(); ++i)
				{
					if (base[i].getRoomCount() == num) { ++count; }
				}
				if (count > 0) 
				{
					dataBase tmpBase(count);
					count = 0;
					for (int i = 0; i < base.getSize(); ++i)
					{
						if (base[i].getRoomCount() == num) 
						{
							tmpBase[count] = base[i];
							++count;
						}
					}
					std::cout << tmpBase;
				} else { std::cout << "No matching apartments\n"; }
			} else { std::cout << base; }
		}
	    if (act == 6) //write database in .txt file
		{
			char fileName[64];
			std::cout << "Enter file name\n";
			std::cin >> fileName;
			std::ofstream file(fileName);
			int ID, price, roomcount, floor, area;
			char date[16];
			char address[64];
			for (int i = 0; i < base.getSize(); ++i)
			{
				ID = base[i].getID(); strncpy_s(date, base[i].getDate(), 16); price = base[i].getPrice(); roomcount = base[i].getRoomCount(); floor = base[i].getFloor(); area = base[i].getArea(); strncpy_s(address, base[i].getAddress(), 64);
				file << ID << ", " << date << ", " << price << ", " << roomcount << ", " << floor << ", " << area << ", " << address << ".";
			}
		}
		if (act == 7)  //find matching apartment for swap
		{
			int ID_;
			std::cout << "Enter apartment ID\n";
			std::cin >> ID_;
			int check = -1;
			for (int i = 0; i < base.getSize(); ++i)
			{
				if (base[i].getID() == ID_) { check = i; }
			}
			if (check != -1)
			{
				int area = base[check].getArea();
				int room = base[check].getRoomCount();
				int floor = base[check].getFloor();
				std::cout << "Matching apartments for swap:\n";
				for (int i = 0; i < base.getSize(); ++i)
				{
					if ((i != check) && (base[i].getRoomCount() == area) && (base[i].getFloor() == floor) && ((base[i].getArea() - area) <= (area / 5)) && ((base[i].getArea() - area) >= (-area / 5)))
					{
						std::cout << base[i];
					}
				}
			}
			else { std::cout << "Wrong ID\n"; }
		}		
	} while (act!=8);
	apartment a[5]{apartment("04.05.2022", 3, 5, 45, "dybenko", 12000000),
		apartment( "05.05.2022", 4, 6, 50, "dybenko", 15000000 ),
		apartment( "06.05.2022", 5, 7, 55, "dybenko", 18000000 ),
		apartment( "07.05.2022", 6, 8, 60, "dybenko", 21000000 ),
		apartment( "08.05.2022", 7, 9, 65, "dybenko", 24000000 ) };
	/*std::ofstream file("dataBase.dat");
	if (!file) { return 1; }
	for (int i = 0; i < 5; ++i)
	{
		file << a[i];
	}
	file.close();*/
	std::ifstream file1("dataBase.dat");
	if (!file1) { return 1; }
	dataBase c;
	file1 >> c;
	file1.close();
	dataBase b(5, a);
	//std::cout << c <<std::endl;
	std::cout << b;
	dataBase d(5);
	for (int i = 0; i < 5; ++i)
	{
		d[i] = b[i];
	}
	std::cout << d;
	std::cout << 500/sizeof(apartment);
	system("pause");
	return 0;
}
