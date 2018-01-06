# Code documentation

This directory contains the Doxyfile which is suitable to generate the code
documentation for simple-chess with doxygen. If doxygen is not installed on your
machine, then just type the appropriate install command into a terminal:

    # Debian
    apt-get install doxygen
    # Raspbian, Ubuntu
    sudo apt-get install doxygen
    # CentOS
    yum install doxygen

You will need sudo or root privileges to do that.

To create the documentation, just change to this directory and type

    doxygen

That will create the documentation in HTML format and put that documentation
into the subdirectory html/. This directory will contain about 750 files
(including subdirectories). Open the file index.html in that directory with a
browser of your choice to see the documentation.
