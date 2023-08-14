#ifndef _SERVICE_MANAGER_H_
#define _SERVICE_MANAGER_H_
#pragma once

#include "../config/config.h"
#include "../logger/logger.h"

#include "../raw_hid/hid_device_handle.h"
//#include "../database/database.h"
#include "../tcp_client/tcp_client.h"

#include <windows.h>

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);
VOID WINAPI ServiceCtrlHandler(DWORD fdwControl);
int initialize_service(int argc, char *argv[]);

#endif // _SERVICE_MANAGER_H_