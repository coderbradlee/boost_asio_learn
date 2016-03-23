#ifndef TEST_HPP
#define	TEST_HPP
#include "serverResource.hpp"
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
#include <bitset>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
void rotate(std::vector<std::vector<string>>& vec)
{
	for (int layer = 0; layer < 6 / 2; ++layer)
	{
		int first = layer;
		int last = 6 - 1 - layer;
		for (int i = first; i < last; ++i)
		{
			/*int offset = i - first;
			string top = vec[first][i];
			vec[first][i] = vec[last - offset][first];
			vec[last - offset][first] = vec[last][last - offset];
			vec[last][last - offset] = vec[i][last];
			vec[i][last] = top;*/
			string top = vec[first][i];
			vec[first][i] = vec[last - i][first];
			vec[last - i][first] = vec[last][last - i];
			vec[last][last - i] = vec[i][last];
			vec[i][last] = top;
		}
	}
}
void print(std::vector<std::vector<string>> vec)
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}
void test()
{
	std::vector<std::vector<string>> vec(6);
	for (int i = 0; i < 6; ++i)
		vec[i].resize(6);
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
			vec[i][j] = boost::lexical_cast<string>(i)+boost::lexical_cast<string>(j);
	}
	print(vec);
	rotate(vec);
	cout << "==================================" << endl;
	print(vec);

	

}

class tree
{	
public:
	tree(int data) :data(data), left(nullptr), right(nullptr)
	{}
	int data;
	boost::shared_ptr<tree> left;
	boost::shared_ptr<tree> right;
};
bool covers(boost::shared_ptr<tree> root, boost::shared_ptr<tree> p)
{
	if (root == nullptr) return false;
	if (root == p) return true;
	return covers(root->left, p) || covers(root->right, p);
}
boost::shared_ptr<tree> common_ancestor_helper(boost::shared_ptr<tree> root, boost::shared_ptr<tree> p, boost::shared_ptr<tree> q)
{
	if (root == nullptr) return nullptr;
	if (root == p || root == q) return root;
	bool p_in_left = covers(root->left, p);
	bool q_in_left = covers(root->left, q);

	if (p_in_left != q_in_left) return root;
	else
	{
		boost::shared_ptr<tree> child = p_in_left ? root->left : root->right;
		return common_ancestor_helper(child, p, q);
	}
}
boost::shared_ptr<tree> common_ancestor(boost::shared_ptr<tree> root, boost::shared_ptr<tree> p, boost::shared_ptr<tree> q)
{
	if (!covers(root, p) || !covers(root, q))
		return nullptr;
	return common_ancestor_helper(root, p, q);
}
void mid_travel(boost::shared_ptr<tree> root)
{
	if (root == nullptr)
	{
		cout << "root is nullptr" << endl;
	}
	else
	{
		mid_travel(root->left);
		cout << root->data << endl;
		mid_travel(root->right);
	}
}
void test_tree()
{
	//ÖÐÐò±éÀúÎª£º123654
	boost::shared_ptr<tree> node1 = boost::shared_ptr<tree>(new tree(1));
	boost::shared_ptr<tree> node3 = boost::shared_ptr<tree>(new tree(3));
	boost::shared_ptr<tree> node4 = boost::shared_ptr<tree>(new tree(4));
	
	boost::shared_ptr<tree> node2 = boost::shared_ptr<tree>(new tree(2));
	node2->left = node1;
	node2->right = node3;
	boost::shared_ptr<tree> node6 = boost::shared_ptr<tree>(new tree(6));
	node6->left = node2;
	boost::shared_ptr<tree> node5 = boost::shared_ptr<tree>(new tree(5));
	node6->right = node5;
	node5->right = node4;

	mid_travel(node6);
	boost::shared_ptr<tree> test1=common_ancestor(node6, node1, node3);
	cout << test1->data << endl;
	boost::shared_ptr<tree> test2=common_ancestor(node6, node3, node4);
	cout << test2->data << endl;
	boost::shared_ptr<tree> test3 = common_ancestor(node6, node4, node5);
	cout << test3->data << endl;
	boost::shared_ptr<tree> test4 = common_ancestor(node6, node2, node3);
	cout << test4->data << endl;
}
int length(int x)
{
	int ret = 0;
	while(x > 0)
	{
		ret++;
		x=x >> 1;
		//cout << __LINE__ << ":"<<x << endl;
	}
	return ret;
}
void merge_bit(int n, int m, int j, int i)
{
	int space = j - i + 1;
	int len = length(m);
	/*int min = len <space ? len : space;
	cout << "len:" << len << endl;
	cout << "min:" << min << endl;*/
	int mask = 0;
	for (int i = 0; i < space; ++i)
		mask += (i +1)* 2;
	n &= ~mask;
	cout << "n:" << hex << n << endl;
	int temp = m << (j-len+1);
	cout << "temp:" << hex << temp << endl;
	cout << hex << n + temp << endl;
}
int update_bit(int n, int m, int i, int j)
{
	int all = ~0;
	int left = all << (j + 1);
	int right = ((1 << i) - 1);
	int mask = left | right;
	int clear = n&mask;
	int shift = m << i;
	return clear | shift;
}
void test_merge_bit()
{
	//01101100 010 3 1 结果输出100
	//merge_bit(108, 2, 3, 1);
	merge_bit(0x400, 0x13, 6, 2);
	cout << hex << update_bit(0x400, 0x13, 2, 6) << endl;
}
void test_bit_set()
{
	auto str1 = "0011";
	auto str2 = "0110";
	bitset<10> one(str1);
	bitset<10> two(str2);
	auto three = one&two;
	cout << three << endl;
	three <<= 4;
	cout << three << endl;
}
int find_missing(std::vector<bitset<8>>& vec,int column)
{
	if(column>=8)
	{
		return 0;
	}
	std::vector<bitset<8>> one_num;
	std::vector<bitset<8>> zero_num;
	for(auto & item:vec)
	{
		if(item[column]==0)
			zero_num.push_back(item);
		else
			one_num.push_back(item);
	}
	if(zero_num.size()<=one_num.size())
	{
		int v=find_missing(zero_num,column+1);
		return (v<<1)|0;
	}	
	else
	{
		int v=find_missing(one_num,column+1);
		return (v<<1)|1;
	}

}
int find_missing(std::vector<bitset<8>>& vec)
{
	return find_missing(vec,0);
}

