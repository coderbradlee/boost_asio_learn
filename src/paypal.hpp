#ifndef PAYPAL_HPP
#define	PAYPAL_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
//#define DEBUG

class paypal
{
public:
	paypal(const std::string& client_id, const std::string& client_secret) :m_client_id(client_id), m_client_secret(client_secret)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);
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
	void payments_payment(const std::string& content)
	{
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, payments_payment_callback);
		curl(m_uri_sandbox + "payments/payment?"+content, "GET", content);
		
	}
	void payments_payment_post(const std::string& content)
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
	}
	
protected:	
	static size_t identity_openidconnect_userinfo_get_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			cout << __LINE__ << endl;
			return ((paypal*)thisPtr)->identity_openidconnect_userinfo_get_write_data(buffer, size, nmemb);
		}

		else
		{
			cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t identity_openidconnect_userinfo_get_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.append(buffer, size*nmemb);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		cout << __LINE__ << ":" << m_data << endl;
		
		return result;
	}

	static size_t vault_credit_cards_get_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			cout << __LINE__ << endl;
			return ((paypal*)thisPtr)->vault_credit_cards_get_write_data(buffer, size, nmemb);
		}

		else
		{
			cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t vault_credit_cards_get_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.append(buffer, size*nmemb);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		cout << __LINE__ << ":" << m_data << endl;
		
		return result;
	}

	static size_t payments_billing_plans_get_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			cout << __LINE__ << endl;
			return ((paypal*)thisPtr)->payments_billing_plans_get_write_data(buffer, size, nmemb);
		}

		else
		{
			cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t payments_billing_plans_get_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.append(buffer, size*nmemb);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		cout << __LINE__ << ":" << m_data << endl;
		//ptree pt;
		//stringstream stream;
		//stream << m_data;
		//read_json(stream, pt);

		//string scope = pt.get<string>("scope");
		//string nonce = pt.get<string>("nonce");
		//m_access_token = pt.get<string>("access_token");
		//m_token_type = pt.get<string>("token_type");
		//string app_id = pt.get<string>("app_id");
		//size_t expires_in = pt.get<size_t>("expires_in");
		////#ifdef DEBUG
		//cout << scope << endl;
		//cout << nonce << endl;
		//cout << m_access_token << endl;
		//cout << m_token_type << endl;
		//cout << app_id << endl;
		//cout << expires_in << endl;

		//#endif
		return result;
	}

	static size_t payments_payment_post_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			cout << __LINE__ << endl;
			return ((paypal*)thisPtr)->payments_payment_post_write_data(buffer, size, nmemb);
		}

		else
		{
			cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t payments_payment_post_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.append(buffer, size*nmemb);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		cout << __LINE__ << ":" << m_data << endl;
		//ptree pt;
		//stringstream stream;
		//stream << m_data;
		//read_json(stream, pt);

		//string scope = pt.get<string>("scope");
		//string nonce = pt.get<string>("nonce");
		//m_access_token = pt.get<string>("access_token");
		//m_token_type = pt.get<string>("token_type");
		//string app_id = pt.get<string>("app_id");
		//size_t expires_in = pt.get<size_t>("expires_in");
		////#ifdef DEBUG
		//cout << scope << endl;
		//cout << nonce << endl;
		//cout << m_access_token << endl;
		//cout << m_token_type << endl;
		//cout << app_id << endl;
		//cout << expires_in << endl;

		//#endif
		return result;
	}

	static size_t payments_payment_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			//cout << __LINE__ << endl;
			return ((paypal*)thisPtr)->payments_payment_write_data(buffer, size, nmemb);
		}

		else
		{
			//cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t payments_payment_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.append(buffer, size*nmemb);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		cout << __LINE__ << ":" << m_data << endl;
		//ptree pt;
		//stringstream stream;
		//stream << m_data;
		//read_json(stream, pt);

		//string scope = pt.get<string>("scope");
		//string nonce = pt.get<string>("nonce");
		//m_access_token = pt.get<string>("access_token");
		//m_token_type = pt.get<string>("token_type");
		//string app_id = pt.get<string>("app_id");
		//size_t expires_in = pt.get<size_t>("expires_in");
		////#ifdef DEBUG
		//cout << scope << endl;
		//cout << nonce << endl;
		//cout << m_access_token << endl;
		//cout << m_token_type << endl;
		//cout << app_id << endl;
		//cout << expires_in << endl;

		//#endif
		return result;
	}

	void curl(const std::string& uri, const std::string& method = "GET", const std::string& content="", bool auth=false)
	{
		
		set_url(uri);
		if (auth)
		{
			cout << __LINE__ << ":" << uri << endl;
			add_header("Accept: application/json");
			add_header("Accept-Language: en_US");
			
			string userpass = m_client_id + ":" + m_client_secret;
			curl_easy_setopt(m_curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);
			curl_easy_setopt(m_curl, CURLOPT_USERPWD, userpass.c_str());
			
			curl_easy_setopt(m_curl, CURLOPT_SSH_KNOWNHOSTS, "/root/.ssh/known_hosts");
		
			curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, auth_request_callback);

			curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)29);
			curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);

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
		curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, content.c_str());
		curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_headerlist);
		curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());
		
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
		try
		{
			
			if (buffer != 0)
			{
				m_data.append(buffer, size*nmemb);
				result = size*nmemb;
			}
			/*cout <<__LINE__<<":"<<  buffer << endl;*/
			cout << __LINE__ << ":" << m_data << endl;
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
		}
		catch (std::exception& e)
		{
			cout << e.what() << endl;
		}
		//finally()
		{
			return result;
		}
		
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
class taxfile
{
	// The filename of the uploaded file
private:
	std::string filename;

