#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

class set_class {
public:
	string name;
	int prev;//ÏÈÐÞ¿Î³Ì
	int num;//±àºÅ
};

int main()
{
	char oper;
	string class_name[100];
	int prev_class[100];
	int num=0;//±àºÅ
	int j = 0;
	set_class course[100];
	while (cin >> oper)
	{
		if (oper == 'c')
		{
			cin >> class_name[j];
			cin >> prev_class[j];//ÏÈÐÞ¿Î³Ì
			
			course[j].name = class_name[j];
			course[j].prev = prev_class[j];
			course[j].num = num++;
			j++;
		}

		else if (oper == 's')
		{
			
			for (int i = 0; i < num; i++)
			{
				printf("Course %d-%s has prerequisites: ", course[i].num, course[i].name.c_str());
				if (course[i].prev == -1) cout << "none" << endl;
				else
				{
					int cur = course[i].prev;
					bool first = true;
					while (cur != -1)
					{
						if (!first)
						{
							cout << ' ';
						}
						cout << course[cur].name;
						first = false;
						cur = course[cur].prev;
					}
				}cout << endl;
			}
		}
		else if (oper == 'e')
		{
			
			return 0;
		}
	}
}