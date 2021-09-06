/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// MultiThread
/// C++ Run Time Library Multithreading
///
/// Windowsのマルチスレッドには4種類あります
/// 使い分けが必要ですが、結局、Win32が一番使い勝手が良い
/// 
/// ①C++11のライブラリ
/// ②C Run Time Library   <----- これ！
/// ③MFC Multithread
/// ④Win32 API Multithread
/// ⑤Linux Multithread
/// 
///     2021/09/06      Retar.jp 
///
/// Windowsの古参の関数たち・・・使わんほう良さそう
/// _beginthread
/// _beginthreadex
/// _endthread
/// _endthreadex
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <process.h>
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// スレッド関数
void ThreadProc(void* param);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main
int main()
{
	//数字列
	std::vector<double> closePrice = { 10.0f,20.0f,30.0f };
	std::for_each(closePrice.begin(), closePrice.end(), [](auto& cPrice) {std::cout << cPrice << " " << std::endl; });

	//スレッドのハンドラ
	HANDLE handle;

	//ハンドラを設定
	handle = (HANDLE)_beginthread(ThreadProc, 0, &closePrice);
	
	//実行
	WaitForSingleObject(
		handle			//ハンドラ
		, INFINITE		//待ち時間（無限待ち）
	);

	// スレッドの終了コードを取得
	DWORD dwExitCode = 0;
	GetExitCodeThread(handle, &dwExitCode);
	std::wcout << L"Thread End Code (" << dwExitCode << L")" << std::endl;

	// スレッドハンドルの解放・ハンドラはこの時点で開放されているので不要
	//CloseHandle(handle);

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// スレッド関数
void ThreadProc(void* param)
{
	//渡されたハンドラを元データにする
	auto closePrice = *((std::vector<double>*)param);

	//演算
	double sum = 0.0f;
	for (auto itr = closePrice.begin(); itr != closePrice.end(); itr++)
	{
		sum += (*itr);
	}
	std::cout << "sum : " << sum << "  average : " << sum / closePrice.size() << std::endl;
	
	//スレッド終了・呼び出しで開放されるため、mainでのハンドラ開放不要
	_endthread();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
