#ifndef PAYPAL_HPP
#define	PAYPAL_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
#define DEBUG

class paypal
{
public:
	paypal(const std::string& client_id, const std::string& client_secret) :m_client_id(client_id), m_client_secret(client_secret)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
		
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
		m_headerlist = NULL;

#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
#endif
		m_oauth2_token_uri = m_uri_sandbox + "oauth2/token";
		//m_oauth2_token_uri = m_uri_live+ "oauth2/token";
		curl(m_oauth2_token_uri, "POST", m_auth_content,true);
	}
	virtual ~paypal()
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();
		
	}
	//void payments_payment(const std::string& content)
	/*{
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, payments_payment_callback);
		curl(m_uri_sandbox + "payments/payment?"+content, "GET", content);
		
	}*/
	/*void payments_payment_post(const std::string& content)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, payments_payment_post_callback);
		curl(m_uri_sandbox + "payments/payment", "POST", content);
	}
	void payments_billing_plans_get(const std::string& content)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, payments_billing_plans_get_callback);
		curl(m_uri_sandbox + "payments/billing-plans?page_size=3&status=CREATED&page=2&total_required=yes", "GET", content);
	}
	void vault_credit_cards_get(const std::string& content)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, vault_credit_cards_get_callback);
		curl(m_uri_sandbox + "vault/credit-cards?external_card_id=card-1", "GET", content);
	}
	void identity_openidconnect_userinfo_get(const std::string& content)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, identity_openidconnect_userinfo_get_callback);
		curl(m_uri_sandbox + "identity/openidconnect/userinfo/?schema=openid", "GET", content);
	}*/
