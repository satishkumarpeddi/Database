Building Our Database

We'll maintain two ways of looking at this: a simple "Friendly Data Box" view for intuition, and a "Technical Engine" view for deep knowledge.

🧸 Simple View (Friendly Data Box)
The Listener (REPL): The ear that hears your commands.
The Translator (Compiler & VM): Turns your words into robot-talk.
The Notebook (Pager): Writes things down on the disk so it's permanent.
The Organizer (B-Tree): Keeps the notebook tidy so we can find things fast.
⚙️ Technical View (The Engine)

1. REPL (Read-Execute-Print Loop)
The main interface. We use getline() to read input from stdin. It parses "meta-commands" (starting with .) and handles "SQL statements".

2. SQL Compiler & Virtual Machine
Tokenizer/Parser: Checks if the SQL is valid (e.g., insert, select).
VM: Executes internal opcodes. Instead of directly writing to disk, it tells the storage engine what to do.
3. Pager & Disk Persistence
Pager: Manages a cache of "pages" (usually 4KB). It reads from and writes to the database file.
Persistence: Ensures that even if the program crashes, the data stays on the disk.
4. B-Tree Storage
The core data structure. SQLite uses B-Trees to store tables and indexes. It allows $O(\log n)$ search, insert, and delete.

Proposed Changes
[Component] Core Database Shell
[NEW] 
db.c
The main entry point. We'll start with the REPL and basic command handling.

Verification Plan
Automated & Manual Tests
Verify .exit works.
Verify insert and select work in-memory first.
Verify data persists after closing and reopening the database.

Implementing the SQL Translator (Compiler & VM)
We are moving from a simple "Exit Only" REPL to a system that can understand and execute SQL commands (like insert and select).

Proposed Changes
[Component] SQL Front-end & VM
[MODIFY] 
db.c
Define MetaCommandResult enum to handle meta-commands like .exit.
Define PrepareResult enum to handle SQL parsing results.
Define StatementType enum (INSERT, SELECT) and a Statement struct.
Implement do_meta_command() to handle commands starting with ..
Implement prepare_statement() (the "Compiler") to parse input into a Statement.
Implement execute_statement() (the "Virtual Machine") to execute the Statement.
Update the main loop to use these new components.
Verification Plan
Manual Verification
Run the compiled 
db.exe
.
Test .exit (should still work).
Test .unrecognized (should show error).
Test insert (should print "This is where we would do an insert.").
Test select (should print "This is where we would do a select.").
Test an unknown SQL command (should print "Unrecognized keyword at start of '...'.").