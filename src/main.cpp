
#include "serverResource.hpp"
#include "paypal.hpp"
#include <boost/asio/yield.hpp>
#include <boost/asio/coroutine.hpp>
using namespace boost::asio;
#include <restbed>
#include <test.hpp>
using namespace std;
using namespace restbed;

int main() {
	try
	{

		cout<<sizeof(short)<<endl;
		cout<<sizeof(int)<<endl;
		cout<<sizeof(long)<<endl;
		cout<<sizeof(float)<<endl;
		cout<<sizeof(double)<<endl;
		cout<<sizeof(long double)<<endl;
		cout<<sizeof(long long)<<endl;
		cout<<sizeof(int *)<<endl;
		cout<<sizeof(size_t)<<endl;		
		//read config.ini
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("config.ini", pt);
		unsigned short port = boost::lexical_cast<unsigned short>(pt.get<std::string>("webserver.port"));
		size_t threads = boost::lexical_cast<size_t>(pt.get<std::string>("webserver.threads"));

		{
			boost::timer::cpu_timer pass;
			pass.start();

			boost::shared_ptr<call_center> test=call_center::get_instance();
			boost::shared_ptr<caller> c=boost::shared_ptr<caller>(new caller());
			// c->set_rank(0);
			// test->add_call(c);
			// test->dispatch_call();

			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		////HTTP-server at port 8080 using 4 threads
		//boost::shared_ptr<HttpServer> server = boost::shared_ptr<HttpServer>(new HttpServer(port, threads));
		////serverResource(server);
		//server_resource t;
		//t(server);
		//thread server_thread([&server](){
		//	//Start server
		//	server->start();
		//});
		//
		//server_thread.join();
		//boost::shared_ptr<HttpsServer> server = boost::shared_ptr<HttpsServer>(new HttpsServer(port, threads, "ssl/server.crt", "ssl/server.key", 5,300,"ssl/dh768.pem"));
		//servers_resource t(server);
		//thread server_thread([&server](){
		//	//Start server
		//	server->start();
		//});
		//this_thread::sleep_for(chrono::seconds(10));
		//
		//
		//server_thread.join();
		
		//{
		//	//curl -X POST 'https://api.sandbox.paypal.com/v1/oauth2/token'  -H "Accept: application/json"  -H "Accept - Language: en_US"  -u "AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo" -d "grant_type=client_credentials"
		//	//boost::timer::cpu_timer pass;
		//	//pass.start();
		//	//HttpsClient client("api.sandbox.paypal.com", false);
		//	//HttpsClient client("127.0.0.1:8888", false);
		//	HttpsClient client("127.0.0.1:8888", true, "ssl/server.crt", "ssl/server.key", "ssl/dh768.pem");
		//	//cout << __LINE__ << endl;
		//	std::stringstream ss;
		//	ss << "grant_type=client_credentials";
		//	std::map<std::string, std::string> header;
		//	header.insert(make_pair("Accept", "application/json"));
		//	header.insert(make_pair("Accept-Language", "en_US"));
		//	//header.insert(make_pair("Authorization", "Basic AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo"));
		//	string auth = "AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo";
		//	auto r1 = client.request("POST", "/v1/oauth2/token", ss, header,auth);
		//	//auto r1 = client.request("POST", "/v1/oauth2/token");
		//	cout << __LINE__<<":"<<r1->content.rdbuf() << endl;
		//	//std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		//}
		//
		//{
		//	//curl -v -X GET 'https://api.sandbox.paypal.com/v1/payments/payment?sort_order=asc&sort_by=update_time' -H "Content-Type:application/json" -H "Authorization: Bearer A101.aSJ8QgWcCXOAsB6vGPrHxqNxjB7M5-P5-RoIECH3VFQrjap_Jw1plDKJ6CdqNE5M.qJHuEy4Ubs_gmzOE9PbP6cFJmla"
		//	//boost::timer::cpu_timer pass;
		//	//pass.start();
		//	HttpsClient client("api.sandbox.paypal.com", false);
		//	std::stringstream ss;
		//	std::map<std::string, std::string> header;
		//	header.insert(make_pair("Content-Type", "application/json"));
		//	header.insert(make_pair("Authorization", "Bearer A101.aSJ8QgWcCXOAsB6vGPrHxqNxjB7M5-P5-RoIECH3VFQrjap_Jw1plDKJ6CdqNE5M.qJHuEy4Ubs_gmzOE9PbP6cFJmla"));
		//	
		//	auto r1 = client.request("GET", "/v1/payments/payment?sort_order=asc&sort_by=update_time", ss, header, "");
		//	//auto r1 = client.request("POST", "/v1/oauth2/token");
		//	cout << __LINE__ << ":" << r1->content.rdbuf() << endl;
		//	//std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		//}
	}
	catch (std::exception& e) {
		//cout << diagnostic_information(e) << endl;
		cout << e.what() << endl;
        }
	catch(...) 
	{
         
	}
    return 0;
}