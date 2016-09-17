# Language for Interface
The Hyundai Center of Excellence (HCE) researchers use Matlab 2015 64-bit to building their systems. 
On our side we use C++ Qt to build the interface, using Matlab Engine API to work interchangeably with our codes.
Note that Matlab and Qt need to be both 32-bit or both 64-bit for linking libraries. 
And Qt must be configured with MinGW instead of msvc.

# Meetings Record
## August 23, 2016
First formal meeting with HCE people. The researchers in HCE have built a simulation system for vehicle parameter analysis. 
They need us to make an interface that is intuitive enough for Hyundai engineers to use.
Their program has 3 major stages:
1. Build a vehicle. They have their file system for storing vehicle parameters and read vehicles from files.
2. Run simulations under certain test modes. They have Simulink modules for several kinds of tests. One vehicle with one test mode at a time.
3. Analysis. After they run a simulation, some default results are presented in graphs and tables. They populate graphs and tables out together 
and save all results in a huge (>100MB) excel file.

After the meeting, we discussed about possible interface design solutions and sketched an initial layout. Basically it is divided into 3 pages corresponding with their designs. The first two pages look like the following
![alt text](https://github.com/RoyJames/VisVehicle/raw/master/interface1.jpg)
![alt text](https://github.com/RoyJames/VisVehicle/raw/master/interface2.jpg)
As for the third page, neither of us had any ideas.

They cannot give us their codes at the moment. But we confirmed that all data are double precision numbers.
## August 26, 2016
Second meeting with HCE people. They explained in detail the workflow of their file loading system. We then agreed that a default vehicle should be
loaded, and we would let the user change parameters on our interface and write changes to a new or existing vehicle file.
For the test part, they hoped to run sensitivity analysis in the future, although they have not done this yet. This requires us to do parametric sweep.
They said that they would never do parametric study over more than 2 parameters at the same time. The question is how we could let users specify proper ranges for parameters.

## August 31, 2016
Meeting with HCE people at Orange lab. They have sent us a Beta version of their codes and we managed to run their system on our devices.
We pointed out that they did not divide their utilities clearly enough because they mixed tasks in the test and analysis part.
Then they agreed to separate these two parts to make the concepts clear. So the three stages of their program are not dependent on one another.

We also exchanged ideas about data transfer methods between Matlab and C++ codes. 
At first we wanted to use SQLite database for the purpose since we can read and write SQLite .db file from both sides.
But they later reported there might be security issue with external plugins so we would try other options.

## September 7, 2016
Meeting with HCE people at Bainer Hall. We abandoned SQLite database and agreed to pass variables in formated strings, which means we both need to write
parsers for the other side. A possible plan is to use the escape character '\' to make '\0' a separator. Also, we decided that after a test is run, 
default plots and tables should be drawn immediately in the analysis window. The number of plots and tables will be given by HCE researchers in certain format.


# Unsolved Problems
* Parametric sweep range specification.
* Internal data exchange protocal between Matlab and C++ without plugins.
* GUI aesthetic design.

# Schedule
## ~~September 7, 2016~~
### Goals
* Establish the framework for the project. 
* Finish code for basic interaction in the first stage (generating vehicles). 
* Buttons for choosing parameters are defined by HCE researchers and should be automatically loaded onto the interface. 

### Progress
First two tasks done. Format for loading buttons for the second stage (choosing test modes) is determined and is being written by HCE researchers.

## ~~September 15, 2016~~
### Goals
* Handle data transfer problems between Matlab and C++ codes.
* Complete the logic for pair multiple vehicles with multiple test modes in the second stage.

### Progress
Data transfer protocol is tested locally with success. Pairing logic is completed and the display is automatic. The HCE people need more time before sending us new codes, so we still have to test locally without actual data.

## September 22, 2016
### Goals
* Configure QPainter and QOpenGL for plotting result data.
* Add some aesthetics using CSS. 
* If new codes come from HCE people, integrate their codes with ours.
