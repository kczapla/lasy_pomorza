#include "logging.hpp"


int main(void)
{
	logging::add_file("tmp.log");
	log(logging::Level::info) << "sztos" << std::endl;
	system("PAUSE");
	return 0;
}