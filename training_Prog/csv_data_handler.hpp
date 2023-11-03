#ifndef CSV_DATA_HANDLER_HPP
#define CSV_DATA_HANDLER_HPP

#include <string>
#include "csv_parser.hpp"
#include "csv_data.hpp"

namespace csv_parser {

	class Csv_data_handler {
			Csv_data& data_;
			bool has_headers_;
			bool at_beginning_of_line;
			bool at_first_line;
		public:
			bool field_handler(std::string const & s)
			{
				if(at_first_line && has_headers_)
				{
					data_.headers_.push_back(s);
					return true;
				}
				else
				{
					if(at_first_line)
						data_.headers_.push_back("header" + std::to_string(data_.headers_.size()));
					if(at_beginning_of_line)
					{
						data_.new_record();
						at_beginning_of_line = false;
					}
					return data_.add_field(std::stof(s));
				}
			}
			bool end_line_handler()
			{
				at_beginning_of_line = true;
				at_first_line = false;
				return true;
			}

			Csv_data_handler(Csv_data& data, bool has_header_line, Csv_parser & parser) :
				data_(data),
				has_headers_(has_header_line),
				at_beginning_of_line(true),
				at_first_line(true)
			{
				parser.field_handler = [this](std::string const& s) { return field_handler(s); };
				parser.end_line_handler = [this]() { return end_line_handler(); };
			}
	};
}

#endif