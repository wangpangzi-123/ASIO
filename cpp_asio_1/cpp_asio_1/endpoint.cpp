#include "endpoint.h"
#include <boost/asio.hpp>
#include <iostream>
using namespace boost;

//***********************���� ip �� �˿�***********************//
void error_log(boost::system::error_code& ec)
{
	if (ec.value() != 0)
	{
		std::cout << "Failed to parse the IP address. Error code = "
			<< ec.value() << "Message :" << ec.message() << '\n';
	}
}

int client_end_point()
{
	//ʹ�� asio ȥ���� 
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port = 3333;
	//������һ��������
	boost::system::error_code ec;
	//������һ��ip_address ���� fr
	boost::asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address, ec);
	error_log(ec);

	asio::ip::tcp::endpoint ep(ip_address, port);
	return 0;
}

int server_end_point()
{
	//���������Ҳ��һ�������
	unsigned short port_num = 3333;
	//����˵� ip ��ַһ����any
	boost::asio::ip::address ip_address = asio::ip::address_v6::any();
	asio::ip::tcp::endpoint ep(ip_address, port_num);

	return 0;
}
//***********************���� ip �� �˿�***********************//

//***********************���� tcp �� socket*******************//
int create_tcp_socket()
{
	//����socket��Ϊ4��, �°�ֻ��Ҫ3����
	// 
	//1������ ������iocontext
	asio::io_context ios;

	//2������ipv4��Э��
	asio::ip::tcp protocol = asio::ip::tcp::v4();

	//3������socket
	asio::ip::tcp::socket sock(ios);

	////4����socket, �°治��Ҫ����һ����
	//boost::system::error_code ec;
	//sock.open(protocol, ec);
	//error_log(ec);

	return 0;
}

int create_acceptor_socket()
{
	//�°汾ֻ��Ҫ����
	asio::io_context ios;

	//asio::ip::tcp::acceptor acceptor(ios);

	//asio::ip::tcp protocol = asio::ip::tcp::v4();

	//boost::system::error_code ec;

	//acceptor.open(protocol, ec);
	//if (ec.value() != 0)
	//{

	//}
	
	//�°汾
	asio::ip::tcp::acceptor acceptor(ios, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 3333));


	return 0;
}

int bind_acceptor_socket()
{
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(),
		port_num);

	asio::io_context ios;

	asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
	
	boost::system::error_code ec;
	// Step 4. Binding the acceptor socket.
	acceptor.bind(ep, ec);
	// Handling errors if any.
	if (ec.value() != 0) {
		// Failed to bind the acceptor socket. Breaking
		// execution.
		std::cout << "Failed to bind the acceptor socket."
			<< "Error code = " << ec.value() << ". Message: "
			<< ec.message();
		return ec.value();
	}
	return 0;
}

int connect_to_end()
{
	std::string raw_ip_address = "192.168.1.124";
	unsigned short port_num = 3333;
	try 
	{
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ios;
		asio::ip::tcp::socket sock(ios, ep.protocol());
		sock.connect(ep);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code()
			<< ".Message:" << e.what();
		return e.code().value();
	}
	return 0;
}

//��������
int dns_connnect_to_end()
{
	std::string host = "llfc.club";
	std::string port_num = "3333";
	asio::io_context ios;

	asio::ip::tcp::resolver::query resolver_query(host, port_num, asio::ip::tcp::resolver::query::numeric_service);

	asio::ip::tcp::resolver resolver(ios);	//�󶨵����������

	try 
	{
		asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);
		asio::ip::tcp::socket sock(ios);
		asio::connect(sock, it);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}

	return 0;
}

int accept_new_connnection()
{
	const int BACKLOG_SIZE = 30;
	unsigned short port_num = 3333;
	asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);

	asio::io_context ios;

	try
	{
		asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
		// Step 4. Binding the acceptor socket to the 
		// server endpint.
		acceptor.bind(ep);
		// Step 5. Starting to listen for incoming connection
		// requests.
		acceptor.listen(BACKLOG_SIZE);
		// Step 6. Creating an active socket.
		asio::ip::tcp::socket sock(ios);
		// Step 7. Processing the next connection request and 
		// connecting the active socket to the client.
		acceptor.accept(sock);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
}

void use_const_buffer()
{
	std::string buf = "hello world";
	asio::const_buffer asio_buf(buf.c_str(), buf.length());

	std::vector<asio::const_buffer> buffer_sequence;

	buffer_sequence.push_back(asio_buf);

	//asio.send()
}

void use_buffer_str()
{
	asio::const_buffers_1 output_buf = asio::buffer("hello world");
}

void use_buffer_array()
{
	const size_t BUF_SIZE_BYTES = 20;
	std::unique_ptr<char[]>buf(new char[BUF_SIZE_BYTES]);
	auto input_buf = asio::buffer(static_cast<void*>(buf.get()), BUF_SIZE_BYTES);
}
void write_to_socket(asio::ip::tcp::socket& sock)
{
	std::string buf = "Hello World!";
	std::size_t total_bytes_written = 0;

	while (total_bytes_written != buf.length())
	{
		total_bytes_written += sock.write_some(asio::buffer(buf.c_str() + total_bytes_written, buf.length() - total_bytes_written));
	}
}

extern int send_data_by_write_some()
{
	std::string raw_ip_address = "192.168.3.11";
	unsigned short port_num = 3304;
	try
	{
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());
		
		sock.connect(ep);
		write_to_socket(sock);
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

int send_data_by_send()
{
	std::string raw_ip_address = "192.168.3.11";
	unsigned short port_num = 3304;
	std::string buf = "Hello World";
	try
	{
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());

		sock.connect(ep);
		int send_length = sock.send(asio::buffer(buf.c_str(), buf.length()));	//sock.write_some ��TCP �������п��оͷ��ͣ� sock.write �� һ���Խ�buf �͸�TCP ������
		if (send_length <= 0)
		{
			return 0;
		}
		
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}


int send_data_by_write()
{
	std::string raw_ip_address = "192.168.3.11";
	unsigned short port_num = 3304;
	std::string buf = "Hello World";
	try
	{
		asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);
		asio::io_context ioc;
		asio::ip::tcp::socket sock(ioc, ep.protocol());

		sock.connect(ep);
		int send_length = asio::write(sock, asio::buffer(buf.c_str(), buf.length()));	//Ҳ�������ȴ� һ���Է���
	}
	catch (system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code()
			<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}

std::string read_from_socket(asio::ip::tcp::socket& sock)
{
	return NULL;
}