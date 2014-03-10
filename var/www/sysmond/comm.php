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
			<h2>communicate with the daemon</h2>
<hr noshade size=4 width='50%' align=left>
<?php

//Check if the daemon is running
//include other information for the server
include("includes/other_info.inc");

if (!file_exists($filename)) 
   {
      $id = 0;
   }
else 
   {
      $id = 1;
   }

$file = fopen("$filename","r");
if (!$file)
   {
      $id1 = 0;
   }
else
   {
      $id1 = 1;
   }

$pid = fread($file, 6);

if ($pid > 0)
   {
      $id2 = 1;
   }
else
   {
      $id2 = 0;
   }

if ( $id + $id1 + $id2 == 3)
   {
      echo 'Sysmond daemon OK.';
      $flag = 1;
      echo '<br>';
   }
else
   {
      echo 'There seems to be a problem with sysmond daemon.';
      $flag = 0;
      echo '<br>';
   }

fclose($file);

//Check if MySQL Server is OK
//include information to connect to the server
include("includes/m_login.inc");

//connect to the server
$conn = mysql_connect($host, $user, $pass);

if (!$conn) 
   {
      $id = 0;
   }
else
   {
      $id = 1;
   }

//select the database
$db_selected = mysql_select_db($db_name, $conn);
if (!$db_selected) 
   {
      $id1 = 0;
   }
else
   {
      $id1 = 1;
   }


if ($id + $id1 == 2)
   {
      echo 'MySQL Server is OK. ';
      $flag1 = 1;
      echo '<br>'; 
   } 
else
   {
      echo 'There seems to be a problem with MySQL Server.';
      $flag1 = 0;
      echo '<br>';
   }

mysql_close($conn);

if ($flag + $flag1 == 2)
   {
      echo '<br>';
      echo 'All the options below will probably work.'; 
   } 
else
   {
      echo '<br>';
      echo "The options below probably won't work.";
   }

?>
<h3><u>create the databases</u></h3>
EXISTING DATABASES WILL GET OVERWRITTEN.
<br>
<br>
<form name="input" action="" method="post">
<input type="radio" name="command" value="oneee">1. Create md5sum safe db.<br>
<input type="radio" name="command" value="twooo">2. Create md5sum unsafe db and the differences db.<br>
<input type="radio" name="command" value="three">3. Create safe services db.<br>
<input type="radio" name="command" value="fourr">4. Create unsafe services db and the differences db.<br>
<input type="radio" name="command" value="fivee">5. Create an database with lsof data.<br>
<input type="radio" name="command" value="killt">6. Drop all the temporary tables in the db.<br><br>
<input type="submit" value="Submit">
</form> 

<p>Press submit to send the command to the daemon.
Wait until the page fully loads, and you see the confirmation from the daemon.</p>



<?php

//include other information for the server
include("includes/other_info.inc");

if(isset($_POST["command"])) 
  {
     $snd_msg = $_POST["command"];
     $rcv_msg = "";
     $timeout = 40;
     $socket = stream_socket_client($remote_socket, $errorno, $errorstr, $timeout);
     stream_set_timeout($socket, $timeout);

     echo("Sending Command to daemon...<br>\n");
     if(!fwrite($socket, $snd_msg))
  {
            echo("Error while sending the command to the daemon!<br>\n");
  }

     
     if (!($rcv_msg = fread($socket, 1024)))
  { 
            echo("Error while reading the daemon responce!<br>\n");
  }
     else
        { 
            echo($rcv_msg."<br>\n");
  }


       if (!($rcv_msg = fread($socket, 1024)))
  { 
            echo("Error receiving the daemon confirmation!<br>\n");
  }
     else
        { 
            echo($rcv_msg."<br>\n");
  }

  }

?>
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
