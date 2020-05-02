/*==================================================================================================

                           Copyright (c) Kartik Srivastava
                           All Rights Reserved.

====================================================================================================
Project description:
    
This project allows the user to leverage the capabilities from a text based interface.
No UI is supported now.
The operations supported are:
Read from a text file or from console
	- input supported is in a line-by-line format
Write to a text file or from console
Load previous data from the session
Undo/Redo operations on a per line basis
Search and Replace-All operations on the entire data
A separate thread runs in the background that saves the file periodically to prevent any data loss
On unintended interrupts an interrupt call takes care of saving the data before session exit
The data is written to the file load_file_text_based_interface.txt from where it could be read next time the application is loaded

Note: The is customizable and developers may modify it as per their own requirements. Code may be downloaded by sending pull requests
====================================================================================================
   Date       Name                    Description of Change
22-Apr-2020   Kartik Srivastava       Created
$HISTORY$
==================================================================================================*/

----------------------
Command Line Arguments
----------------------

enter 1 or any other number to load previous data or not load respectively (it is good to have file load_file_text_based_interface.txt in the directory)
enter 1 to read from a previous file or any other number to read from console
enter texts line by line to read into the interface
a left arrow followed immediately by ENTER would apply undo on the previously entered line and so on
a right arrow followed immediately by ENTER would apply redo if applicable (if an undo preceded immediately)
a down arrow key followed immediately by ENTER would allow search operations on the interface
an up arrow key followed immediately by ENTER would alow searching and replacing all the search results with a new line
a CTRL followed immediately by ENTER key would terminate the input process
enter 1 to write the texts to a file or any other number to display texts to the console.

-------------------------
Design Description
-------------------------
I have implemented separate utilities to handle file handling operations. a utility to handle all operations and a data model class which holds on the data.
Each implementation has their own interfaces exposed to the clients. 
A simple MenuHandler utility takes care of all the menu items displayed at appropriate places

-------------------------
Uses
-------------------------
Could be leveraged to implement simple functionalities like handling a big chunk of text and implementing 
undo and redo on it on the fly; per line basis unline other textual interfaces
search and replace-all operations too are quite handy

-------------------------
Future improvements
-------------------------
Plan to add a history utility class to enable system log generation and tracking user input keys

/*==================================================================================================*/

