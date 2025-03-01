// stdafx.cpp : 只包括标准包含文件的源文件
// WordCount.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息
#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

bool cmp(const pair<string, int> &n1, const pair<string, int> &n2) 
{
	if (n1.second == n2.second)
		return n1.first < n2.first;
	else
		return n1.second > n2.second;
}
Word::Word()
{
	mapword.clear();
	//初始化
	linesnum = 0;
	characters = 0;
	words = 0;
	initans = 0;//代表是否进行过初始化
}
int Word::initdisplayphrase(ifstream& in, int ans,int length)
{
	deque<int>phrase;
	int phraseans = 0;
	unordered_map<string, int>::iterator iter;
	__int64 wordpos, answord;
	string name, str;
	int num, i, j, quan = 1, begin, beishu = 1;
	if (ans)quan = 10;
	bool anslint = 0, trueword = 1;
	while (getline(in, name))
	{
		phrase.clear();
		phraseans = 0;//模拟队列字符长度；
		answord = 0;
		begin = 0;
		if (name.size() <= 2)continue;
		characters += (int)(name.size() + 1);
		num = (int)name.size();
		if (name[0] == 'T'&&name[1] == 'i'&&name[2] == 't'&&name[3] == 'l'&&name[4] == 'e'&&name[5] == ':')
		{
			
			begin = 7;
			characters -= 7;
			beishu = 1;
		}
		else if (name[0] == 'A'&&name[1] == 'b'&&name[2] == 's'&&name[3] == 't'&&name[4] == 'r'&&name[5] == 'a') {
			
			begin = 10;
			characters -= 10;
			beishu = quan;
		}
		for (i = begin; i < num; i++)
		{
			if (!anslint&&name[i] != 0x9 && name[i] != 0xd && name[i] != 0xa && name[i] != 0x20)
			{
				anslint = 1;//标记； 
			}//统计空白行 
			if (('a' <= name[i] && name[i] <= 'z') || ('A' <= name[i] && name[i] <= 'Z'))
			{
				if (65 <= name[i] && name[i] <= 90)name[i] += 32;//大小写转化
				answord++;
				continue;
			}
			if ('0' <= name[i] && name[i] <= '9')
			{
				if (answord >= 4)
					answord++;
				else
				{
					for (j = i + 1; j < num; j++)
					{
						if ('0' <= name[j] && name[j] <= '9')
							continue;
						else if (('a' <= name[j] && name[j] <= 'z') || ('A' <= name[j] && name[j] <= 'Z'))
							continue;
						else
						{
							while (j < num)
							{
								if (('a' <= name[j + 1] && name[j + 1] <= 'z') || ('A' <= name[j + 1] && name[j + 1] <= 'Z'))
								{
									phraseans = 0;
									phrase.clear();
									break;
								}
								else
									j++;
							} //寻找下一个单词的开头 
							i = j;
							break;
						}
					}	//寻找下一个分隔符 
					if (j == num)
					{
						break;
					}	//寻找不到下一个分隔符 
					answord = 0;
				}
			}
			else
			{
				if (answord >= 4)
				{
					
					//	cout<<"word:"<<word<<endl;
					phraseans++;
					phrase.push_back(i- answord);
					if (phraseans == length)
					{
						int lon = phrase.front();//词组起始位置；
						phrase.pop_front();
						str = name.substr(lon, i - lon);
						mapword[str] = mapword[str] + beishu;
						phraseans--;
						words++;
					}
				}
				while (i < num)
				{
					if (answord < 4)
					{
						phraseans = 0;
						phrase.clear();
					}
					if (('a' <= name[i + 1] && name[i + 1] <= 'z') || ('A' <= name[i + 1] && name[i + 1] <= 'Z'))
					{			
						break;
					}
					else
						i++;
				} //寻找下一个单词的开头 
				answord = 0;
			}
		}
		if (answord >= 4)
		{

			//	cout<<"word:"<<word<<endl;
			phraseans++;
			phrase.push_back(i - answord);
			if (phraseans == length)
			{
				int lon = phrase.front();//词组起始位置；
				phrase.pop_front();
				str = name.substr(lon, i - lon);
				mapword[str] = mapword[str] + beishu;
				phraseans--;
				words++;
			}
		}
		if (anslint)
		{
			linesnum++;
			anslint = 0;
		}
		//	cout<<name<<endl;;	
	}
	characters--;
	//初始化完成；
	initans = 1;
	return 0;
}
int Word::init(ifstream& in,int ans)
{
	unordered_map<string, int>::iterator iter;
	__int64 wordpos ,answord;
	string name,str;
	int num,i,j,quan=1,begin,beishu=1;
	if (ans)quan = 10;
	bool anslint = 0, trueword = 1;
	while (getline(in, name))
	{
		characters += (int)(name.size()+1);
		wordpos = 0;
		answord = 0;
		begin = 0;
		if (name.size() <= 2)continue;
		num = (int)name.size();
		if (name[0] == 'T'&&name[1] == 'i'&&name[2] == 't'&&name[3] == 'l'&&name[4] == 'e'&&name[5] == ':')
		{
			wordpos = 7;
			begin = 7;
			characters -= 7;
			beishu = 1;
		}
		else if (name[0] == 'A'&&name[1] == 'b'&&name[2] == 's'&&name[3] == 't'&&name[4] == 'r'&&name[5] == 'a') {
			wordpos = 10;
			begin = 10;
			characters -= 10;
			beishu = quan;
		}
		for (i = begin; i < num; i++)
		{
			if (!anslint&&name[i] != 0x9 && name[i] != 0xd && name[i] != 0xa && name[i] != 0x20)
			{
				anslint = 1;//标记； 
			}//统计空白行 
			if (('a' <= name[i] && name[i] <= 'z') || ('A' <= name[i] && name[i] <= 'Z'))
			{
				if (65 <= name[i] && name[i] <= 90)name[i] += 32;//大小写转化
				answord++;
				continue;
			}
			if ('0' <= name[i] && name[i] <= '9')
			{
				if (answord >= 4)
					continue;
				else
				{
					for (j = i+1; j < num; j++)
					{
						if ('0' <= name[j] && name[j] <= '9')
							continue;
						else if (('a' <= name[j] && name[j] <= 'z') || ('A' <= name[j] && name[j] <= 'Z'))
							continue;
						else
						{
							while (j < num)
							{
								if (('a' <= name[j + 1] && name[j + 1] <= 'z') || ('A' <= name[j + 1] && name[j + 1] <= 'Z'))
								{
									wordpos = j + 1;
									break;
								}
								else
									j++;
							} //寻找下一个单词的开头 
							i = j;
							break;
						}
					}	//寻找下一个分隔符 
					if (j == num)
					{
						break;
					}	//寻找不到下一个分隔符 
					answord = 0;
				}
			}
			else
			{
				if (answord >= 4)
				{
					str = name.substr(wordpos, i - wordpos);
					mapword[str]= mapword[str]+ beishu;
					//	cout<<"word:"<<word<<endl;
					words++;
				}//获取单词
				while (i < num)
				{
					if (('a' <= name[i + 1] && name[i + 1] <= 'z')|| ('A' <= name[i + 1] && name[i + 1] <= 'Z'))
					{
						wordpos = i + 1;
						break;
					}
					else
						i++;
				} //寻找下一个单词的开头 
				answord = 0;
			}
		}
		if (answord >= 4)
		{
			str = name.substr(wordpos, i - wordpos);
			mapword[str] = mapword[str] + beishu;
			words++;
		}
		if (anslint)
		{
			linesnum++;
			anslint = 0;
		}
		//	cout<<name<<endl;;	
	}
	characters--;
	//初始化完成；
	initans = 1;
	return 0;
}
int Word::Countlines(ifstream& in,int ans)
{
	//统计非空白行
	if (!initans)
		init(in,ans);
	return linesnum;
}
int Word::Countwords(ifstream& in,int ans)
{
	if (!initans)
		init(in,ans);
	return words;
}
int Word::Countcharacters(ifstream& in,int ans)
{
	//统计ascll码的数量
	/*
	char ch;
	while (in.peek() != EOF) {
		in.get(ch);
		characters++;
	}
	in.seekg(0, ios::beg);
	*/
	if (!initans)
		init(in,ans);
	return characters;
}
vector<pair<string, int>> Word::Counttop10(ifstream& in,int n,int ans)
{
	if (!initans)
		init(in, ans);
	__int64 num;
	vector<pair<string, int>>top(mapword.begin(), mapword.end()),top10;
	sort(top.begin(), top.end(), cmp);
	num = 0;
	for(int i=0;i < top.size() ; i++ )
	{
		num++;
		top10.insert(top10.end(),top[i]);
		if (num == n)
			break;
	}
	return top10;
}
void Word::display(ofstream& fout,int num,ifstream& in,int ans)
{
	fout << "characters: " << Countcharacters(in,ans) << endl;
	fout << "words: " << Countwords(in,ans) << endl;
	fout << "lines: " << Countlines(in,ans) << endl;
	vector<pair<string, int>> v = Counttop10(in,num,ans);
	vector<pair<string, int>>::iterator iter = v.begin();
	for (; iter != v.end(); iter++)
	{
		fout << "<" << iter->first << ">: " << iter->second << endl;
	}
	return ;
}
void Word::displayphrase(ofstream& fout, int num, ifstream& in, int ans,int length)
{
	initdisplayphrase(in,ans,length);
	fout << "characters: " << characters << endl;
	fout << "words: " << words << endl;
	fout << "lines: " << linesnum << endl;
	vector<pair<string, int>> v = Counttop10(in, num, ans);
	vector<pair<string, int>>::iterator iter = v.begin();
	for (; iter != v.end(); iter++)
	{
		fout << "<" << iter->first << ">: " << iter->second << endl;
	}
	return;
}

