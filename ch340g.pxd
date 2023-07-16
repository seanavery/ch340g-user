cdef extern from "ch340g.h":
    cdef cppclass CH340G:
        CH340G() except +
        int init()
        int init_usb()
        int handshake()
        int set_baud()
        int up()
        int bulk_write(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout)
        int bulk_read(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout)

cdef extern from "ch340g.cpp":
    pass