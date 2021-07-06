#pragma once
typedef unsigned char bit8_t;
typedef unsigned short bit16_t;
typedef unsigned long bit32_t;
typedef unsigned long long bit64_t;

/*
    이더넷 헤더
*/

#define ETH_ADDR_LEN 6
#define ETH_HDR_LEN 14

typedef struct ethernet_header { 
    bit8_t eth_dst_mac[ETH_ADDR_LEN]; // 도착지 맥주소
    bit8_t eth_src_mac[ETH_ADDR_LEN]; // 출발지 맥주소
    bit16_t eth_type; // 패킷 타입
}eth_hdr;

/*
    IP 헤더
*/
#define IP4_ADDR_LEN 4
#define IP6_ADDR_LEN 8

typedef struct ipv4_header { 
#if __BYTE_ORDER == __LITTLE_ENDIAN // 리틀엔디안
    bit8_t ip4_hdrlen : 4; // 헤더 길이
    bit8_t ip4_ver : 4; // 버전
#elif __BYTE_ORDER == __BIG_ENDIAN // 빅엔디안
    bit8_t ip4_ver : 4; // 버전
    bit8_t ip4_hdrlen : 4; // 헤더 길이
#endif
    bit8_t ip4_tos; // 서비스 타입
    bit16_t ip4_tot_len; // 전체 길이
    bit16_t ip4_id; // 확인 숫자
    bit16_t ip4_frag_off; // 플래그와 분할 오프셋
    bit8_t ip4_ttl; // 생존 타임
    bit8_t ip4_protocol; // 프로토콜 타입
    bit16_t ip4_checksum; // 체크섬
    bit8_t ip4_src_ip[IP4_ADDR_LEN]; // 출발지 ip
    bit8_t ip4_dst_ip[IP4_ADDR_LEN]; // 도착지 ip
}ip4_hdr;

typedef struct ipv6_header {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    bit8_t ip6_tclass; // 우선순위
    bit8_t ip6_ver : 4; // 버전
#elif __BYTE_ORDER == __BIG_ENDIAN
    bit8_t ip6_ver : 4; // 버전
    bit8_t ip6_tclass; // 우선순위
#endif
    bit32_t ip6_flow_lbl : 20; // 흐름 처리
    bit16_t ip6_pay_len; // 페이로드 길이
    bit8_t ip6_next; // 다음 헤더
    bit8_t ip6_hop_limit; // ipv6 TTL
    bit16_t ip6_src_ip[IP6_ADDR_LEN]; // 출발지 ip6
    bit16_t ip6_dst_ip[IP6_ADDR_LEN]; // 도착지 ip6
}ip6_hdr;

/*
    ARP 헤더
*/

#define ARP_MAC_LEN 6
#define ARP_IP_LEN 4

typedef struct arp_header {
    bit16_t arp_hard_type; // 하드웨어 타입
    bit16_t arp_protocol; // 프로토콜
    bit8_t arp_addr_len; // MAC 주소 길이
    bit8_t arp_protocol_len; // 프로토콜 길이
    bit16_t arp_opcode; // 명령코드
    bit8_t arp_src_mac[ARP_MAC_LEN]; // 출발지 MAC
    bit8_t arp_src_ip[ARP_IP_LEN]; // 출발지 IP
    bit8_t arp_dst_mac[ARP_MAC_LEN]; // 도착지 MAC
    bit8_t arp_dst_ip[ARP_IP_LEN]; // 도착지 IP
}arp_hdr;

/*
    ICMP, IGMP 헤더
*/

typedef struct icmp_header { // TODO
    bit8_t icmp_type; // ICMP 타입
    bit8_t icmp_code; // 코드
    bit16_t icmp_checksum; // 체크섬
    bit8_t icmp_msg[4]; // 예약(순서번호, 인터넷 주소 등)
    bit32_t icmp_data; // 데이터
}icmphdr;

typedef struct igmp_header { // TODO
    bit8_t igmp_type;
    bit8_t igmp_code;
    bit16_t igmp_checksum;
    bit8_t igmp_group_ip[IP4_ADDR_LEN];
}igmp_hdr;


/*
    TCP, UDP 헤더
*/

typedef struct tcp_header { 
    bit16_t tcp_src_port; // 출발지 포트
    bit16_t tcp_dst_port; // 도착지 포트
    bit32_t tcp_seq; // 순서 번호
    bit32_t tcp_ack; // 승인 번호
#if __BYTE_ORDER == __LITTLE_ENDIAN
    bit8_t tcp_rsvd : 6; // 사용 하지 않음
    bit8_t tcp_hlen : 4; // 데이터 오프셋
#elif __BYTE_ORDER == __BIG_ENDIAN
    bit8_t tcp_hlen : 4; // 데이터 오프셋
    bit8_t tcp_rsvd : 6; // 사용 하지 않음
#endif
    bit8_t tcp_flags : 6; // 2비트 예비 + 플래그
    #define TCP_FIN 0x01 // 0b00000001
    #define TCP_SYN 0X02 // 0b00000010
    #define TCP_RST 0X04 // 0b00000100
    #define TCP_PSH 0X08 // 0b00001000
    #define TCP_ACK 0X10 // 0b00010000
    #define TCP_URG 0X20 // 0b00100000
    bit16_t tcp_window; // 윈도우 사이즈
    bit16_t tcp_checksum; // TCP 체크섬
    bit16_t tcp_urgent; // 긴급 포인터
}tcp_hdr;

typedef struct udp_header { 
    bit16_t udp_src_port; // 출발지 포트
    bit16_t udp_dst_port; // 도착지 포트
    bit16_t udp_len; // 길이
    bit16_t udp_checksum; // UDP 체크섬
}udp_hdr;