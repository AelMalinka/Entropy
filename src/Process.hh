/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_PROCESS_INC
#	define ENTROPY_PROCESS_INC

#	include "Exception.hh"

#	include <iostream>

// 2017-03-23 AMR TODO: split out unix/windows implementations
#	include <unistd.h>

// 2016-01-19 AMR FIXME: implement what is needed of this on own, boost is using deprecated headers
#	include <boost/iostreams/stream.hpp>
#	include <boost/iostreams/device/file_descriptor.hpp>

	namespace Entropy
	{
		class Process
		{
			public:
				explicit Process(const std::function<void ()> &);
				explicit Process(const std::string &);
				~Process();
				std::ostream &In();
				std::istream &Out();
				std::istream &Error();
				int Return();
				void Term();
			private:
				class Pipe
				{
					public:
						Pipe();
						~Pipe();
						int Read();
						int Write();
					private:
						bool _read;
						bool _write;
						int _pipes[2];
				};
				void _iam_child(const std::function<void ()> &); 
				void _iam_parent();
			private:
				pid_t _child;
				Pipe _in_pipe;
				Pipe _out_pipe;
				Pipe _err_pipe;
				boost::iostreams::stream<boost::iostreams::file_descriptor> _in;
				boost::iostreams::stream<boost::iostreams::file_descriptor> _out;
				boost::iostreams::stream<boost::iostreams::file_descriptor> _err;
		};
	}

#endif
