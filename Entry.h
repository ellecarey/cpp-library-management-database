#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Catalogue;

class Entry {
private:
	static std::size_t m_itemCount; // base class counter
protected:
	std::string m_ID;
	std::string m_name;
	std::string m_year;
	std::string m_borrowedBy;
	bool m_borrowed;
public:
	Entry(bool count = true) : m_name(" "), m_year(" "), m_borrowed(false), m_borrowedBy(" ") { if (count) ++m_itemCount; } //constructor for no input
	Entry(std::string name, std::string year, bool borrowed, std::string borrowedBy, bool count) : m_name(name), m_year(year), m_borrowed(borrowed), m_borrowedBy(borrowedBy) { if (count) ++m_itemCount; } // constructor with inputs
	virtual ~Entry() {}; // destructor for counter
	virtual void PrintDetails() {};
	virtual void ChargeFee() {};
	virtual void SaveToFile() {};
	virtual std::string GetStream() = 0;
	void EntryBorrowed(std::string& borrowedBy);
	void EntryReturned();
	std::string Space2Underscore(std::string& text) {std::replace(text.begin(), text.end(), ' ', '_'); return text; } // replace spaces with _
	std::string Underscore2Space(std::string& text) {std::replace(text.begin(), text.end(), '_', ' '); return text; } // replace _ with spaces

	// mutators
	void SetID(std::string ID) { m_ID = ID; }
	void SetBorrowed(bool borrowed) { m_borrowed = borrowed; }
	void SetBorrowedBy(std::string borrowedBy) { m_borrowedBy = borrowedBy; }
	
	// accessors
	std::string GetID() { return m_ID; }
	std::string GetName() { return m_name; }
	std::string GetYear() { return m_year; }
	std::string GetBorrowedBy() { return m_borrowedBy; }
	bool GetBorrowed() { return m_borrowed; }
	static std::size_t GetItemCount() { return m_itemCount; } 

	friend class Catalogue; // make catalogue a friend to access item attributes
};

class MusicAlbum : public Entry {
private:
	std::string m_artist;
	std::string m_recordLabel;
	static std::size_t m_itemCount;
	std::string GetStream();
public:
	MusicAlbum(bool count = true); // constructor for no input
	MusicAlbum(std::string name, std::string year, std::string artist, std::string recordLabel, bool borrowed, std::string borrowedBy, bool count); // constructor with inputs
	void PrintDetails();
	void SaveToFile();
	
	// accessors
	static std::size_t GetItemCount() { return m_itemCount; }

	friend class Catalogue; // make catalogue a friend to access the counters
};

class Book : public Entry {
private:
	std::string m_author;
	std::string m_publisher;
	std::string m_edition;
	void SaveToFile();
	static std::size_t m_itemCount;
	std::string GetStream();
public:
	Book(bool count = true);
	Book(std::string name, std::string year, std::string author, std::string publisher, std::string edition, bool borrowed, std::string borrowedBy, bool count);
	void PrintDetails();
	static std::size_t GetItemCount() { return m_itemCount; }

	// accessors
	std::string GetEdition() { return m_edition; }

	friend class Catalogue;
};

class Film : public Entry {
private:
	std::string m_director;
	std::string m_language;
	std::string m_fee;
	static std::size_t m_itemCount;
	std::string GetStream();
public:
	Film(bool count = true);
	Film(std::string name, std::string year, std::string director, std::string language, bool borrowed, std::string borrowedBy, bool count);
	void PrintDetails();
	void ChargeFee();
	void SaveToFile();

	// accessors
	static std::size_t GetItemCount() { return m_itemCount; }

	friend class Catalogue;
};

class Catalogue {
private:
	std::vector<std::unique_ptr<Entry>> m_database;
	bool FileExists(const std::string& fileName);
	bool EntryExists(const std::unique_ptr<Entry>& entry);
	bool StringBool(const std::string& borrowed) { if (borrowed == "1") { return true; } else { return false; } } //convert string to bool
	void DeleteFileEntry(std::string& ID);
	void ReplaceFileEntry(std::vector<std::unique_ptr<Entry>>::iterator entry);
public:

	void AddItem();
	void DeleteItem();
	void IssueItem();
	void ReturnItem();
	void SearchItem();
	void DisplayAll();
	void DisplayStats();
	void ImportCatalogue();
	void ReadFile(std::string& fileName);
};

// global functions 

// clear the screen when moving between menus
inline void ClearScreen(void) { 
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// pause the console when selecting menu options, clear the buffer
inline void ConsolePause(void) { 
	std::cin.clear();
	std::cin.ignore(256, '\n');
	std::cin.get();
}

#endif