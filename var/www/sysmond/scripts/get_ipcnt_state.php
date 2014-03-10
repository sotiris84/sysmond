<?php/*
 * get_ipcnt_state.php - sysmond web interface
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
$q = $_GET["q"];

//We mute all the non error messages for a less cluttered interface.
//include information to connect to the server
include("../includes/m_login.inc");

//connect to the server
$conn = mysql_connect($host, $user, $pass);

if (!$conn) 
   {
      echo ("Can't connect to server: " . mysql_error());
      echo '<br>';
   }
else
   {
      //echo ' Connected to server.<br/>';
   }

//select the database
$db_selected = mysql_select_db($db_name, $conn);
if (!$db_selected) 
   {
      echo ('Can\'t connect to database : ' . mysql_error());
      echo '<br>';
   }
else
   {
      //echo ' Connected to database.<br><br/>';
   }

$sql="SELECT * FROM net_ipcnt_temp WHERE state = '".$q."'";

$result = mysql_query($sql);

echo "<table border='1'>
<tr>
<th>Id</th>
<th>Number Of Connections</th>
<th>Address:Port</th>
<th>State</th>
</tr>";

while($row = mysql_fetch_array($result))
  {
  echo "<tr>";
  echo "<td>" . $row['id'] . "</td>";
  echo "<td>" . $row['number_of_connections'] . "</td>";
  echo "<td>" . $row['address_port'] . "</td>";
  echo "<td>" . $row['state'] . "</td>";
  echo "</tr>";
  }
echo "</table>";

mysql_close($conn);
?>
