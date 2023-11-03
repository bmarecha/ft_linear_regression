#include "csv_parser.hpp"

namespace csv_parser {

	bool Csv_parser::consume(char c)
	{
		//std::cout << state_ << c;
		curr_str_pos_ += 1;
		switch(state_)
		{
			case state::initial:
			case state::new_line:
			{
				if(is_separator(c))
				{
					field_handler(curr_str); // Empty if no problem
					curr_str.clear(); // Not necessary
					state_ = state::between_records;
				}
				else if(is_double_quote(c))
					state_ = state::quoted_record;
				else if(is_start_comment(c))
					state_ = state::comment;
				else if(is_new_line(c))
				{
					end_line_handler();
					state_ = state::new_line;
				}
				else
				{
					curr_str.push_back(c);
					state_ = state::record;
				}
				break;
			}
			case state::record:
			{
				if(is_separator(c))
				{
					field_handler(curr_str);
					curr_str.clear();
					state_ = state::between_records;
				}
				else if(is_new_line(c))
				{
					field_handler(curr_str);
					curr_str.clear();
					end_line_handler();
					state_ = state::new_line;
				}
				else
					curr_str.push_back(c);
				break;
			}
			case state::quoted_record:
			{
				if(is_double_quote(c))
					state_ = state::quote_quoted_record;
				else
				{
					if(is_new_line(c))
						line_counter++;
					curr_str.push_back(c);
				}
				break;
			}
			case state::quote_quoted_record:
			{
				if(is_separator(c))
				{
					field_handler(curr_str);
					curr_str.clear();
					state_ = state::between_records;
				}
				else if(is_double_quote(c))
				{
					curr_str.push_back(c);
					state_ = state::quoted_record;
				}
				else if(is_new_line(c))
				{
					field_handler(curr_str);
					curr_str.clear();
					end_line_handler();
					state_ = state::new_line;
				}
				else
					error_handler(error::malformed_quoted_string);
				break;
			}
			case state::between_records:
			{
				if(is_separator(c))
				{
					field_handler(curr_str); // Empty if no problem
					curr_str.clear(); // Not necessary
					state_ = state::between_records;
				}
				else if(is_double_quote(c))
					state_ = state::quoted_record;
				else if(is_new_line(c))
				{
					field_handler(curr_str);
					curr_str.clear();
					end_line_handler();
					state_ = state::new_line;
				}
				else
				{
					curr_str.push_back(c);
					state_ = state::record;
				}
				break;
			}
			case state::comment:
			{
				if(is_new_line(c))
				{
					comment_handler(curr_str);
					curr_str.clear();
					state_ = state::new_line;
					line_counter++;
				}
				else
					curr_str.push_back(c);
				break;
			}
		}
		return true;
	}

	void Csv_parser::end_of_data()
	{
		switch(state_)
		{
			case state::quote_quoted_record:
			case state::record:
			case state::between_records:
				field_handler(curr_str); // Empty if no problem
				end_line_handler();
				break;
			case state::quoted_record:
				error_handler(error::unterminated_quoted_string);
				break;
			case state::new_line:
				break;
			case state::comment:
				comment_handler(curr_str);
				break;
			case state::initial:
				error_handler(error::empty_file);
				break;
		}
		if(end_file_handler && error_ == error::no_error)
		{
			if(!end_file_handler())
				error_ = error::user_aborted;
		}
	}

	std::ostream& operator << (std::ostream& os, const state& obj)
	{
		switch (obj)
		{
			case state::initial:
			{
				os << "{initial}";
				break;
			}
			case state::comment:
			{
				os << "{comment}";
				break;
			}
			case state::record:
			{
				os << "{record}";
				break;
			}
			case state::quoted_record:
			{
				os << "{quoted_record}";
				break;
			}
			case state::quote_quoted_record:
			{
				os << "{quote_quoted_record}";
				break;
			}
			case state::new_line:
			{
				os << "{new_line}";
				break;
			}
			case state::between_records:
			{
				os << "{between_records}";
				break;
			}
		}
		return os;
	}
}