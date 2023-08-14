// database.h
#ifndef database_h
#define database_h

#include <mysql.h>
#include <stdio.h>

#pragma once

typedef struct db_connection_info_t {
    char* host;
    char* user;
    char* password;
    char* database;
    unsigned int port;
} db_connection_info_t;

typedef void* DatabaseConnection;

DatabaseConnection db_connect(db_connection_info_t *connection_info);
void db_disconnect(DatabaseConnection conn);

int record_message_in_database(DatabaseConnection db_conn, const char *message, const char *status);
int record_response_in_database(DatabaseConnection db_conn, const char *response, const char *status);
static int execute_query(DatabaseConnection db_conn, const char *query);

#endif // database_h
