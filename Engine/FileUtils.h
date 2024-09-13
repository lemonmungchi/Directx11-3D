#pragma once

//파일입출력용
enum FileMode :uint8
{
	Write,
	Read,
};

class FileUtils
{
public:
	FileUtils();
	~FileUtils();

	void Open(wstring filePath, FileMode mode);

	//쓸때 어떤자료형 쓸지 모름
	template<typename T>
	void Write(const T& data)
	{
		DWORD numOfBytes = 0;
		assert(::WriteFile(_handle, &data, sizeof(T), (LPDWORD)&numOfBytes, nullptr));
	}
	//템플릿특수화 - 예외적 상황가정
	template<>
	void Write<string>(const string& data)
	{
		return Write(data);
	}

	void Write(void* data, uint32 dataSize);
	void Write(const string& data);

	template<typename T>
	void Read(OUT T& data)
	{
		DWORD numOfBytes = 0;
		assert(::ReadFile(_handle, &data, sizeof(T), (LPDWORD)&numOfBytes, nullptr));
	}

	template<typename T>
	T Read()
	{
		T data;
		Read(data);
		return data;
	}

	void Read(void** data, uint32 dataSize);
	void Read(OUT string& data);

private:
	HANDLE _handle = INVALID_HANDLE_VALUE;
};