protected:	
	//static size_t identity_openidconnect_userinfo_get_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	//{
	//	if (thisPtr)
	//	{
	//		cout << __LINE__ << endl;
	//		return ((paypal*)thisPtr)->identity_openidconnect_userinfo_get_write_data(buffer, size, nmemb);
	//	}

	//	else
	//	{
	//		cout << __LINE__ << endl;
	//		return 0;
	//	}

	//}
	//size_t identity_openidconnect_userinfo_get_write_data(const char *buffer, size_t size, size_t nmemb)
	//{
	//	int result = 0;
	//	if (buffer != 0)
	//	{
	//		//cout << __LINE__ << endl;
	//		m_data.append(buffer, size*nmemb);
	//		result = size*nmemb;
	//	}
	//	/*cout <<__LINE__<<":"<<  buffer << endl;*/
	//	cout << __LINE__ << ":" << m_data << endl;
	//	
	//	return result;
	//}

	//static size_t vault_credit_cards_get_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	//{
	//	if (thisPtr)
	//	{
	//		cout << __LINE__ << endl;
	//		return ((paypal*)thisPtr)->vault_credit_cards_get_write_data(buffer, size, nmemb);
	//	}

	//	else
	//	{
	//		cout << __LINE__ << endl;
	//		return 0;
	//	}

	//}
	//size_t vault_credit_cards_get_write_data(const char *buffer, size_t size, size_t nmemb)
	//{
	//	int result = 0;
	//	if (buffer != 0)
	//	{
	//		//cout << __LINE__ << endl;
	//		m_data.append(buffer, size*nmemb);
	//		result = size*nmemb;
	//	}
	//	/*cout <<__LINE__<<":"<<  buffer << endl;*/
	//	cout << __LINE__ << ":" << m_data << endl;
	//	
	//	return result;
	//}

	//static size_t payments_billing_plans_get_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	//{
	//	if (thisPtr)
	//	{
	//		cout << __LINE__ << endl;
	//		return ((paypal*)thisPtr)->payments_billing_plans_get_write_data(buffer, size, nmemb);
	//	}

	//	else
	//	{
	//		cout << __LINE__ << endl;
	//		return 0;
	//	}

	//}
	//size_t payments_billing_plans_get_write_data(const char *buffer, size_t size, size_t nmemb)
	//{
	//	int result = 0;
	//	if (buffer != 0)
	//	{
	//		//cout << __LINE__ << endl;
	//		m_data.append(buffer, size*nmemb);
	//		result = size*nmemb;
	//	}
	//	/*cout <<__LINE__<<":"<<  buffer << endl;*/
	//	cout << __LINE__ << ":" << m_data << endl;
	//	//ptree pt;
	//	//stringstream stream;
	//	//stream << m_data;
	//	//read_json(stream, pt);

	//	//string scope = pt.get<string>("scope");
	//	//string nonce = pt.get<string>("nonce");
	//	//m_access_token = pt.get<string>("access_token");
	//	//m_token_type = pt.get<string>("token_type");
	//	//string app_id = pt.get<string>("app_id");
	//	//size_t expires_in = pt.get<size_t>("expires_in");
	//	////#ifdef DEBUG
	//	//cout << scope << endl;
	//	//cout << nonce << endl;
	//	//cout << m_access_token << endl;
	//	//cout << m_token_type << endl;
	//	//cout << app_id << endl;
	//	//cout << expires_in << endl;

	//	//#endif
	//	return result;
	//}

	//static size_t payments_payment_post_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	//{
	//	if (thisPtr)
	//	{
	//		cout << __LINE__ << endl;
	//		return ((paypal*)thisPtr)->payments_payment_post_write_data(buffer, size, nmemb);
	//	}

	//	else
	//	{
	//		cout << __LINE__ << endl;
	//		return 0;
	//	}

	//}
	//size_t payments_payment_post_write_data(const char *buffer, size_t size, size_t nmemb)
	//{
	//	int result = 0;
	//	if (buffer != 0)
	//	{
	//		//cout << __LINE__ << endl;
	//		m_data.append(buffer, size*nmemb);
	//		result = size*nmemb;
	//	}
	//	/*cout <<__LINE__<<":"<<  buffer << endl;*/
	//	cout << __LINE__ << ":" << m_data << endl;
	//	//ptree pt;
	//	//stringstream stream;
	//	//stream << m_data;
	//	//read_json(stream, pt);

	//	//string scope = pt.get<string>("scope");
	//	//string nonce = pt.get<string>("nonce");
	//	//m_access_token = pt.get<string>("access_token");
	//	//m_token_type = pt.get<string>("token_type");
	//	//string app_id = pt.get<string>("app_id");
	//	//size_t expires_in = pt.get<size_t>("expires_in");
	//	////#ifdef DEBUG
	//	//cout << scope << endl;
	//	//cout << nonce << endl;
	//	//cout << m_access_token << endl;
	//	//cout << m_token_type << endl;
	//	//cout << app_id << endl;
	//	//cout << expires_in << endl;

	//	//#endif
	//	return result;
	//}

	//static size_t payments_payment_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	//{
	//	if (thisPtr)
	//	{
	//		//cout << __LINE__ << endl;
	//		return ((paypal*)thisPtr)->payments_payment_write_data(buffer, size, nmemb);
	//	}

	//	else
	//	{
	//		//cout << __LINE__ << endl;
	//		return 0;
	//	}

	//}
	//size_t payments_payment_write_data(const char *buffer, size_t size, size_t nmemb)
	//{
	//	int result = 0;
	//	if (buffer != 0)
	//	{
	//		//cout << __LINE__ << endl;
	//		m_data.append(buffer, size*nmemb);
	//		result = size*nmemb;
	//	}
	//	/*cout <<__LINE__<<":"<<  buffer << endl;*/
	//	cout << __LINE__ << ":" << m_data << endl;
	//	//ptree pt;
	//	//stringstream stream;
	//	//stream << m_data;
	//	//read_json(stream, pt);

	//	//string scope = pt.get<string>("scope");
	//	//string nonce = pt.get<string>("nonce");
	//	//m_access_token = pt.get<string>("access_token");
	//	//m_token_type = pt.get<string>("token_type");
	//	//string app_id = pt.get<string>("app_id");
	//	//size_t expires_in = pt.get<size_t>("expires_in");
	//	////#ifdef DEBUG
	//	//cout << scope << endl;
	//	//cout << nonce << endl;
	//	//cout << m_access_token << endl;
	//	//cout << m_token_type << endl;
	//	//cout << app_id << endl;
	//	//cout << expires_in << endl;

	//	//#endif
	//	return result;
	//}

	void curl(const std::string& uri, const std::string& method = "GET", const std::string& content="", bool auth=false)
	{
		
		set_url(uri);
		if (auth)
		{
			cout << __LINE__ << ":" << uri << endl;
			add_header("Accept: application/json");
			add_header("Accept-Language: en_US");
			/*
			string userpass = m_client_id + ":" + m_client_secret;
			curl_easy_setopt(m_curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
			curl_easy_setopt(m_curl, CURLOPT_USERPWD, userpass.c_str());
			
			curl_easy_setopt(m_curl, CURLOPT_SSH_KNOWNHOSTS, "/root/.ssh/known_hosts");
		*/
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, auth_request_callback);

			//curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)29);
			//curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);

			//////////////////////////////////////////////////////////////////////////
			curl_easy_setopt(m_curl, CURLOPT_URL, "https://api.sandbox.paypal.com/v1/oauth2/token");
			curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 1L);
			curl_easy_setopt(m_curl, CURLOPT_USERPWD, "AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo");
			curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
			curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)29);
			curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "curl/7.29.0");
			
			curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);
			curl_easy_setopt(m_curl, CURLOPT_SSH_KNOWNHOSTS, "/root/.ssh/known_hosts");
			curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
			curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);

		}
		else 
		{
			cout << __LINE__ << ":" << uri << endl;
			add_header("Content-Type:application/json");
			add_header("Authorization:"+m_token_type+" "+ m_access_token);
		}
