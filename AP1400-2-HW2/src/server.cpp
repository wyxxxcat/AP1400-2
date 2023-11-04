#include "client.h"
#include "server.h"
#include<bits/stdc++.h>
using MPD = std::map<std::shared_ptr<Client>, double>;
std::vector<std::string> pending_trxs;
void  show_wallets(const  Server& server)
{
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& client: *((MPD*)&server))
		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}
Server::Server()
{
}
std::shared_ptr<Client> Server::add_client(std::string id)
{
	std::string tail = "";
	for(int i = 0;i < 4;i ++)
	{
		size_t r = rand() % 9;
		tail += std::to_string(r);
	}
	for(const auto& it : clients)
	{
		if(it.first->get_id() == id)
		{
			id += tail;
		}
	}
	auto cli = std::make_shared<Client>(id,*this);
	clients[cli] = 5;
	return cli;
}
std::shared_ptr<Client> Server::get_client(std::string id)const
{
	for(const auto& it : clients)
	{
		if(it.first->get_id() == id)
		{
			return it.first;
		}
	}
	return nullptr;
}
double Server::get_wallet(std::string id)const
{
	for(const auto& c : clients)
	{
		if(c.first->get_id() == id)
		{
			return c.second;
		}
	}
	return 0;
}
bool Server::parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value)
{
	std::string pattern = "(\\w+)-(\\w+)-(\\d+\\.\\d+)";
	std::regex r(pattern);
	std::smatch res;
	if(std::regex_match(trx,res,r))
	{
		sender = res.str(1);
		receiver = res.str(2);
		value = std::stod(res.str(3));
		return true;
	}else
	{
		throw std::runtime_error("runtime error");
	}
	return false;
}
bool Server::add_pending_trx(std::string trx, std::string signature)const
{
	std::string receiver,sender;
	double value = 0;
	Server::parse_trx(trx,sender,receiver,value);
	auto receiver_ = get_client(receiver);
	auto sender_ = get_client(sender);
	if(receiver_ == nullptr)
	{
		return false;
	}
	bool ok = crypto::verifySignature(sender_->get_publickey(),trx,signature);
	if(ok && clients.at(sender_) >= value)
	{
		pending_trxs.push_back(trx);
		return true;
	}
	return false;
}
size_t Server::mine()
{
	std::string s{};
	for(const auto& it : pending_trxs)
	{
		s += it;
	}
	size_t nonce = 0;
	bool ok = 0;
	while(!ok)
	{
		for(auto& it : clients)
		{
			nonce = it.first->generate_nonce();
			if(crypto::sha256(s + std::to_string(nonce)).substr(0,10).find("000")
			 != std::string::npos)
			{
				ok = 1;
				for(const auto& it : pending_trxs)
				{
					std::string sender,receiver;
					double value;
					Server::parse_trx(it,sender,receiver,value);
					clients[get_client(sender)] -= value;
					clients[get_client(receiver)] += value;
				}
				pending_trxs.clear();
				return nonce;
			}
		}
	}
	return nonce;
}