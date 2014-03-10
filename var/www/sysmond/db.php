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
			 <h2>view databases</h2>
<hr noshade size=4 width='50%' align=left>
<?php

//Check if MySQL Server is OK
//include information to connect to the server
include("includes/m_login.inc");

//connect to the server
$conn = mysql_connect($host, $user, $pass);

if (!$conn) 
   {
      echo ("Can't connect to server: " . mysql_error());
      echo '<br>';
      $id = 0;
   }
else
   {
      echo ' Connected to server.<br/>';
      $id = 1;
   }

//select the database
$db_selected = mysql_select_db($db_name, $conn);
if (!$db_selected) 
   {
      echo ('Can\'t connect to database : ' . mysql_error());
      echo '<br>';
      $id1 = 0;
   }
else
   {
      echo ' Connected to database.<br><br/>';
      $id1 = 1;
   }


if ($id + $id1 == 2)
   {
     echo 'Data ready to display.'; 
   } 
else
   {
     echo '<br>';
     echo 'Data not ready to display';
   }

mysql_close($conn);
?>

<br>
<table border="1" bordercolor="#ffffff" frame="void">
<tr>
    <td><input type="button" value="   md5sum safe db   " onclick="window.open('db/db1.php')" /></td>
    <td><input type="button" value="  md5sum unsafe db  " onclick="window.open('db/db2.php')" /></td>
    <td><input type="button" value=" md5sum differences " onclick="window.open('db/db12.php')" /></td>
</tr>
<tr>
    <td><input type="button" value="   services safe db   " onclick="window.open('db/db3.php')" /></td>
    <td><input type="button" value="  services unsafe db   " onclick="window.open('db/db4.php')" /></td>
    <td><input type="button" value=" services differences  " onclick="window.open('db/db34.php')" /></td>
</tr>
<tr>
    <td><input type="button" value="   lsof command db  " onclick="window.open('db/db5.php')" /></td>
    <td></td>
    <td></td>
</tr>
</table>

<br>
<br>
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
