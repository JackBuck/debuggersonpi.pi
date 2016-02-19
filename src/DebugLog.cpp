#include "DebugLog.hpp"

#ifdef DEBUG_LOG_ENABLE

#include <exception>

namespace bornander
{
	namespace debug
	{
		int log::indentation = 0;
		std::ostream* log::stream = &std::cout;

		log::log(const std::string& ctx)
			: context(ctx)
#ifdef DEBUG_LOG_ENABLE_TIMING
			, start_time(clock())
#endif
		{
#ifdef DEBUG_SHOW_FUNCTIONS_ENABLE
			write_indentation();
			*stream << "--> " << context << std::endl;
			++indentation;
			stream->flush();
#endif
		}

		log::~log()
		{
#ifdef  DEBUG_SHOW_FUNCTIONS_ENABLE
			--indentation;
			write_indentation(std::uncaught_exception() ? '*' : ' ');
			*stream << "<-- " << context;
#endif
#ifdef DEBUG_LOG_ENABLE_TIMING
			*stream << " in " << ((double)(clock() - start_time) / CLOCKS_PER_SEC) << "s";
#endif
			*stream << std::endl;
			stream->flush();
		}

		void log::set_stream(std::ostream& stream)
		{
			log::stream = &stream;
		}


		void log::write_indentation()
		{
			write_indentation(' ');
		}

		void log::write_indentation(const char prefix)
		{
			*stream << prefix;
			for(int i = 0; i < indentation * 2; ++i)
			{
				*stream << " ";
			}
		}

		void log::message(const std::string& message)
		{
			write_indentation();
			*stream << message << std::endl;
			stream->flush();
		}

	}
}
#endif