#include "inject.h"

#include <iostream>
#include <map>

#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>

using namespace std;

int main()
{
    string processname = argc > 1 ? argv[1] : "";
    string dllpath = argc > 2 ? argv[2] : "";

    map<string, bool> flag;

    if(argc > 3) {
        for(int i = 3; i < argc; i++) {
            string arg = argv[i];
            for(auto &c : arg) c = tolower(c);
            flag[argv[i]] = true;
        }
    }

    cin >> ws;
    getline(cin, processname);
    cin >> ws;
    getline(cin, dllpath);

    if(processname.empty() || dllpath.empty()) {
        cout << "Usage: " << argv[0] << " <process name> <dll path> [flags]" << endl;
        cout << "Flags:" << endl;
        cout << "  -h, --help: Show this help message" << endl;
        cout << "  -l, --list: List all processes" << endl;
        cout << "  -p, --pid: Use process ID instead of process name" << endl;
        return 0;
    }

    if(flag["-h"] || flag["--help"]) {
        cout << "Usage: " << argv[0] << " <process name> <dll path> [flags]" << endl;
        cout << "Flags:" << endl;
        cout << "  -h, --help: Show this help message" << endl;
        cout << "  -l, --list: List all processes" << endl;
        cout << "  -p, --pid: Use process ID instead of process name" << endl;
        return 0;
    }

    if(flag["-l"] || flag["--list"]) {
        HANDLE hProcessSnap;
        PROCESSENTRY32 pe32;
        hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if(hProcessSnap == INVALID_HANDLE_VALUE) {
            cout << "CreateToolhelp32Snapshot (of processes)" << endl;
            return 1;
        }
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if(!Process32First(hProcessSnap, &pe32)) {
            cout << "Process32First" << endl;
            CloseHandle(hProcessSnap);
            return 1;
        }
        do {
            cout << pe32.th32ProcessID << " " << pe32.szExeFile << endl;
        } while(Process32Next(hProcessSnap, &pe32));
        CloseHandle(hProcessSnap);
        return 0;
    }

    if(flag["-p"] || flag["--pid"]) {
        DWORD pid = atoi(processname.c_str());
        if(pid == 0) {
            cout << "Invalid process ID" << endl;
            return 1;
        }
        if(!inject(pid, dllpath)) {
            cout << "Failed to inject" << endl;
            return 1;
        }
        return 0;
    }

    DWORD pid = get_pid(processname);

    if(pid == 0) {
        cout << "Failed to find process" << endl;
        return 1;
    }

    if(!inject(pid, dllpath)) {
        cout << "Failed to inject" << endl;
        return 1;
    }

    cout << dllpath.data() << endl;
    cout << processname.data() << endl;

    KernelContext *kcontext;
    CapcomContext *ccontext;
}