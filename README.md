# C++ Library Management System

This is a library management system created using C++. It provides the main functions you would expect from a library database system, such as adding, deleting, issuing, returning, etc.



## Features

* Add three entry types: music album, book or film
* Delete an entry
* Search the database by item ID, name, year or member ID
* Issue an entry
* Return an entry
* Import a pre-existing catalogue from a .txt file
* View the current catalogue
* View the number of entries in the catalogue
* Automatically creates and updates 'catalogue.txt' as changes are made 



## Project Status

Project is complete



## Improvements and Limitations

* The search function is case sensitive
* A user can only search by parent attributes 
  * Being able to search for the artist of a music album for example would be useful
* When importing an external catalogue the base "catalogue.txt" file is not updated
* An alternative storage container such as a map would speed up searches if the catalogue were to become large