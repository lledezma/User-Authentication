# User-Authentication

## Overview

This project is a simple user authentication system that allows users to register accounts with login credentials, log in to their accounts, and log out. User data is stored in an XML file using [tinyxml2](include/tinyxml2.h), a lightweight and open-source XML parser.

## Features

- Register new accounts with username and password
- Log in with existing credentials
- Log out functionality
- User data stored in `Accounts.xml` using XML format

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++, clang++, MSVC)
- All files (`main.cpp` and the `include/` folder) must be in the same directory

### Build Instructions

1. Clone the repository or download the source files.
2. Compile the project using your preferred C++ compiler. Example with g++:
	```sh
	g++ main.cpp include/tinyxml2.cpp -o user-auth
	```
3. Run the executable:
	```sh
	./user-auth
	```

### Usage

- Run the program and follow the prompts to register, log in, or log out.
- User accounts are stored in `Accounts.xml` in the project directory.

## Project Structure

```
.gitignore
main.cpp
README.md
include/
	 tinyxml2.cpp
	 tinyxml2.h
```

- `main.cpp`: Main application logic for user authentication.
- `include/tinyxml2.h`, `include/tinyxml2.cpp`: TinyXML-2 library for XML parsing and manipulation.

## License

This project uses TinyXML-2, which is distributed under the zlib license. See the header of `include/tinyxml2.h` for details.

