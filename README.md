# ByteType
By Vivian Huynh (5), Rachel Leong (10), Steve Wang (10)
A.K.A. distressed dog, distressed hamster, distressed cat

### Description
  Welcome to ByteType, a type-racing game modeled after the game NitroType which you can find and play at nitrotype.com. To play, up to 4 players will join a game. The “race host” has the option to start when everyone is ready by pressing a button. After a short delay, users will type a paragraph of text selected randomly from a database as fast, and accurately as they can before the other players finish. Each player (not including bots) is given a boost that players can use once per game to skip a word. Statistics like words per minute and accuracy as well as positions will be displayed in real time. 

### Required Libraries
 - The ncurses library is needed in order for the game to be run.
    - In order to install ncurses, do sudo apt-get install libncurses5-dev libncursesw5-dev
    
### How to Play
  - Compile sclient and sserver using make
  - Run ./server ./client on one terminal
  - On another terminal, run ./client to start the game
  - Type the paragraph you see on the screen. If a letter turns green, the letter has been typed successfully.
  - Words per minute and accuracy is displayed at the bottom of the screen
  - When the race is over, simple press any key to exit

### Bugs / Attempted and failed
  - Unsuccessfully tried to implement pipes into networking between the main server and subservers, so it was left out entirely on master branch
  - Unsuccessfully attempted to connect multiple players and race simultaneously: when pulling and running the code from master branch a client can still race by themselves and see their own stats for the current race before exiting via a key press
  - (Not on master branch but on networking branches) When the client is prompted for input the first time, input is sucessfully transferred to the server but then the client gets stalled afterwards until another client connects to the server, probably because of something to do with the reading 
### Devlog
#### Thurs, 1/2/2020 - Tues, 1/7/2020
 - Proposal got finalized after fixing the initial issues
 - Initial empty files were added
 
#### Wed, 1/8/2020
 - Rachel:
   - Completed char_check function
   - Having issues with ending the race
   - Attempted to find a library to utilize for real-time typing but didn't get it --> ask later in class
 - Steve: 
   - Added the 30 random paragraphs to paragraphs.txt
 
#### Thurs, 1/9/2020
 - Vivian:
   - Began working on displaying the paragraph as the user types and tried to figure out how to implement colors into terminal
 - Rachel:
   - Got the game to end properly
   - User inputing and typing works, but you have to press enter after every key in order to type which is very annoying *ugh*
   - Added a string to keep track of what was already typed (for display function to be implemented later)
     - Updated parameters for char_check accordingly
 - Steve:
   - Worked on functions to select a random paragraph from the file paragraphs.txt
   
#### Fri, 1/10/2020
  - Vivian:
    - Learning about ncurses and tried to start implementing
  - Rachel:
    - Reviewing pipes and networking code
  - Steve:
    - Continued working on function to select a random paragraph from paragraphs.txt
  
#### Sat, 1/11/2020
  - Vivian:
    - Continued trying to implement ncurses
  - Rachel:
    - Continued to get a better idea about pipes and networking
    
#### Sun, 1/12/2020
  - Vivian:
    - Finished implementing typing. The program should end after completely typing the paragraph.
  - Rachel:
    - Helped Vivian and Steve debug parts of their functions
  - Steve:
    - Tried something else for random_paragraph(), works better but still doesn't work.

#### Mon, 1/13/2020
  - Rachel:
    - Helped Steve fix random_paragraph()
    - More review of pipes
    - Added .gitignore for C to repo
    - "typed" variable no long is twice the size it should be (fixed!)
  - Steve:
    - Fixed random_paragraph() and integrated it into main() to select a random paragraph and run the game with it.
    
#### Tues, 1/14/2020
  - Vivian:
    - Tried to calculate statistics, however having a hard time with wpm because it's much more complicated than we originally thought :'(
    - The paragraphs had a lot of blankspaces after them that were not spaces and I tried getting rid of them because the race can't end without typing those blankspaces but I did not succeed
  - Rachel:
    - Started trying to integrate pipes into networking code and typing, but was unsuccessful 
    - Decided it might be a better idea to focus on integrating pipes into networking before adding the typing
    
#### Thurs, 1/16/2020
  - Steve:
    - Renamed original README.md to PROPOSAL.md
    - Created and updated README.md
  - Rachel:
    - Got some help in class and tried to focus on using unnamed pipes to keep track of changes on subservers

#### Fri, 1/17/2020
  - Rachel: 
    - Continued trying to figure out networking on my branch
    
#### Sat, 1/18/2020
  - Vivian:
    - Fixed the issue with the blackspace
    - Finally got the wpm calculator to work
    - Added an accuracy calculator as well
    - Successfuly implemented nitros
  - Rachel:
    - Worked on fixing the bug where the data was getting messed up somehow while typing
    - Found out that the bug is actually in strcpy so there's something buggy with the built in function??
#### Sun, 1/19/2020
  - Rachel:
    - Fixed that bug with strcpy by avoiding using it at all and the typing works now
    - Continued trying to integrate pipes into networking
#### Mon, 1/20/2020
  - Steve:
    - Started with networking, incorporated it into the client
    - Successfully made the client send words per minute statistic to the server then to the client.
  - Rachel:
    - Was somewhat successful getting pipes to work with subservers, but running into issues with reading and the program pausing to get data. This was all work done on a separate repo but I added
    - When data is getting written and read from the pipes, the retrieval and writing of data is only successful when the client first connects to the server and sends in its first input, but afterwards client gets stalled and the pipes in the server/subservers receive weird data from previous clients, a seg fault occurs and crashes the server. Clients are left hanging
    - Unable to get pipes to work because program would pause and information would only be read in pipes after a new client has joined for some reason. Couldn't figure out why after being unable to test code because I kept getting the error that address was already in use.
  - Vivian:
    - Tried to deal with data being passed between client and sub-server, but there was an error that didn't allow the game to continue. 
    - Added in a function where the user types in their username before starting the race
    - Tried to implement the use of structs into the communication between the sub-servers and the server but pipes weren't working, so was very unsuccessful
