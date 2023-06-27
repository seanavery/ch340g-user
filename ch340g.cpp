#include "ch340g.h"
#include <stdio.h>
#include <iostream>

namespace driver {
int CH340G::init() {
    int err;
    
    err = init_usb();
    if (err != 0) {
        printf("error: %d \n", err);
        return err;
    }
    printf("usb interface initialized \n");

    err = handshake();
    if (err != 0) {
        printf("error: %d \n", err);
        return err;
    }
    printf("ch340g initialized \n");

    err = set_baud();
    if (err != 0) {
        printf("error: %d \n", err);
        return err;
    }

    err = up();
    if (err != 0) {
        printf("error: %d \n", err);
        return err;
    }
    printf("ch340g up \n");

    return err;
}

int CH340G::init_usb() {
    int err;

    err = libusb_init(&ctx);
    if (err != 0) {
        return err;
    }

    libusb_device **dev_list = NULL;
    ssize_t num_devices = libusb_get_device_list(ctx, &dev_list);
    if (num_devices < 0) {
        return -1;
    }

    // iterate through num_devices
    for (int i = 0; i < num_devices; i++) {
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(dev_list[i], &desc);
        std::cout << "idVendor: " << desc.idVendor << std::endl;
        std::cout << "idProduct: " << desc.idProduct << std::endl;
        if (desc.idVendor == VENDOR && desc.idProduct == PRODUCT) {
            printf("found product/vendor \n");
            dev_handle = libusb_open_device_with_vid_pid(ctx, VENDOR, PRODUCT);
        }
    }

    if (dev_handle == NULL) {
        printf("could not find MCU \n");
        return -1;
    }
    
    err = libusb_claim_interface(dev_handle, INTERFACE);
    if (err < 0) {
        printf("could not claim interface \n");
        return err;
    }

    return err;
}

int CH340G::handshake() {
  if (dev_handle == NULL) {
    printf("dev_handle not defined \n");
    return -1;
  }

  int err = 0;

  // 1
  err = libusb_control_transfer(dev_handle, CTRL_OUT, 0xa1, 0, 0, NULL, 0, 1000);
  if (err < 0)
  {
    printf("setp 1 failed \n");
    return err;
  }
  // 2
  err = libusb_control_transfer(dev_handle, CTRL_OUT, 0x9a, 0x2518, 0x0050, NULL, 0, 1000);
  if (err < 0)
  {
    printf("step 2 failed \n");
    return err;
  }
  // 3
  err = libusb_control_transfer(dev_handle, CTRL_OUT, 0xa1, 0x501f, 0xd90a, NULL, 0, 1000);
  if (err < 0)
  {
    printf("step 3 failed \n");
    return err;
  }

  return 0;
}

int CH340G::set_baud() {
    static int baud[] = {2400, 0xd901, 0x0038, 4800, 0x6402,
                0x001f, 9600, 0xb202, 0x0013, 19200, 0xd902, 0x000d, 38400,
                            0x6403, 0x000a, 115200, 0xcc03, 0x0008};

    int err = 0;
    for (int i = 0; i < sizeof(baud)/sizeof(int) / 3; i++) {
        if (baud[i * 3] == BAUDRATE) {

            err = libusb_control_transfer(dev_handle, CTRL_OUT, 0x9a, 0x1312, baud[i * 3 + 1], NULL, 0, 1000);
            if (err < 0) {
                printf("could not set baudrate \n");
                return err;
            }

            err = libusb_control_transfer(dev_handle, CTRL_OUT, 0x9a, 0x0f2c, baud[i * 3 + 2], NULL, 0, 1000);
            if (err < 0) {
                printf("could not set baudrate \n");
                return err;
            }
        }
    }
    return err;
}

int CH340G::up() {
    int err = 0;
    err = libusb_control_transfer(dev_handle, CTRL_OUT, 0xa4, ~((dtr ? 1 << 5 : 0) | (rts ? 1 << 6 : 0)), 0, NULL, 0, 1000);
    if (err < 0) {
        printf("first handshake failed \n");
        return err;
    }
    return err;
}

int CH340G::bulk_write(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout) {
    int err = 0;
    
    int transferred = 0;
    err = libusb_bulk_transfer(dev_handle, endpoint, data, length, &transferred, timeout);
    if (err < 0) {
        printf("error during bulk write \n");
        return err;
    }

    printf("transferred %d bytes \n", transferred);
    
    return err;
}

int CH340G::bulk_read(unsigned char endpoint, unsigned char* data, int length, unsigned int timeout) {
    int err = 0;

    int transferred = 0;
    err = libusb_bulk_transfer(dev_handle, endpoint, data, length, &transferred, timeout);
    if (err < 0) {
        printf("error during bulk read \n");
        return err;
    }

    std::cout << "read bytes: " << transferred << std::endl;

    return transferred;
}
}