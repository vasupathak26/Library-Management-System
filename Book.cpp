/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/

/* Citation and Sources...
Final Project Milestone 4
Module: Book
Filename: Book.cpp
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2023/07/27  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <cstring>
namespace sdds {
	Book::Book() :Publication() {
		authorName = nullptr;
	}
	Book::~Book() {
		if (authorName) {
			delete[] authorName;
			authorName = nullptr;
		}
	}
	Book::Book(const Book& book) :Publication(book) {
		*this = book;
	}
	Book& Book:: operator=(const Book& book) {
		(Publication&)*this = book;
		if (this != &book) {
			if (authorName) {
				delete[] authorName;
				authorName = nullptr;
			}
			if (book.authorName) {
				authorName = new char[strlen(book.authorName) + 1];
				strcpy(authorName, book.authorName);
			}

		}
		return *this;
	}
	char Book::type()const {
		return 'B';
	}
	std::ostream& Book::write(std::ostream& ostr)const {
		Publication::write(ostr);
		if (conIO(ostr)) {
			char name[SDDS_AUTHOR_WIDTH + 1]{ 0 };
			strncpy(name, authorName, SDDS_AUTHOR_WIDTH);
			ostr << " ";
			ostr.width(SDDS_AUTHOR_WIDTH);
			ostr << std::left;
			ostr.fill(' ');
			ostr << name;
			ostr << " |";
		}
		else {
			ostr << '\t';
			ostr << authorName;
		}
		return ostr;
	}
	std::istream& Book::read(std::istream& istr) {
		char a_name[256]{ 0 };
		Publication::read(istr);
		if (authorName) {
			delete[] authorName;
			authorName = nullptr;
		}
		if (conIO(istr)) {
			istr.ignore();
			std::cout << "Author: ";
		}
		else {
			istr.ignore(32647,'\t');
		}
		istr.get(a_name, 256);
		if (!istr.fail()) {

			authorName = new char[strlen(a_name)+1];
			strcpy(authorName, a_name);
		}

		return istr;
	}
	void Book::set(int member_id) {
		Publication::set(member_id);
		Publication::resetDate();
	}
	Book::operator bool() const {
		bool result = false;
		if (authorName) {
			if (Publication::operator bool()) {
				result = true;
			}
		}
		return result;
	}
}
