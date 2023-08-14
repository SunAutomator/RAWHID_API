#include "database.h"
#include "mysql.h"

static int execute_query(DatabaseConnection db_conn, const char *query);

DatabaseConnection db_connect(db_connection_info_t *connection_info) {
    MYSQL* conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }

    if (mysql_real_connect(conn, connection_info->host, connection_info->user, 
                          connection_info->password, connection_info->database, 
                          connection_info->port, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }

    return (DatabaseConnection) conn;
}

void db_disconnect(DatabaseConnection db_conn) {
    mysql_close((MYSQL*)db_conn);
}

int record_message_in_database(DatabaseConnection db_conn, const char *message, const char *status) {
    char escaped_message[2 * strlen(message) + 1];
    char escaped_status[2 * strlen(status) + 1];

    mysql_real_escape_string((MYSQL*)db_conn, escaped_message, message, strlen(message));
    mysql_real_escape_string((MYSQL*)db_conn, escaped_status, status, strlen(status));

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO raw_hid (message, status, timestamp) VALUES ('%s', '%s', NOW())", escaped_message, escaped_status);
    return execute_query(db_conn, query);
}

int record_response_in_database(DatabaseConnection db_conn, const char *response, const char *status) {
    char escaped_response[2 * strlen(response) + 1];
    char escaped_status[2 * strlen(status) + 1];

    mysql_real_escape_string((MYSQL*)db_conn, escaped_response, response, strlen(response));
    mysql_real_escape_string((MYSQL*)db_conn, escaped_status, status, strlen(status));

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO raw_hid (message, status, timestamp) VALUES ('%s', '%s', NOW())", escaped_response, escaped_status);
    return execute_query(db_conn, query);
}

static int execute_query(DatabaseConnection db_conn, const char *query) {
    if (mysql_query((MYSQL*)db_conn, query)) {
        fprintf(stderr, "INSERT failed: %s\n", mysql_error((MYSQL*)db_conn));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
