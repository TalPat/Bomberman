# Insure bins exist in PATH
REQUIREMENTS = conan cmake
VALIDATE := $(foreach exec,$(REQUIREMENTS),\
        $(if $(shell which $(exec)),,$(error "$(exec) not found in PATH")))

TOP := $(dir $(lastword $(MAKEFILE_LIST)))
BUILD_PATH := $(TOP)/build

OS := $(shell uname)

CONAN_PROFILE := $(if ifeq  $(OS) "linux",linux.profile,mac.profile)

all: install

install:
		# && conan install .. --build=missing -s compiler.libcxx=libstdc++11
	@mkdir -p $(BUILD_PATH)
	@cd $(BUILD_PATH) \
		&& conan install .. --build=missing --profile ../$(CONAN_PROFILE) \
		&& cmake .. \
		&& make

run:
	$(BUILD_PATH)/bin/bomberman

clean:
	rm -rf $(BUILD_PATH)

re: clean install

.PHONY: install all check_conan test
