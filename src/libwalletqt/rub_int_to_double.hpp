#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>

//typedef boost::multiprecision::cpp_dec_float_50 rub_float;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<64> > rub_float;
typedef boost::multiprecision::cpp_int rub_int;
typedef boost::multiprecision::uint128_t rub_uint_128;

const rub_float RUB_UINT = rub_float(1000000000000.0);
const rub_uint_128 RUB_INT_MAX = rub_uint_128((uint64_t)10000000000000000000ull);

inline double rub_int_to_double(rub_int amount) {
        rub_uint_128 amount_128 = amount.convert_to<rub_uint_128>();
        //std::cout<<"uint128_t amount:" << amount_128 << std::endl;

	if(amount_128 < RUB_INT_MAX)
	{
		uint64_t int_amount = amount_128.convert_to<uint64_t>();
		//std::cout<< "amount < RUB_DEFAULT_DECIMAL :" << int_amount << std::endl;
		double ret = int_amount / 1000000000000.0;
		//std::cout<< "****** return value:" << ret << std::endl;
		return ret;
	}
	//std::setprecision(std::numeric_limits<rub_float>::max_digits10);
	//std::cout<<"# RUB int to double ==> rub_int:" << amount << std::endl;
	//rub_float amount_float = amount_128.convert_to<rub_float>();
	rub_float amount_float = rub_float(amount_128);
	//std::cout<<"# RUB int to double ==> rub_float:" << amount_float << std::endl;
	rub_float amount_rub = amount_float / RUB_UINT;
	//std::cout<<"#RUB int to double ==> amount_rub:" << amount_rub << std::endl;
	double ret = amount_rub.convert_to<double>();
	//std::cout<<"#RUB int to double ==> result:" << ret << std::endl;
	return ret;
}
