#include <iostream>
#include <string>
#include <Windows.h>

#include "aikit_spark_api.h"
#include "aikit_biz_config.h"
#include "aikit_err.h"
#include <fstream>

using namespace std;
using namespace AIKIT;

//编码格式转换
int multibyteToUnicode(const char *multiByteStr, int multiByteStrLen, UINT multiByteCharsetFlag, char *unicodeStr, int unicodeStrLen)
{
	if (multiByteStr == NULL)//原始字符串为空
	{
		return -1;
	}

	if (multiByteStrLen <= 0)//原始字符串长度小于等于0
	{
		return -2;
	}

	if (multiByteCharsetFlag != CP_ACP && multiByteCharsetFlag != CP_UTF8)//原始字符串字符集标识既不是GBK/GB2312又不是UTF-8
	{
		return -3;
	}

	if (unicodeStr == NULL)//用于存放unicode串的缓存区为空
	{
		return -4;
	}

	if (unicodeStrLen <= 0)//用于存放unicode串的缓存区的长度小于等于0
	{
		return -5;
	}

	int requiredUnicode = MultiByteToWideChar(multiByteCharsetFlag, 0, multiByteStr, multiByteStrLen, NULL, 0);//此种情况用来获取转换所需的wchar_t的个数

	if (sizeof(WCHAR)*requiredUnicode > unicodeStrLen)//接收被转换字符串的缓冲区小于实际需要的字节数
	{
		return -6;
	}

	WCHAR *tmp = new WCHAR[requiredUnicode];//动态分配unicode临时缓存区

	wmemset(tmp, 0, requiredUnicode);//将临时缓存区数据清零

	//执行真实转换，并将转换后的unicode串写到tmp缓存区
	int parsedUnicode = MultiByteToWideChar(multiByteCharsetFlag, 0, multiByteStr, multiByteStrLen, tmp, requiredUnicode);

	if (parsedUnicode != requiredUnicode)//判断真实解析的unicode字符数和分配的字符数是否一致
	{
		delete[]tmp;
		tmp = NULL;
		return -7;
	}

	memset(unicodeStr, 0, unicodeStrLen);//将目标unicode缓存区清零
	memcpy(unicodeStr, tmp, sizeof(WCHAR)*requiredUnicode);//将数据由临时缓存区拷贝到目标unicode缓存区

	delete[] tmp;//释放空间
	tmp = NULL;

	return sizeof(WCHAR)*requiredUnicode;//返回解析好的总字节数
}
int unicodeToMultibyte(const char *unicodeStr, int unicodeStrLen, char *multiByteStr, int multiByteStrLen, UINT multiByteCharsetFlag)
{
	if (unicodeStr == NULL)//原始unicode字符串为空
	{
		return -1;
	}

	if (unicodeStrLen <= 0)//原始unicode字符串的长度小于等于0
	{
		return -2;
	}

	if (multiByteStr == NULL)//用于存放多字节字符串的缓存区为空
	{
		return -3;
	}

	if (multiByteStrLen <= 0)//用于存放多字节字符串的缓存区的长度小于等于0
	{
		return -4;
	}

	if (multiByteCharsetFlag != CP_ACP && multiByteCharsetFlag != CP_UTF8)//目标字符串所使用的字符集既不是CP_ACP（gbk/gb2312）又不是CP_UTF8（utf-8）
	{
		return -5;
	}

	WCHAR *tmp = new WCHAR[unicodeStrLen / 2];//动态分配用于存放原始Unicode字符串的临时缓存区

	wmemset(tmp, 0, unicodeStrLen / 2);//将临时缓存区清零

	memcpy(tmp, unicodeStr, unicodeStrLen);//将原始Unicode字符串拷贝到临时缓存区

	int requiredByte = WideCharToMultiByte(multiByteCharsetFlag, 0, tmp, unicodeStrLen / 2, NULL, 0, NULL, NULL);//获取用于存放目标字符串的字节数

	if (requiredByte > multiByteStrLen)//接收被转换字符串的缓冲区小于实际需要的字节数
	{
		delete[]tmp;
		tmp = NULL;
		return -6;
	}


	memset(multiByteStr, 0, multiByteStrLen);//将目标缓存区清零
	//执行真正转换，将转换后的多字节字符串存放到目标缓存区中，并返回实际解析的字节数
	int parsedByte = WideCharToMultiByte(multiByteCharsetFlag, 0, tmp, unicodeStrLen / 2, multiByteStr, multiByteStrLen, NULL, NULL);
	if (parsedByte != requiredByte)//实际解析的字节数不正确
	{
		delete[]tmp;
		tmp = NULL;
		return -7;
	}

	delete[]tmp;//释放临时缓存区
	tmp = NULL;

	return parsedByte;//返回解析好的总字节数
}
int gbkToUtf8(const char * gbkstr, int gbkstrlen, char * utf8str, int utf8strlen)
{
	if (gbkstr == NULL || gbkstrlen <= 0 || utf8str == NULL || utf8strlen <= 0)//字符串为空或长度小于等于0
	{
		return -1;
	}

	char *unicodestr = new char[2 * gbkstrlen];//分配缓存区，长度为gbk字符串长度的2倍

	int unicodebytes = multibyteToUnicode(gbkstr, gbkstrlen, CP_ACP, unicodestr, 2 * gbkstrlen);//gbk转unicode

	if (unicodebytes < 0)//gbk转unicode失败
	{
		delete[] unicodestr;
		unicodestr = NULL;
		return -2;
	}

	int utf8bytes = unicodeToMultibyte(unicodestr, unicodebytes, utf8str, utf8strlen, CP_UTF8);//unicode转utf-8

	if (utf8bytes < 0)//unicode转utf-8失败
	{
		delete[] unicodestr;
		unicodestr = NULL;
		return -3;
	}

	delete[] unicodestr;//释放内存
	unicodestr = NULL;

	return utf8bytes;//返回解析好的总utf8字节数
}
int utf8ToGbk(const char * utf8str, int utf8strlen, char * gbkstr, int gbkstrlen)
{
	if (utf8str == NULL || utf8strlen <= 0 || gbkstr == NULL || gbkstrlen <= 0)//字符串为空或长度小于等于0
	{
		return -1;
	}

	char *unicodestr = new char[2 * utf8strlen];//分配缓存区，长度为utf8字符串长度的2倍

	int unicodebytes = multibyteToUnicode(utf8str, utf8strlen, CP_UTF8, unicodestr, 2 * utf8strlen);//utf8转unicode

	if (unicodebytes < 0)//utf8转unicode失败
	{
		delete[] unicodestr;
		unicodestr = NULL;
		return -2;
	}

	int gbkbytes = unicodeToMultibyte(unicodestr, unicodebytes, gbkstr, gbkstrlen, CP_ACP);//unicode转GBK

	if (gbkbytes < 0)//unicode转gbk失败
	{
		delete[] unicodestr;
		unicodestr = NULL;
		return -3;
	}

	delete[] unicodestr;
	unicodestr = NULL;

	return gbkbytes;//返回解析好的gbk字节数
}
//输入数据
string getUsrInput(string input) {
	/*cout << "\xC4\xE3\xB5\xC4\xCE\xCA\xCC\xE2:" << endl << "\t";
	string text;
	cin >> text;
	cout << "\xBB\xD8\xB4\xF0:" << endl << "\t";*/
	char *tpp = new char[400];
	gbkToUtf8(input.c_str(), input.size(), tpp, 400);//将命令行输入的GBK转UTF-8
	string fy(tpp);
	delete[]tpp;
	return fy;
}
//发送数据
int sendRequest(string input)
{
	if (input == "")
	{
		exit(0);
		return -1;
		
	}
	//请求参数配置
	ChatParam* config = ChatParam::builder();
	config->uid("xxx_uid")
		->maxToken(4096);
	
	int ret = AIKIT_AsyncChat(config, getUsrInput(input).c_str(), nullptr);//文本数据输入输出以UTF-8编码格式
	if (ret != 0) {
		printf("AIKIT_AsyncChat failed:%d\n", ret);
		printf("check appid key secret whether been set\n");
		return ret;
	}
}
//事件
void chatTokenCount(AIChat_Handle* handle, const int& completionTokens, const int& promptTokens, const int& totalTokens) {
	cout << endl;
	sendRequest("");//新对话
}
static void chatOnOutput(AIChat_Handle* handle, const char* role, const  char* content, const int& index) {
	if (*content != '\0')
	{
		char *t = new char[400];
		int i = 0;
		while (content[i] != '\0')
		{
			i++;
		}
		utf8ToGbk(content, i, t, 400);//将返回的UTF-8转GBK
		string jieg(t);
		delete[]t;
		//ofstream ofs;

		// 2、打开文件
		//ofs.open("Spark.txt", ios::out); // 输出模式打开指定的文件
		//// 如果文件不存在，则会创建
		//// 如果文件存在，则会清空内容
		//ofs << jieg;

		//// 4、关闭流
		//ofs.close();
		cout << jieg;
	}

}
static void chatOnError(AIChat_Handle* handle, const int& err, const char* errDesc) {
	printf("chatOnError: err:%d,desc:%s\n", err, errDesc);
	sendRequest("");
}

int main(int argc, char* argv[])
{
	/*for (int i = 0; i < argc; i++)cout << argv[i] << '\t';
	std::cout << '\n';*/
	string input = argv[1];
	//ofstream ofs;

	// 2、打开文件
	//ofs.open("Spark.txt", ios::out);
	//string input = "你好世界";

	//SDK初始化参数配置
	//system("chcp 65001");
	AIKIT_Configurator::builder()
		.log()
		.logLevel(100) //设置日志等级，0:debug
		.app()
		.appID("43a4cc46")//自己的appid
		.apiKey("c3c6e5c690481ff8fcee705faa81d727")//自己的apiKey
		.apiSecret("MTJmMWVhNzViNGFmZDZmYjI1Mzg2MDE3");//自己的apiSecret
	//SDK初始化
	int ret = AIKIT_Init();
	if (ret != 0) {
		printf("AIKIT_Init failed:%d\n", ret);
		return -1;
	}
	//异步回调注册
	AIKIT_ChatCallback({ chatOnOutput, chatTokenCount, chatOnError });
	sendRequest(input);
	Sleep(500000);
	AIKIT_UnInit();
	return 0;
}