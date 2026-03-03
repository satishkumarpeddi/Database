#ifndef DB_H
#define DB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
/** 
    Returned by meta_command() in main.c
    Meta-commands start with '.' (eg., ".exit",".tables") and are handled
    before the SQL parser even sees the input.
    
    codes: 
    META_COMMAND_SUCCESS : The command was recognized and run.
    META_COMMAND_UNRECOGNIZED_COMMAND : We got a '.something' we don't know.
*/
typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
}MetaCommandResult;

/**
 * PrepareResult
 * -------------
 * Returned by prepare_statement() in compiler.c.
 * This layer tokenizes the raw text into a structured Statement object.
 *
 * Codes:
 *   PREPARE_SUCCESS                — Parsing was successful.
 *   PREPARE_SYNTAX_ERROR           — Arguments were present but malformed
 *                                    (e.g., "insert foo bar" — id is not a number).
 *   PREPARE_UNRECOGNIZED_STATEMENT — The keyword itself is unknown
 *                                    (e.g., "upsert 1 a b").
 *
 * NOTE: We add PREPARE_SYNTAX_ERROR now as a separate case even though
 * it's not fully wired up yet. This is forward-thinking: it avoids a future
 * breaking change to the enum and all switch statements that depend on it.
 */
typedef enum{
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT,
}PrepareResult;

#endif