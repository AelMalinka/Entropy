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
				const char *what() const throw();
				~ExceptionBase() throw();
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
			virtual ~Exception() throw();
			virtual const char *what() const throw();
			protected:
				Exception(const std::string &Type);
				Exception(const std::string &Type, const std::string &Desc);
		};

#		define ENTROPY_EXCEPTION_BASE(NAME, DESC) struct NAME : ::Entropy::Exception {\
			NAME() : ::Entropy::Exception(DESC, "") {} \
			NAME(const std::string &What) : ::Entropy::Exception(DESC, What) {} \
			NAME(const std::string &Desc, const std::string &What) : ::Entropy::Exception(Desc, What) {} \
			virtual ~NAME() throw(); }; \
			inline NAME::~NAME() throw() = default

//		2010-03-05 AMR TODO: BASE is not checked to be of eventual type Entropy::Exception
#		define ENTROPY_EXCEPTION(NAME, DESC, BASE) struct NAME : BASE {\
			NAME() : BASE(DESC, "") {}\
			NAME(const std::string &What) : BASE(DESC, What) {}\
			virtual ~NAME() throw(); }; \
			inline NAME::~NAME() throw() = default

#		define ENTROPY_ERROR_INFO(NAME, TYPE)\
			typedef boost::error_info<struct tag_##NAME, TYPE> NAME

#		define ENTROPY_ATTACH_TRACE(x)\
			(::boost::enable_error_info(x) <<\
			::boost::throw_function(BOOST_CURRENT_FUNCTION) <<\
			::boost::throw_file(__FILE__) <<\
			::boost::throw_line((int)__LINE__))

#		define ENTROPY_THROW(x)\
			::boost::throw_exception(ENTROPY_ATTACH_TRACE(x))

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

		inline ExceptionBase::ExceptionBase() = default;

		inline ExceptionBase::ExceptionBase(const std::string &Type) :
			boost::exception(), m_type(Type), m_desc(), m_what(Type)
		{}

		inline ExceptionBase::ExceptionBase(const std::string &Type, const std::string &Desc) :
			boost::exception(), m_type(Type), m_desc(Desc), m_what(((Desc != "") ? Type + ": " + Desc : Type))
		{}

		inline ExceptionBase::~ExceptionBase() throw() = default;

		inline const char *ExceptionBase::what() const throw()
		{
			return m_what.c_str();
		}

		inline Exception::Exception(const std::string &Type)
			: std::exception(), ExceptionBase(Type)
		{}

		inline Exception::Exception(const std::string &Type, const std::string &Desc)
			: std::exception(), ExceptionBase(Type, Desc)
		{}

		inline Exception::~Exception() throw() = default;

		inline const char *Exception::what() const throw()
		{
			return ExceptionBase::what();
		}
	}

	template<typename charT>
	inline std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &os, const std::exception &e)
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