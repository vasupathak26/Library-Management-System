/*
Name-Vasu Shaun Pathak
Student ID- 117488221
Email - vpathak2@myseneca.ca
*/
/* Citation and Sources...
Final Project Milestone 1
Module: LibApp
Filename: LibAPP.h
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

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include <iostream>
#include "Menu.h"
#include "Lib.h"
#include "Streamable.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"
namespace sdds {
    class LibApp {
    private:
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        Menu m_publicationType;
        char m_fileName[256];
        Publication* PPA[SDDS_LIBRARY_CAPACITY]; 
        int NOLP; 
        int LLRN; 
        bool confirm(const char* message);
        void load();
        void save();
        int search(int typeOfSearch);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();

    public:
        LibApp(const char* fileName);
        ~LibApp();
        void run();
        Publication* getPub(int libRef);

    };
}

#endif