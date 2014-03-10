/* sysmond (system monitoring daemon) is a daemon that monitors a system's CPU usage, memory usage, processes and open network connections and prints then on a file 
  *for later processing.

  *Author: Sotiris Karagiorgis 
  *Copyright (C) 2010, 2014 Sotiris Karagiorgis <skaragiorgis@gmail.com>

 *This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

*/

/* Contains all of the options specified by the user. */
/*You must compile the daemon after each change you make to this file.*/

#include "options.h"

//In seconds
//int updateinterval = 2;

/*
BE CAREFULL WHEN EDITING THIS OPTION! The folders must start with / and have one space character between them.
You must not change anything around the | and > operators!

Original options in case you messed it up. :)
const char  command[] = "../exec/find /home/sotos/Downloads -type f -print0 | xargs -0 ../exec/md5sum > my_pipe";
const char command1[] = "../exec/ps -e -o command > temp.dat";
const char command2[] = "../exec/lsof -n -i -P > temp.dat";
const char command3[] = "../exec/date > my_pipe1";  */
//const char command4[] = "../exec/sed s/\ \ */\ /g lsof.dat > final.dat"; 


const char command[] = "find /home/sotos/Downloads -type f -print0 | xargs -0 md5sum > my_pipe";
const char command0[] = "find /home/sotos/Downloads -type f -print0 | xargs -0 md5sum > md5sum.dat";
const char command1[] = "ps -e -o command > services.dat";
const char command2[] = "lsof -n -i -P > lsof.dat";
const char command3[] = "date > my_pipe1";
const char command4[] = "sed 's/\ \ */\ /g' lsof.dat > final.dat";
const char command5[] = "ss -t -a -n > ss.dat";
const char command6[] = "sed 's/\ \ */\ /g' ss.dat > final.dat";
const char command7[] = "ss -l -n > ss_ports.dat";
const char command8[] = "sed 's/\ \ */\ /g' ss_ports.dat > final.dat";
const char command9[] = "ss -o -n state all '( dport = :http or sport = :http )' > ss_http.dat";
const char command10[] = "sed 's/\ \ */\ /g' ss_http.dat > final.dat";
const char command11[] = "netstat -n -p|grep SYN_REC | wc -l > final.dat";
const char command12[] = "netstat -n -p | grep SYN_REC | sort -u > final.dat";
const char command13[] = "netstat -nt | awk '{print $5,$6}' | uniq -c > net_ipcnt.dat";
const char command14[] = "sed 's/\ \ */\ /g' net_ipcnt.dat > temp.dat";
const char command15[] = "sed 's/^ *//;s/ *$//' temp.dat > final.dat";
const char command16[] = "sed 's:.*/::g' md5sum.dat > temp.dat";
const char command17[] = "paste -d " " md5sum.dat temp.dat > tmp.dat";
const char command18[] = "sed 's/\ \ */\  /g' tmp.dat > fin.dat";
const char command19[] = "sed 's/$/  /' fin.dat > final.dat";
