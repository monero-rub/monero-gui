#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>

//typedef boost::multiprecision::cpp_dec_float_50 xmc_float;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<64> > xmc_float;
typedef boost::multiprecision::cpp_int xmc_int;
typedef boost::multiprecision::uint128_t xmc_uint_128;

const xmc_float XMC_UINT = xmc_float(1000000000000.0);
//const xmc_int XMC_INT_UINT = xmc_int(1000000000000);
const xmc_uint_128 XMC_INT_MAX = xmc_uint_128((uint64_t)10000000000000000000ull);

inline double xmc_int_to_double(xmc_int amount) {
        xmc_uint_128 amount_128 = amount.convert_to<xmc_uint_128>();
        std::cout<<"uint128_t amount:" << amount_128 << std::endl;

	if(amount_128 < XMC_INT_MAX)
	{
		uint64_t int_amount = amount_128.convert_to<uint64_t>();
		//std::cout<< "amount < XMC_DEFAULT_DECIMAL :" << int_amount << std::endl;
		double ret = int_amount / 1000000000000.0;
		//std::cout<< "****** return value:" << ret << std::endl;
		return ret;
	}
	//std::setprecision(std::numeric_limits<xmc_float>::max_digits10);
	//std::cout<<"# XMC int to double ==> xmc_int:" << amount << std::endl;
	//xmc_float amount_float = amount_128.convert_to<xmc_float>();
	xmc_float amount_float = xmc_float(amount_128);
	//std::cout<<"# XMC int to double ==> xmc_float:" << amount_float << std::endl;
	xmc_float amount_xmc = amount_float / XMC_UINT;
	//std::cout<<"#XMC int to double ==> amount_xmc:" << amount_xmc << std::endl;
	double ret = amount_xmc.convert_to<double>();
	//std::cout<<"#XMC int to double ==> result:" << ret << std::endl;
	return ret;
}
