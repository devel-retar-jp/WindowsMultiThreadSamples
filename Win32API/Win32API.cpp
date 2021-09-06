/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// MultiThread
/// C++ Run Time Library Multithreading
///
/// Windowsのマルチスレッドには4種類あります
/// 使い分けが必要ですが、結局、Win32が一番使い勝手が良い
/// 
/// ①C++11のライブラリ
/// ②C Run Time Library
/// ③MFC Multithread 
/// ④Win32 API Multithread  <----- これ！
/// ⑤Linux Multithread
/// 
///     2021/09/06      Retar.jp 
/// 
/// Win32で定義されているスレッド・データ
/// 
/// Data members
/// m_hThread			The current thread handle
/// m_bAutoDelete		Whether the thread has set to auto delete or not
/// m_nThreadID			The current thread ID
///
/// Data Functions 
/// CreateThread		Start the exec execution of thread
/// SuspendThread		Increment thread suspend count.When the resume thread occur only the thread resume.
/// ResumeThread		Resume the thread.Decrements the thread count stack
/// SetThreadPriority	Set thread priority(LOW, BELOW LOW or HIGH)
/// GetThreadPriority	Get the thread Priority
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <process.h>
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////スレッドに渡す引数
struct lpVOID
{
	std::vector<double> closePrice;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// スレッド関数
UINT ThreadProc(LPVOID param);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//WinMain
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//コンソールがないときは割り当てる
	if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
		if (AllocConsole() == FALSE)
		{
			std::cout << "Console Error : " << GetLastError() << std::endl;
			return 1;
		}
	}
	//入出力先を変更
	FILE* fpOut = NULL;
	::freopen_s(&fpOut, "CONOUT$", "w", stdout);
	FILE* fpErr = NULL;
	::freopen_s(&fpErr, "CONOUT$", "w", stderr);
	FILE* fpIn = NULL;
	::freopen_s(&fpIn, "CONIN$", "r", stdin);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//数字列
	std::vector<double> closePrice = { 10.0f,20.0f,30.0f };
	std::for_each(closePrice.begin(), closePrice.end(), [](auto& cPrice) {std::cout << cPrice << " " << std::endl; });

	//スレッドのハンドラ
	HANDLE handle;
	lpVOID tobj;

	tobj.closePrice = closePrice;

	if (!(
		handle = CreateThread(
			NULL,									// no security attributes 
			0,										// use default stack size 
			(LPTHREAD_START_ROUTINE)ThreadProc,		// function
			(LPVOID)&tobj,							// param to thread func 
			CREATE_SUSPENDED,						// creation flag 
			NULL)
		)) {
		MessageBox(NULL, L"Thread Create Error", L"Thread", MB_OK);
		return FALSE;
	}

	//スレッドのプライオリティを設定・C++11では設定不可能
	SetThreadPriority(handle, THREAD_PRIORITY_HIGHEST);

	//スレッドの実行
	if (-1 == ResumeThread(handle)) {
		MessageBox(NULL, L"Thread Resume Error", L"handle", MB_OK);
		return FALSE;
	}

	// スレッドの終了待ち
	WaitForSingleObject(handle, INFINITE);

	// ハンドラの終了待ち
	DWORD dwExitCode = 0;
	while (1)
	{
		auto ret = GetExitCodeThread(handle, &dwExitCode);
		if (ret == STILL_ACTIVE) {
			printf("still working\n");
			Sleep(0);
		}
		else {
			break;
		}
	}

	//ハンドラのクローズ
	CloseHandle(handle);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("\r\nDone....");
	auto chAnswer = getchar();
	//コンソール開放
	FreeConsole();
	return 0;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// スレッド関数
UINT ThreadProc(LPVOID param)
{
	//渡されたハンドラを元データにする
	auto closePrice = (*((lpVOID*)param)).closePrice;

	//演算
	double sum = 0.0f;
	for (auto itr = closePrice.begin(); itr != closePrice.end(); itr++)
	{
		sum += (*itr);
	}
	std::cout << "sum : " << sum << "  average : " << sum / closePrice.size() << std::endl;

	//スレッド終了
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
