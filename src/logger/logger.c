#include "logger.h"

FILE *logFile = NULL;
HANDLE logMutex = NULL;

void init_logger() {
    logFile = fopen("C:\\Users\\avons\\Code\\Chrome\\ChromeProxyHost\\logFile.txt", "a");
    if (logFile == NULL) {
        perror("Error opening file");
        exit(-1);
    }

    logMutex = CreateMutex(NULL, FALSE, NULL);
    if (logMutex == NULL) {
        // Print the error to stderr
        fprintf(stderr, "Error: Unable to create mutex.\n");
        fclose(logFile);
        exit(-1);
    }
}

void write_log(const char *message) {
    // Get the current time
    time_t current_time;
    char time_string[100]; // buffer to store formatted time
    struct tm *local_time_info;

    time(&current_time);
    local_time_info = localtime(&current_time);

    // Format the time as "YYYY-MM-DD HH:MM:SS"
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", local_time_info);

    WaitForSingleObject(logMutex, INFINITE);  // Wait for ownership of the mutex.

    // Write the log message with the timestamp
    if (fprintf(logFile, "%s: %s\n", time_string, message) < 0) {
        // Print the error to stderr if there's an issue writing to the log
        fprintf(stderr, "Error: Unable to write to log file.\n");
    }

    fflush(logFile);
    ReleaseMutex(logMutex);  // Release ownership of the mutex.
}

void close_logger() {
    if (logFile) {
        fclose(logFile);
    }
    if (logMutex) {
        CloseHandle(logMutex);
    }
}
