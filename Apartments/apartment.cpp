#include"apartment.h"

int apartment::counter = 0;

std::ostream& operator<< (std::ostream& out, const apartment& x)
{
	out << x.getID() << ", " << x.getDate() << ", " << x.getPrice() << ", " << x.getRoomCount() << ", " << x.getFloor() << ", " << x.getArea() << ", " << x.getAddress() << ".";
	return out;
}
std::istream& operator>> (std::istream& in, apartment& x)
{
	char tmp1[64], tmp2[64];
	int room = 0, floor = 0, area = 0, price = 0;
	std::cout << "Date: ";
	std::cin >> tmp1;
	std::cout << "Room count: ";
	std::cin >> room;
	std::cout << "Floor: ";
	std::cin >> floor;
	std::cout << "Area: ";
	std::cin >> area;
	std::cout << "Address: ";
	std::cin >> tmp2;
	std::cout << "Price: ";
	std::cin >> price;
	x = { tmp1, room, floor, area, tmp2, price };
	return in;
}
std::ofstream& operator<< (std::ofstream& out, const apartment& x)
{
	out.write((const char*)&x, sizeof(apartment));
	return out;
}
std::ifstream& operator>> (std::ifstream& in, apartment& x)
{
	in.read((char*)&x, sizeof(apartment));
	return in;
}

std::ostream& operator<<(std::ostream& out, const dataBase& x)
{
	int a, b;
	int s = x.getSize();
	int* pos = new int[s];
	int* price = new int[s];
	for (int i = 0; i < s; ++i)
	{
		pos[i] = i;
		price[i] = (x.getApartment(i)).getPrice();
	}
	for (int i = 0; i < s; ++i)
	{
		for (int j = 0; j < s-i-1; ++j)
		{
			if (price[j] > price[j + 1])
			{
				a = price[j];
				price[j] = price[j + 1];
				price[j + 1] = a;
				b = pos[j];
				pos[j] = pos[j + 1];
				pos[j + 1] = b;
			}
		}
	}
	for (int i = 0; i < s; ++i)
	{
		std::cout << x.getApartment(pos[i])<<std::endl;
	}
	return out;
}
std::ofstream& operator<<(std::ofstream& out, const dataBase& x)
{
	for (int i = 0; i < x.getSize(); ++i)
	{
		out << x.getApartment(i);
	}
	return out;
}
std::ifstream& operator>>(std::ifstream& in, dataBase& x)
{
	in.seekg(0,std::ios_base::end);
	int byteCounter = (int)in.tellg();
	int size = byteCounter / sizeof(apartment);
	apartment* base = new apartment[size];
	in.seekg(0, std::ios_base::beg);
	for (int i = 0; i < size; ++i)
	{
		in >> base[i];
	}
	x = dataBase(size, base);
	delete[] base;
	return in;
}
