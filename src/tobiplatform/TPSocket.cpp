/*
    Copyright (C) 2009-2011  EPFL (Ecole Polytechnique Fédérale de Lausanne)
    Michele Tavella <michele.tavella@epfl.ch>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TPSOCKET_CPP 
#define TPSOCKET_CPP 

#include "TPSocket.hpp" 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

TPHost::TPHost(void) {
	memset(this->address, 0, TPHost::AddressSize);
	this->port = 0;
}

TPSocket::TPSocket(int type, size_t bsize) {
	this->_type = type;
	this->_bsize = bsize;
	this->_mc = 256;
	this->_buffer = NULL;
}

TPSocket::~TPSocket(void) {
}

void TPSocket::Init(void) {
	this->_fd = 0;
	this->_mc = 0;
	this->_bsizemax = 0;
	
	this->Free();
	this->_buffer = malloc(this->_bsize);
	memset(this->_buffer, 0, this->_bsize);
	
	memset(&(this->_address), 0, sizeof(this->_address));
	memset(&(this->_results), 0, sizeof(this->_results));
	memset(&(this->_endpoint), 0, sizeof(this->_endpoint));

	this->_bsizemax = 0;
}
		
void TPSocket::Free(void) {
	if(this->_buffer == NULL)
		return;
	free(this->_buffer);
	this->_buffer = NULL;
}

bool TPSocket::GetLocal(void) {
	const char* status = NULL;
	struct sockaddr addr;
	int addrlen = sizeof(addr);

	getsockname(this->_fd, 
			(struct sockaddr*)&addr, (socklen_t*)&addrlen);
	struct sockaddr_in *addr_ptr = (struct sockaddr_in*)&addr;

	this->local.port = ntohs(addr_ptr->sin_port);
	status = inet_ntop(AF_INET, 
			&(addr_ptr->sin_addr.s_addr), this->local.address, (socklen_t)addrlen);

	return(status != NULL);
}

bool TPSocket::GetRemote(void) {
	const char* status = NULL;
	struct sockaddr addr;
	int addrlen = sizeof(addr);
	
	getpeername(this->_fd, 
			(struct sockaddr*)&addr, (socklen_t*)&addrlen);
	struct sockaddr_in *addr_ptr = (struct sockaddr_in*)&addr;
	
	this->remote.port = ntohs(addr_ptr->sin_port);
	status = inet_ntop(AF_INET, &(addr_ptr->sin_addr.s_addr),
			this->remote.address, (socklen_t)addrlen);

	return(status != NULL);
}
		
void TPSocket::GetMaxBSize(void) {
	socklen_t optlen = sizeof(this->_bsizemax);
	if(getsockopt(this->_fd, SOL_SOCKET, SO_SNDBUF, &this->_bsizemax, &optlen) < 0)
		this->_bsizemax = 0;
}

bool TPSocket::Open(bool asserver) {
	switch(this->_type) {
		case TPSocket::TCP:
			this->_results.ai_socktype = SOCK_STREAM;
			break;
		case TPSocket::UDP:
			this->_results.ai_socktype = SOCK_DGRAM;
			break;
		default:
			return false;
	}
	if(asserver == true)
		this->_results.ai_flags = AI_PASSIVE;
	this->_results.ai_family = AF_UNSPEC;
	return true;
}

bool TPSocket::Close(void) {
	return(close(this->_fd) == 0);
}
		
bool TPSocket::Bind(const std::string& port) {
	int retopt = 0;
	int bndret = 0;
	struct addrinfo *ai; 
	int opt = 1;

	if(getaddrinfo(NULL, port.c_str(), &(this->_results), &ai) != 0)
		return -1;

	for(this->_info = ai; this->_info != NULL; 
			this->_info = this->_info->ai_next) {
		this->_fd = socket(this->_info->ai_family, 
				this->_info->ai_socktype,
				this->_info->ai_protocol);
		if(this->_fd == -1) 
			continue;

		if(this->_type == TPSocket::TCP) {
			retopt = setsockopt(this->_fd, 
					SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
			if(retopt == -1) 
				return false;
		}

		bndret = bind(this->_fd, this->_info->ai_addr, this->_info->ai_addrlen);
		if(bndret == -1) {
			close(this->_fd);
			continue;
		}
		break;
	}
	freeaddrinfo(ai);
	
	this->GetLocal();

	return bndret;
}

bool TPSocket::Listen(void) {
	return(listen(this->_fd, this->_mc) == 0);
}
		
int TPSocket::Accept(TPSocket* endpoint) {
	if(endpoint->_type != this->_type) 
		return -3;

	unsigned int addrlen = sizeof(endpoint->_address);
	endpoint->_fd = accept(this->_fd, (struct sockaddr*)&this->_endpoint,
			&addrlen);

	// Fill local and remote host structures
	this->GetLocal();
	this->GetRemote();
	//tr_gethost_remote(endpoint, &(endpoint->remote));
	//tr_getmaxbsize(endpoint);
	
	return endpoint->_fd;
}

#endif
