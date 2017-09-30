#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Entropy;
using namespace Entropy::Test;

namespace Tests
{
	class Application :
		public Entropy::Application
	{
		public:
			Application()
				: Entropy::Application()
			{}
			~Application() = default;
			void operator () ();
	};

	TEST_CLASS(ApplicationTests)
	{
		public:
			TEST_METHOD(Run)
			{
			}
	};
}