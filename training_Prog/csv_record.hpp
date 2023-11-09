#ifndef CSV_RECORD_HPP
#define CSV_RECORD_HPP


#include <vector>
#include <optional>
#include <string>

namespace csv_parser {

	class Csv_data;

	class Csv_record {
		public:
			// Working on float so value type is float for now, should be string or integer in most cases.
			typedef float value_type;
			typedef std::vector<value_type>::const_iterator const_iterator;
		private:
			friend class Csv_data;
			Csv_data const& owner_;
			std::vector<value_type> fields_;

		public:
			Csv_record(Csv_data const& owner) : owner_(owner) {}
			bool add_field(value_type new_field);
			const_iterator begin() const;
			const_iterator end() const;
			value_type const& operator[](size_t i) const;
			std::optional<value_type> operator[](std::string const& header) const;
			size_t size() const;
	};
}

#include "csv_data.hpp"

#endif