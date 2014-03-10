<?php/*
 * net_ip_temp.php - sysmond web interface
 *
 * Copyright (C) 2012 - Sotiris Karagiorgis
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



<?php

//include other information for the server
include("../includes/other_info.inc");

$rcv_msg = "";
$timeout = 40;
$socket = stream_socket_client($remote_socket, $errorno, $errorstr, $timeout);
stream_set_timeout($socket, $timeout);

//We mute all the non error messages for a less cluttered interface.
//echo("Sending Command to daemon...<br>\n");
if(!fwrite($socket, $snd_msg5))
   {     
      echo("Error while sending the command to the daemon!<br>\n");
   }

     
if (!($rcv_msg = fread($socket, 1024)))
   { 
      echo("Error while reading the daemon responce!<br>\n");
   }
else
   { 
      //echo($rcv_msg."<br>\n");
   }


if (!($rcv_msg = fread($socket, 1024)))
   { 
      echo("Error receiving the daemon confirmation!<br>\n");
   }
else
   { 
      //echo($rcv_msg."<br>\n");
   }

?>


<html>
<head>
<title>ip's of SYN_RECV-real time</title>
<script src="../js/sorttable.js"></script>
<style media="screen" type="text/css">
table tr:nth-child(odd) { background-color: #ccc; }
</style>
</head>
<body>
<center>
<table>
  <tr>
    <td align="center">REAL TIME IP's OF SYN-RECV OCCURING DATABASE</td>
  </tr>
  <tr>
    <td>
    <br>
    <br>
      <table class="sortable" border="1">
      <tr>
        <td><font face=arial size=3/><b>Id</b></font></td>
        <td><font face=arial size=3/><b>Ip's</b></font></td>
      </tr>
<?php

//include information to connect to the server
include("../includes/m_login.inc");

//connect to the server
$conn = mysql_connect($host, $user, $pass);

if (!$conn) 
   {
      die('Could not connect: ' . mysql_error());
   }

echo 'Connected to MySQL server<br/>';

//select the database
$db_selected = mysql_select_db($db_name, $conn);

if (!$db_selected) 
   {
      die ('Can\'t connect to database : ' . mysql_error());
   }

echo 'Connected to database<br/>';

//select the lsof table				
$result = mysql_query("SELECT * FROM $tbl_name14");	
if (!$result)
    { 
       die('Invalid query: ' . mysql_error());
    } 

$num_rows = mysql_num_rows($result);

echo "There are $num_rows records<P>"; 

//display the contents of the lsof table				
while($data = mysql_fetch_row($result))
     {
         echo("<tr><td><font face=arial size=3/>$data[0]</font></td><td><font face=arial size=3/>$data[1]</font></td></tr>");
     }

mysql_free_result($result);
mysql_close($conn);
?>
     </table>
</table>

<?php

function killfunc()
{
//include other information for the server
include("../includes/other_info.inc");

$rcv_msg = "";
$timeout = 40;
$socket = stream_socket_client($remote_socket, $errorno, $errorstr, $timeout);
stream_set_timeout($socket, $timeout);

//We mute all the non error messages for a less cluttered interface.
//echo("Sending Command to daemon...<br>\n");
if(!fwrite($socket, $snd_msgkill))
   {     
      echo("Error while sending the command to the daemon!<br>\n");
   }

     
if (!($rcv_msg = fread($socket, 1024)))
   { 
      echo("Error while reading the daemon responce!<br>\n");
   }
else
   { 
      //echo($rcv_msg."<br>\n");
   }


if (!($rcv_msg = fread($socket, 1024)))
   { 
      echo("Error receiving the daemon confirmation!<br>\n");
   }
else
   { 
      //echo($rcv_msg."<br>\n");
   }

}


if (isset($_POST['killt']))
   {
     killfunc();     
   }


?>
<br>
<br>
<table>
<tr>
<td>
<form>
<input type="button" onClick="history.go(0)" value="      Refresh      ">
</form>
</td>
<td>
<form action="" method="post">
<input type="submit" name="killt" value="    Drop database   " />
</form>
</td>
<td>
<form action="" method="post">
<input type="button" value="     Close Page     " onclick="self.close()" />
</form>
</td>
</tr>
</table>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<center>sysmond web interface</center>
</body>
</html>
