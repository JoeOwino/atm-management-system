# ATM Management System

## Project Overview
This is an ATM management system implemented in C that allows users to perform various banking operations. The system provides features for user authentication, account management, and financial transactions.

## Features

### Core Features
- **User Authentication**
  - Login with existing credentials
  - Register new users (with unique username validation)
  
- **Account Management**
  - Create new accounts
  - View details of existing accounts (with interest calculations)
  - Update account information (country and phone number)
  - Remove existing accounts
  - Transfer account ownership to another user

- **Transactions**
  - Deposit funds
  - Withdraw funds
  - Restrictions on fixed-term accounts

### File System Structure
```
.
├── data
│   ├── records.txt (stores account information)
│   └── users.txt (stores user credentials)
│   └── history.txt (stores transaction history)
├── Makefile
└── src
    ├── auth.c (authentication logic)
    ├── header.h (header file)
    ├── main.c (main program)
    |── system.c (system operations)
    |── acconts.c (Accounts operations)
    |── docs.c (file operations)
    └── registratio.c (Register users)

```

### Data Format
- **users.txt**: `(id, name, password)`
- **records.txt**: `(id, user_id, user name, account id, date of creation, country, phone nº, balance, type of account)`


## Getting Started

### Prerequisites
- A C compiler
- Make utility

### Installation
1. Clone the repository:
   ```bash
   git clone https://learn.zone01kisumu.ke/git/joseowino/atm-management-system.git
   ```
2. Navigate to project directory:
   ```bash
   cd atm-management-system
   ```
3. Compile using Makefile:
   ```bash
   make
   ```
4. Run the executable:
   ```bash
   ./atm_system
   ```

## Usage
1. Register or login with existing credentials
2. Navigate the menu to perform various banking operations
3. All changes are automatically saved to the corresponding files

## Implementation Details
The project demonstrates:
- C language fundamentals
- File manipulation and data structures
- Memory management
- Makefile usage

## Contributing
Contributions are welcome! Please submit issues or pull requests for any improvements.

## Author
Joseph Owino (joseowino)