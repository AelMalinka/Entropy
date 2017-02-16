/*	Copyright 2010 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
	Exception
*/

#if !defined ENTROPY_EXCEPTION_INC
#	define ENTROPY_EXCEPTION_INC

#	include <boost/exception/all.hpp>
#	include <boost/throw_exception.hpp>

#	include <stdexcept>
#	include <iostream>

	namespace Entropy
	{
		struct ErrorInfoNotFound;

		struct ExceptionBase :
			boost::exception
		{
			public:
				const char *what() const noexcept;
				~ExceptionBase() noexcept;
				template<typename ErrorInfo>
				const typename ErrorInfo::value_type &get() const;
				template<typename ErrorInfo>
				bool has() const;
			protected:
				ExceptionBase();
				ExceptionBase(const std::string &Type);
				ExceptionBase(const std::string &Type, const std::string &Desc);
			private:
				std::string m_type;
				std::string m_desc;
				std::string m_what;
		};

		struct Exception :
			std::exception,
			ExceptionBase
		{
			virtual ~Exception() noexcept;
			virtual const char *what() const noexcept;
			protected:
				Exception(const std::string &Type);
				Exception(const std::string &Type, const std::string &Desc);
		};

#		define ENTROPY_EXCEPTION_BASE(NAME, DESC) struct NAME : ::Entropy::Exception {\
			NAME() : ::Entropy::Exception(DESC, "") {} \
			NAME(const std::string &What) : ::Entropy::Exception(DESC, What) {} \
			NAME(const std::string &Desc, const std::string &What) : ::Entropy::Exception(Desc, What) {} \
			virtual ~NAME() noexcept; }; \
			inline NAME::~NAME() noexcept = default

//		2010-03-05 AMR TODO: BASE is not checked to be of eventual type Entropy::Exception
#		define ENTROPY_EXCEPTION(NAME, DESC, BASE) struct NAME : BASE {\
			NAME() : BASE(DESC, "") {}\
			NAME(const std::string &What) : BASE(DESC, What) {}\
			virtual ~NAME() noexcept; }; \
			inline NAME::~NAME() noexcept = default

#		define ENTROPY_ERROR_INFO(NAME, TYPE)\
			typedef boost::error_info<struct tag_##NAME, TYPE> NAME

		ENTROPY_ERROR_INFO(SystemErrorCode, std::error_code);
		ENTROPY_ERROR_INFO(SystemError, std::string);
		ENTROPY_ERROR_INFO(BackTrace, std::string);

		using ::boost::throw_function;
		using ::boost::throw_file;
		using ::boost::throw_line;

		void AttachTrace(boost::exception &);

		template<typename E>
		typename ::boost::exception_detail::enable_error_info_return_type<E>::type enable_trace(const E &);

#		define ENTROPY_ATTACH_TRACE(x)\
			(::Entropy::enable_trace(x) <<\
			::Entropy::throw_function(BOOST_CURRENT_FUNCTION) <<\
			::Entropy::throw_file(__FILE__) <<\
			::Entropy::throw_line((int)__LINE__))

#		define ENTROPY_THROW(x)\
			::boost::throw_exception(ENTROPY_ATTACH_TRACE(x))
	}

	template<typename charT>
	std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &os, const std::exception &e);

#	include "Exception.impl.hh"

#endif