#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);
#endif
		/*curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, content.c_str());
		curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headerlist);
		curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());*/
		
		on_request();
		
		curl_slist_free_all(m_headerlist);
		m_headerlist = NULL;
	}
	void set_url(const std::string& url) const
	{
		curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	}
	bool on_request() 
	{
		m_data.clear();
		return 0 == curl_easy_perform(m_curl);
	}

	static size_t auth_request_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
			return ((paypal*)thisPtr)->auth_write_data(buffer, size, nmemb);
		else
			return 0;
	}

	/**
	* Function used to write the received html/json content to a c++ string.
	*
	* @param buffer
	* @param size
	* @param nmemb
	* @return
	*/
	size_t auth_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			m_data.append(buffer, size*nmemb);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		cout << __LINE__<<":"<< m_data << endl;
		ptree pt;
		stringstream stream;
		stream << m_data;
		read_json(stream, pt);

		string scope = pt.get<string>("scope");
		string nonce = pt.get<string>("nonce");
		m_access_token = pt.get<string>("access_token");
		m_token_type = pt.get<string>("token_type");
		string app_id = pt.get<string>("app_id");
		size_t expires_in = pt.get<size_t>("expires_in");
#ifdef DEBUG
		cout << scope << endl;
		cout << nonce << endl;
		cout << m_access_token << endl;
		cout << m_token_type << endl;
		cout << app_id << endl;
		cout << expires_in << endl;
#endif
		return result;
	}
	void add_header(const std::string& h)
	{
		m_headerlist = curl_slist_append(m_headerlist, h.c_str());
	}
protected:
	std::string m_access_token;
	std::string m_token_type;
	std::string m_client_id;
	std::string m_client_secret;
	std::string m_oauth2_token_uri;
	std::string m_data;
	CURL* m_curl;
	struct curl_slist *m_headerlist;
	static const std::string m_uri_sandbox;
	static const std::string m_uri_live;
	static const std::string m_auth_content;
};
const string paypal::m_uri_sandbox = "https://api.sandbox.paypal.com/v1/";
const string paypal::m_uri_live = "https://api.paypal.com/v1/";
const string paypal::m_auth_content = "grant_type=client_credentials";


#endif	/* PAYPAL_HPP */

