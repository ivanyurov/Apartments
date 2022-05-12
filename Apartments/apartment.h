#pragma once
#include<iostream>
#include<fstream>

class apartment
{
	int ID;
	char date_[16];
	int price_;
	int roomCount_;
	int floor_;
	int area_;
	char address_[64];
	static int counter;
public:
	apartment(const char *date = "", int roomCount = 0, int floor = 0, int area = 0, const char *address = "", int price = 0)
	{
		ID = ++counter;
		strncpy_s(date_, date, 16);
		roomCount_ = roomCount;
		floor_ = floor;	
		area_ = area;
		strncpy_s(address_, address, 64);
		price_ = price;
	}
	apartment& operator=(const apartment& x)
	{
		if (this != &x)
		{
			strncpy_s(date_, x.getDate(), 16);
			roomCount_ = x.getRoomCount();
			floor_ = x.getFloor();
			area_ = x.getArea();
			strncpy_s(address_, x.getAddress(), 64);
			price_ = x.getPrice();
		}
		return *this;
	}
	int getID() const { return ID; }
	const char* getDate() const { return date_; }
	int getPrice() const { return price_; }
	int getRoomCount() const { return roomCount_; }
	int getFloor() const { return floor_; }
	int getArea() const { return area_; }
	const char* getAddress() const { return address_; }

};

std::ostream& operator<< (std::ostream& out, const apartment& x);
std::istream& operator>> (std::istream& in, apartment& x);
std::ofstream& operator<< (std::ofstream& out, const apartment& x);
std::ifstream& operator>> (std::ifstream& in, apartment& x);

class dataBase
{
	int size_;
	apartment* base_;
public:
	explicit dataBase(int size=0, const apartment* base=nullptr)
	{
		if (size > 0) 
		{
			size_ = size;
			base_ = new apartment[size_];
			if (base != nullptr)
			{
				for (int i = 0; i < size_; ++i)
				{
					base_[i] = base[i];
				}
			}
		}
		else
		{
			size_ = 0;
			base_ = new apartment[1];
			base_[0] = {};
		}
	}
	dataBase(const dataBase& x) :size_(x.getSize())
	{
		base_ = new apartment[size_];
		for (int i = 0; i < size_; ++i)
		{
			base_[i] = x.getApartment(i);
		}
	}
	~dataBase()
	{
		delete[] base_;
	}
	dataBase& operator=(const dataBase& x)
	{
		if (this != &x)
		{
			size_ = x.getSize();
			delete[] base_;
			base_ = new apartment[size_];
			for (int i = 0; i < size_; ++i)
			{
				base_[i] = x.getApartment(i);
			}

		}
		return *this;
	}
	apartment& operator[](int i)
	{
		if (i < 0 || i >= size_)
		{
			throw "Out of limits";
		}
		return base_[i];
	}
	int getSize() const { return size_; }
	apartment getApartment(int num) const { return base_[num]; }
};

std::ostream& operator<<(std::ostream& out, const dataBase& x);
std::ofstream& operator<<(std::ofstream& out, const dataBase& x);
std::ifstream& operator>>(std::ifstream& in, dataBase& x);
