#include <libusb-1.0/libusb.h>
#include <vector>
#include <string>

#define BAUDRATE 115200

#define CTRL_IN (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CTRL_OUT (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)
#define EP_DATA_OUT (0x2 | LIBUSB_ENDPOINT_OUT)

class CH340 {
    private:
        uint8_t dtr = 0;
        uint8_t rts = 0;
        libusb_context *ctx = NULL;
        libusb_device_handle *dev_handle = NULL;
    
    public:
        // USB driver
        bool connected;
        int init(int vendor, int product, int baudrate=BAUDRATE);
        int init_usb(int vendor, int product);
        int handshake();
        int set_baud(int baudrate);
        int up();
        int bulk_write(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout);
        int bulk_read(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout);

};
