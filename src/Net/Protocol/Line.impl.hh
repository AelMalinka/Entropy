/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_NET_PROTOCOL_LINE_IMPL
#	define ENTROPY_NET_PROTOCOL_LINE_IMPL

#	include <type_traits>

	namespace Entropy
	{
		namespace Net
		{
			namespace Protocol
			{
				namespace detail
				{
					template<typename T, typename F, typename Sfinae = void>
					struct has_connect : std::false_type {};

					template<typename T, typename F, typename Sfinae = void>
					struct has_error : std::false_type {};

					template<typename T, typename F, typename Sfinae = void>
					struct has_disconnect : std::false_type {};

					template<typename T, typename R, typename ...A>
					struct has_connect<T, R(A...),
						typename std::enable_if<
							std::is_same<R, void>::value ||
							std::is_convertible<decltype(
								std::declval<T>().onConnect(std::declval<A>()...)
							), R>::value
						>::type
					> : std::true_type {};

					template<typename T, typename R, typename ...A>
					struct has_error<T, R(A...),
						typename std::enable_if<
							std::is_same<R, void>::value ||
							std::is_convertible<decltype(
								std::declval<T>().onError(std::declval<A>()...)
							), R>::value
						>::type
					> : std::true_type {};

					template<typename T, typename R, typename ...A>
					struct has_error<T, R(A...),
						typename std::enable_if<
							std::is_same<R, void>::value ||
							std::is_convertible<decltype(
								std::declval<T>().onDisconnect(std::declval<A>()...)
							), R>::value
						>::type
					> : std::true_type {};

					template<typename A, bool Has>
					struct call_connect
					{
						template<typename ...Params>
						static void apply(A &a, Params && ...params)
						{
							a.onConnect(params...);
						}
					};

					template<typename A, bool Has>
					struct call_error
					{
						template<typename ...Params>
						static void apply(A &a, Params && ...params)
						{
							a.onError(params...);
						}
					};

					template<typename A, bool Has>
					struct call_disconnect
					{
						template<typename ...Params>
						static void apply(A &a, Params && ...params)
						{
							a.onDisconnect(params...);
						}
					};

					template<typename A>
					struct call_connect<A, false>
					{
						template<typename ...Params>
						static void apply(A &, Params && ...)
						{}
					};

					template<typename A>
					struct call_error<A, false>
					{
						template<typename ...Params>
						static void apply(A &, Params && ...)
						{}
					};

					template<typename A>
					struct call_disconnect<A, false>
					{
						template<typename ...Params>
						static void apply(A &, Params && ...)
						{}
					};
				}

				template<typename Application, typename Socket>
				Line<Application, Socket>::Line(Application &a, const std::string &delim)
					: _app(a), _buffs(), _delim(delim)
				{}

				template<typename Application, typename Socket>
				Line<Application, Socket>::Line(Application &a)
					: Line<Application, Socket>(a, "\r\n")
				{}

				template<typename Application, typename Socket> Line<Application, Socket>::~Line() = default;

				template<typename Application, typename Socket>
				void Line<Application, Socket>::onConnect(Socket &s)
				{
					_buffs[s].reserve(_buffer_size);
					detail::call_connect<Application, detail::has_connect<Application, void(Socket &s)>::value>::apply(_app, s);
				}

				template<typename Application, typename Socket>
				void Line<Application, Socket>::onDisconnect(Socket &s)
				{
					_buffs.erase(s);
					detail::call_disconnect<Application, detail::has_disconnect<Application, void(Socket &s)>::value>::apply(_app, s);
				}

				template<typename Application, typename Socket>
				void Line<Application, Socket>::onError(const Net::Exception &e)
				{
					detail::call_error<Application, detail::has_error<Application, void(const Net::Exception &e)>::value>::apply(_app, e);

					if(!detail::has_error<Application, void(const Net::Exception &e)>::value)
						throw e;
				}

				template<typename Application, typename Socket>
				void Line<Application, Socket>::onData(Socket &sock, std::string &&buff)
				{
					using std::string;
					using std::size_t;

					_buffs[sock] += buff;
					size_t pos = string::npos;
					while((pos = _buffs[sock].find(_delim)) != string::npos)
					{
						_app.onLine(sock, _buffs[sock].substr(0, pos));
						_buffs[sock].erase(0, pos + _delim.size());
					}
				}
			}
		}
	}

#endif
