#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/numeric/conversion/cast.hpp>

typedef boost::multiprecision::cpp_dec_float_50 xmc_float;
typedef boost::multiprecision::cpp_int xmc_int;
static xmc_float XMC_UINT = 1000000000000.0;

inline double xmc_int_to_double(xmc_int amount) {
	xmc_float amount_float = amount.convert_to<xmc_float>();
	xmc_float amount_xmc = amount_float / XMC_UINT;
	double ret = amount_xmc.convert_to<double>();
	return ret;
}
