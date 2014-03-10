<?php/*
 * index.php - sysmond web interface
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
 */?>


<html>
<head>
<title>sysmond - web interface</title>
<meta http-equiv="refresh" content="300">
<link rel="stylesheet" type="text/css" href="style.css">
</head>

<body>

<div id="container">
	<div id="header">
		<h1>
			sysmond
		</h1>
	</div>
	<div id="navigation">
		<ul>
			<li><a href="index.php">Home</a></li>
			<li><a href="db.php">View Databases</a></li>
			<li><a href="comm.php">Communicate with the daemon</a></li>
			<li><a href="realt.php">Real time system data</a></li>
			<li><a href="about.php">About</a></li>
		</ul>
	</div>
	<div id="content-container">
	<!--
		<div id="section-navigation">
			<ul>
				<li><a href="#">Section page 1</a></li>
				<li><a href="#">Section page 2</a></li>
				<li><a href="#">Section page 3</a></li>
				<li><a href="#">Section page 4</a></li>
			</ul>
		</div>
		-->
		<div id="content">
			 <h2>real time system data</h2>
       <hr noshade size=4 width='50%' align=left>
CREATE REAL TIME DATA FROM THE COMMANDS BELOW
<br><br>
<table border="1" bordercolor="#ffffff" frame="void">
<tr>
    <td><u>View Network Connections.</u><tr></tr></td>
    <td><input type="button" name= "command" value="   lsof -i -n -P   " onclick="window.open('temp/lsof_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
<tr>
    <td><u>View Network Connections.</u><tr></tr></td>
    <td><input type="button" name= "command" value="    ss -t -a -n    " onclick="window.open('temp/ss_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
<tr>
    <td><u>View All Open Ports.</u><tr></tr></td>
    <td><input type="button" name= "command" value="      ss -l -n      " onclick="window.open('temp/ss_ports_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
<tr>
    <td><u>View All HTTP Connections.</u><tr></tr></td>
    <td><input type="button" name= "command" value="ss -o -n state all '( dport = :http or sport = :http )'" onclick="window.open('temp/ss_http_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
<tr>
    <td><u>View number of active SYN-RECV.</u><tr></tr></td>
    <td>Let users know how many active SYN-RECV are occurring and happening on the server. The number should be pretty low, preferably less than 5. On DoS attack incident or mail bombed, the number can jump to twins. However, the value always depends on the system. So a number over 5 might not always indicate a dos attack.<br>
    <input type="button" name= "command" value="netstat -n -p|grep SYN_REC | wc -l" onclick="window.open('temp/net_synrec_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
<tr>
    <td><u>View the ip's involved with the SYN-RECV.</u><tr></tr></td>
    <td><input type="button" name= "command" value="netstat -n -p | grep SYN_REC | sort -u" onclick="window.open('temp/net_ip_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
<tr>
    <td><u>View the number of connections each ip:port has to the server and it's state.</u><tr></tr></td>
    <td><input type="button" name= "command" value="netstat -nt | awk '{print $5,$6}' | uniq -c" onclick="window.open('temp/net_ipcnt_temp.php')" /></td>
    <td><tr><tr><tr><tr><tr></tr></tr></tr></tr></tr></td>
</tr>
</table>

		</div>
		<!--
		<div id="aside">
			<h3>
				Aside heading
			</h3>
			<p>
				Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan.
			</p>
		</div>
		-->
		<div id="footer">
			Copyright &copy; Sotiris Karagiorgis, 2014
		</div>
	</div>
</div>

</body>
</html>
