#include <iostream>
#include "LinkedList.h"
#include <string>

int main ()
{
	LinkedList<std::string> list;
	list.push_back("bac");
	list.push_front("buc");
	list.push_front("str");
	list.push_back("222");
	list.push_back("222");
	list.push_back("222");
	list.push_back("222");

	list.unique();

	list.push_front("222");
	list.push_back("212");

	list.sort();
	list.unique();
	list.reverse();

	list.print();


	return 0;
}