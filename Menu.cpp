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
#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_MENU_CPP
#define SDDS_MENU_CPP
#include<iostream>
#include "Menu.h"
#include <cstring>
namespace sdds {

	MenuItem::MenuItem() {
		content = nullptr;
	}
	MenuItem::MenuItem(const char* newcontent) {
		if (newcontent && newcontent[0]) {
			content = new char[strlen(newcontent) + 1];
			strcpy(content, newcontent);
		}
		else {
			content = nullptr;
		}
	}
	MenuItem::~MenuItem() {
		delete[]content;
	}
	
	MenuItem::operator bool() const {
		bool valid;
		if (content&&content[0]) {
			valid = true;
		}
		else {
			valid = false;
		}
		return valid;
	}
	MenuItem::operator const char* () const{
		return content;
	}
	std::ostream& MenuItem:: displayMenuItem(std::ostream& os ) {
		if (content){
			os << content;
		}
		return os;
	}
	Menu::Menu(){
		trackMenuItem = 0;
	}
	Menu::Menu(const char* menuItemTitle):menuTitle(menuItemTitle) {}	
	Menu::~Menu() {
		for (unsigned int i = 0; i < MAX_MENU_ITEMS; i++) {
			delete menuItem[i];
		}
	}
	std::ostream& Menu:: displayTitle(std::ostream& os) {
		if (menuTitle) {
			menuTitle.displayMenuItem();
		}
		return os;
	}
	std::ostream& Menu::display(std::ostream& os) {
		if (menuTitle) {
			menuTitle.displayMenuItem();
			 os << std::endl;
		}
		for (unsigned int i = 0; i < trackMenuItem; i++) {
			os.width(2);
			os.fill(' ');
			os.setf(std::ios::right);
			os << i + 1 << "- ";
			os.unsetf(std::ios::right);
			menuItem[i]->displayMenuItem(os);
			os << std::endl;
		}
		os << " 0- Exit" << std::endl;
		os << "> ";
		return os;
	}
	unsigned int Menu::run() {
		unsigned int userInput;
		bool flag = true;
		display();
		
		while (flag) {
			std::cin >> userInput;
			if (userInput >= 0 && userInput <= trackMenuItem && std::cin) {
				flag = false;
			}
			else {
				std::cout<< "Invalid Selection, try again: ";
				std::cin.clear();
				std::cin.ignore(3276, '\n');
				flag = true;
			}
		}
		return userInput;
	}
	unsigned int Menu:: operator~() {
		return run();
	}
	Menu& Menu::operator<<(const char* menuitemConent) {
		if (trackMenuItem < MAX_MENU_ITEMS)
		{
			MenuItem* newMenuItem = new MenuItem(menuitemConent);
			menuItem[trackMenuItem] = newMenuItem;
			trackMenuItem++;
		}
		
		return *this;
	}
	Menu::operator int() {
		return trackMenuItem;
	}
	Menu::operator unsigned int() {
		return trackMenuItem;
	}
	Menu::operator bool() {
		bool valid;
		if (trackMenuItem > 0) {
			valid = true;
		}
		else {
			valid = false;
		}
		return valid;
	}
	std::ostream& operator<<(std::ostream& os, Menu& menu) {
		return(menu.displayTitle(os));
	}	
	const char* Menu::operator[](unsigned int index) const {

		if (index > trackMenuItem) {
			return (menuItem[index%= trackMenuItem]->content);
		}
		return(menuItem[index]->content);
	}
}
	
		


#endif // !SDDS_MENU_CPP
