#include <boost/interprocess/detail/config_begin.hpp>
//[doc_message_queueA
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <boost/asio.hpp>
#include <utility>
#include <unistd.h>

using namespace boost::interprocess;

int main()
{
	try
	{
		message_queue::remove("camera message_queue");
		message_queue mq(
		create_only
		, "camera message_queue"
		, 100
		, sizeof(char)
		);
		//usleep(1000000*100000000); 
	}
	catch (interprocess_exception &ex)
	{
		std::cout << "From main: " << ex.what() << std::endl;
	}
	
}
