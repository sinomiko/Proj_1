[root@li1734-30 proto-buffer]# export PATH=$PATH:/usr/local/protobuf/bin/
[root@li1734-30 proto-buffer]# export PKG_CONFIG_PATH=/usr/local/protobuf/lib/pkgconfig/
[root@li1734-30 proto-buffer]# vim /etc/ld.so.conf  #add /usr/local/protobuf/lib 

[root@li1734-30 proto-buffer]# ldconfig

[root@li1734-30 proto-buffer]#  protoc -I=. --cpp_out=./output ./addressbook.proto
[libprotobuf WARNING google/protobuf/compiler/parser.cc:546] No syntax specified for the proto file: addressbook.proto. Please use 'syntax = "proto2";' or 'syntax = "proto3";' to specify a syntax version. (Defaulted to proto2 syntax.)

[root@li1734-30 proto-buffer]#  cd output/

[root@li1734-30 proto-buffer]#  g++ addressbook.pb.cc write.cpp -o write `pkg-config --cflags --libs protobuf`
[root@li1734-30 proto-buffer]#  g++ addressbook.pb.cc read.cpp -o read `pkg-config --cflags --libs protobuf`
