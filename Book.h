/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/

/* Citation and Sources...
Final Project Milestone 4
Module: Book
Filename: Book.h
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
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
namespace sdds {
	class Book :public Publication {
		char* authorName{nullptr};
	public:
		Book();
		~Book();
		Book(const Book& book);
		Book& operator=(const Book& book);
		char type()const;
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
		virtual void set(int member_id);
		operator bool() const;
};

}
#endif // !SDDS_BOOK_H
