TARGET=compiler
CXXFLAGS = -std=c++11 -g -Iinclude
GXXFLAGS = -Iinclude
LDFLAGS = -lstdc++
all : dirs bin/parser bin/compiler bin/test_postprocessor tests

.PHONY: dirs
dirs :
	mkdir -p tmp bin lib

.PHONY: tests mockscannertests mockparsertests realtests

tests : mockscannertests mockparsertests realtests
mockscannertests : bold1-ms.html bold2-ms.html bold3-ms.html
mockparsertests : bold1-mp.html bold2-mp.html bold3-mp.html
realtests : bold1.html bold2.html bold3.html

bold%.html : bold%.md bin/compiler
	bin/compiler bold$*.md

bold%-ms.html : bold%.md bin/compiler
	cp bold$*.md bold$*-ms.md
	bin/compiler --mockScan bold$*-ms.md

bold%-mp.html : bold%.md bin/compiler
	cp bold$*.md bold$*-mp.md
	bin/compiler --mockParse bold$*-mp.md

include rules.mk
