/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Process.hh"
#include <cstdlib>
#include <cerrno>
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>

using namespace Entropy;
using namespace std;
using namespace boost::iostreams;

Process::Process(const function<void()> &what)
	: _child(0), _in_pipe(), _out_pipe(), _err_pipe(), _in(), _out(), _err()
{
	_child = fork();

	if(_child == 0)
		_iam_child(what);
	else if(_child > 0)
		_iam_parent();
	else
		ENTROPY_THROW(
			GeneralFailure("Fork Failed") <<
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
}

Process::Process(const string &what)
	: _child(0), _in_pipe(), _out_pipe(), _err_pipe(), _in(), _out(), _err()
{
	_child = fork();

	if(_child == 0)
		_iam_child([what](){
			execl("/bin/sh", "sh", "-c", what.c_str(), (char *)NULL);
		});
	else if(_child > 0)
		_iam_parent();
	else
		ENTROPY_THROW(
			GeneralFailure("Fork Failed") <<
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
}

Process::~Process()
{
	int status = EXIT_FAILURE;
	waitpid(_child, &status, 0);
}

ostream &Process::In()
{
	return _in;
}

istream &Process::Out()
{
	return _out;
}

istream &Process::Error()
{
	return _err;
}

int Process::Return()
{
	int status;

	waitpid(_child, &status, 0);

	return WEXITSTATUS(status);
}

void Process::Term()
{
	if(kill(_child, SIGTERM) < 0)
		ENTROPY_THROW(
			GeneralFailure("Sending TERM to child failed") <<
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
}

void Process::_iam_child(const function<void()> &what)
{
	// 2015-12-25 AMR NOTE: close write side in and read side out/error
	close(_in_pipe.Write());
	close(_out_pipe.Read());
	close(_err_pipe.Read());
	// 2015-12-25 AMR NOTE: redirect to pipes
	int newfd = dup2(_in_pipe.Read(), STDIN_FILENO);
	if(newfd == -1)
		ENTROPY_THROW(
			GeneralFailure("unable to dup STDIN") <<
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
	else if(newfd != STDIN_FILENO)
		ENTROPY_THROW(
			GeneralFailure("unable to dup STDIN")
		);

	newfd = dup2(_out_pipe.Write(), STDOUT_FILENO);
	if(newfd == -1)
		ENTROPY_THROW(
			GeneralFailure("unable to dup STDOUT") <<
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
	else if(newfd != STDOUT_FILENO)
		ENTROPY_THROW(
			GeneralFailure("unable to dup STDOUT")
		);

	newfd = dup2(_err_pipe.Write(), STDERR_FILENO);
	if(newfd == -1)
		ENTROPY_THROW(
			GeneralFailure("unable to dup STDERR") <<
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
	else if(newfd != STDERR_FILENO)
		ENTROPY_THROW(
			GeneralFailure("unable to dup STDERR")
		);
	
	// 2015-12-25 AMR NOTE: run what
	what();
	exit(0);
}

void Process::_iam_parent()
{
	// 2015-12-25 AMR NOTE: close read side in and write side out/error
	close(_in_pipe.Read());
	close(_out_pipe.Write());
	close(_err_pipe.Write());
	// 2015-12-25 AMR NOTE: wrap pipes
	_in.open(_in_pipe.Write(), never_close_handle);
	_out.open(_out_pipe.Read(), never_close_handle);
	_err.open(_err_pipe.Read(), never_close_handle);
}

Process::Pipe::Pipe()
{
	if(pipe(_pipes) < 0)
		ENTROPY_THROW(
			GeneralFailure("Pipe creation failed") << 
			SystemErrorCode(error_code(errno, system_category())) <<
			SystemError(strerror(errno))
		);
}

Process::Pipe::~Pipe()
{
	close(_pipes[0]);
	close(_pipes[1]);
}

int Process::Pipe::Read()
{
	return _pipes[0];
}

int Process::Pipe::Write()
{
	return _pipes[1];
}
