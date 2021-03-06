<?php/*
 * net_ipcnt_temp.php - sysmond web interface
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
if(!fwrite($socket, $snd_msg6))
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
<title>number of connections each ip has to the server-real time</title>
<script>
function showState(str)
{
if (str=="")
  {
  document.getElementById("txtHint").innerHTML="";
  return;
  } 
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
    document.getElementById("txtHint").innerHTML=xmlhttp.responseText;
    }
  }
xmlhttp.open("GET","../scripts/get_ipcnt_state.php?q="+str,true);
xmlhttp.send();
}
</script>
<script src="../js/sorttable.js"></script>
<style media="screen" type="text/css">
table tr:nth-child(odd) { background-color: #ccc; }
</style>
</head>
<body>
<center>
<table>
  <tr>
    <td align="center">REAL TIME NUMBER OF TCP CONNECTIONS EACH IP HAS TO THE SERVER DATABASE</td>
  </tr>
  <tr>
    <td>
    <br>
    <br>
      <table class="sortable" border="1">
      <tr>
        <td><font face=arial size=3/><b>Id</b></font></td>
        <td><font face=arial size=3/><b>Number Of Connections</b></font></td>
        <td><font face=arial size=3/><b>Address:Port</b></font></td>
	<td><font face=arial size=3/><b>State</b></font></td>
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
$result = mysql_query("SELECT * FROM $tbl_name15");	
if (!$result)
    { 
       die('Invalid query: ' . mysql_error());
    } 

$num_rows = mysql_num_rows($result);

echo "There are $num_rows records<P>"; 

//display the contents of the lsof table				
while($data = mysql_fetch_row($result))
     {
         echo("<tr><td><font face=arial size=3/>$data[0]</font></td><td><font face=arial size=3/>$data[1]</font></td><td><font face=arial size=3/>$data[2]</font></td><td><font face=arial size=3/>$data[3]</font></td></tr>");
     }

mysql_free_result($result);
mysql_close($conn);

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

</table>
  </td>
</tr>
</table>
<br>
<br>
<br>
<table>
<tr>
<td>
<form>
<select name="status" onchange="showState(this.value)">
<option value="">Select a state:</option>
<option value="LISTEN">LISTEN</option>
<option value="ESTABLISHED">ESTABLISHED</option>
<option value="CLOSE_WAIT">CLOSE_WAIT</option>
<option value="SYN_SENT">SYN-SENT</option>
<option value="SYN_RECV">SYN-RECV</option>
<option value="FIN_WAIT-1">FIN-WAIT-1</option>
<option value="FIN_WAIT-2">FIN-WAIT-2</option>
<option value="TIME_WAIT">TIME-WAIT</option>
<option value="CLOSED">CLOSED</option>
<option value="CLOSE_WAIT">CLOSE-WAIT</option>
<option value="LAST_ACK">LAST-ACK</option>
<option value="CLOSING">CLOSING</option>
</select>
</form>
</td>
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
<br />
<div id="txtHint"><b>Info will be listed here.</b></div>
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
