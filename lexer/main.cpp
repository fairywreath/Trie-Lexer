#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <chrono>

#include "trie.hpp"
#include "lexer.hpp"

namespace
{
	void repl()
	{
		std::string line;


		for (;;)
		{
			std::cout << "~> ";
			std::getline(std::cin, line);

			Lexer lexer(line);
			lexer.scanAll();
		}
	}

	void readFile(const std::string& path)
	{
		std::ifstream fin;

		std::cout << "Open file: " << path << std::endl;

		fin.open(path);

	
		if (fin.is_open())
		{
			std::stringstream buffer;
			buffer << fin.rdbuf();
			std::string src = buffer.str();

			Lexer lexer(src);
			lexer.scanAll();
		}
		else
		{
			fin.close();
			throw std::runtime_error("File " + path + " cannot be opened");
		}

		fin.close();
	}

}
int main(int argc, const char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();

	if (argc == 1)
		repl();

	if (argc == 2)
	{
		try
		{
			readFile(argv[1]);
		}
		catch (std::exception& e)
		{
			std::cout << "\nEXCEPTION: " << e.what() << std::endl;
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "Execution time: " << duration.count() << " ms\n";

	return 0;
}

