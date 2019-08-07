# MCQ-Correction
Automatic MCQ correction using C++ and Qt for the Back-End and with a web interface for the Front-End.

## Getting Started
This app is a school project.

#### Goal of the project
We had to design and implement a web application that can:
* Analyse scanned MCQ grids
* Detect and display the checked boxes
* Allow the user to edit the checkmarks manually as needed

#### Technical constraints
* Client-server architecture (client and server can be on different machines)
* Web Font-end (HTML / JS / CSS)
* Back-end in C ++ (> = 11)
* MySQL database
* No PHP

## Server

#### Mandatory features
* Data storage - entities and minimum information:
  * Students: name, first name, promotion
  * Examinations: title, date, promotion, questions, correct answers, rating by question
  * Student responses to each question, associated rating
* Access to data must be secure

#### Use
The server is automatically called by the client and requests are made by the different interaction with the web interface.

You can modify the configuration of the server by modifying the server.cfg file.
You can modify the adress and how to connect to the database.
Furthermore, the IP of the image server (where the examination scans are stored) can also be changed if needed.

Moreover, you can select in which corner is the black square (which plays an important role in the algorithm process).
In the default configuration the black square is located in the top left corner.

**Default configuration file**
```
#----------------------------
# Server Configuration File
#---------------------------
#

database:
{
    ip = "";
    db = "";
    user = "";
    password = "";
};

images:
{
    ip = "";
};

scan:
{
    startCorner:
    {
        right = false;
        bottom = false;
    }
};
```

**Good to know**
* We choose to use an REST API in order to minimize the server-side resources as we have no state management to do.
* The correction algorithm assumes that the rating is the same for each question of an examination.

## Client

#### Mandatory features
* Correction request on a promotion or a student
* Display of the scan with highlighting of the detection of the boxes checked
* Presentation interface and modification of the answers:
  * One "checkbox" element per quiz box
  * The elements are pre-checked with the result of the detection
  * The user can manually modify the answers, by (un)ticking elements by itself. These changes must be persistent.
  * Several boxes can be checked.

#### Use
On the client-side interface you firstly have to authenticate to access the app functionalities.
The interface is pretty straight forward and intuitive.

You can modify the IP and the port of the server to connect to by modifying the ajax variable in the config.js file.

When you are connected you can select a promotion and a examination.
You then see the list of corresponding students.
For each student you can chose to consult their exam paper or to correct it.
For each correction you can verify it and make sure the server-side application has well corrected it following the exam responses.

If there is an error you can modify it and save it in the database.
The displayed image will stay the same as it is the result of the correction algorithm, but the database values will be changed.

Otherwise, you can also chose to correct all a promotion at once for a specific exam by clicking on a single button.

### Installing
Download the zip file from [Github](https://github.com/adrienls/MCQ-Correction)
```
wget --no-cookies https://github.com/adrienls/MCQ-Correction/archive/master.zip -O MCQ-Correction-master.zip
```

Unzip the folder
```
unzip ./MCQ-Correction-master.zip
```
Install the needed dependencies
```
# apt install libconfig++-dev
# apt install qt5-default
# apt install libssl-dev
# apt install libsoci-dev
```


Compile the project for your system using the [CMakeLists.txt](Back-End/CMakeLists.txt) available

Start the server by launching the ./MCQ_Correction file and open the index.html to have the Front-End interface.

## Built With
* [Simple-Web-Server](https://gitlab.com/eidheim/Simple-Web-Server) - A very simple, fast, multithreaded, platform independent HTTP and HTTPS server and client library implemented using C++11 and Boost.Asio. Created to be an easy way to make REST resources available from C++ applications.

* [OpenSSL](https://www.openssl.org/) - OpenSSL is a robust, commercial-grade, and full-featured toolkit for the Transport Layer Security (TLS) and Secure Sockets Layer (SSL) protocols.

* [SOCI](https://github.com/SOCI/soci) - SOCI is a database access library for C++ that makes the illusion of embedding SQL queries in the regular C++ code, staying entirely within the Standard C++.

* [Qt](https://www.qt.io/) - Qt is a cross-platform application framework and widget toolkit for creating classic and embedded graphical user interfaces.

* [libconfig](https://hyperrealm.github.io/libconfig/) - C/C++ library for processing configuration files.

## Versioning
* [Git](https://git-scm.com/) is used for versioning.

## Authors
* [qsvtr](https://github.com/qsvtr)
* [jeremybeaugeard](https://github.com/jeremybeaugeard)
* [adrienls](https://github.com/adrienls)

## License
This project is licensed under the GNU AGPLv3 License - see the [LICENSE.md](LICENSE.md) file for details

License chosen thanks to [choosealicense.com](https://choosealicense.com/)

## Acknowledgments
This MCQ corrector is the final two weeks project of our second year of engineering school in France.
