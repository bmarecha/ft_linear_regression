#ifndef CSV_DATA_HPP
#define CSV_DATA_HPP

#include <string>
#include <vector>
#include "csv_parser.hpp"
#include "csv_record.hpp"

namespace csv_parser {
	class Csv_data {
		public:
			typedef std::vector<Csv_record>::const_iterator const_iterator;
		private :
			friend class Csv_data_handler;
			std::vector<Csv_record> records_;
			std::vector<std::string> headers_;
			void new_record() { records_.emplace_back(*this); }
			bool add_field(Csv_record::value_type const& field) { return records_.back().add_field(field); }
		public:
			inline const_iterator begin() const { return records_.cbegin();}
			inline const_iterator end() const { return records_.cend(); }
			inline Csv_record const& operator[](size_t i) { return records_[i]; }
			inline size_t size() const { return records_.size(); }
			inline std::vector<std::string> const& headers() const { return headers_; }
	};
}


#endif