#include "service_manager.h"
#include <windows.h>
#include <stdio.h>

HIDDeviceHandle device;
//DatabaseConnection db_conn;
TCPClient tcp_client;

void initialize_hid_device();
//void initialize_database();
void initialize_tcp_client();

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv) {
    
    // Register the handler function for the service
    SERVICE_STATUS_HANDLE hStatus = RegisterServiceCtrlHandler("HID_Router", ServiceCtrlHandler);
    if (hStatus == 0) {
        return;
    }

    //initialize_database();

    initialize_tcp_client();

    // Inform the service control manager that the service is running
    SERVICE_STATUS status = {0};
    status.dwServiceType = SERVICE_WIN32;
    status.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &status);

    initialize_hid_device();

    // Perform the server operations
    while (true) {
        // Forward using tcp
        tcp_client_send(&client, data->data, data->length);

        unsigned char response_buffer[256];
        int response_len = tcp_client_receive(&client, response_buffer, sizeof(response_buffer));

        if (response_len > 0) {
            // Translate TCP response to HID response and send it back
            hid_respond(device, response_buffer, response_len);
        }
    }
}

// Control handler function
VOID WINAPI ServiceCtrlHandler(DWORD fdwControl) {
    switch (fdwControl) {
        case SERVICE_CONTROL_SHUTDOWN:
            hid_close_device(device);
            //db_disconnect(db_conn);
            close_logger();
            break;
        default:
            break;
    }
}

int initialize_service(int argc, char *argv[]) {
    // Initialize the logger
    init_logger();

    // Register the handler function for the service
    SERVICE_TABLE_ENTRY serviceTable[] = {
        { "HID_Router", ServiceMain },
        { NULL, NULL }
    };

    // Start the service control dispatcher
    if (!StartServiceCtrlDispatcher(serviceTable)) {
        // Handle error
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void initialize_hid_device() {
    char* decrypted_data = get_decrypted_config("hid.config");
    hid_device_usage_config config;
    // Assuming decrypted data is in JSON or some easy-to-parse format:
    // This is a simple parser and will need to be replaced with an actual JSON or XML parser based on your config format.
    sscanf(decrypted_data, "{ \"vendor_id\": \"%hx\", \"product_id\": \"%hx\", \"target_usage_page\": \"%hx\", \"target_usage\": \"%hhx\" }", 
           &config.vendor_id, &config.product_id, &config.target_usage_page, &config.target_usage);
    free(decrypted_data);
    // Here you might need to read some config if required.
    device = hid_open_device(config);
    if (device == NULL) {
        printf("HID device opening failed\n");
        write_log("HID device opening failed");
        //db_disconnect(db_conn);
        return;
    }
}

// void initialize_database() {
//     // Read database configuration file
//     char* db_config_data = get_decrypted_config("repository.config");
//     db_connection_info_t connection_info;
//     if (db_config_data) {
//         if (sscanf(db_config_data, "%s %d %s %s %s", connection_info.host, &connection_info.port,
//                connection_info.user, connection_info.password, connection_info.database) != 5) {
//             // Handle parsing error
//             free(db_config_data);
//             printf("Database configuration file is corrupted\n");
//             write_log("Database configuration file is corrupted");
//             return;
//         }
//         free(db_config_data);
//     }

//     // Connect to the database
//     db_conn = db_connect(&connection_info);
//     if (db_conn == NULL) {
//         printf("Database connection failed\n");
//         write_log("Database connection failed");
//         return;
//     }
// }

void initialize_tcp_client() {
    char* config_data = get_decrypted_config("tcp_client.config");
    tcp_client_connection_info_t connection_info;

    if (config_data) {
        if (sscanf(config_data, "%s %d", connection_info.host, &connection_info.port) != 2) {
            // Handle parsing error
            free(config_data);
            printf("TCP Client configuration file is corrupted\n");
            write_log("TCP Client configuration file is corrupted");
            return;
        }
        free(config_data);
    }

    if (!tcp_client_connect(&tcp_client, "127.0.0.1", 8080)) {
        write_log("Failed to connect to TCP Router");
        return;
    }
}
