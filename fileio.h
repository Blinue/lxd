﻿#pragma once

#include "defines.h"
#include <string_view>
#include <vector>
#include <string>
#include <ctime>

namespace lxd {
	enum OpenMode {
		NotOpen = 0x0000,
		ReadOnly = 0x0001,
		WriteOnly = 0x0002,
		ReadWrite = ReadOnly | WriteOnly,
		Append = 0x0004,
		Truncate = 0x0008,
		Text = 0x0010,
		Unbuffered = 0x0020,
		NewOnly = 0x0040,
		ExistingOnly = 0x0080
	};

	enum SeekMode {
		FileBegin = 0,
		FileCurrent,
		FileEnd
	};
	
	DLL_PUBLIC bool FileExists(std::wstring_view path);
	DLL_PUBLIC void* OpenFile(std::wstring_view path, int mode);
	DLL_PUBLIC bool CloseFile(void* handle);
	DLL_PUBLIC bool WriteFile(std::wstring_view path, char const* buffer, size_t bufferSize);
	DLL_PUBLIC std::string ReadFile(std::wstring_view path);
	DLL_PUBLIC bool RemoveFile(std::wstring_view path);

	DLL_PUBLIC bool CreateDir(std::wstring_view path);
	DLL_PUBLIC bool CreateDirRecursive(std::wstring_view path);
	DLL_PUBLIC int DeleteDir(std::wstring_view path, bool bDeleteSubdirectories = true);
	DLL_PUBLIC bool DirExists(std::wstring_view path);
	DLL_PUBLIC bool ListDir(std::wstring_view path, std::vector<std::wstring>& result, bool recursive = false, const wchar_t* filter = nullptr);

	DLL_PUBLIC std::wstring GetExePath();

	class DLL_PUBLIC File {
	public:
		File(std::wstring_view path, int mode);
		~File();
		long long size() { return _size; }
		bool seek(long long distance, SeekMode mode, long long* newPtr = nullptr);
		bool read(void* buffer, unsigned long nNumberOfBytesToRead, unsigned long* lpNumberOfBytesRead = nullptr);
		bool write(void* buffer, size_t size);
		struct tm getLastWriteTime();
		bool isOlderThan(struct tm);
	private:
		void* _handle{};
		long long _size{};
	};
}