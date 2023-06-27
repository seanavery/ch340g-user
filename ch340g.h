#include <libusb-1.0/libusb.h>

#define VENDOR 0x1a86
#define PRODUCT 0x7523
#define INTERFACE 0
#define BAUDRATE 115200

#define CTRL_IN (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CTRL_OUT (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)
#define EP_DATA_OUT (0x2|LIBUSB_ENDPOINT_OUT)
uint8_t dtr = 0;
uint8_t rts = 0;


// 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter
// VENDOR: 6790; PRODUCT: 29987
namespace driver {
class CH340G {
    private:
        libusb_context *ctx = NULL;
        libusb_device_handle *dev_handle;
    
    public:
        // USB driver
        bool connected;
        int init();
        int init_usb();
        int handshake();
        int set_baud();
        int up();
        int bulk_write(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout);
        int bulk_read(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout);

};
}