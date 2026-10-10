#include "CrashDump.hpp"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <dbghelp.h>

#include <atomic>
#include <cstdlib>
#include <cwchar>
#include <exception>
#include <string>
#include <vector>

namespace
{
    std::atomic_flag dumpInProgress = ATOMIC_FLAG_INIT;

    bool CreateDirectoryIfMissing(const std::wstring &path)
    {
        if (CreateDirectoryW(path.c_str(), nullptr))
            return true;

        if (GetLastError() != ERROR_ALREADY_EXISTS)
            return false;

        const DWORD attributes = GetFileAttributesW(path.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
    }

    std::wstring GetCrashDumpDirectory()
    {
        std::vector<wchar_t> basePath(32768);
        DWORD length = GetEnvironmentVariableW(L"LOCALAPPDATA", basePath.data(), static_cast<DWORD>(basePath.size()));
        if (length == 0 || length >= basePath.size())
        {
            length = GetTempPathW(static_cast<DWORD>(basePath.size()), basePath.data());
            if (length == 0 || length >= basePath.size())
            {
                if (GetLastError() == ERROR_SUCCESS)
                    SetLastError(ERROR_PATH_NOT_FOUND);
                return {};
            }
        }

        basePath.resize(length);
        std::wstring directory(basePath.begin(), basePath.end());
        if (!directory.empty() && directory.back() != L'\\' && directory.back() != L'/')
            directory += L'\\';
        directory += L"SLGameLoggerDisplay\\CrashDumps";

        const size_t appDirectoryEnd = directory.rfind(L'\\');
        if (appDirectoryEnd == std::wstring::npos)
        {
            SetLastError(ERROR_PATH_NOT_FOUND);
            return {};
        }

        if (!CreateDirectoryIfMissing(directory.substr(0, appDirectoryEnd)) ||
            !CreateDirectoryIfMissing(directory))
            return {};

        return directory;
    }

    std::wstring MakeDumpPath()
    {
        const std::wstring directory = GetCrashDumpDirectory();
        if (directory.empty())
            return {};

        SYSTEMTIME time;
        GetLocalTime(&time);

        wchar_t fileName[96];
        const int length = std::swprintf(
            fileName,
            sizeof(fileName) / sizeof(fileName[0]),
            L"SLGameLoggerDisplay_%04u%02u%02u_%02u%02u%02u_%lu.dmp",
            time.wYear,
            time.wMonth,
            time.wDay,
            time.wHour,
            time.wMinute,
            time.wSecond,
            GetCurrentProcessId());
        if (length < 0 || static_cast<size_t>(length) >= sizeof(fileName) / sizeof(fileName[0]))
        {
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            return {};
        }

        return directory + L'\\' + fileName;
    }

    void ShowDumpResult(const std::wstring &path, DWORD error)
    {
        if (error == ERROR_SUCCESS)
        {
            const std::wstring message = L"A full crash dump was saved to:\n" + path;
            MessageBoxW(nullptr, message.c_str(), L"SLGameLoggerDisplay crashed", MB_OK | MB_ICONERROR | MB_TASKMODAL);
            return;
        }

        wchar_t message[512];
        std::swprintf(
            message,
            sizeof(message) / sizeof(message[0]),
            L"Failed to write a crash dump (Windows error %lu).\n\nCrash dumps are normally saved under %%LOCALAPPDATA%%\\SLGameLoggerDisplay\\CrashDumps.",
            error);
        MessageBoxW(nullptr, message, L"SLGameLoggerDisplay crashed", MB_OK | MB_ICONERROR | MB_TASKMODAL);
    }

    void WriteDump(EXCEPTION_POINTERS *exceptionPointers)
    {
        if (dumpInProgress.test_and_set())
            return;

        const std::wstring path = MakeDumpPath();
        if (path.empty())
        {
            const DWORD error = GetLastError();
            ShowDumpResult({}, error == ERROR_SUCCESS ? ERROR_PATH_NOT_FOUND : error);
            return;
        }

        HANDLE file = CreateFileW(
            path.c_str(),
            GENERIC_WRITE,
            0,
            nullptr,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            nullptr);
        if (file == INVALID_HANDLE_VALUE)
        {
            ShowDumpResult({}, GetLastError());
            return;
        }

        MINIDUMP_EXCEPTION_INFORMATION exceptionInformation{
            GetCurrentThreadId(),
            exceptionPointers,
            FALSE};
        const MINIDUMP_TYPE dumpType = static_cast<MINIDUMP_TYPE>(
            MiniDumpWithFullMemory |
            MiniDumpWithFullMemoryInfo |
            MiniDumpWithHandleData |
            MiniDumpWithThreadInfo |
            MiniDumpWithUnloadedModules);
        const BOOL written = MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            file,
            dumpType,
            exceptionPointers ? &exceptionInformation : nullptr,
            nullptr,
            nullptr);
        const DWORD error = written ? ERROR_SUCCESS : GetLastError();
        CloseHandle(file);

        if (!written)
            DeleteFileW(path.c_str());
        ShowDumpResult(path, error);
    }

    LONG WINAPI HandleUnhandledException(EXCEPTION_POINTERS *exceptionPointers)
    {
        WriteDump(exceptionPointers);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    void HandleTerminate()
    {
        WriteDump(nullptr);
        std::abort();
    }
}

#endif

void CrashDump::Initialize()
{
#ifdef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS))
    {
        FILE *f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONOUT$", "w", stderr);
        return;
    }

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h && h != INVALID_HANDLE_VALUE && GetFileType(h) != FILE_TYPE_UNKNOWN)
        return;

    FILE *f;
    freopen_s(&f, "SLGameLoggerDisplay.log", "w", stdout);
    freopen_s(&f, "SLGameLoggerDisplay.log", "a", stderr);

    SetUnhandledExceptionFilter(HandleUnhandledException);
    std::set_terminate(HandleTerminate);
#endif
}
