#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <cctype>
#include <vector>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

using namespace std;

bool isMailChar(char x);

int main()
{
	string filename, pagename;
	filename = "page.html";
	fstream file;
	ofstream outfile(filename.c_str());
	outfile << "x" << endl;
	outfile.close();
	cout << "Please insert full adress to page you want to search through" << endl;
	cin >> pagename;
	
	if (!URLDownloadToFile(NULL, pagename.c_str(), filename.c_str(), 0, NULL) == S_OK)
	{
		cout << "Downloading file was unsuccesfull";
		system("pause");
		return 0;
	}
	file.open(filename.c_str(), ios::in);
	if (!file.good())
	{
		cout << "Unable to open the file " << endl;
		system("pause");
		return 0;
	}
	string page;
	string part;
	while (!file.eof())
	{
		getline(file, part);
		page += part;
		page += "\n";
	}
	vector<string> mails;
	string mail;
	for (int i = 0; i < page.size(); i++)
	{
		if (page.at(i) == '@')
		{
			while (isMailChar(page.at(i)))
			{
				if (i - 1 > 0)
				{
					i--;
				}
			}
			mail = "";
			while (isMailChar(page.at(i+1)))
			{
				if (i + 1 < page.size())
				{
					i++;
					mail += page.at(i);
				}
			}
			mails.push_back(mail);
		}
	}
	for (int i = 0; i < mails.size(); i++)
	{
		cout << mails.at(i) << endl;
	}
	
	system("pause");
	return 0;
}

bool isMailChar(char x)
{
	if (x == 46)
	{
		return true;
	}
	if (x >= 48 && x <= 57)
	{
		return true;
	}
	if (x >= 65 && x <= 90)
	{
		return true;
	}
	if (x == 95)
	{
		return true;
	}
	if (x >= 97 && x <= 122)
	{
		return true;
	}
	if (x == '@')
	{
		return true;
	}
	return false;
}