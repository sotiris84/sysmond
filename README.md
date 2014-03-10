Sysmond is a lightweight linux daemon for collecting various data from a linux server. The system administrator would then study those data and see if the server has been compromised. It is a tool designed for system or network administrators.

It requires user input as it does nothing on its own.  User input might be from the linux terminal or from a web user interface. Sysmond uses mysql database to store and retrieve the results. It’s best to be installed on a freshly set up linux server, because you will know it is not compromised.

This is my university thesis. It is a work in progress. Sysmond is being developed and tested in Ubuntu.

HOW TO RUN
1) You need the LAMP stack
2) Install the build-essentials
3) Install the mysql development library
4) Create a database and a user with access to that database.
5) Enter these information in src/mysql.c and var/www/sysmond/includes/m_login.inc
6) make
7 ./sysmond with root privileges