void test_lack_bit()
{
	std::vector<bitset<8>> vec;
	for (int i = 0; i < 16; ++i)
	{
		bitset<8> b(i);
		//cout << b << endl;
		vec.push_back(b);
	}
	for(auto i= vec.begin(); i != vec.end(); ++i )
	{
		if(*i==10)
			vec.erase(i);
	}
	for(auto &i: vec)
	{
		cout<<i<<endl;
	}
	int i=find_missing(vec);
	cout << i << " is missing" << endl;
}

class caller
{
public:
	void set_rank(int rank)
	{
		m_rank=rank;
	}
	int get_rank()
	{
		return m_rank;
	}
private:
	int m_rank;
};
class employee
{
public:
	virtual bool handle_call(boost::shared_ptr<caller> call)=0;
	
protected:
	string m_frist_name;
	string m_last_name;
	string m_age;
	int m_rank;
	boost::shared_ptr<caller> m_caller;
};
class respondent:public employee
{
public:
	//respondent():m_rank(0){}
	respondent(){m_rank=0;}
	bool handle_call(boost::shared_ptr<caller> call)
	{
		cout<<"respondent received call"<<endl;
		call->set_rank(m_rank+1);//测试不能处理
		return false;
	}
};
class manager:public employee
{
	public:
	manager(){m_rank=2;}
	bool handle_call(boost::shared_ptr<caller> call)
	{
		cout<<"manager received call"<<endl;
		call->set_rank(m_rank+1);//测试不能处理
		return false;
	}
};
class director:public employee
{
	public:
	director(){m_rank=1;}
	bool handle_call(boost::shared_ptr<caller> call)
	{
		cout<<"director received call"<<endl;
		call->set_rank(m_rank+1);//测试不能处理
		return false;
	}
};

