
#include <stdio.h>
#include "pgen.h"
#include "address.h"
#include "packet.h"
#include "mytypes.h"
#include "netutil.h"

#include "debug.h"


#define PACKET_MINLEN 14



bool pgen_unknown::IPaddris(ipaddr addr){
	if(!isIP) return false;
	printf("ipaddr is %s ", addr.c_str());
	summary();
	return (addr==IP.src || addr==IP.dst);
}
bool pgen_unknown::MACaddris(macaddr addr){
	if(!isETH) return false;
	printf("macaddr is %s ", addr.c_str());
	summary();
	return (addr==ETH.src || addr==ETH.dst);
}
bool pgen_unknown::TCPportis(unsigned short port){
	if(!isTCP) return false;
	printf("tcp port is %d ", port);
	summary();
	return (port==TCP.src || port==TCP.dst);	
}
bool pgen_unknown::UDPportis(unsigned short port){
	if(!isUDP) return false;
	printf("udp port is %d ", port);
	summary();
	return (port==UDP.src || port==UDP.dst);	
}





pgen_unknown::pgen_unknown(){
	clear();
}


pgen_unknown::pgen_unknown(const bit8* packet, int len){
	clear();
	cast(packet, len);
}


void pgen_unknown::clear(){
	ETH.src = 0;
	ETH.dst = 0;
	IP.src = 0;
	IP.dst = 0;
	TCP.src = 0;
	TCP.dst = 0;
	UDP.src = 0;
	UDP.dst = 0;
	isETH = false;
	isARP = false;
	isIP  = false;
	isICMP= false;
	isTCP = false;
	isUDP = false;
}





void pgen_unknown::summary(){
	printf("unknown(packet=[");
	if(isTCP) printf("TCP|");
	if(isUDP) printf("UDP|");
	if(isICMP) printf("ICMP|");
	if(isIP) printf("IP|");
	if(isARP) printf("ARP|");
	if(isETH) printf("ETH]  ");


	if(isTCP)			
		printf("%s:%d > %s:%d", IP.src.c_str(), TCP.src, IP.dst.c_str(), TCP.dst);
	else if(isUDP)	
		printf("%s:%d > %s:%d", IP.src.c_str(), UDP.src, IP.dst.c_str(), UDP.dst);
	else if(isICMP)	
		printf("%s > %s", IP.src.c_str(), IP.dst.c_str());
	else if(isIP)		
		printf("%s > %s", IP.src.c_str(), IP.dst.c_str()); 
	else if(isARP)	
		printf("%s > %s", ETH.src.c_str(), ETH.dst.c_str()); 
	else if(isETH)	
		printf("%s > %s", ETH.src.c_str(), ETH.dst.c_str());
	else			
		printf("no support");
	printf(" len=%d\n", len);
}


bool pgen_unknown::cast(const bit8* packet, int len){
	clear();
	if(!(14 < len && len < PGEN_MAX_PACKET_LEN)){
		fprintf(stderr, "recv packet length is not support (len=%d)\n", len);
		return false;
	}
	this->len = len;

	struct MYETH*  eth;
	struct MYARP*  arp;
	struct MYIP*   ip;
	struct MYICMP* icmp;
	struct MYTCP*  tcp;
	struct MYUDP*  udp;
		
	const bit8* p = packet;
	isETH = true;
	eth = (struct MYETH*)p;
	p += sizeof(struct MYETH);
	ETH.src.setmacbyarry(eth->ether_shost);
	ETH.dst.setmacbyarry(eth->ether_dhost);

	if(ntohs(eth->ether_type) == MT_ETHERTYPE_IP){
		isIP = true;
		ip = (struct MYIP*)p;
		p += sizeof(struct MYIP);
		IP.src._addr = ip->saddr;
		IP.dst._addr = ip->daddr;

		if(ip->protocol == MT_IPPROTO_ICMP){
			isICMP = true;
			icmp = (struct MYICMP*)p;
			p += sizeof(struct MYICMP);
		}
		else if(ip->protocol == MT_IPPROTO_TCP){
			isTCP = true;
			tcp = (struct MYTCP*)p;
			p += sizeof(struct MYTCP);
			TCP.src = ntohs(tcp->source);
			TCP.dst = ntohs(tcp->dest);
		}
		else if(ip->protocol == MT_IPPROTO_UDP){
			isUDP = true;
			udp = (struct MYUDP*)p;
			p += sizeof(struct MYUDP);
			UDP.src = ntohs(udp->source);
			UDP.dst = ntohs(udp->dest);
		}
		else{
			//fprintf(stderr, "unknown L4 protocol 0x%04x\n", ip->protocol);
			return false;
		}
	}
	
	else if(ntohs(eth->ether_type) == MT_ETHERTYPE_ARP){
		isARP = true;
	}
	else{
		//fprintf(stderr, "unknown L3 protocol 0x%04x\n", ntohs(eth->ether_type));
		return false;
	}
	
	return true;
}

