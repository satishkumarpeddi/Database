C Database Engine Documentation
This document explains the architecture and components of the database engine we are building.

🏗️ Architecture Overview

The database follows a classic tiered architecture:

Frontend (REPL): The entry point that reads user input.
Middle Tier (Compiler): Translates raw text into internal "Opcodes" or Statements.
Backend (Virtual Machine): Executes the statements against the storage layer.

🧩 Component Breakdown

1. Input Handling (InputBuffer)
Manages the state of the user's input. We use a heap-allocated buffer to store the current command string.

new_input_buffer()
: Allocates memory for the buffer and initializes its state.
read_input()
: Uses getline() (or a portable equivalent) to safely read arbitrary-length lines from stdin.
2. The Compiler (
prepare_statement
)
The "Brain" that understands SQL. It performs string analysis to determine the user's intent.

Enums: PrepareResult tracks if the command was understood.
Logic: It currently looks for keywords like insert and select.
Output: Produces a Statement object which is the "machine code" of our database.
3. The Virtual Machine (
execute_statement
)
The "Engine" that carries out the physical work.

It uses a switch statement to dispatch the correct logic based on the StatementType.
This separation allows us to change how we store data without changing how we parse it.

⚠️ Known Implementation Details (The "Segfault" Fixes)

1. Proper Malloc Size
When allocating a struct behind a typedef pointer, we must allocate the size of the struct, not the size of the pointer.

Incorrect: malloc(sizeof(InputBuffer)) (Allocates 4 or 8 bytes)
Correct: malloc(sizeof(struct inputbuffer)) (Allocates the full struct)
2. Pointer Initialization
Before passing a Statement to 
prepare_statement
, memory must be allocated for it. Providing an uninitialized pointer causes the program to attempt to write to random memory, resulting in a Segmentation Fault.

Solution: We either allocate memory on the heap for the statement or pass a pointer to a stack-allocated struct.
🛠️ How to Compile & Run
bash
gcc db.c -o db.exe
./db.exe
Inside the prompt:

Use .exit to close the database.
Use insert or select to test the engine.