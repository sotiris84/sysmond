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
                                                                               
 /* Header file for options.c */

#ifndef OPTIONS_H
#define OPTIONS_H 1

/* The interval between updates. */
extern int updateinterval;
extern const char command[];
//extern const char command1[];

#endif /* options.h */
