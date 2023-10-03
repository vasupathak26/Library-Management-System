/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/

/* Citation and Sources...
Final Project Milestone 3
Module: Publication
Filename: Publication.h
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
#ifndef SDDS_PUBLICATION_H
#define SDDS_PUBLICATION_H
#include "Lib.h"
#include "Date.h"
#include "Streamable.h"
namespace sdds {
	class Publication:public Streamable {
		char* m_title;
		char m_shelfId[SDDS_SHELF_ID_LEN + 1];
		int m_membership;
		int m_libRef;
		Date m_date;
	public:
		Publication();
		~Publication();
		Publication(const Publication& publication);
		Publication& operator=(const Publication& publication);
		void setDefaultValue();
		virtual void set(int member_id);
		// Sets the membership attribute to either zero or a five-digit integer.
		void setRef(int value);
		// Sets the **libRef** attribute value
		void resetDate();
		// Sets the date to the current date of the system.
		virtual char type()const;
		//Returns the character 'P' to identify this object as a "Publication object"
		bool onLoan()const;
		//Returns true is the publication is checkout (membership is non-zero)
		Date checkoutDate()const;
		//Returns the date attribute
		bool operator==(const char* title)const;
		//Returns true if the argument title appears anywhere in the title of the 
		//publication. Otherwise, it returns false; (use strstr() function in <cstring>)
		operator const char* ()const;
		//Returns the title attribute
		int getRef()const;
		//Returns the libRef attirbute. 
		 std::ostream& write(std::ostream& ostr)const;
		 std::istream& read(std::istream& istr) ;
		  bool conIO(std::ios& io)const;
		 operator bool() const;
	};
	



}
#endif // !SDDS_PUBLICATION_H
