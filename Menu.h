/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/
/* Citation and Sources...
Final Project Milestone 1
Module: Menu
Filename: Menu.cpp
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2023/07/08  Preliminary release
2023/-/-  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>

namespace sdds {
	const unsigned int MAX_MENU_ITEMS = 20;
	class MenuItem {
		char* content{};
		MenuItem();
		MenuItem(const char*);
		MenuItem(const MenuItem&) = delete;
		void operator=(const MenuItem&) = delete;
		~MenuItem();
		operator bool() const;
		operator const char*() const;
		std::ostream& displayMenuItem(std::ostream& os = std::cout);
		friend class Menu;
	};
	class Menu {
		MenuItem menuTitle{};
		MenuItem* menuItem[MAX_MENU_ITEMS]{ nullptr };
		unsigned int trackMenuItem=0;
	public:
		Menu(const Menu&) = delete;
		void operator=(const Menu&) = delete;
		Menu();
		Menu(const char* menuItemTitle);
		~Menu();
		std::ostream& displayTitle(std::ostream& os);
		std::ostream& display(std::ostream& os = std::cout);
		unsigned int run();
		unsigned int operator~();
		Menu& operator<<(const char* );
		operator int();
		operator unsigned int();
		operator bool();
		const char* operator[](unsigned int index) const;
	};
	std::ostream& operator<<(std::ostream& os,Menu& );
}


#endif // !SDDS_MENU_H
