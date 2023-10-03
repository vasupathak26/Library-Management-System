/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/
/* Citation and Sources...
Final Project Milestone 1
Module: LibApp
Filename: LibAPP.cpp
Version 1.0
Author	John Doe
Revision History
-----------------------------------------------------------
Date      Reason
2023/07/15  Preliminary release
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
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "LibApp.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	LibApp::LibApp(const char* fileName) :m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicationType("Choose the type of publication:") {
		m_changed = false;
		NOLP = 0;
		LLRN = 0;
		strcpy(m_fileName, fileName);
		m_mainMenu << "Add New Publication" << "Remove Publication" << "Checkout publication from library" << "Return publication to library";
		m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";
		m_publicationType << "Book" << "Publication";
		load();
	}
	LibApp::~LibApp() {
		for (int i = 0; i < NOLP; i++) {
			delete PPA[i];
		}
	}
	bool LibApp::confirm(const char* message) {
		bool valid;
		Menu menu(message);
		menu << "Yes";
		int returnValue;
		returnValue = menu.run();
		if (returnValue == 1) {
			valid = true;
		}
		else {
			valid = false;
		}
		return valid;
	}
	void LibApp::load() {
		cout << "Loading Data" << endl;
		ifstream m_read(m_fileName);
		char character{};
		int i = 0;
		while (m_read && i < SDDS_LIBRARY_CAPACITY) {
			m_read >> character;
			m_read.ignore();
			if (m_read) {
				if (character == 'P') {
					PPA[i] = new Publication;
				}
				else if (character == 'B') {

					PPA[i] = new Book;
				}
				if (PPA[i]) {
					m_read >> *PPA[i];
					NOLP++;
					LLRN = PPA[i]->getRef();
				}
			}
			i++;
		}
	}
	void LibApp::save() {
		cout << "Saving Data" << endl;
		ofstream m_write(m_fileName);
		for (int i = 0; i < NOLP; i++) {
			if (PPA[i]->getRef() != 0) {
				m_write << *PPA[i] << endl;
			}
		}
		m_write.close();
	}
	int LibApp::search(int typeOfSearch) {
		char _title[256]{};
		char character;
		int searchType = 0,libraryRefrence = 0;
		PublicationSelector pubSelector("Select one of the following found matches:", 15);
		searchType = m_publicationType.run();
		if (searchType == 1) {
			character = 'B';
		}
		else if (searchType == 2) {
			character = 'P';
		}
		std::cin.ignore(1000, '\n');
		std::cout << "Publication Title: ";
		std::cin.getline(_title, 256);
		if (typeOfSearch == 1) {
			for (int i = 0; i < NOLP; i++) {
				if (PPA[i]->operator==(_title) && character == PPA[i]->type() && PPA[i]->getRef() != 0) {
					pubSelector << PPA[i];
				}
			}
		}
		else if (typeOfSearch == 2) {
			for (int i = 0; i < NOLP; i++) {
				if (PPA[i]->operator==(_title) && PPA[i]->onLoan() && character == PPA[i]->type() && PPA[i]->getRef() != 0) {
					pubSelector << PPA[i];
				}
			}
		}
		else if (typeOfSearch == 3) {
			for (int i = 0; i < NOLP; i++) {
				if (PPA[i]->operator==(_title) && !PPA[i]->onLoan() && character == PPA[i]->type() && PPA[i]->getRef() != 0) {
					pubSelector << PPA[i];
				}
			}
		}
		if (pubSelector) {
			pubSelector.sort();
			libraryRefrence = pubSelector.run();

			if (libraryRefrence == 0){
				std::cout << "Aborted!" << std::endl;
			}	
			else {
				std::cout << *getPub(libraryRefrence) << std::endl;
			}
		}
		else {
			std::cout << "No matches found!" << std::endl;
		}

		return libraryRefrence;
	}
	Publication* LibApp::getPub(int libRef) {

		for (int i = 0; i < NOLP; i++) {
			if (PPA[i]->getRef() == libRef) {
				return PPA[i];
			}
		}
		return nullptr;
	}
	void LibApp::returnPub() {
		cout << "Return publication to the library" << endl;
		int check = search(2);
		if (check > 0) {
			if (confirm("Return Publication?")) {
				int loanDays = Date() - getPub(check)->checkoutDate();
				if (loanDays > SDDS_MAX_LOAN_DAYS) {
					double penalty = (loanDays - SDDS_MAX_LOAN_DAYS) * 0.5;
					cout<<fixed;
					cout.precision(2);
					cout << "Please pay $" << penalty << " penalty for being " << (loanDays - SDDS_MAX_LOAN_DAYS) << " days late!" << endl;
				}
				getPub(check)->set(0);
				m_changed = true;
			}
			cout << "Publication returned" << endl;
		}
		
		cout << endl;

	}
	void LibApp::newPublication() {
		bool flag = false;
		if (NOLP == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
			flag = true;
		}
		else {
			cout << "Adding new publication to the library" << endl;
			int type = m_publicationType.run();
			std::cin.ignore(1000, '\n');
			Publication* pub = nullptr;
			switch (type) {
			case 0:
				cout << "Aborted!" << endl;
				flag = true;
				break;
			case 1:
				pub = new Book;
				cin >> *pub;

				if (cin.fail())
				{
					cin.ignore(1000, '\n');
					cin.clear();
					cout << "Aborted!" << endl;
					exit(0);

				}
				else {
					if (!flag && confirm("Add this publication to the library?")) {
						if (!*pub) {
							std::cout << "Failed to add publication!" << std::endl;
							delete pub;
						}
						else {
							LLRN++;
							pub->setRef(LLRN);
							PPA[NOLP] = pub;
							NOLP++;
							m_changed = true;
							std::cout << "Publication added" << std::endl;
						}
					}
				}
				break;
			case 2:
				pub = new Publication;
				cin >> *pub;
				if (std::cin.fail())
				{
					std::cin.ignore(1000, '\n');
					std::cin.clear();
					std::cout << "Aborted!" << std::endl;

				}
				else {
					if (!flag && confirm("Add this publication to the library?")) {

						if (!*pub) {
							std::cout << "Failed to add publication!" << std::endl;
							delete pub;
						}
						else {
							LLRN++;
							pub->setRef(LLRN);
							PPA[NOLP] = pub;
							NOLP++;
							m_changed = true;
							std::cout << "Publication added" << std::endl;
						}
					}
				}
				break;
			}
		}
		cout << endl;
	}
	void LibApp::removePublication() {
		cout << "Removing publication from the library" << endl;
		int all = search(1);
		
		if (all) {
			bool returnValue;
			returnValue = confirm("Remove this publication from the library?");
			if (returnValue) {
				getPub(all)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}

		}
		cout << endl;
	}
	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;
		int check = search(3);
		bool flag = false;
		if (check > 0) {
			bool returnValue = confirm("Check out publication?");
			if (returnValue) {
				cout << "Enter Membership number: ";
				int membership;
				while (!flag){
					cin >> membership;
					if (membership < 10000 || membership > 99999||!cin){

						cout << "Invalid membership number, try again: ";
						cin.clear();
						cin.ignore(1000, '\n');
						flag = false;
					}
					else
					{
						flag = true;
					}

				}
				getPub(check)->set(membership);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
		cout << endl;
	}
	void LibApp::run() {
		int input, exit;
		do {
			input = m_mainMenu.run();
			switch (input) {
			case 0: if (m_changed == false) {
				cout << endl;
				break;
			}
				  else if (m_changed == true) {
				exit = m_exitMenu.run();
				switch (exit) {
				case 0:
					bool returnValue;
					returnValue = confirm("This will discard all the changes are you sure?");
					if (returnValue) {
						m_changed = false;
					}
					break;
				case 1: save();
					break;


				case 2: input = 1;
					break;
				}
			}
				  cout << endl;
				  break;
			case 1: newPublication();
				break;
			case 2: removePublication();
				break;
			case 3: checkOutPub();
				break;
			case 4: returnPub();
				break;
			}

		} while (input != 0);
		cout << "-------------------------------------------" << endl;
		cout << "Thanks for using Seneca Library Application" << endl;

	}
}
