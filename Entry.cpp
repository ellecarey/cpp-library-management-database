#include "Entry.h"

// intialise counters for parent and child classes
std::size_t Entry::m_itemCount = 0;
std::size_t MusicAlbum::m_itemCount = 0;
std::size_t Book::m_itemCount = 0;
std::size_t Film::m_itemCount = 0;


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ENTRY ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
* update entry as borrowed and who has borrowed it
* 
* @param[in] member ID number
*/
inline void Entry::EntryBorrowed(std::string& borrowedBy) {
	SetBorrowed(true);
	SetBorrowedBy(borrowedBy);
	std::cout << " *** Entry successfully issued *** " << std::endl;
}

/**
* update entry as returned
*/

inline void Entry::EntryReturned() {
	SetBorrowed(false);
	SetBorrowedBy(" ");
	std::cout << " *** Entry successfully returned *** " << std::endl;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MUSIC ALBUM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
* MusicAlbum constructor when no input values are given
*
* when an empty MusicAlbum obj is created the user is prompted to provide 
* information to initialise the class attributes. If the item is on loan 
* they will provide the member ID. If an inccorrect input is given they will
* be asked the questions again.
* 
* @param[in] MusicAlbum counter = true
* @param[in] Entry counter = false
*/

MusicAlbum::MusicAlbum(bool count) : Entry(false) { 
	std::string temp;
	std::stringstream ID;
	bool stop = false;
	if (count) ++m_itemCount; // increase MusicAlbum obj counter
	
	ID << "MA_" << GetItemCount();
	SetID(ID.str()); // assign unique item ID

	while (!stop) { // get album info from user
		std::cout << " Please enter the following details about the music album to proceed: " << "\n" << std::endl;
		std::cout << " -> Enter the name of the album: " << std::endl;
		std::getline(std::cin >> std::ws, m_name);
		std::cout << " -> Enter the year of release of the album: " << std::endl;
		std::getline(std::cin, m_year);
		std::cout << " -> Enter the name of the artist: " << std::endl;
		std::getline(std::cin >> std::ws, m_artist);
		std::cout << " -> Enter the name of the record label: " << std::endl;
		std::getline(std::cin >> std::ws, m_recordLabel);
		std::cout << " -> Is the album currently on loan? Enter 'Y' or 'N': " << std::endl;
		std::getline(std::cin, temp);

		if (temp == "Y" || temp == "y") { // item on loan, get the member ID
			SetBorrowed(true);
			std::cout << " -> Enter the member ID for who it is on loan to: " << std::endl;
			std::getline(std::cin, m_borrowedBy);
			PrintDetails();
			stop = true; // correct format input, break the while loop
		}
		else if (temp == "N" || temp == "n") { // item not on loan, no more info needed
			SetBorrowed(false);
			SetBorrowedBy(" ");
			PrintDetails();
			stop = true; // correct format input, break the while loop
		}
		else { // while loop repeats to get correct Y/N input from user
			std::cout << " You have entered incorrect details, please try again. " << std::endl;
			ConsolePause();
			ClearScreen();
		}
	}
	
}

/**
* MusicAlbum constructor when input values are given
*
* Constructs the MusicAlbum obj according to inputs and assigns it a unique ID, updates the counter
* 
* @params[in] album name, year, artist, record label, borrowed/not borrowed, member ID, counter 
* 
*/
inline MusicAlbum::MusicAlbum(std::string name, std::string year, std::string artist, std::string recordLabel, bool borrowed, std::string borrowedBy, bool count) :
	Entry(name, year, borrowed, borrowedBy, false), m_artist(artist), m_recordLabel(recordLabel) { // initialiser list to initialise base class and child members
	std::stringstream ID;
	if (count) ++m_itemCount; 
	ID << "MA_" << GetItemCount();
	SetID(ID.str()); 
}

/**
* Generates the string of item details, two options depending on whether it is on loan or available
*
* @params[out] string of item details
*
*/
std::string MusicAlbum::GetStream() { 
	std::ostringstream stream;
	if (m_borrowed == true) {
		stream << "\n" << " Item:         Album \n"
			<< " ID:           " << GetID() << "\n"
			<< " Name:         " << Underscore2Space(m_name) << "\n"
			<< " Year:         " << GetYear() << "\n"
			<< " Artist:       " << Underscore2Space(m_artist) << "\n"
			<< " Record Label: " << Underscore2Space(m_recordLabel) << "\n"
			<< " Status:       On Loan " << "\n"
			<< " Loaned By:    " << GetBorrowedBy() << "\n";
	}
	else {
		stream << "\n" << " Item:         Album " << "\n" 
			<< " ID:           " << GetID() << "\n"
			<< " Name:         " << Underscore2Space(m_name) << "\n"
			<< " Year:         " << GetYear()  << "\n"
			<< " Artist:       " << Underscore2Space(m_artist) << "\n"
			<< " Record Label: " << Underscore2Space(m_recordLabel) << "\n"
			<< " Status:       Availiable " << "\n";
	}
	return stream.str(); // convert the stream to a string and return
}

/**
* Prints the detils of the item on the screen to the user
*/
inline void MusicAlbum::PrintDetails() {
	std::cout << GetStream() << std::endl;
}

/**
* Writes the obj information to the catalogue.txt file
*/

inline void MusicAlbum::SaveToFile() { // function to save the obj details to a txt file
	std::ofstream file;
	file.open("catalogue.txt", std::fstream::app); // check file exist, if it does append. If not create the file 
	file << GetID() << '\t' << Space2Underscore(m_name) << '\t' << GetYear() << '\t' << Space2Underscore(m_artist) << '\t' << Space2Underscore(m_recordLabel) << '\t' << GetBorrowed() << '\t' << Space2Underscore(m_borrowedBy) << std::endl;
	file.close();
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BOOK ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
* Book constructor when no input values are given
*
* when an empty Book obj is created the user is prompted to provide
* information to initialise the class attributes. If the item is on loan
* they will provide the member ID. If an inccorrect input is given they will
* be asked the questions again.
*
* @param[in] Book counter = true
* @param[in] Entry counter = false
*/

Book::Book(bool count) : Entry(false) {
	std::string temp;
	std::stringstream ID;
	bool stop = false;
	if (count) ++m_itemCount; // increase MusicAlbum obj counter

	ID << "B_" << GetItemCount();
	SetID(ID.str());

	while (!stop) {
		std::cout << " Please enter the following details about the book to proceed: " << "\n" << std::endl;
		std::cout << " -> Enter the name of the book: " << std::endl;
		std::getline(std::cin >> std::ws, m_name);
		std::cout << " -> Enter the year of release of the book: " << std::endl;
		std::getline(std::cin, m_year);
		std::cout << " -> Enter the name of the author: " << std::endl;
		std::getline(std::cin >> std::ws, m_author);
		std::cout << " -> Enter the name of the publisher: " << std::endl;
		std::getline(std::cin >> std::ws, m_publisher);
		std::cout << " -> Enter the edition: " << std::endl;
		std::getline(std::cin, m_edition);
		std::cout << " -> Is the book currently on loan? Enter 'Y' or 'N': " << std::endl;
		std::getline(std::cin, temp);
		if (temp == "Y" || temp == "y") {
			SetBorrowed(true);
			std::cout << " -> Enter the member ID for who it is on loan to: " << std::endl;
			std::getline(std::cin, m_borrowedBy);
			PrintDetails();
			stop = true;
		}
		else if (temp == "N" || temp == "n") {
			SetBorrowed(false);
			SetBorrowedBy(" ");
			PrintDetails();
			stop = true;
		}
		else {
			std::cout << " You have entered incorrect details, please try again. " << std::endl;
			ConsolePause();
			ClearScreen();
		}
	}
}

/**
* Book constructor when input values are given
*
* Constructs the Book obj according to inputs and assigns it a unique ID, updates the counter
*
* @params[in] book name, year, author, publisher, edition, borrowed/not borrowed, member ID, counter
*
*/
inline Book::Book(std::string name, std::string year, std::string author, std::string publisher, std::string edition, bool borrowed, std::string borrowedBy, bool count) :
	Entry(name, year, borrowed, borrowedBy, false), m_author(author), m_publisher(publisher), m_edition(edition) {
	std::stringstream ID;
	if (count) ++m_itemCount;
	ID << "B_" << GetItemCount();
	SetID(ID.str());
}

/**
* Generates the string of item details, two options depending on whether it is on loan or available
*
* @params[out] string of item details
*
*/
std::string Book::GetStream() {
	std::ostringstream stream;
	if (m_borrowed == true) {
		stream << "\n" << " Item:         Book " << "\n"
			<< " ID:           " << GetID() << "\n"
			<< " Name:         " << Underscore2Space(m_name) << "\n"
			<< " Year:         " << GetYear() << "\n"
			<< " Author:       " << Underscore2Space(m_author) << "\n"
			<< " Publisher:    " << Underscore2Space(m_publisher) << "\n"
			<< " Edition:      " << GetEdition() << "\n"
			<< " Status:       On Loan " << "\n"
			<< " Loaned By:    " << GetBorrowedBy() << "\n";
	}
	else {
		stream << "\n" << " Item:         Book " << "\n"
			<< " ID:           " << GetID() << "\n"
			<< " Name:         " << Underscore2Space(m_name) << "\n"
			<< " Year:         " << GetYear() << "\n"
			<< " Author:       " << Underscore2Space(m_author) << "\n"
			<< " Publisher:    " << Underscore2Space(m_publisher) << "\n"
			<< " Edition:      " << GetEdition() << "\n"
			<< " Status:       Availiable " << "\n";
	}
	return stream.str();
}

/**
* Prints the detils of the item on the screen to the user
*/
inline void Book::PrintDetails() {
	std::cout << GetStream() << std::endl;
}

/**
* Writes the obj information to the catalogue.txt file
*/
inline void Book::SaveToFile() {
	std::ofstream file;
	file.open("catalogue.txt", std::fstream::app);
	file << m_ID << '\t' << Space2Underscore(m_name) << '\t' << GetYear() << '\t' << Space2Underscore(m_author) << '\t' << Space2Underscore(m_publisher) << '\t' << GetEdition() << '\t' << GetBorrowed() << '\t' << Space2Underscore(m_borrowedBy) << std::endl;
	file.close();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FILM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
* Film constructor when no input values are given
*
* when an empty Film obj is created the user is prompted to provide
* information to initialise the class attributes. If the item is on loan
* they will provide the member ID. If an inccorrect input is given they will
* be asked the questions again.
*
* @param[in] Film counter = true
* @param[in] Entry counter = false
*/

Film::Film(bool count) : Entry(false) {
	std::string temp;
	std::stringstream ID;
	bool stop = false;
	if (count) ++m_itemCount; // increase MusicAlbum obj counter

	ID << "F_" << GetItemCount();
	SetID(ID.str()); // assign unique item ID

	while (!stop) {
		std::cout << " \nPlease enter the following details about the film to proceed: " << "\n" << std::endl;
		std::cout << " -> Enter the name of the film: " << std::endl;
		std::getline(std::cin >> std::ws, m_name);
		std::cout << " -> Enter the year of release of the film: " << std::endl;
		std::getline(std::cin, m_year);
		std::cout << " -> Enter the name of the director: " << std::endl;
		std::getline(std::cin >> std::ws, m_director);
		std::cout << " -> Enter the language of the film: " << std::endl;
		std::getline(std::cin, m_language);
		std::cout << " -> Is the film currently on loan? Enter 'Y' or 'N': " << std::endl;
		std::getline(std::cin, temp);

		if (temp == "Y" || temp == "y") {
			SetBorrowed(true);
			std::cout << " -> Enter the member ID for who it is on loan to: " << std::endl;
			std::getline(std::cin, m_borrowedBy);
			PrintDetails();
			stop = true;
		}
		else if (temp == "N" || temp == "n") {
			SetBorrowed(false);
			SetBorrowedBy(" ");
			PrintDetails();
			stop = true;
		}
		else {
			std::cout << " You have entered incorrect details, please try again. " << std::endl;
			ConsolePause();
			ClearScreen();
		}
	}
}

/**
* Film constructor when input values are given
*
* Constructs the Film obj according to inputs and assigns it a unique ID, updates the counter
*
* @params[in] film name, year, director, language, borrowed/not borrowed, member ID, counter
*
*/
inline Film::Film(std::string name, std::string year, std::string director, std::string language, bool borrowed, std::string borrowedBy, bool count) :
	Entry(name, year, borrowed, borrowedBy, false), m_director(director), m_language(language){
	std::stringstream ID;
	if (count) ++m_itemCount;
	ID << "F_" << GetItemCount();
	SetID(ID.str());
}

/**
* Generates the string of item details, two options depending on whether it is on loan or available
*
* @params[out] string of item details
*
*/
std::string Film::GetStream() {
	std::ostringstream stream;
	if (m_borrowed == true) {
		stream << "\n" << " Item:         Film " << "\n"
			<< " ID:           " << GetID() << "\n"
			<< " Name:         " << Underscore2Space(m_name) << "\n"
			<< " Year:         " << GetYear() << "\n"
			<< " Director:     " << Underscore2Space(m_director) << "\n"
			<< " Language:     " << Underscore2Space(m_language) << "\n"
			<< " Status:       On Loan " << "\n"
			<< " Loaned By:    " << GetBorrowedBy() << "\n";
	}
	else {
		stream << "\n" << " Item:         Film " << "\n"
			<< " ID:           " << GetID() << "\n"
			<< " Name:         " << Underscore2Space(m_name) << "\n"
			<< " Year:         " << GetYear() << "\n"
			<< " Director:     " << Underscore2Space(m_director) << "\n"
			<< " Language:     " << Underscore2Space(m_language) << "\n"
			<< " Status:       Availiable " << "\n";
	}
	return stream.str();
}

/**
* Prints the detils of the item on the screen to the user
*/
inline void Film::PrintDetails() {
	std::cout << GetStream() << std::endl;
}

/**
* Writes the obj information to the catalogue.txt file
*/
inline void Film::SaveToFile() {
	std::ofstream file;
	file.open("catalogue.txt", std::fstream::app);
	file << GetID() << '\t' << Space2Underscore(m_name) << '\t' << GetYear() << '\t' << Space2Underscore(m_director) << '\t' << Space2Underscore(m_language) << '\t' << GetBorrowed() << '\t' << Space2Underscore(m_borrowedBy) << std::endl;
	file.close();
}

/**
* Prompts the user to add a fee when a film is being issued
*/
inline void Film::ChargeFee() {
	std::cout << " \n Enter the rental fee for this film: "
		<< "\n" << " Your selection: ";
	getline(std::cin, m_fee); // get the renatal fee
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CATALOGUE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
* Delete an entry from the text file
* 
* Reads the text file line by line and writes it to a temp file unless its a duplicate entry.
* Original file is deleted and the temp file is renamed to match the original.
* 
* If file cannot be opened an error is generated
* If file cannot be renamed an error is generated
* 
* @param[in] item ID
*/
void Catalogue::DeleteFileEntry(std::string& ID) { // function to delete entry from file 
	std::ifstream database("catalogue.txt");
	std::ofstream temp("temp.txt");

	if (database.is_open()) {
		std::string line;
		while (getline(database, line)) { // copy each line to tempory file excluding the one that matches ID
			if (line.find(ID) == std::string::npos) {
				temp << line << std::endl;
			}
		}
	}
	else {
		std::cerr << "Error: couldn't open file \n";
	}
	temp.close(); // close files
	database.close();

	std::remove("catalogue.txt"); // delete original file
	if (std::rename("temp.txt", "catalogue.txt") != 0) { // rename new file that omits deleted entry
		std::cerr << "Error: couldn't rename file \n";
	};

}

/**
* Replace an entry from the text file
*
* Reads the text file line by line and writes it to a temp file unless it matches the obj ID passed to the function
* Original file is deleted and the temp file is renamed to match the original
* obj is saved to the new text file
* 
* If file cannot be opened an error is generated
* If file cannot be renamed an error is generated
*
* @param[in] catalogue entry 
*/
void Catalogue::ReplaceFileEntry(std::vector<std::unique_ptr<Entry>>::iterator entry) {
	std::ifstream database("catalogue.txt");
	std::ofstream temp("temp.txt");

	if (database.is_open()) {
		std::string line;
		while (getline(database, line)) {
			if (line.find((*entry)->m_ID) == std::string::npos) {
				temp << line << std::endl;
			}
		}
	}
	else {
		std::cerr << "Error: couldn't open file \n";
	}
	temp.close();
	database.close();

	std::remove("catalogue.txt");
	if (std::rename("temp.txt", "catalogue.txt") != 0) { // rename new file that omits deleted entry
		std::cerr << "Error: couldn't rename file \n";
	};

	(*entry)->SaveToFile(); // save updated entry to renamed file
}

/**
* Checks if an entry already exists in the catalogue
*
* Iterator goes through each obj in the database checking for matching attributes
* 
* @param[in] catalogue entry
* @param[out] entry exists / does not exist
*/
bool Catalogue::EntryExists(const std::unique_ptr<Entry>& entry) {
	for (auto item = m_database.begin(); item != m_database.end(); item++) { // loop through vector
		if ((*item)->m_name == entry->m_name && (*item)->m_year == entry->m_year) { // if entry has matching name and year
			return true;
		}
		else {
			return false;
		}
	}
}

/**
* User adding an item to the catalogue
*
* User is prompted to add an item to the catalogue, an empty obj calls the constructor
* Checks are made to ensure no duplicates in the catalogue and a message is shown to the
* user if it is a duplicate
* Incorrect input returns user to menu
*/

void Catalogue::AddItem() {
	bool exit = false;
	while (!exit) { // while user does not invoke case 4
		ClearScreen();
		int choice;
		std::unique_ptr<Entry> entry;
		std::cout << "\n" << " What item would you like to add? " << "\n\n" // ask user what item to add
			<< " [1] : Music Album" << "\n"
			<< " [2] : Book" << "\n"
			<< " [3] : Film" << "\n"
			<< " [4] : Main Menu" << "\n"
			<< "\n" << " Your selection: ";
		std::cin >> choice;
		ClearScreen();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ensure cin buffer is cleared
		
		switch (choice) {

		case 1: {
			entry = std::make_unique<MusicAlbum>(); // create MusicAlbum obj and assign to entry ptr
			bool entryExists = EntryExists(entry); // check if entry is already in the catalogue

			if (entryExists == false||m_database.empty()) {
				entry->SaveToFile();
				m_database.push_back(move(entry));  // transfer memory ownership and push onto vector
				
				std::cout << " ***  has been successfully added to the system  *** " << std::endl;
			}
			else {
				std::cout << " The entry already exists in the catalogue." << std::endl;
			}
			ConsolePause();
			break;
		}

		case 2: {
			entry = std::make_unique<Book>(); 
			bool entryExists = EntryExists(entry);

			if (entryExists == false || m_database.empty()) {
				entry->SaveToFile();
				m_database.push_back(move(entry)); 
				std::cout << " ***  has been successfully added to the system  *** " << std::endl;
			}
			else {
				std::cout << " The entry already exists in the catalogue." << std::endl;
			}
			ConsolePause();
			break;
		}
		case 3: {
			entry = std::make_unique<Film>(); 
			bool entryExists = EntryExists(entry);

			if (entryExists == false || m_database.empty()) {
				entry->SaveToFile();
				m_database.push_back(move(entry));
				std::cout << " ***  has been successfully added to the system  *** " << std::endl;
			}
			else {
				std::cout << " The entry already exists in the catalogue." << std::endl;
			}
			ConsolePause();
			break;
		}
		case 4: {
			exit = true; // return to main menu
			break;
		}
		default: {
			std::cout << "Incorrect Input\n"; // incorrect input give, return to menu
			ConsolePause();
		}
		}
	}
}

/**
* Print the entire catalogue
*
* iterate through vector and print each element
*/
void Catalogue::DisplayAll() { // display all objs stored in vector
	std::cout << "\n  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CATALOGUE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << std::endl;
	for (auto const& item : m_database) { // loop through ecach obj and print details
		item->PrintDetails();
	}
}

/**
* User deleting an item from the catalogue
*
* User is shown the entire catalogue and prompted to chose one to delete
* A check is offered to the user to ensure they have selected the correct one
* 
* A bad input will give a message to the user and they can try again
*/
void Catalogue::DeleteItem() {
	std::string ID;
	bool exit = false;

	while (!exit) { // while user does not invoke case 4
		int choice;
		std::string line;

		ClearScreen();
		DisplayAll(); // display entire catalogue

		std::cout << "\n" << " Please enter the ID, e.g. 'MA_1', of the item you wish to delete: " << "\n\n" // ask user what item to delete
			<< "\n" << " Your selection: ";
		std::cin >> ID; // get item ID
		ClearScreen();

		for (auto item = m_database.begin(); item != m_database.end();) { // loop through vector, find matching ID
			if ((*item)->m_ID == ID) {
				(*item)->PrintDetails();
				std::cout << "\n Would you like to delete this item? " << "\n\n" // ask user what item to add
					<< " [1] : Delete Item" << "\n"
					<< " [2] : Reselect Item" << "\n"
					<< " [3] : Main Menu" << "\n"
					<< "\n" << " Your selection: ";
				std::cin >> choice;
				ClearScreen();

				switch (choice) {

				case 1: {
					item = m_database.erase(item); // delete the item from database
					DeleteFileEntry(ID);
					std::cout << " *** Entry successfully deleted *** " << std::endl;
					exit = true;
					break;
				}
				case 2: {
					ConsolePause();
					break;
				}
				case 3: {
					exit = true;
					break;
				}
				default: {
					std::cout << "Incorrect Input\n"; // incorrect input give, return to menu
					ConsolePause();
				}
				}
				break;
			}
			else {
				item++;
			}
		}
	}
}

/**
* User deleting an item from the catalogue
*
* User is shown the entire catalogue and prompted to chose one to delete
* A check is offered to the user to ensure they have selected the correct one
*
* A bad input will give a message to the user and they can try again
*/
void Catalogue::IssueItem() {
	bool exit = false;

	while (!exit) { // while user does not invoke case 3
		std::string line;
		int choice;

		ClearScreen();
		DisplayAll(); // display entire catalogue

		std::string memberID;
		std::string ID;
		std::cout << "\n" << " Please enter the ID, e.g. 'MA_1', of the item you wish to issue: " << "\n\n" // ask user what item to delete
			<< "\n" << " Your selection: ";
		getline(std::cin, ID); // get item ID
		ClearScreen();

		for (auto item = m_database.begin(); item != m_database.end();) { // loop through vector, find matching ID
			if ((*item)->m_ID == ID && (*item)->m_borrowed == false) { // if ID matches and the item is available 
				(*item)->PrintDetails();
				std::cout << "\n Would you like to issue this item? " << "\n\n" // confirm user has selected the intended item
					<< " [1] : Issue Item" << "\n"
					<< " [2] : Reselect Item" << "\n"
					<< " [3] : Main Menu" << "\n"
					<< "\n" << " Your selection: ";
				std::cin >> choice;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clear the cin bufferA
				ClearScreen();

				switch (choice) {
				case 1: {
					(*item)->ChargeFee(); // will only be invoked if film is selected
					ClearScreen();

					std::cout << "\n Please provide the member ID of the customer: " << std::endl;
					getline(std::cin, memberID); // get member ID
					ClearScreen();

					(*item)->EntryBorrowed(memberID); // set status to borrowed
					ReplaceFileEntry(item);
					exit = true;
					break;
				}
				case 2: {
					ConsolePause();
					break;
				}
				case 3: {
					exit = true;
					break;
				}
				default: {
					std::cout << "Incorrect Input\n"; // incorrect input give, return to menu
					ConsolePause();
					break;
				}
				}
				break;
			}
			else if ((*item)->m_ID == ID && (*item)->m_borrowed == true) { // if item is currently on loan
				(*item)->PrintDetails();
				std::cout << " \n The item you have requested to issue is not currently available. \n";
				ConsolePause();
				break;
			}
			else {
				item++;
			}
		}
	}
}

/**
* User returning an item to the catalogue
*
* User is shown the entire catalogue and prompted to chose one to return
* A check is offered to the user to ensure they have selected the correct one
* Updates borrowed to false
* ReplaceEntry(item) replaces the text file entry to the updated values
*
* A bad input will give a message to the user and they can try again
*/
void Catalogue::ReturnItem() {
	bool exit = false;

	while (!exit) { // while user does not invoke case 4
		std::string ID;
		std::string line;
		int choice;

		ClearScreen();
		DisplayAll(); // display entire catalogue
		
		std::cout << "\n" << " Please enter the ID, e.g. 'MA_1', of the item you wish to return: " << "\n\n" // ask user what item to delete
			<< "\n" << " Your selection: ";
		getline(std::cin, ID); // get item ID
		ClearScreen();

		for (auto item = m_database.begin(); item != m_database.end();) { // loop through vector, find matching ID
			if ((*item)->m_ID == ID && (*item)->m_borrowed == true) {
				(*item)->PrintDetails();
				std::cout << "\n Would you like to return this item? " << "\n\n" // ask user what item to add
					<< " [1] : Return Item" << "\n"
					<< " [2] : Reselect Item" << "\n"
					<< " [3] : Main Menu" << "\n"
					<< "\n" << " Your selection: ";
				std::cin >> choice;
				ClearScreen();

				switch (choice) {

				case 1: {
					(*item)->EntryReturned();
					ReplaceFileEntry(item);
					exit = true;
					break;
				}
				case 2: {
					ConsolePause();
					break;
				}
				case 3: {
					exit = true;
					break;
				}
				default: {
					std::cout << "Incorrect Input\n"; // incorrect input give, return to menu
					ConsolePause();
				}
				}
				break;
			}
			else if((*item)->m_ID == ID && (*item)->m_borrowed == false) {
				std::cout << " Item is not currently on loan so cannot be returned. Please check you selected the right item. \n"; // incorrect input give, return to menu
				ConsolePause();
				break;
			}
			else {
				item++;
			}
		}
	}
}

/**
* Allows a user to search for an item in the catalogue
*
* A user can search the catalogue by ID, name, member ID or year of release
* An iterator is used to find the matchin obj in the catalogue
* If a match is found the details of the item will be printed on screen to the user
* 
* If no match is found a message will be shown to the user
*/
void Catalogue::SearchItem() {
	bool found = false;
	std::string search;

	std::cout << " \n You can search this catalogue by: ID, Name, the member ID of who it is issued to or the year of release \n "
		<< "\n" << " Please enter your search: " << "\n\n" // ask user for search term
		<< "\n" << " Your search: ";
	getline(std::cin >> std::ws, search); // get search term
	ClearScreen();

	for (auto item = m_database.begin(); item != m_database.end(); item++) { // loop through vector, find matching term
		if ((*item)->m_ID == search || (*item)->m_name == search || (*item)->m_borrowedBy == search || (*item)->m_year == search) {
			found = true;
			std::cout << "\n Search Result \n" << std::endl;
			(*item)->PrintDetails();
		}
	}
	if (found == false) {
		std::cout << " \n No entries matched your search term... \n" << std::endl;
	}
	else {}
}

/**
* Checks to see if a specified file exists
*
* @param[in] file path
* 
* @param[out] file exists / does not exist
*/
inline bool Catalogue::FileExists(const std::string& fileName) { //check that a file exists 
	struct stat buffer;
	if (stat(fileName.c_str(), &buffer) != -1) {
		return true;
	}
	return false;
}

/**
* Reads the entries from a text file and adds them to the database vector
*
* Base class attributes are read in first and the ID dictates how the rest of the entry will be read in
* If catalogue file does not exist it will be created ready for writing
* 
* @param[in] file path
*/
void Catalogue::ReadFile(std::string& fileName) {
	std::ifstream inFile(fileName);
	std::string ID, name, year, borrowed, borrowedBy;
	bool fileExists = FileExists(fileName);
	if (fileExists == true) {
		while (inFile >> ID) { // read in parent attributes
			inFile >> name;
			inFile >> year;

			if (ID.find("MA_") != std::string::npos) { // if ID code is that of a music album 
				std::string artist, recordLabel;
				inFile >> artist;
				inFile >> recordLabel;
				inFile >> borrowed;
				inFile >> borrowedBy;
				m_database.push_back(std::make_unique<MusicAlbum>(name, year, artist, recordLabel, StringBool(borrowed), borrowedBy, true));
			}
			else if (ID.find("B_") != std::string::npos) { // if ID code is that of a book
				std::string author, publisher, edition;
				inFile >> author;
				inFile >> publisher;
				inFile >> edition;
				inFile >> borrowed;
				inFile >> borrowedBy;
				m_database.push_back(std::make_unique<Book>(name, year, author, publisher, edition, StringBool(borrowed), borrowedBy, true));
			}
			else { // if ID code is that of a film
				std::string director, language;
				inFile >> director;
				inFile >> language;
				inFile >> borrowed;
				inFile >> borrowedBy;
				m_database.push_back(std::make_unique<Film>(name, year, director, language, StringBool(borrowed), borrowedBy, true));
			}
		}
	}
	else {
		std::ofstream makeFile;
		makeFile.open("catalogue.txt", std::ofstream::out | std::ofstream::app);
		makeFile.close();
	}
}

/**
* Import a pre-existing catalogue in the form of a tab dellimeted text file
*
* User is prompted to enter the file path/name of a .txt file they wish to import
* The path is checked to contain ".txt" to ensure the file is of the correct format
* The path is checked to exist using FileExists() 
* When the file has been read the user is shown a success message and the database vector is updated
* 
* If user provides a file that is not a .txt file they are shown a warning message
* If a user provides a .txt file but it does not exist they are shown a warning message
*/
void Catalogue::ImportCatalogue() {
	std::string fileName;
	std::string check = ".txt"; // implement check criteria to ensure a txt file is provided

	std::cout << " \n You can import a pre-existing catalogue in a .txt file format that is tab separated \n "
		<< "\n" << " Please enter the name of the file you wish to import in the form 'filename.txt': " << "\n\n" // get the name of the file to import 
		<< "\n" << " Your entry: ";
	std::cin >> fileName; // get search term
	ClearScreen();

	if (fileName.find(check) != std::string::npos) { // check that the file contains .txt
		bool fileExists = FileExists(fileName);
		if (fileExists == true) {
			ReadFile(fileName);
			std::cout << " \n Catalogue successfully imported. " << std::endl;
		}
		else
		{
			std::cout << " \n File does not exist. " << std::endl;
		}
	}
	else {
		std::cout << "\n You have not provided a .txt file, please try again. " << std::endl;
	}
}

/**
* Displays the number of individual items and total items in the catalogue
*
* The item counters are accessed for each class and displad to the user
*/
void Catalogue::DisplayStats() {
	std::cout << " \n This catalogue currently contains: \n"
		<< " Entries:      " << MusicAlbum::GetItemCount() + Book::GetItemCount() + Film::GetItemCount()
		<< "\n Music Albums: " << MusicAlbum::GetItemCount()
		<< "\n Books:        " << Book::GetItemCount()
		<< "\n Films:        " << Film::GetItemCount();
}

