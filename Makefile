TARGET ?= $(shell uname -m)
ifeq ($(TARGET),arm64)
	DOCKER = Dockerfile.arm64
else ifeq ($(TARGET),x86_64)
	DOCKER = Dockerfile.x86
else
	DOCKER = Dockerfile.x86
endif

.PHONY: build install build-x86 build-arm64 bin-arm64

install: build
	cd build && \
	make install

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

build:
	docker build \
	-t lib-ch340-$(TARGET) \
	-f ./etc/$(DOCKER) ./

sync:
	rm -rf ./bin || true
	mkdir -p ./bin
	docker run --name lib-ch340-$(TARGET)-bin lib-ch340-$(TARGET)
	docker cp lib-ch340-$(TARGET)-bin:/usr/local/lib/ ./bin
	docker cp lib-ch340-$(TARGET)-bin:/usr/local/include/ ./bin
	docker stop lib-ch340-$(TARGET)-bin
	docker rm lib-ch340-$(TARGET)-bin
