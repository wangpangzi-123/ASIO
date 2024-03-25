#pragma once
#include <boost/asio.hpp>
extern void error_log(boost::system::error_code& ec);

extern int client_end_point();
extern int server_end_point();

extern int create_tcp_socket();

extern int create_acceptor_socket();

extern int bind_acceptor_socket();

extern int connect_to_end();

extern int dns_connnect_to_end();

extern int accept_new_connnection();

extern void use_const_buffer();

extern void use_buffer_str();

extern int send_data_by_write_some();