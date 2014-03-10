/*
 * main.c
 *
 * Copyright (C) 2014 - Sotiris Karagiorgis
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <mysql.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>





#define BUFSIZE 64
#define MSGSIZE 6
#define SOCK_PATH "/var/run/sysmond.sock"
#define PERM "0666"
#define WAIT 0
#define LISTEN_BACKLOG 50
#define C_MSG "Daemon got the command. "
#define cnfrm_str " Command executed!"
#define BUF_SIZE 100



/* functions declaration */
void kill_temp_db(void);
void lsof_temp_db (void);
void ss_temp_db(void);
void ss_ports_temp_db(void);
void ss_http_temp_db(void);
void net_synrec_temp_db(void);
void net_ip_temp_db(void);
void net_ipcnt_temp_db(void);
void lsof_db (void);
void ser_safe_db (void);
void ser_unsafe_db (void);
void md5_safe_db (void);
void md5_unsafe_db (void);
void check_conn (void);
void usage (void);
void ver (void);
int getnum (void);



//Function to kill the temp tables
void kill_temp_db(void)
{

  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      exit (EXIT_FAILURE);
    }

  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS lsof_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS ss_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS ss_ports_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }



  if (mysql_query (conn, "DROP TABLE IF EXISTS ss_http_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  
  if (mysql_query (conn, "DROP TABLE IF EXISTS net_synrec_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS net_ip_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS net_ipcnt_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Temp tables deleted succesfully. ");
  closelog ();

}




//Function to create the temp lsof -i -n -P database
void lsof_temp_db (void)
{

  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command2[];
  extern const char command4[];

  system (command2);

  system (command4);
  unlink ("lsof.dat");

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS lsof_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE lsof_temp (id int not null primary key auto_increment, command varchar(35), pid int(21), user varchar(25), fd varchar(18), type varchar(15), device int(20), sizeoff varchar(15), node varchar(17), name varchar(60), state varchar(30) null)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' IGNORE INTO TABLE lsof_temp FIELDS TERMINATED BY ' ' IGNORE 1 LINES (command, pid, user, fd, type, device, sizeoff, node, name, state)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog ();

}



//Function to create the ss -t -a -n database
void ss_temp_db(void)
{
  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command5[];
  extern const char command6[];

  system (command5);

  system (command6);
  unlink ("ss.dat");

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS ss_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE ss_temp (id int not null primary key auto_increment, state varchar(20), recvQ int(7), sendQ int(20), local_address_port varchar(30), peer_address_port varchar(30))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' IGNORE INTO TABLE ss_temp FIELDS TERMINATED BY ' ' IGNORE 1 LINES (state, recvQ, sendQ, local_address_port, peer_address_port)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog ();

}



//Function to create the ss -l -n database
void ss_ports_temp_db(void)
{
  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command7[];
  extern const char command8[];

  system (command7);

  system (command8);
  unlink ("ss_ports.dat");

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS ss_ports_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE ss_ports_temp (id int not null primary key auto_increment, state varchar(20), recvQ int(7), sendQ int(20), local_address_port varchar(30), peer_address_port varchar(30))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' IGNORE INTO TABLE ss_ports_temp FIELDS TERMINATED BY ' ' IGNORE 1 LINES (state, recvQ, sendQ, local_address_port, peer_address_port)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog ();

}



//Function to create the ss -l -n database
void ss_http_temp_db(void)
{
  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command9[];
  extern const char command10[];

  system (command9);

  system (command10);
  unlink ("ss_http.dat");

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS ss_http_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE ss_http_temp (id int not null primary key auto_increment, state varchar(20), recvQ int(7), sendQ int(20), local_address_port varchar(30), peer_address_port varchar(30))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' IGNORE INTO TABLE ss_http_temp FIELDS TERMINATED BY ' ' IGNORE 1 LINES (state, recvQ, sendQ, local_address_port, peer_address_port)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog ();

}


//Function to create the netstat -n -p|grep SYN_REC | wc -l database
void net_synrec_temp_db(void)
{
    MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command11[];

  system (command11);

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS net_synrec_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE net_synrec_temp (id int not null primary key auto_increment, count int(5))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' INTO TABLE net_synrec_temp FIELDS TERMINATED BY ' ' (count)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog (); 
}



//Function to create the netstat -n -p | grep SYN_REC | sort -u database
void net_ip_temp_db (void)
{
    MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command12[];

  system (command12);

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS net_ip_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE net_ip_temp (id int not null primary key auto_increment, ips varchar(35))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' INTO TABLE net_ip_temp FIELDS TERMINATED BY ' ' (ips)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog (); 
}



//Function to create the netstat -nt | awk '{print $5,$6}' | uniq -c database
void net_ipcnt_temp_db (void)
{
    MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command13[];
  extern const char command14[];
  extern const char command15[];

  system (command13);
  system (command14);
  system (command15);
  unlink("net_ipcnt.dat");
  unlink("temp.dat");

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS net_ipcnt_temp"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE net_ipcnt_temp (id int not null primary key auto_increment, number_of_connections int(5), address_port varchar(30), state varchar(30))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' IGNORE INTO TABLE net_ipcnt_temp FIELDS TERMINATED BY ' ' IGNORE 2 LINES (number_of_connections, address_port, state)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog (); 
}



//Function to create the lsof -i -n -P database
void lsof_db (void)
{

  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command2[];
  extern const char command4[];

  system (command2);

  system (command4);
  unlink ("lsof.dat");

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("final.dat");
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      printf ("5Error1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("5Error2 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS lsof"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("5Error3 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE lsof (id int not null primary key auto_increment, command varchar(35), pid int(21), user varchar(25), fd varchar(18), type varchar(15), device int(20), sizeoff varchar(15), node varchar(17), name varchar(60), state varchar(30) null)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("5Error4 %u (%s)n", mysql_errno (conn), mysql_error (conn));
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'final.dat' IGNORE INTO TABLE lsof FIELDS TERMINATED BY ' ' IGNORE 1 LINES (command, pid, user, fd, type, device, sizeoff, node, name, state)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("5Error5: %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("final.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("final.dat");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog ();
  printf ("Database created and data loaded succesfully!\n");

}



/* Function to create the services database of the system (safe).*/
void ser_safe_db (void)
{
  MYSQL *conn;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command1[];

  system (command1);

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      unlink ("services.dat");
      exit (EXIT_FAILURE);
    }

  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      printf ("3Error1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("3Error2 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS services_safe"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("3Error3 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE services_safe (id int not null primary key auto_increment, services varchar(450))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("3Error4 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'services.dat' IGNORE INTO TABLE services_safe FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n' IGNORE 1 LINES (services) "))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("3Error5 %u (%s\n", mysql_errno (conn), mysql_error (conn));
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("services.dat");
  mysql_close (conn);
  mysql_library_end ();
  printf ("Database created and data loaded succesfully\n");
}



/* Function to create the services database of the system for comparison (possibly unsafe).*/
void ser_unsafe_db (void)
{
  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;
  int num_fields;
  int i, status;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command1[];

  system (command1);

  FILE *fp2;
  if ((fp2 = fopen ("diffs.dat", "w")) == NULL)
    {
      printf ("Can't open the file to write.\n");
      fclose (fp2);
      exit (EXIT_FAILURE);
    }

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      printf ("4Error1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("4Error2 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS services_unsafe"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("4Error3 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE services_unsafe (id int not null primary key auto_increment, services varchar(450))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("4Error4 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS diff_ser"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("4Error3.1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE diff_ser (id int not null primary key auto_increment, num int, services varchar(450))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("4Error4.1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'services.dat' IGNORE INTO TABLE services_unsafe FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n' IGNORE 1 LINES (services)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("4Error5 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      unlink ("services.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("services.dat");
  //printf ("Database created and data loaded succesfully!\n\n");

  //printf ("Comparing the two databases.\n\n");

  status = mysql_query (conn, "SELECT * FROM services_safe\
		 	       WHERE services NOT IN (SELECT services FROM services_unsafe)\
		 	       UNION\
		 	       SELECT * FROM services_unsafe\
		 	       WHERE services NOT IN (SELECT services FROM services_safe)");

  if (status)
    {
      printf ("Could not list the different services in 2 the databases!\n");

      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to query the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("4Error6 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp2);
      unlink ("diffs.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  result = mysql_store_result (conn);

  num_fields = mysql_num_fields (result);

  printf ("\nListing the different services. If nothing is shown then the 2 databases are the same.\n\n");
  while ((row = mysql_fetch_row (result)))
    {
      for (i = 0; i < num_fields; i++)
	    {
	       fprintf (fp2, "%s ", row[i] ? row[i] : "NULL");
	       printf ("%s ", row[i] ? row[i] : "NULL");
	    }
      fprintf (fp2, "\n");
      printf ("\n");
    }

  fflush(stdout);
  fclose (fp2);
  printf ("\n");

  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'diffs.dat' IGNORE INTO TABLE diff_ser FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n' IGNORE 1 LINES (num, services)"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("4Error7 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      unlink ("diffs.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  unlink ("diffs.dat");
  mysql_free_result (result);
  mysql_close (conn);
  mysql_library_end ();

}



/* Function to create the md5sum database of important (safe) system files.*/
void md5_safe_db (void)
{

  MYSQL *conn;
  int pipe, pipe1;
  FILE *fpipe, *fpipe1;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command0[];
  extern const char command3[];
  //extern const char command16[];
  //extern const char command17[];
  //extern const char command18[];
  //extern const char command19[];


  system (command0);
  //system (command16);
  //system (command17);
  //system (command18);
  //system (command19);

  umask (0);
  pipe1 = mkfifo ("my_pipe1", 0666);
  if (pipe1 != 0)
    {
      printf ("Can't create the FIFO pipe1. \n");
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't create the FIFO pipe1. ");
      closelog ();
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      exit (EXIT_FAILURE);
    }

  if (!(fpipe1 = popen (command3, "r")))
    {
      printf ("Can't write/read to/from the FIFO pipe1. \n");
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't write/read to/from the FIFO pipe1. ");
      closelog ();
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      exit (EXIT_FAILURE);
    }


  if (mysql_library_init (0, NULL, NULL))
    {
      printf ("Can't initialize the MySQL library. \n");
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      printf ("1Error1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("1Error2 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }




  if (mysql_query (conn, "DROP TABLE IF EXISTS md5sums_safe"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("1Error4 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS date_md5sums_safe"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("1Error4.1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE md5sums_safe (id int not null primary key auto_increment, md5sum varchar(33), path varchar(250))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("1Error5 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "CREATE TABLE date_md5sums_safe (date varchar(30) )"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("1Error5.1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'md5sum.dat' INTO TABLE md5sums_safe FIELDS TERMINATED BY '  ' (md5sum, path) "))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("1Error6: %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }


  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'my_pipe1' INTO TABLE date_md5sums_safe (date) "))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the date data into mysql server. ");
      closelog ();
      printf ("1Error6.1: %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      mysql_close (conn);
      pclose (fpipe1);
      unlink ("final.dat");
      unlink ("md5sum.dat");
      unlink ("my_pipe1");
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  pclose (fpipe1);
  //unlink ("final.dat");
  //unlink ("fin.dat");
  unlink ("md5sum.dat");
  //unlink ("temp.dat");
  //unlink ("tmp.dat");
  unlink ("my_pipe1");
  mysql_close (conn);
  mysql_library_end ();
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Database created and data loaded succesfully. ");
  closelog ();
  printf ("Database created and data loaded succesfully!\n\n");



}



/* Function to create the md5sum database of important (unsafe) system files.*/
void md5_unsafe_db (void)
{


  MYSQL *conn;
  FILE *fpipe;
  MYSQL_RES *result;
  MYSQL_ROW row;
  int num_fields;
  int i, status, pipe;
  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];
  extern const char command[];

  umask (0);
  pipe = mkfifo ("my_pipe", 0666);
  if (pipe != 0)
    {
      printf ("FIFO did not createdn");
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't create the FIFO pipe. ");
      closelog ();
      unlink ("my_pipe");
      exit (EXIT_FAILURE);
    }

  if (!(fpipe = popen (command, "r")))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't write data to the FIFO pipe. ");
      closelog ();
      pclose (fpipe);
      unlink ("my_pipe");
      exit (EXIT_FAILURE);
    }

  FILE *fp;
  if ((fp = fopen ("diff.dat", "w")) == NULL)
    {
      printf ("Can't open the file to write. \n");
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      exit (EXIT_FAILURE);
    }

  if (mysql_library_init (0, NULL, NULL))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Can't initialize the MySQL library. ");
      closelog ();
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      exit (EXIT_FAILURE);
    }

  conn = mysql_init (NULL);
  if (conn == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
      closelog ();
      printf ("2Error1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  /* Need to pass that option to mysql to enable the LOAD DATA LOCAL INFILE... 
     necessary for mysql v5.5.x+ and mysql client v5.1.x+  */
  mysql_options (conn, MYSQL_OPT_LOCAL_INFILE, NULL);

  if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("2Error2 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS md5sums_unsafe"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("2Error3 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE md5sums_unsafe (id int not null primary key auto_increment, md5sum varchar(34), path varchar(450))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("2Error4 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "DROP TABLE IF EXISTS diff_md5"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to drop table in the db to make a new one. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("2Error3.1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "CREATE TABLE diff_md5 (id int not null primary key auto_increment, num int, md5sum varchar(34), path varchar(450))"))
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to create table in the db. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("2Error4.1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'my_pipe' INTO TABLE md5sums_unsafe FIELDS TERMINATED BY '  ' (md5sum, path)") != 0)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("2Error5 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      pclose (fpipe);
      unlink ("my_pipe");
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  //printf ("Database created and data loaded succesfully!\n\n");
  pclose (fpipe);
  unlink ("my_pipe");

  //printf ("Comparing the two databases.\n\n");

  status = mysql_query (conn, "SELECT * FROM md5sums_safe\
		 	       WHERE md5sum NOT IN (SELECT md5sum FROM md5sums_unsafe)\
		 	       UNION\
		 	       SELECT * FROM md5sums_unsafe\
		 	       WHERE md5sum NOT IN (SELECT md5sum FROM md5sums_safe)");

  if (status)
    {
      printf ("Could not list the different md5sums in 2 the databases!\n");

      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to query the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
      closelog ();
      printf ("2Error6 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      fclose (fp);
      unlink ("diff.dat");
      mysql_close (conn);
      mysql_library_end ();
      exit (EXIT_FAILURE);
    }

  result = mysql_store_result (conn);

  num_fields = mysql_num_fields (result);

  printf ("\n\nListing the different md5sums. If nothing is shown then the 2 databases are the same.\n\n");
  while ((row = mysql_fetch_row (result)))
    {
      for (i = 0; i < num_fields; i++)
	    {
	       fprintf (fp, "%s ", row[i] ? row[i] : "NULL");
	       printf ("%s ", row[i] ? row[i] : "NULL");
	    }
      fprintf (fp, "\n");
      printf ("\n");
    }

  fflush(stdout);
  fclose (fp);
  printf ("\n");

  if (mysql_query (conn, "LOAD DATA LOCAL INFILE 'diff.dat' INTO TABLE diff_md5 FIELDS TERMINATED BY ' ' LINES TERMINATED BY '\n' (num, md5sum, path)") != 0)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Unable to load the data into mysql server. ");
      closelog ();
      printf ("2Error7 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
      mysql_close (conn);
      mysql_library_end ();
      unlink ("diff.dat");
      exit (EXIT_FAILURE);
    }

  unlink ("diff.dat");
  mysql_free_result (result);
  mysql_close (conn);
  mysql_library_end ();

}



int getnum (void)
  {
    char s[80];
    gets (s);
    return (atoi (s));
  }


void usage (void)
  {
    printf ("\nusage: sudo sysmond [option]\n\n");
    printf ("options:\n");
    printf ("  -h, --help                   show this help and exit\n");
    printf ("  -v, --version                display version information and exit\n");
    printf ("  -d, --daemon                 start as a daemon immediately\n");
    printf ("  -1, --md5_safe               create the safe md5sums database and exit\n");
    printf ("  -2, --md5_unsafe             create the unsafe md5sums database, compare with the safe and exit\n");
    printf ("  -3, --services_safe          create the safe services database and exit\n");
    printf ("  -4, --services_unsafe        create the unsafe md5sums database, compare with the safe and exit\n");
    printf ("  -5, --lsof                   create the lsof -i -n -P database, and exitn\n");
    printf ("examples:\n");
    printf ("  sudo sysmond                 start the program without option\n");
    printf ("  sudo sysmond -d              start as a daemon\n");
    printf ("  sudo sysmond -1              create the safe md5sums database only and exit\n");
    printf ("  sudo sysmond -3              create the safe services database only and exit\n");
    printf ("  sudo sysmond --version       show version and copyright information and exit\n\n");
    printf ("To exit the daemon: use the SIGTERM signal\n");
    printf ("  sudo kill -TERM <pid>\n");
    printf ("  sudo kill -15 <pid>\n\n");
    exit (EXIT_SUCCESS);
  }


void ver (void)
  {
    extern const char version[6];
    printf ("nSystem Monitoring Daemon (SYSMOND) v%s\n", version);
    printf ("Copyright (C) 2010, 2014 Sotiris Karagiorgis\n");
    printf ("GNU General Public License v3\n\n");
    exit (EXIT_SUCCESS);
  }


int connection = 0;

void check_conn(void)
  {
    char tmp[LINE_MAX] = {0x0};
    system("netstat -tnp > netstat.dat");
    FILE *fp=fopen("netstat.dat","r");
    while (fp != NULL && fgets(tmp, sizeof(tmp), fp) != NULL)
       {
          if (strstr(tmp, ":3111") && strstr(tmp, "ESTABLISHED"))
	      connection = 1;
       }

    if (fp != NULL)
      fclose (fp);
    system ("rm netstat.dat");
  }


int done = 0;

void term (int signum)
{
  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
  syslog (LOG_INFO, "Received SIGTERM. Now exiting... ");
  closelog ();
  done = 1;
}


int main (int argc, char *argv[])
{

  MYSQL *conn;
  MYSQL_RES *result;
  MYSQL_ROW row;

  /* Our process ID and Session ID */
  pid_t pid_a, sid_a;
  pid_t pid_b, sid_b;

  int pid;
  int fd;
  int op = 0;
  int opt, optidx = 1;
  int sd, sd2;
  int totalcnt = 0, on = 1;
  int i = 0;
  int num_fields;
  int server_socket, accepted_socket, n;

  char buf[BUF_SIZE];
  char buffer[BUF_SIZE];
  char recvd_msg[BUFSIZE], out_str[BUFSIZE];
  char daemon_responce[8] = {'D', 'o', 'n', 'e', '.', '.', '!', '\0'};
  char c;

  //extern int updateinterval;
  extern const char version[6];

  extern const char host[];
  extern const char user[];
  extern const char password[];
  extern const char database[];

  struct flock fl = { F_WRLCK, SEEK_SET, 0, 0, 0 };
  fl.l_pid = getpid ();

  struct sockaddr_un my_addr, peer_addr;
  socklen_t peer_addr_size;
  mode_t mode = strtol(PERM, 0, 8);

  struct sockaddr_in serveraddr;
  struct sockaddr_in their_addr;
  fd_set read_fd;

  struct timeval timeout;
  timeout.tv_sec = 600;		//10 mins timeout
  timeout.tv_usec = 0;

  static struct option opts[] = {
    {"help",            no_argument, 0, 'h'},
    {"version",         no_argument, 0, 'v'},
    {"daemon",          no_argument, 0, 'd'},
    {"md5_safe",        no_argument, 0, '1'},
    {"md5_unsafe",      no_argument, 0, '2'},
    {"services_safe",   no_argument, 0, '3'},
    {"services_unsafe", no_argument, 0, '4'},
    {"lsof",            no_argument, 0, '5'},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };

  if (argc > 2)
    usage();

  while ((opt = getopt_long (argc, argv, "hvd12345", opts, &optidx)))
    {
      if (opt < 0)
        {
	       break;
	    }

      switch (opt)
	    {
	      case 0:
	        break;
	      case 'd':
	        goto daemonize;
	        break;
	      case 'v':
	        ver();
	        break;
	      case 'h':
	        usage();
	        break;
	      case '1':
	        md5_safe_db();
	        exit (EXIT_SUCCESS);
	        break;
	      case '2':
	        md5_unsafe_db();
	        exit (EXIT_SUCCESS);
	        break;
	      case '3':
	        ser_safe_db();
	        exit (EXIT_SUCCESS);
	        break;
	      case '4':
	        ser_unsafe_db();
	        exit (EXIT_SUCCESS);
	        break;
	      case '5':
	        lsof_db();
	        exit (EXIT_SUCCESS);
	        break;
	      default:
	        usage();
	        break;
	    }
    }


  printf ("\nSystem Monitoring Daemon (SYSMOND) v%s\n", version);
  printf ("Copyright (C) 2010, 2014 Sotiris Karagiorgis\n\n");
  printf ("sysmond comes with NO WARRANTY,\n");
  printf ("to the extent permitted by law.\n");
  printf ("You may redistribute copies of sysmond\n");
  printf ("under the terms of the GNU General Public License.\n");

loop_menu:
  do
    {
      printf ("\n\nOptions Menu:\n\n");
      printf ("[1].   Create safe md5sum database. This must be done only once when the system\n");
      printf ("       installs to ensure that there are no infected files. \n");
      printf ("[2].   Create another db with possibly compromised md5 hashes and compare it with the 1st database.\n");
      printf ("[3].   Create database containing the services. Do that once when the system installs.\n");
      printf ("[4].   Create another database for the services to compare with the first one.\n");
      printf ("[5].   Create a database from the output of lsof -i -n -P command.\n");
      printf ("[6].   Drop the temp tables.\n");
      printf ("[7].   Start the daemon.\n");
      printf ("[8].   Exit.\n");

      printf ("\nPlease Choose an Option: ");
      op = getnum ();

    }
  while (op < 1 || op > 8);


  switch (op)
    {
    case 1:
      printf ("\n\nCreating the initial (safe) md5sum database of the /lib /bin /sbin and /opt folders.\n");
      printf ("This might take some time...\n\n");


      if (mysql_library_init (0, NULL, NULL))
	     {
	       /* Open log, output to /var/log/syslog */
	       openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	       syslog (LOG_INFO, "Can't initialize the MySQL library. ");
	       closelog ();
	       exit (EXIT_FAILURE);
	      }


      conn = mysql_init (NULL);
      if (conn == NULL)
	    {
	      /* Open log, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "mysql_init() failed. Now Exiting. ");
	      closelog ();
	      printf ("0Error1 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
	      mysql_close (conn);
	      mysql_library_end ();
	      exit (EXIT_FAILURE);
	    }

      if (mysql_real_connect (conn, host, user, password, database, 0, NULL, 0) == NULL)
	    {
	      /* Openlog, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Unable to login to the mysql server. Make sure mysql is up and running and you gave the right credentials. ");
	      closelog ();
	      printf ("0Error2 %u (%s)\n", mysql_errno (conn), mysql_error (conn));
	      mysql_close (conn);
	      mysql_library_end ();
	      exit (EXIT_FAILURE);
	    }

      if (mysql_query (conn, "SELECT * FROM date_md5sums_safe"))
	    {
	      /* Open log, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "The table does not exist. Not to worry. Probably the first time you are creating the safe md5sums list. ");
	      closelog ();
	      printf ("%u (%s)\n", mysql_errno (conn), mysql_error (conn));
	      printf ("This is probably the first time you are creating the safe md5sums database. Doing it now!\n\n");
	      mysql_close (conn);
	      mysql_library_end ();
	      md5_safe_db ();
	      goto loop_menu;
	    }

      result = mysql_store_result (conn);
      num_fields = mysql_num_fields (result);
      row = mysql_fetch_row (result);

      printf ("The last time you updated the md5sum database was at %s. Be advised that if you have previously created the safe md5sum database and you run it again you might replace it with unsafe data.\n", row[i]);

    loop_menu1:

      do
	    {
	      printf ("\nAre you sure you want to continue (y / n)? ");

	      scanf ("%c", &c);
	      if (c == 'y')
	        break;
	      else if (c == 'Y')
	        break;
	      else if (c == 'n')
	        {
	          mysql_close (conn);
	          mysql_library_end();
	          goto loop_menu;
	        }
	      else if (c == 'N')
	        {
	          mysql_close (conn);
	          mysql_library_end();
	          goto loop_menu;
	        }
	      else
	        printf ("\nWrong Answer!\n");
	      goto loop_menu1;
	    }
      while (1);

      mysql_close (conn);
      mysql_library_end();

      md5_safe_db ();
      goto loop_menu;
      break;
    case 2:
      printf ("\n\nCreating md5sum database of /lib /bin /sbin /etc folders that might have been patched\n");
      printf ("and will compare it with the first database you created. This might take some time...\n\n");
      md5_unsafe_db ();
      goto loop_menu;
      break;
    case 3:
      printf ("\n\nCreating the initial services database. This can take some time.\n\n");
      ser_safe_db ();
      goto loop_menu;
      break;
    case 4:
      printf ("\n\nCreating services database to compare with the first one. This can take some time.\n\n");
      ser_unsafe_db ();
      goto loop_menu;
      break;
    case 5:
      printf ("\n\nCreating the lsof database. This can take some time.\n\n");
      lsof_db ();
      goto loop_menu;
      break;
    case 6:
      printf ("\n\nNow droping all the temporary tables in the database.\n\n");
      kill_temp_db();
      goto loop_menu;
      break;
    case 7:
      printf ("\n\nStarting the daemon. Check the logs...\n\n");
      printf ("Please use the SIGTERM signal to properly exit the daemon!\n");
      sleep (1);
      goto daemonize;
      break;
    case 8:
      printf ("\n\nNow Exiting the program...\n\n");
      exit (EXIT_SUCCESS);
      break;
    }


daemonize:
  // Trap signals that we expect to receive
  signal (SIGTERM, term);

  /* Fork the parent process */
  pid_a = fork ();

  if (pid_a < 0)
    {
      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Fork Failed. Now exiting. ");
      closelog ();
      exit (EXIT_FAILURE);
    }

  
  if (pid_a > 0) 
	{
	  /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Exiting the parent process. ");
      closelog ();	
      exit(EXIT_SUCCESS);
    } 

  if (pid_a == 0)
  {


      /* Open or create the pidfile and lock it to prevent other instances of the daemon to run */
      if ((fd = open ("/var/run/sysmond.pid", O_RDWR | O_CREAT, 0644)) == -1)
	    {
	       printf ("Error opening/creating the pidfile. Are you root? Now exiting.\n");

	       /* Open any logs here, output to /var/log/syslog */
	       openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	       syslog (LOG_INFO, "Can't open/create the pidfile. You need administrative privileges to run the program. ");
	       closelog ();
	       close (fd);
	       exit (EXIT_FAILURE);
	    }
    
      if (fcntl (fd, F_SETLK, &fl) == -1)
	    {
	       printf ("Looks like the daemon is already running. Now exiting!\n");

	       /* Open any logs here, output to /var/log/syslog */
	       openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	       syslog (LOG_INFO, "Only one instance of the daemon is allowed to run. ");
	       closelog ();
	       close (fd);
	       exit (EXIT_FAILURE);
	    }

    
      if (ftruncate (fd, 0) == -1)
	    {
	      printf ("Could not truncate pidfile.\n");

	      /* Open any logs here, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Could not truncate the pidfile. PID in pidfile might be wrong or messed up. ");
	      closelog ();
	    }
    }

      snprintf (buf, BUF_SIZE, "%ld\n", (long) getpid ());

      if (write (fd, buf, strlen (buf)) != strlen (buf))
	    {
	      printf ("Can't write the PID in the pidfile\n");

	      /* Open any logs here, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Could not write the PID in the pidfile. PID might be wrong or messed up. ");
	      closelog ();
	    }


      /* Change the file mode mask. Now executing as the child process. */
      umask (0);

      /* Open any logs here, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Fork 1 Successful. ");
      closelog ();

      /* Create a new SID for the child process */
      sid_a = setsid ();
      if (sid_a < 0)
	    {
	      /* Open log, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Creating Session ID Failed. Now Exiting. ");
	      closelog ();
          exit (EXIT_FAILURE);
	    }

      /* Open log, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "Child Process Created, daemon is Running. ");
      closelog ();

      /* Change the current working directory */
      if ((chdir ("/")) < 0)
	    {
	      /* Open log, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Changing Current Working Directory Failed. Now Exiting. ");
	      closelog ();
          exit (EXIT_FAILURE);
	    }

      /* Close out the standard file descriptors */
      close (STDIN_FILENO);
      close (STDOUT_FILENO);
      close (STDERR_FILENO);

      /* Daemon-specific initialization goes here */

      /* Creating a Unix domain socket */
      server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
      if (server_socket  == -1)
	     {
             openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
             syslog (LOG_INFO, "Error creating unix socket. ");
             closelog ();
	     }


      /* Binding the socket to a file */
      memset(&my_addr, 0, sizeof(struct sockaddr_un)); /* Clear structure */
      my_addr.sun_family = AF_UNIX;
      strncpy(my_addr.sun_path, SOCK_PATH, sizeof(my_addr.sun_path) - 1);
      unlink(my_addr.sun_path);


      if (bind(server_socket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un)) == -1)
         {
             openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
             syslog (LOG_INFO, "Error binding unix socket. ");
             closelog ();
         }
     
      /* Instructing the socket to listen for incoming connections */
      if (listen(server_socket, LISTEN_BACKLOG) == -1)
	     { 
             openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
             syslog (LOG_INFO, "Unix socket listen error. ");
             closelog ();
         }

 
       /* Changing permission of socket the file */
       if (chmod(SOCK_PATH, mode) == -1)
	      {
             openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
             syslog (LOG_INFO, "Error changing permissions on unix socket. ");
             closelog ();
	      }

	 /* Open log, output to /var/log/syslog */
        openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
        syslog (LOG_INFO, "Collecting Data. ");
        closelog ();
   

     /* The actual daemon work */
    while (!done) 
    	{

	       if (done == 1)
		     {
		        goto sigterm_received;
		     }


	    /* Accepting incoming connections one at a time */
            peer_addr_size = sizeof(struct sockaddr_un);
	
	    if (done == 1)
		    {
		       goto sigterm_received;
		    }

            accepted_socket = accept(server_socket, (struct sockaddr *) &peer_addr, &peer_addr_size);

	    if (done == 1)
		    {
		       goto sigterm_received;
		    }
            if (accepted_socket == -1)
	           {
                  openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                  syslog (LOG_INFO, "Unix socket accept connection error. ");
                  closelog ();
		       //goto cont;
	           }

	    if (done == 1)
	       goto sigterm_received;

            /* Receiving data */
            n = recv(accepted_socket, recvd_msg, MSGSIZE, 0);

	    if (done == 1)
	       goto sigterm_received;

            if (n < 0)
	           { 
                   openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                   syslog (LOG_INFO, "Error reading data on unix socket. ");
                   closelog ();
	           }

	    if (done == 1)
	       goto sigterm_received;

            /* Printing received data */
            snprintf(out_str, strlen(C_MSG)+1, "%s", C_MSG);

	    if (done == 1)
	       goto sigterm_received;

            /* Waiting just for fun */
            sleep(WAIT);

	    if (done == 1)
	       goto sigterm_received;

            /* Sending data */
	    n = send(accepted_socket, C_MSG, strlen(C_MSG), 0);

 	    if (done == 1)
	       goto sigterm_received;

            if (n < 0)
	           {
                   openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                   syslog (LOG_INFO, "Error writing data to the unix socket. ");
                   closelog ();
	           }

	    if (done == 1)
	       goto sigterm_received;

	       /* Execute the commands the server received from client */
	      if (strcmp (recvd_msg, "oneee") == 0)
		    {
		      md5_safe_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		    }

	      else if (strcmp (recvd_msg, "twooo") == 0)
		    {
		       md5_unsafe_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		    }
	      else if (strcmp (recvd_msg, "three") == 0)
		     {
		       ser_safe_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }
	      else if (strcmp (recvd_msg, "fourr") == 0)
		    {
		       ser_unsafe_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		    }
	      else if (strcmp (recvd_msg, "fivee") == 0)
		     {
		       lsof_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }

          else if (strcmp (recvd_msg, "sixxt") == 0)
		      {
		        lsof_temp_db();
		        if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		           }
		      }

	      else if (strcmp (recvd_msg, "seven") == 0)
		     {
		       ss_temp_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }

	      else if (strcmp (recvd_msg, "eight") == 0)
		     {
		       ss_ports_temp_db();
		       if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		      }

	      else if (strcmp (recvd_msg, "ninee") == 0)
		     {
		        ss_http_temp_db();
		        if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }

	      else if (strcmp (recvd_msg, "tennn") == 0)
		     {
		        net_synrec_temp_db();
		        if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }

	      else if (strcmp (recvd_msg, "eleve") == 0)
		     {
		        net_ip_temp_db();
		        if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }

	      else if (strcmp (recvd_msg, "twelv") == 0)
		     {
		        net_ipcnt_temp_db();
		        if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }

	      else if (strcmp (recvd_msg, "killt") == 0)
		     {
		        kill_temp_db();
		        if (send(accepted_socket, cnfrm_str, strlen(cnfrm_str), 0) < 0)
                    {
		               openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
                       syslog (LOG_INFO, "Error sending confirmation string to unix socket. ");
                       closelog ();	
		            }
		     }	
	
	      if (done == 1)
	        goto sigterm_received;

        }  //End of the while loop
	 
       sigterm_received:

       /* Cleaning up */
       close(accepted_socket);
       unlink("/var/run/sysmond.sock");

      /* Unlocking the pidfile */
      fl.l_type = F_UNLCK;

      if (ftruncate (fd, 0) == -1)
	    {
	      /* Open any logs here, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Could not truncate pidfile on unlocking. ");
	      closelog ();
	      close (fd);
	    }

      if (fcntl (fd, F_SETLK, &fl) == -1)
	    {
	      /* Open any logs here, output to /var/log/syslog */
	      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
	      syslog (LOG_INFO, "Could not unlock the pidfile. ");
	      closelog ();
	      close (fd);
	    }


      /* Open any logs here, output to /var/log/syslog */
      openlog ("sysmond", LOG_PID | LOG_CONS, LOG_USER);
      syslog (LOG_INFO, "sysmond daemon exited successfully! ");
      closelog ();

      pid = getpid ();
      kill (pid, SIGTERM);
      close (fd);
   
      exit (EXIT_SUCCESS);
      return 0;
} //End of main()

