#include <iostream>

char charinput()
{
	char iput;
	while ((!(std::cin >> iput) || (std::cin.peek() != '\n')))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "ошибка!" << std::endl;
	}
	return iput;
}
int intinput()
{
	int iput;
	while ((!(std::cin >> iput) || (std::cin.peek() != '\n')))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "ошибка!" << std::endl;
	}
	return iput;
}