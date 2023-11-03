#include "csv_record.hpp"

namespace csv_parser {

	bool Csv_record::add_field(value_type new_field) {
		if (owner_.headers().size() <= fields_.size())
			return false;
		fields_.push_back(new_field);
		return true;
	}

	Csv_record::const_iterator Csv_record::begin() const {
		return fields_.cbegin();
	}

	Csv_record::const_iterator Csv_record::end() const {
		return fields_.cend();
	}

	Csv_record::value_type const& Csv_record::operator[](size_t i) const {
		return fields_[i];
	}

	std::optional<Csv_record::value_type> Csv_record::operator[](std::string const& header) const {
		Csv_record::const_iterator it = fields_.cbegin();
		Csv_record::const_iterator ite = fields_.cend();
		auto ith = owner_.headers().begin();
		auto ithe = owner_.headers().end();
		while (ith != ithe && it != ite) {
			if (*ith == header)
				return std::make_optional<value_type>(*it);
			ith++;
			it++;
		}
		return std::make_optional<value_type>();
	}

	size_t Csv_record::size() const {
		return fields_.size();
	}

}