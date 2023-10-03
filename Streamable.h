/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/

/* Citation and Sources...
Final Project Milestone 3
Module: Streamable
Filename: Streamable.h
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2023/07/21  Preliminary release
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
#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H
#include <iostream>
namespace sdds {
	class Streamable {
	public:
		virtual std::ostream& write(std::ostream& ostr)const=0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual  bool conIO(std::ios& io)const=0;
		virtual operator bool() const=0;
		virtual ~Streamable();
	};
	std::ostream& operator <<(std::ostream& os, const Streamable& s);
	std::istream& operator >>(std::istream& is, Streamable& s);
}



#endif // !SDDS_STREAMABLE_H
