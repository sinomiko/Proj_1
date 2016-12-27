#install sqlite3
  wget https://www.sqlite.org/2016/sqlite-autoconf-3150200.tar.gz
  tar -zvxf  sqlite-autoconf-3150200.tar.gz 

  sqlite-autoconf-3150200

  ./configure  --prefix=/usr/
  make -j4 && make install
 
#create db student
  sqlite3 student
#create table user(username text primary key, password text); 
#insert into user values("tianyou121", "123");
#select * from user;

#create test file
  vim sqlite3_t.c
  gcc -o sqlite_t sqlite3_t.c -lsqlite3