//文件工具类；

File::File() 
{
	input = "./input.txt";
	output = "./result.txt";
	flagcountphrase = 0;
	countphrase = 1;
	outtop = 10;
	countquz = 0;
}
int File::FileTest(char *argv[])
{
	int ans = 1;
	if (argv[1] == NULL)
	{
		printf("no file\n");
		ans = 0;
	}
	fstream Fileread;
	Fileread.open(input, std::ios::in);
	if (Fileread.fail())
	{
		printf("file isn't exist\n");
		ans = 0;
	}
	Fileread.close();
	return ans;
}
void File::del(char *argv[])
{
	for (int i = 1; argv[i] != NULL; i = i + 2)
	{
		if (strcmp(argv[i],"-i") == 0) {
			input = argv[i + 1];
			continue;
		}
		else if (strcmp(argv[i], "-o") == 0) {
			output = argv[i + 1];
			continue;
		}
		else if (strcmp(argv[i], "-w") == 0) {
			countquz = atoi(argv[i + 1]);
			//cout << countquz << "aaa" << endl;
		}
		else if (strcmp(argv[i], "-m") == 0) {
			countphrase = atoi(argv[i + 1]);
			flagcountphrase = 1;
			//cout << countphrase << "bbb" << endl;
		}
		else if (strcmp(argv[i], "-n") == 0) {
			outtop = atoi(argv[i + 1]);
			//cout << outtop << "ccc" << endl;
		}
	}
	return;
}
int File::Filein()
{
	int ans = 0;
	fin.open(input, ios::in);
	if (fin.fail())
	{
		printf("file isn't exist\n");
		ans = 1;
	}
	fout.open(output, ios::out);
	if (fout.fail())
	{
		printf("file isn't exist\n");
		ans = 1;
	}
	return ans;
}
void File::Fileout()
{
	fin.close();
	fout.close();
	return;
}