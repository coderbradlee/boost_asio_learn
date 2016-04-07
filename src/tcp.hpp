#ifndef TCP_HPP
#define	TCP_HPP

#include  "include.hpp"
//#define DEBUG
#include "fcgio.h"
#include <unistd.h>
#include <sstream>
#include <unistd.h>
#define FORCE_TO_USE_MSG_RECV_BUFFER
#include "include/st_asio_wrapper_base.h"
#include "include/st_asio_wrapper_tcp_client.h"
using namespace st_asio_wrapper;
class tcp_client
{
private:
	st_service_pump m_service_pump;
	st_tcp_sclient m_client;
public:
    tcp_client(const string& host,int port):m_client(service_pump)
    {
		m_client.set_server_addr(port, host);
		m_service_pump.start_service();
		m_client.safe_send_msg(str);
	}
};
#endif