	// The size of the uploaded file
	int size;

	// The ressource to the file
	std::ofstream fp;
	//std::mutex conLock_;
	/**
	* Constructs a new File Upload
	* @param $filename : the name of the file
	* @param $size : the size of the file
	*/
	/*public function __construct($filename, $size) {
	$this->setFilename($filename);
	$this->setSize($size);

	$this->fp = fopen('/tmp/'.$filename, 'w+');
	}*/
public:
	taxfile(std::string filename, int size, bool bin = false)
	{
		this->setFilename(filename);
		this->setSize(size);
		/*if (bin)
		{
		this->fp = std::ofstream(filename, std::ios::app);
		}
		else
		{
		this->fp = std::ofstream(filename, std::ios::app | std::ios::binary);
		}*/
		if (bin)
		{
			this->fp = std::ofstream(filename, std::ios::binary);
		}
		else
		{
			this->fp = std::ofstream(filename);
		}
	}
	/**
	* Updates the name of the file
	* @param $filename : the new name
	*/
	/*public function setFilename($filename) {
	$this->filename = $filename;
	}*/
	void setFilename(std::string filename)
	{
		this->filename = filename;
	}
	/**
	* Updates the size of the file
	* @param $size : the new size of the file
	*/
	/*public function setSize($size) {
	$this->size = $size;
	}*/
	void setSize(int size)
	{
		this->size = size;
	}
	/**
	* Adds data to the file
	* @param $data : the data to add to the file
	*/
	/*public function addData($data) {
	fwrite($this->fp, $data);
	}*/
	void addData(std::string data)
	{

		this->fp.write(data.c_str(), data.length());
		//std::cout << data << std::endl;
	}
	/**
	* Close the file
	*/
	/*public function close() {
	fclose($this->fp);
	}*/
	~taxfile()
	{
		//std::unique_lock<std::mutex> locker(conLock_);
		this->fp.close();
	}
};

bool create_dir(std::string dir)
{
	try
	{
		return boost::filesystem::create_directories(dir);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	catch (...)
	{
		std::cout << "unknown error" << std::endl;
		return false;
	}
}

class download_tax_from_taxrate
{
public:
	download_tax_from_taxrate(const std::string& filename, const std::string& save_path) :path(save_path)
	{
		m_taxfile = boost::shared_ptr<taxfile>(new taxfile(path+"/"+filename, 22));
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);

#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
#endif
		
		curl(m_download_url, "GET", filename, true);
	}
	virtual ~download_tax_from_taxrate()
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();	
	}
	
protected:	
	static size_t download_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			//cout << __LINE__ << endl;
			return ((download_tax_from_taxrate*)thisPtr)->download_write_data(buffer, size, nmemb);
		}

		else
		{
			//cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t download_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			m_data.clear();
			m_data.append(buffer, size*nmemb);
			m_taxfile->addData(m_data);
			result = size*nmemb;
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		//cout << __LINE__ << ":" << m_data << endl;
		
		return result;
	}

	void curl(const std::string& uri, const std::string& method = "GET", const std::string& filename="", bool auth=false)
	{		
		set_url(uri+filename);		
		//cout << __LINE__ << ":" << uri << endl;
		
#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);
#endif
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, download_callback);
		curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());
		cout << __LINE__ << "request:"<<filename << endl;
		on_request();
		
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
	
protected:	
	std::string m_data;
	CURL* m_curl;
	static const std::string m_download_url;
	boost::shared_ptr<taxfile> m_taxfile;
	std::string path;
};
const string download_tax_from_taxrate::m_download_url = "http://taxrates.csv.s3.amazonaws.com/";

#endif	/* PAYPAL_HPP */

