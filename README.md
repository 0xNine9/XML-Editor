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
A short demo for the project can be found in [Here](https://drive.google.com/drive/folders/1bTCNUiJa6xAfqMQF5LiEZuhSYPcjPOXm?usp=share_link)

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

`Xml_parse()` parses the XML text and creates a parse tree.

![image](https://user-images.githubusercontent.com/62956414/216623892-1ba0b7c4-302a-4e0f-ab24-2110a2e07090.png)


`validate()` returns any errors detected in the XML text.

![image](https://user-images.githubusercontent.com/62956414/216624065-b7bb4df6-3bf5-4361-aa9c-ec0c918be2f7.png)


`get_tree()` returns the parse tree of the XML text.

`compress()` compresses the XML text.

![image](https://user-images.githubusercontent.com/62956414/216625454-75c9c1f9-1b86-4d2d-b56c-a45ba1b42ace.png)


`decompress()` decompresses the XML text.
![image](https://user-images.githubusercontent.com/62956414/216625513-714114ff-0281-40ba-9dd2-f02ab2e65b4f.png)

`minify()` removes white spaces and newlines from the XML text.

![image](https://user-images.githubusercontent.com/62956414/216625609-27f0027c-1c43-47b3-913b-f8a8d2483495.png)


`prettify()` formats the XML text in a readable format.
![image](https://user-images.githubusercontent.com/62956414/216629073-f6e11bf7-6ded-4aef-90f4-966025ebe330.png)


`convert_json()` converts the XML text to a JSON format.
![image](https://user-images.githubusercontent.com/62956414/216628946-9936cc5c-6626-4949-8106-4f555053e267.png)

#### Dependencies
The XmlEditor class uses Node class to parse the XML text and create the parse tree. The SString class provides helper functions for string manipulation. The Compressor class compresses and decompresses the XML text.


### SocialNetwork Class
A C++ implementation of a social network, where you can find the most influential user and the most active user based on the followers and posts in the network.

#### Methods
`followers_list(Node* root)`: takes the root of the Social Network tree and stores the information about the users and their followers in the `users` member.
![image](https://user-images.githubusercontent.com/62956414/216629728-361b2a71-9190-4be6-aa8f-fd7b312ca2d7.png)

`posts_vector(Node* root)`: takes the root of the Social Network tree and stores the information about the posts in the `posts` member.
![image](https://user-images.githubusercontent.com/62956414/216629560-cde011d3-d0b9-4fcc-bd9e-1820129fcd2f.png)

 `string get_post(int i)`: returns the body of the post at index `i` in the `posts` member.

 `string most_influencer()`: returns the most influential user in the network.
 ![image](https://user-images.githubusercontent.com/62956414/216629922-0c483d38-88f2-4847-a660-194c807e05b2.png)

 `string most_active()`: returns   the most active user in the network.
 ![image](https://user-images.githubusercontent.com/62956414/216629875-1f79191b-450a-4a99-ad95-54ecb6e5ba5a.png)

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
