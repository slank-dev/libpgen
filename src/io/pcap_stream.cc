


#include <pgen2/io/stream.h>
#include <pgen2/types.h>
#include <pgen2/exception.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


namespace pgen {


void pcap_stream::open(const char* name, pgen::open_mode mode) {
    switch (mode) {
        case pgen::open_mode::pcap_write:
            fopen(name, "wb");
            file_header.magic = 0xa1b2c3d4;
            file_header.version_major = 0x0002;
            file_header.version_minor = 0x0004;
            file_header.timezone = 0x0000;
            file_header.sigfigs  = 0x0000;
            file_header.snaplen  = 0x0000ffff;
            file_header.linktype = 0x00000001;
            fwrite(&file_header, sizeof(file_header));
            break;

        case pgen::open_mode::pcap_read:
            fopen(name, "rb");
            fread(&file_header, sizeof(file_header));
            break;

        default:
            throw pgen::exception("pgen::pcap_stream::open: unknown mode \n");
            break;
    }
}



void pcap_stream::close() {
    this->fclose();
}


size_t pcap_stream::send(const void* buf, size_t buflen) {
   
    struct pgen::pcap_packet_headr ph;
    ph.timestamp_sec  = 0;
    ph.timestamp_usec = 0;
    ph.include_len    = buflen;
    ph.original_len   = buflen;

    this->fwrite(&ph, sizeof(ph));
    this->fwrite(buf, buflen);

    return buflen;
}

size_t pcap_stream::recv(void* buf, size_t buflen) {
    
    struct pgen::pcap_packet_headr ph;
    this->fread(&ph, sizeof(ph));
    
    if (buflen < ph.original_len) {
        throw pgen::exception("pgen::pcap_stream::recv: buffer length is too small");
    }

    this->fread(buf, ph.original_len);
    return ph.original_len;
}



bool pcap_stream::eof() const {
    /*
     * FIXME
     * If below's code uncomment out, this function always
     * throw exception. Please help...
     */
    // if (mode() != pgen::open_mode::pcap_read) {
    //     throw pgen::exception("pgen::pcap_stream::flush: mode not support");
    // }

    return this->feof();
}


void pcap_stream::flush() const {
    this->fflush();
}




} /* namespace pgen */
