# Windows MultiThread Samples

C++ Run Time Library Multithreadingのサンプルコード。<br>
Windowsのマルチスレッドには4種類あります。<br>
使い分けが必要ですが、結局、Win32が一番使い勝手が良いと思います。<br>
オマケでLinux版のpthreadも。<p>
 
- ①C++11のライブラリ<br>
C++11の機能で書いています。<br>
Windows Threadのような細やかな制御が出来ません。<p<
 
- ②C Run Time Library<br>
Windows2000時代からあるライブラリ。<br>
使い勝手が悪いです。<p>
 
- ③MFC Multithread<br>
MFCのマルチスレッド。<br>
最近はMFCではなく、Win32 APIなので必要ないかも？<p>
 
- ④Win32 API Multithread<br>
使いやすく便利なAPIです。<br>
比較検討すると「これが良い」になると思います<p>
 
- ⑤Linux Multithread<br>
Solaris伝来のpthread。<p>
本家なので素直。<p>
