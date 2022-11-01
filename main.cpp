#include "Entry.h"

/**
* The main menu should be intuitive to navigate however when moving between menus you may have to press enter more than once
* (usually twice is sufficient) due to the console pause. 
* 
* The system automatically creates a .txt file that dynamically updates as you add items to the catalogue so that they will still
* be there when you next run the program.
* 
*/
int main(void) {
    int choice;
    bool exit = false;
    Catalogue catalogue;
    std::string fileName = "catalogue.txt";
    catalogue.ReadFile(fileName);

    while (!exit) {
        
        ClearScreen();
        std::cout << "\n" << " Welcome to the library catalogue system. \n Entries are automatically saved into 'catalogue.txt' file for your convenience. \n Please select an option from the following: " << "\n\n"
            << " [1] : Add a new item \n"
            << " [2] : Delete an item \n"
            << " [3] : Search for an item \n"
            << " [4] : Issue an item \n"
            << " [5] : Return an item \n"
            << " [6] : Import a catalogue \n"
            << " [7] : View the catalogue \n"
            << " [8] : Display the total number of entries \n"
            << " [9] : Exit the program \n"
            << "\n" << " Your selection: ";
        std::cin >> choice;
        ClearScreen();

        switch (choice) {

        case 1: {
            catalogue.AddItem();
            ConsolePause();
            break;
        }

        case 2: {
            catalogue.DeleteItem();
            ConsolePause();
            break;
        }
        case 3: {
            catalogue.SearchItem();
            ConsolePause();
            break;
        }
        case 4: {
            catalogue.IssueItem();
            ConsolePause();
            break;
        }
        case 5: {
            catalogue.ReturnItem();
            ConsolePause();
            break;
        }
        case 6: {
            catalogue.ImportCatalogue();
            ConsolePause();
            break;
        }
        case 7: {
            catalogue.DisplayAll();
            ConsolePause();
            break;
        }
        case 8: {
            catalogue.DisplayStats();
            ConsolePause();
            break;
        }
        case 9: {
            exit = true;
            break;
        }
        default: {
            std::cout << "Incorrect Input\n";
            ConsolePause();
        }
        }
    }
    return 0;
}