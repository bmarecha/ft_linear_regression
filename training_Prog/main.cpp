#include <memory>
#include <iostream>
#include <fstream>
#include <cmath>
#include "csv_parser.hpp"
#include "csv_data_handler.hpp"
#include "csv_data.hpp"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif
#ifndef LEARNING_RATE
# define LEARNING_RATE 0.2
#endif

std::unique_ptr<csv_parser::Csv_data> read_csv_file(std::string path, bool header_line) {
	std::fstream f(path.c_str());
	std::unique_ptr<csv_parser::Csv_data> data(new csv_parser::Csv_data());
	csv_parser::Csv_parser parser;
	csv_parser::Csv_data_handler(*data, header_line, parser);
	char buf[BUFFER_SIZE];
	while(f.good() && parser.get_error() == csv_parser::error::no_error)
	{
		int nb = sizeof(buf);
		f.read(buf, nb);
		if(!f.good())
			nb = f.gcount();
		for(int i = 0; i < nb; ++i)
		{
			parser.consume(buf[i]);
		}
	}
	/*
	std::cout << "Reading over " << f.good();
	if (csv_parser::error::no_error == parser.get_error())
		std::cout << "without error" << std::endl;
	else
		std::cout << "with error" << std::endl; //*/
	if(f.eof())
	{
		parser.end_of_data();
		//if(parser.complete())
			return data;
	}
	return nullptr;
}

void	printThetas(double th1, double th2) {
	std::fstream f(".thetas.txt", std::fstream::out | std::fstream::trunc);
	if (f.good())
		f << th1 << " " << th2 << std::endl;
	else
		std::cout << "An error happened with output file '.thetas.txt'" << std::endl;
}

void computeThetas(std::unique_ptr<csv_parser::Csv_data> const& data, double &th1, double &th2) {
	double sum1 = 0;
	double sum2 = 0;
	size_t	i = 0;
	double witness = 0;

	for (auto record : *data) {
		i++;
		witness = record[0] * record[0];
		sum1 += record[1] - (th1 + th2 * record[0]);
		//sum2 += record[1];
		sum2 += (record[1] - (th1 + th2 * record[0])) * record[0];
	}
	if (i && witness) {
		//std::cout << sum1 / i << std::endl;
		//std::cout << sum2 / i << std::endl;
		th1 += LEARNING_RATE * sum1 * 2 / i;
		th2 += (LEARNING_RATE / witness) * sum2 * 2 / i ;
	}
}

int main(int argc, char** argv) {
	std::unique_ptr<csv_parser::Csv_data> data;
	double	th1 = 0;
	double	th2 = 0;
	double	pth1 = 0;
	double	pth2 = 0;
	double ppth1 = 0;
	double ppth2 = 0;
	size_t	e = 0;

	if (argc == 2) {
		data = read_csv_file(argv[1], true);
	} else {
		data = read_csv_file("data.csv", true);
	}
	if (!data) {
		std::cout << "An error happened with the file." << std::endl;
		return (EXIT_FAILURE);
	}
	//std::cout << "Start Computing :" << std::endl;
	while ( e < 10 ||
			!((ppth1 >= th1 && th1 >= pth1) || (pth1 >= th1 && th1 >= ppth1)) || // value 1 still going in a direction
			!((ppth2 >= th2 && th2 >= pth2) || (pth2 >= th2 && th2 >= ppth2)) // value 2 still going in a direction
			) {
		ppth1 = pth1;
		ppth2 = pth2;
		pth1 = th1;
		pth2 = th2;
		computeThetas(data, th1, th2);
		e++;
		//std::cout << "Th1 from " << pth1 << " to " << th1 << std::endl;
		//std::cout << e << "Diff : " << std::fabs(th1 - pth1) << std::endl;
		//std::cout << "Th2 from " << pth2 << " to " << th2 << std::endl;
		//std::cout << e << "Diff : " << std::fabs(th2 - pth2) << std::endl;
		//std::cout << "e at " << (e * 0.000001) << std::endl;
	}
	if (std::isfinite(th1) && std::isfinite(th2)) {
		printThetas(th1, th2);
	} else {
		std::cout << "An error happened with the dataset, leading to abnormal values." << std::endl;
	}

}