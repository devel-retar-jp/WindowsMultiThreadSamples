/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// MultiThread
/// C++ Run Time Library Multithreading
///
/// Windowsのマルチスレッドには4種類あります
/// 使い分けが必要ですが、結局、Win32が一番使い勝手が良い
/// 
/// ①C++11のライブラリ  <----- これ！
/// ②C Run Time Library 
/// ③MFC Multithread
/// ④Win32 API Multithread
/// ⑤Linux Multithread
/// 
///     2021/09/06      Retar.jp 
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// スレッド関数・C++11では普通に関数を書く
void ThreadProc(std::vector<double> closePrice);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//数字列
	std::vector<double> closePrice = { 10.0f,20.0f,30.0f };
	std::for_each(closePrice.begin(), closePrice.end(), [](double& cPrice) {std::cout << cPrice << " " << std::endl; });

	//スレッドを生成してエラーにならないチェック
	try {
		//C++ 11のスレッド生成
		std::thread cthread(ThreadProc, closePrice);

		//joinして終了を待つ
		if (cthread.joinable())
		{
			cthread.join();
		}
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}

	return (0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// スレッド関数
void ThreadProc(std::vector<double> closePrice)
{
	//演算
	double sum = 0.0f;
	for (auto itr = closePrice.begin(); itr != closePrice.end(); itr++)
	{
		sum += (*itr);
	}
	std::cout << "sum : " << sum << "  average : " << sum / closePrice.size() << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
