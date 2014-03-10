<?php/*
 * db2.php - sysmond web interface
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


<html>
<head>
<title>md5sums_safe</title>
<script src="../js/sorttable.js"></script>
<style media="screen" type="text/css">
table tr:nth-child(odd) { background-color: #ccc; }
</style>
</head>
<body>
<center>
<table>
  <tr>
    <td align="center">SAFE MD5SUMS DATABASE</td>
<?php

//include information to connect to the server
include("../includes/m_login.inc");

//connect to the server
$conn = mysql_connect($host, $user, $pass);

if (!$conn) 
   {
      die('Could not connect: ' . mysql_error());
   }

//echo 'Connected to MySQL server<br/>';

//select the database
$db_selected = mysql_select_db($db_name, $conn);

if (!$db_selected) 
   {
      die ('Can\'t connect to database : ' . mysql_error());
   }

//echo 'Connected to database<br/>';

//select the  date table
$result1 = mysql_query("SELECT * FROM $tbl_name2");
if (!$result1)
    { 
      echo ('Invalid query: ' . mysql_error());
    } 


//display the contents of the date table
echo "<table width=400 border=1>\n";
echo 'Database was created on:<br>';
while ($get_info = mysql_fetch_row($result1))
      { 
         echo "<tr>\n"; 
         foreach ($get_info as $field) 
         echo "\t<td><font face=arial size=3/>$field</font></td>\n"; 
         echo "</tr>\n"; 
      }
 
echo "</table>\n";
mysql_free_result($result1);
mysql_close($conn);
?> 
  </tr>
  <tr>
    <td>
      <table class="sortable" border="1">
      <tr>
        <td><font face=arial size=3/><b>Id</b></font></td>
        <td><font face=arial size=3/><b>Md5sum</b></font></td>
        <td><font face=arial size=3/><b>Path</b></font></td>
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

echo '<br>Connected to MySQL server<br/>';

//select the database
$db_selected = mysql_select_db($db_name, $conn);

if (!$db_selected) 
   {
      die ('Can\'t connect to database : ' . mysql_error());
   }

echo 'Connected to database<br/>';

//select the safe md5sums table				
$result = mysql_query("SELECT * FROM $tbl_name1");	
if (!$result)
    { 
       die('Invalid query: ' . mysql_error());
    } 

$num_rows = mysql_num_rows($result);

echo "There are $num_rows records<P>"; 

//display the contents of the safe table				
while($data = mysql_fetch_row($result))
     {
         echo("<tr><td><font face=arial size=3/>$data[0]</font></td><td><font face=arial size=3/>$data[1]</font></td><td><font face=arial size=3/>$data[2]</font></td></tr>");
     }

mysql_free_result($result);
mysql_close($conn);
?>
    </table>
  </td>
</tr>
</table>


<br>
<br>
<br>
<center>sysmond web interface</center>
</body>
</html>
