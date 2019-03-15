#COMAKE2 edit-mode: -*- Makefile -*-
####################64Bit Mode####################
ifeq ($(shell uname -m),x86_64)
CC=gcc
CXX=g++
CXXFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CFLAGS=-g \
  -pipe \
  -W \
  -Wall \
  -fPIC
CPPFLAGS=-D_GNU_SOURCE \
  -D__STDC_LIMIT_MACROS \
  -DVERSION=\"1.9.8.7\"
INCPATH=-I. \
  -I./include \
  -I./output \
  -I./output/include
DEP_INCPATH=-I../../../../lib2-64/ullib \
  -I../../../../lib2-64/ullib/include \
  -I../../../../lib2-64/ullib/output \
  -I../../../../lib2-64/ullib/output/include \
  -I../../../../third-64/gflags \
  -I../../../../third-64/gflags/include \
  -I../../../../third-64/gflags/output \
  -I../../../../third-64/gflags/output/include \
  -I../../../../third-64/gtest \
  -I../../../../third-64/gtest/include \
  -I../../../../third-64/gtest/output \
  -I../../../../third-64/gtest/output/include

#============ CCP vars ============
CCHECK=@ccheck.py
CCHECK_FLAGS=
PCLINT=@pclint
PCLINT_FLAGS=
CCP=@ccp.py
CCP_FLAGS=


#COMAKE UUID
COMAKE_MD5=1795265c06ed7974d1ec34a4f4bdf0ad  COMAKE


.PHONY:all
all:comake2_makefile_check parse libparse.a unittest/test_user_object ut 
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mall[0m']"
	@echo "make all done"

.PHONY:comake2_makefile_check
comake2_makefile_check:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mcomake2_makefile_check[0m']"
	#in case of error, update 'Makefile' by 'comake2'
	@echo "$(COMAKE_MD5)">comake2.md5
	@md5sum -c --status comake2.md5
	@rm -f comake2.md5

.PHONY:ccpclean
ccpclean:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mccpclean[0m']"
	@echo "make ccpclean done"

.PHONY:clean
clean:ccpclean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mclean[0m']"
	rm -rf parse
	rm -rf ./output/bin/parse
	rm -rf libparse.a
	rm -rf ./output/lib/libparse.a
	rm -rf ./output/include/base_object.h
	rm -rf ./output/include/parse_dict_file.h
	rm -rf ./output/include/user_object.h
	rm -rf unittest/test_user_object
	rm -rf ./output/bin/test_user_object
	rm -rf ut
	rm -rf src/parse_base_object.o
	rm -rf src/parse_main.o
	rm -rf src/parse_parse_dict_file.o
	rm -rf src/parse_user_object.o
	rm -rf unittest/test_user_object_test_user_object.o

.PHONY:dist
dist:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdist[0m']"
	tar czvf output.tar.gz output
	@echo "make dist done"

.PHONY:distclean
distclean:clean
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mdistclean[0m']"
	rm -f output.tar.gz
	@echo "make distclean done"

.PHONY:love
love:
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlove[0m']"
	@echo "make love done"

parse:src/parse_base_object.o \
  src/parse_main.o \
  src/parse_parse_dict_file.o \
  src/parse_user_object.o
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mparse[0m']"
	$(CXX) src/parse_base_object.o \
  src/parse_main.o \
  src/parse_parse_dict_file.o \
  src/parse_user_object.o -Xlinker "-("  ../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../third-64/gflags/lib/libgflags.a \
  ../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../third-64/gtest/lib/libgtest.a \
  ../../../../third-64/gtest/lib/libgtest_main.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o parse
	mkdir -p ./output/bin
	cp -f --link parse ./output/bin

libparse.a:src/parse_base_object.o \
  src/parse_main.o \
  src/parse_parse_dict_file.o \
  src/parse_user_object.o \
  ./include/base_object.h \
  ./include/parse_dict_file.h \
  ./include/user_object.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mlibparse.a[0m']"
	ar crs libparse.a src/parse_base_object.o \
  src/parse_main.o \
  src/parse_parse_dict_file.o \
  src/parse_user_object.o
	mkdir -p ./output/lib
	cp -f --link libparse.a ./output/lib
	mkdir -p ./output/include
	cp -f --link ./include/base_object.h ./include/parse_dict_file.h ./include/user_object.h ./output/include

unittest/test_user_object:unittest/test_user_object_test_user_object.o \
  ./libparse.a
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40munittest/test_user_object[0m']"
	$(CXX) unittest/test_user_object_test_user_object.o -Xlinker "-(" ./libparse.a ../../../../lib2-64/ullib/lib/libullib.a \
  ../../../../third-64/gflags/lib/libgflags.a \
  ../../../../third-64/gflags/lib/libgflags_nothreads.a \
  ../../../../third-64/gtest/lib/libgtest.a \
  ../../../../third-64/gtest/lib/libgtest_main.a -lpthread \
  -lcrypto \
  -lrt -Xlinker "-)" -o unittest/test_user_object
	mkdir -p ./output/bin
	cp -f --link unittest/test_user_object ./output/bin

ut:./unittest/test_user_object
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40mut[0m']"
	echo "build ut over"

src/parse_base_object.o:src/base_object.cpp \
  include/base_object.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/parse_base_object.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/parse_base_object.o src/base_object.cpp

src/parse_main.o:src/main.cpp \
  include/base_object.h \
  include/user_object.h \
  include/base_object.h \
  include/parse_dict_file.h \
  include/user_object.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/parse_main.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/parse_main.o src/main.cpp

src/parse_parse_dict_file.o:src/parse_dict_file.cpp \
  include/parse_dict_file.h \
  include/user_object.h \
  include/base_object.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/parse_parse_dict_file.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/parse_parse_dict_file.o src/parse_dict_file.cpp

src/parse_user_object.o:src/user_object.cpp \
  include/user_object.h \
  include/base_object.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40msrc/parse_user_object.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) $(CPPFLAGS) $(CXXFLAGS)  -o src/parse_user_object.o src/user_object.cpp

unittest/test_user_object_test_user_object.o:unittest/test_user_object.cpp \
  include/user_object.h \
  include/base_object.h \
  include/base_object.h
	@echo "[[1;32;40mCOMAKE:BUILD[0m][Target:'[1;32;40munittest/test_user_object_test_user_object.o[0m']"
	$(CXX) -c $(INCPATH) $(DEP_INCPATH) -D__INLINE__="" \
  -Dprivate=public \
  -Dprotected=public \
  -D__64BIT__ $(CXXFLAGS)  -o unittest/test_user_object_test_user_object.o unittest/test_user_object.cpp

endif #ifeq ($(shell uname -m),x86_64)


