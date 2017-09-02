
#include <pgen/io.h>

uint8_t packet[] = {
#if 0
  /* arp packet */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x06, 0x00, 0x01,
  0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
  0x00, 0x00,
#else
  /* ethernet header */
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x82, 0xb8, 0xe7, 0x8c, 0xae, 0xd9,
  0x08, 0x00,

  /* ipv4 header */
  0x45,
  0x00,                         // ToS
  0x00, 0x1c,                   // totlen (20+8=28=0x1c)
  0x00, 0x00,                   // id
  0x00, 0x00,                   // fragoff
  0x40,                         // ttl
  0x01,                         // protocol
  0x00, 0x00,                   // checksum
  0xc0, 0xa8, 0x00, 0x01,       // src
  0xc0, 0xa8, 0x02, 0x01,       // dst

  /* data */
  0x6c, 0x73, 0x6e, 0x61, 0x64, 0x6b, 0x76, 0x65, // slankdev
#endif
};

int main(int argc, char** argv)
{
  const char* FILENAME = "out.pcapng";
  pgen::pcapng_stream pcap(FILENAME, pgen::open_mode::pcapng_write);
  pcap.send(packet, sizeof(packet));
}