class call_center:public boost::enable_shared_from_this<call_center>,boost::noncopyable
{
public:
	call_center()
	{
		for(int i=0;i<m_num_respondents;++i)
		{
			m_respondents.push(boost::shared_ptr<respondent>(new respondent()));
		}
		for(int i=0;i<m_num_managers;++i)
		{
			m_managers.push(boost::shared_ptr<manager>(new manager()));
		}
		for(int i=0;i<m_num_directors;++i)
		{
			m_directors.push(boost::shared_ptr<director>(new director()));
		}
	}
	static boost::shared_ptr<call_center> get_instance()
	{
		boost::mutex::scoped_lock t(m_mu);
		if (m_ps == nullptr)
		{
			m_ps = boost::shared_ptr<call_center>(new call_center());
		}
		
		return m_ps;
	}
	void dispatch_call()
	{
		cout<<"dispatch_call"<<endl;
		while(!m_callers.empty())
		{
			boost::shared_ptr<caller> c=m_callers.front();
			m_callers.pop();
			if(c->get_rank()==0)
			{
				cout<<"0"<<endl;
				boost::shared_ptr<respondent> r=m_respondents.front();
				m_respondents.pop();
				if(!r->handle_call(c))
				{
					m_callers.push(c);
				}
			}
			else if(c->get_rank()==1)
			{
				boost::shared_ptr<director> d=m_directors.front();
				m_directors.pop();
				if(!d->handle_call(c))
				{
					m_callers.push(c);
				}
			}
			else
			{
				boost::shared_ptr<manager> m=m_managers.front();
				m_managers.pop();
				if(!m->handle_call(c))
				{
					m_callers.push(c);
				}			
			}
		}
	}
	void add_call(boost::shared_ptr<caller> c)
	{
		cout<<"add_call"<<endl;
		m_callers.push(c);
	}
private:
	static boost::mutex m_mu;
	static boost::shared_ptr<call_center> m_ps;
	const int m_levels=3;
	const int m_num_respondents=10;
	const int m_num_managers=4;
	const int m_num_directors=2;
	std::queue<boost::shared_ptr<respondent>> m_respondents;
	std::queue<boost::shared_ptr<manager>> m_managers;
	std::queue<boost::shared_ptr<director>> m_directors;
	std::queue<boost::shared_ptr<caller>> m_callers;
};
boost::shared_ptr<call_center> call_center::m_ps = nullptr;
boost::mutex call_center::m_mu;


class player
{};
class user
{};
class song
{};
class jukebox
{
public:
	jukebox(boost::shared_ptr<player> p,boost::shared_ptr<user> u,std::set<song> s):m_player(p),m_user(u),m_songs(s){}

private:
	boost::shared_ptr<player> m_player;
	boost::shared_ptr<user> m_user;
	std::set<song> m_songs;
	std::map<string,std::set<boost::shared_ptr<song>>> m_play_lists;
};

enum  class vehicle_size
{
	motor,small,large
};
class vehicle
{

};
class level;
class parking_spot
{
public:
	parking_spot(boost::shared_ptr<level> l,int num,vehicle_size v):m_level(l),m_spot_number(num),m_spot_size(v),m_vehicle(nullptr)
	{

	}
	bool is_available()
	{
		return m_vehicle==nullptr;
	}
private:
	boost::shared_ptr<vehicle> m_vehicle;
	vehicle_size m_spot_size;
	int m_spot_number;
	boost::shared_ptr<level> m_level; 
};
class level
{
public:
	level(int flr,int num_spots):m_available_spots(num_spots){}
	int get_available_spots()
	{
		return m_available_spots;
	}
	bool park_vehicle(boost::shared_ptr<vehicle> vec)
	{

	}
	bool park_at_spot(int num,boost::shared_ptr<vehicle> vec)
	{

	}
	void spot_freed()
	{
		m_available_spots++;
	}
private:
	std::std::vector<parking_spot> m_parking_spots;
	int m_available_spots;
	//const int spots_per_row=10;
};
class parking_lot
{
public:
	bool park_vehicle(boost::shared_ptr<vehicle> v)
    {}
private:
    std::vector<level> m_levels;
    const int num_levels=5;

};

#endif

