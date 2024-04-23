TARGET ?= arm64
ifeq ($(TARGET),arm64)
	DOCKER = Dockerfile.arm64
else ifeq ($(TARGET),amd64)
	DOCKER = Dockerfile.amd64
else
	DOCKER = Dockerfile.arm64
endif

.PHONY: build install build-docker sync

install: build
	cd build && \
	make install

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

build-docker:
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
