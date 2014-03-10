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
			<h2>daemon status</h2>
              <hr noshade size=4 width='50%' align=left>
              <br>
              <font face=arial size=2/>Warning! The daemon must be exited with the SIGTERM signal, for the web interface to correctly identify it's status.</font>
              <br>
              <table>
               <td>
                <form>
                  <input type="button" onClick="history.go(0)" value="    Refresh Now    ">
                </form>
               </td>
              </table>
<?php

//Check if the daemons are running
//include other information for the server
include("includes/other_info.inc");

if (file_exists($filename)) 
   {
    
   }
else 
   {
      echo '<br>';
      echo "$filename doesn't exist. Did you reboot the server?";
   }


$file = fopen("$filename","r");
if (!$file)
   {
     echo '<br>';
     echo ("Unable to open file! web interface can't succesfully determine the status of the daemon.");
   }

$pid = fread($file, 6);

if ($pid > 0)
   {
      echo ('<h3><font color="008000">  sysmond daemon running!!</font></h3>');
      echo ("PID: $pid"); 
   }
else
   {
      echo ('<h3><font color="CD0000">sysmond daemon NOT running..</font></h3>');
   }


fclose($file);
?>
<br>
<br>
<br>
<font face=arial size=2/>Usage: If the daemon has crashed or didn't exited correctly, then the pid file will exist and the interface will falsely show the daemon as running.</font>
		</div>
		<!--
		<div id="aside">
			<h3>
				Aside heading
			</h3>
			<p>
				Placeholder text.
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
