#pragma once

#include <vector>
#include "typedefs.hpp"


class DataHolder{
public:
	struct DataType{
		double rproj, vlos, r3d;
	};
private:
	std::vector<DataType> data_;
public:
	DataHolder(const np_array<double> & data) : data_(data.shape(0)){
		if (data.shape(1) != 3){
			throw std::invalid_argument("Data must have 3 columns");
		}
		for (unsigned i = 0; i < data.shape(0); ++i){
			data_[i] = {data.at(i,0), data.at(i,1), data.at(i,2)};
		}
	}
	
	unsigned size() const{
		return data_.size();
	}

	auto begin() const{
		return data_.begin();
	}
	auto begin(){
		return data_.begin();
	}
	auto end() const{
		return data_.end();
	}
	auto end(){
		return data_.end();
	}
	
	DataType operator[](unsigned i) const{
		return data_[i];
	}
	DataType& operator[](unsigned i){
		return data_[i];
	}
};