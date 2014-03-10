Sysmond is a lightweight linux daemon for collecting various data from a linux server. The system administrator would then study those data and see if the server has been compromised. It is a tool designed for system or network administrators.

It requires user input as it does nothing on its own.  User input might be from the linux terminal or from a web user interface. Sysmond uses mysql database to store and retrieve the results. It’s best to be installed on a freshly set up linux server, because you will know it is not compromised.

This is my university thesis. It is a work in progress. Sysmond is being developed and tested in Ubuntu.

HOW TO RUN<br>
1) You need the LAMP stack<br>
2) Install the build-essentials<br>
3) Install the mysql development library<br>
4) Create a database and a user with access to that database.<br>
5) Enter these information in src/mysql.c and var/www/sysmond/includes/m_login.inc<br>
6) make<br>
7) ./sysmond with root privileges<br>

