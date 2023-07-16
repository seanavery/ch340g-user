cdef extern from "ch340g.h":
    cdef cppclass CH340G:
        int init()
        int init_usb()
        int handshake()
        int set_baud()
        int up()
        int bulk_write(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout)
        int bulk_read(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout)

cdef class PyCH340G:
    cdef CH340G* ch340g

    def __cinit__(self):
        self.ch340g = new CH340G()

    def __dealloc__(self):
        del self.ch340g

    def init(self):
        return self.ch340g.init()

    def init_usb(self):
        return self.ch340g.init_usb()

    def handshake(self):
        return self.ch340g.handshake()

    def set_baud(self):
        return self.ch340g.set_baud()

    def up(self):
        return self.ch340g.up()

    def bulk_write(self, endpoint, data, length, timeout):
        cdef unsigned char* data_ptr = <unsigned char*> data
        return self.ch340g.bulk_write(endpoint, data_ptr, length, timeout)

    def bulk_read(self, endpoint, length, timeout):
        cdef unsigned char* data = <unsigned char*> malloc(length)
        cdef int transferred = self.ch340g.bulk_read(endpoint, data, length, timeout)
        cdef bytes result = bytes(data[:transferred])
        free(data)
        return result