#ifndef DATAPOINT_HPP_
#define DATAPOINT_HPP_

template <typename Type>
class DataPoint {

public:
	DataPoint();
	DataPoint(Type);
	
	Type interpolate(DataPoint<Type>, float) const;
	
private:
	Type _value;
	unsigned int _length;
	
};

template <typename Type>
DataPoint<Type>::DataPoint() {
	_length = 0;
}

template <typename Type>
DataPoint<Type>::DataPoint(Type value) {
	_value = value;
	_length = 0;
}

template <typename Type>
Type DataPoint<Type>::interpolate(DataPoint<Type> target, float progression) const {
	Type diff = target._value - _value;
	return _value + (diff * progression);
}

#endif
