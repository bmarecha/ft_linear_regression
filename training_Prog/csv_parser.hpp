#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include <string>
#include <functional>
#include <iostream>

#ifndef CSV_SEPARATOR
# define CSV_SEPARATOR ','
#endif

namespace csv_parser {

	enum class state : char	{
		initial,
		comment,
		record,
		quoted_record,
		quote_quoted_record,
		new_line,
		between_records
	};
	enum class error : char {
		no_error = 0,
		other,
		user_aborted,
		malformed_quoted_string,
		unterminated_quoted_string,
		empty_file
	};


	class Csv_parser {
		public :
			typedef std::string string_type;

		private :
			state state_ = state::initial;
			error error_ = error::no_error;
			string_type curr_str;
			size_t		curr_str_pos_ = 0;
			size_t		line_counter = 0;

		public :

			Csv_parser() {
				comment_handler = [this](__attribute__((unused)) std::string const& s) {return false; };
				field_handler = [this](__attribute__((unused)) std::string const& s) {return false; };
				end_line_handler = [this]() {return false; };
				end_file_handler = [this]() {return false; };
				error_handler = [this](__attribute__((unused)) error e) {};
			}
			error get_error() const { return error_; };
			bool consume(char c);
			void end_of_data();
			std::function<bool(string_type const &)> comment_handler;
			std::function<bool(string_type const &)> field_handler; //done
			std::function<bool()> end_line_handler; //done
			std::function<bool()> end_file_handler;
			std::function<void(error)> error_handler;

	};

	std::ostream& operator << (std::ostream& os, const state& obj);

	inline bool is_separator(char c) {
		return (c == CSV_SEPARATOR);
	}
	inline bool is_new_line(char c) {
		return (c == '\n');
	}
	inline bool is_double_quote(char c) {
		return (c == '"');
	}
	inline bool is_start_comment(char c) {
		return (c == '#');
	}
}

#endif