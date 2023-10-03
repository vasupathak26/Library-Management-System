/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/

/* Citation and Sources...
Final Project Milestone 3
Module: Publication
Filename: Publication.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Publication.h"

namespace sdds {
	void Publication::setDefaultValue() {
		m_title = nullptr;
		m_membership = 0;
        m_shelfId[0] = '\0';
		m_libRef = -1;
		resetDate();

	}
	Publication::Publication() {
		setDefaultValue();
	}
	Publication::~Publication() {
		delete[]m_title;
	}
    Publication::Publication(const Publication& publication) {
        *this = publication;
    }

    Publication& Publication::operator=(const Publication& publication) {
        set(publication.m_membership);
        setRef(publication.m_libRef);
        strcpy(m_shelfId, publication.m_shelfId);
        m_date = publication.m_date;
        if (m_title)
        {
            delete[] m_title;
            m_title = nullptr;
        }
        if (publication.m_title != nullptr) {
            m_title = new char[strlen(publication.m_title) + 1];
            strcpy(m_title, publication.m_title);
        }
        else {
            m_title = nullptr;
        }

        return *this;
    }

	void Publication::set(int member_id) {
		m_membership = member_id;
	}
	void Publication::setRef(int value) {
		m_libRef = value;
	}
	void Publication::resetDate() {
		m_date = Date();
	}
	char Publication::type()const {
		return 'P';
	}
	bool Publication::onLoan()const {
		bool checkout = false;
		if (m_membership != 0) {
			checkout = true;
		}
		return checkout;
	}
	Date Publication::checkoutDate()const {
		return m_date;
	}
	bool Publication::operator==(const char* title)const {
		bool check = false;
		if (strstr(m_title,title) != nullptr) {
			check=true;
		}
		return check;
	}
	Publication::operator const char* ()const {
		return m_title;
	}
	int Publication::getRef()const {
		return m_libRef;
	}
	bool Publication::conIO(std::ios& io)const {
		bool check = false;
		if (&io == &std::cin || &io == &std::cout) {
			check = true;
		}
		return check;
	}
    std::ostream& Publication::write(std::ostream& ostr) const {
        char titleName[SDDS_TITLE_WIDTH + 1]{ 0 };
        strncpy(titleName, m_title, SDDS_TITLE_WIDTH);
        if (conIO(ostr)) {
            ostr << "| " << m_shelfId << " | ";
            ostr.width(30);
            ostr << std::left;
            ostr << std::setfill('.');
            ostr<< titleName << " | ";
            if (m_membership != 0) {
                ostr << m_membership;
            }
            else {
                ostr << " N/A ";
            }
            ostr << " | " << m_date << " |";
        }
        else {
            ostr << type();
            ostr << "\t" << m_libRef;
            ostr << "\t" << m_shelfId;
            ostr<< "\t" << m_title << "\t";
            ostr << m_membership;
            ostr << "\t" << m_date;
        }

        return ostr;
    }
    std::istream& Publication::read(std::istream& istr) {
        char title[256]{}, shelfId[SDDS_SHELF_ID_LEN + 1]{};
        int libRef = -1, membership = 0;
        Date r_date;
        if (m_title) {
            delete[] m_title;
            m_title = nullptr;
        }
        setDefaultValue();
        if (conIO(istr)) {
            std::cout << "Shelf No: ";
            istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1);
            if (strlen(shelfId) != SDDS_SHELF_ID_LEN) {
                istr.setstate(std::ios::failbit);
            }
            std::cout << "Title: ";
            istr.getline(title, 256);
            std::cout << "Date: ";
            istr >> r_date;
        }
        else {
            istr >> libRef;
            istr.ignore();
            istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            istr.getline(title, 256, '\t');
            istr >> membership;
            istr.ignore();
            istr >> r_date;
        }
        if (!r_date) {
            istr.setstate(std::ios::failbit);
        }
        if (istr) {
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
            strcpy(m_shelfId, shelfId);
            m_membership = membership;
            m_date = r_date;
            m_libRef = libRef;
        }

        return istr;
    }
    Publication::operator bool() const {
        bool check = false;
        if (m_title != nullptr && m_shelfId[0] != '\0') {
            check = true;
        }

        return check;
    }
}