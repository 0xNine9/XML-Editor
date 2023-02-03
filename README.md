# XML Editor

This is a Qt-based main window application for XML file editing. It allows you to create new XML files, open existing files, save files and exit the application. It also has features for compressing, decompressing and converting XML files to JSON. The application has a graphical user interface (GUI) that makes it easy to use. This project is a final project for Data Structures and Algorithms (CSE331s) and is developed by a group of students.

## Prerequisites

  - Qt 5 or higher
  - C++ compiler
  
  
## Installation
  1. Clone or download the repository to your local machine.
  2. Open the .pro file using Qt Creator.
  3. Build and run the application.
  
  Or simply run the `.exe` file, which you can download from [Here](https://drive.google.com/drive/folder/1bTCNUiJa6xAfqMQF5LiEZuhSYPcjPOXm?usp=share_link)


## Usage

    1. Choose the "New" option in the "File" menu to create a new XML file.
    2. Choose the "Open" option in the "File" menu to open an existing XML file.
    3. Choose the "Save" option in the "File" menu to save changes to the current file.
    4. Choose the "Save As" option in the "File" menu to save the file with a different file name.
    5. Choose the "Compress" option in the "Edit" menu to compress the current XML file.
    6. Choose the "Decompress" option in the "Edit" menu to decompress the current XML file.
    7. Choose the "Convert to JSON" option in the "Edit" menu to convert the current XML file to JSON.
    8. Choose the "Exit" option in the "File" menu to exit the application.
A short demo for the project can be found in [here](https://drive.google.com/drive/folders/1bTCNUiJa6xAfqMQF5LiEZuhSYPcjPOXm?usp=share_link)

## Code Overview
### XMLEditor Class
an XmlEditor class that allows you to perform various operations on XML text such as parsing, formatting, compressing, decompressing, converting to JSON and so on.

To use the XmlEditor class, you need to include the header file "XmlEditor.h". The class takes a string argument representing the XML text you want to work with.
```C++ #include "XmlEditor.h"
using namespace std;

string xml_text = "<xml>...</xml>";
XmlEditor xml_editor(xml_text); 

```

#### Methods

The class provides several methods to perform operations on the XML text.

`get_current_text()` returns the current XML text being worked on.

`set_current_text(string str)` updates the current XML text with the new string.
 
`get_original_text()` returns the original XML text.

`get_errors()` returns any errors detected in the XML text.

`get_tree()` returns the parse tree of the XML text.

`Xml_parse()` parses the XML text and creates a parse tree.

`compress()` compresses the XML text.

`decompress()` decompresses the XML text.

`prettify()` formats the XML text in a readable format.

`minify()` removes white spaces and newlines from the XML text.

`convert_json()` converts the XML text to a JSON format.

#### Dependencies
The XmlEditor class uses Node class to parse the XML text and create the parse tree. The SString class provides helper functions for string manipulation. The Compressor class compresses and decompresses the XML text.


### SocialNetwork Class
A C++ implementation of a social network, where you can find the most influential user and the most active user based on the followers and posts in the network.

#### Methods
`followers_list(Node* root)`: takes the root of the Social Network tree and stores the information about the users and their followers in the `users` member.

`posts_vector(Node* root)`: takes the root of the Social Network tree and stores the information about the posts in the `posts` member.

 `string get_post(int i)`: returns the body of the post at index `i` in the `posts` member.

 `string most_influencer()`: returns the most influential user in the network.
 
 `string most_active()`: returns   the most active user in the network.
#### Dependencies

The SocialNetwork class uses Node class to parse the XML text and create the parse tree. The SString class provides helper functions for string manipulation, The User class represents the users in the social network, with the following member variables:

    int id: the user's id
    string name: the user's name
    vector<int> followers: the user's followers and Dict class.

A detailed report of the project can be found [Here](https://drive.google.com/drive/folders/1bTCNUiJa6xAfqMQF5LiEZuhSYPcjPOXm?usp=share_link)


## Contributors

The following individuals have contributed to this project:

1. [Nour-Osama](https://github.com/Nour-Osama)
2. [Abdelrahmnan-Osama](https://github.com/Abdelrahmnan-Osama)
3. [ather8](https://github.com/ather8)
4. [BasselYD](https://github.com/BasselYD)
5. [0xNine9](https://github.com/0xNine9)


## Features
    - Create new XML files.
    - Open existing XML files.
    - Save XML files.
    - Save XML files with a different file name.
    - Compress XML files.
    - Decompress XML files.
    - Convert XML files to JSON.
    - Minify XML files
    - prettify XML files
    - Exit the application.


## Conclusoin
This XML Editor application is a simple tool that can be used to edit XML files with ease. With its user-friendly interface and various functionalities, it provides an efficient and convenient way to work with XML files.
