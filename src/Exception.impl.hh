/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_EXCEPTION_IMPL
#	define ENTROPY_EXCEPTION_IMPL

#	include "Exception.hh"

	namespace Entropy
	{
		ENTROPY_EXCEPTION_BASE(GeneralFailure, "General Failure");
		ENTROPY_EXCEPTION_BASE(ErrorInfoNotFound, "Error Info Not Found");

		template<typename ErrorInfo>
		const typename ErrorInfo::value_type &ExceptionBase::get() const
		{
			if(boost::get_error_info<ErrorInfo>(*this) == NULL)
				throw ErrorInfoNotFound();
			return *boost::get_error_info<ErrorInfo>(*this);
		}

		template<typename ErrorInfo>
		bool ExceptionBase::has() const
		{
			return boost::get_error_info<ErrorInfo>(*this) != NULL;
		}

		template<typename E>
		typename ::boost::exception_detail::enable_error_info_return_type<E>::type enable_trace(const E &e)
		{
			auto ret(::boost::enable_error_info(e));

			AttachTrace(ret);

			return ret;
		}
	}

	template<typename charT>
	std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &os, const std::exception &e)
	{
		os << e.what();
#		if defined DEBUG
			using std::endl;
			using boost::diagnostic_information;
			using std::basic_string;

			basic_string<charT> s = diagnostic_information(e);
			s = s.substr(0, s.size() - 1);
			os << endl << s;
#		endif
		return os;
	}

#endif
