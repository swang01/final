# ByteType
By Vivian Huynh (5), Rachel Leong (10), Steve Wang (10)

### Description
  We are attempting to create a type-racing game, modeled after the game NitroType which you can find and play at nitrotype.com. To play, up to 4 players will join a game. The “race host” has the option to start when everyone is ready by pressing a button. After a short delay, users will type a paragraph of text selected randomly from a database as fast, and accurately as they can before the other players finish. Each player (not including bots) is given a boost that players can use once per game to skip a word. Statistics like words per minute and accuracy as well as positions will be displayed in real time. 

### User Interface
  Users will be able to log onto separate computers and sync up in order to start a race. When players connect, their names will appear on the screen for all players connected and the “race host” who created the race will have the option to start. Before the race officially starts, a short delay is given to prepare everyone to get ready. During the race, players will have to type a paragraph of text displayed at the bottom of the screen as quickly and accurately as possible. While typing, there will be an indicator showing what the player has already typed. If the player makes a mistake, the indicator will stay in place until the player types the correct character. Players can also see the positions of all racers with a progress bar and who is currently in first place. A words per minute statistic (number of characters typed divided by 5 divided by the total time spent typing) and accuracy percentage are calculated for each player and those individual values are shown and updated to each player during the course of the race. Players can also skip a word by hitting the Enter key and using a boost to skip the current word. 
  
During the race, players will be able to see everyone’s progress on a progress bar. The race will end when the last person finishes typing. There will be a words per minute statistic and an accuracy percentage are calculated and displayed for everybody at the end of each race and those that finish before others have will need to wait for everyone to finish before seeing all statistics. When players finish racing, they are given the options to race again or quit.

### Topics
  We will incorporate networking, signals, files, processes, and pipes. Networks will be used to communicate statistics and real-time positions between players on different computers. Signals will be used to stop and exit the game. Text files will store a selection of paragraphs to be randomly chosen for players to type. Multiple child processes will be used to calculate statistics as the race is going on. Pipes will be used to transfer information about real time progress from child processes to parent as the race is going on.

### Work Break-Down
- Take real-time input as the race is going on (single computer level and then expand into networking (Rachel and Steve)
  - Create database of paragraphs to type (Steve)
    - Randomly select a paragraph
    - Function to find the number of characters in the paragraph for statistics
  - Test user input against source text and store that information to determine... (Rachel)
    - Real-time progress (% completion)
    - Position relative to other players
    - Words per minute
    - Accuracy
    - Allowing skipping a word using "Enter" key once per player per race
- User Interface (Vivian)
  - Display paragrah typed and an indicator of where the player has typed up to
  - Display statistics
  - Names of players/how to display them
  - Functions for starting and exiting a race (using signals)
  - User input (typing)
- Connect players through networking (All of us)
  - Connect computers to make a "room" to race in
  - Create options to start and exit race
  - Transfer data from computers in real time during the race
- Additional features if posssible:
  - Bots
  
### Data Structures
We will use arrays of strings stored in a shared text file to provide the paragraphs typed during the game and iterate through a selected string, character by character as the players type, allowing for easy iteration of user inputs for the game.

### Algorithms/Processes
We will need a process to access a shared text file that contains the passages to type and randomly selects one to type. Another process will be taking user-input in real time and testing that against the source text to calculate and update statistics and progress. There is also the user interface aspect where the text, statistics, and real-time progress are displayed while user input is being used. Finally these processes will be integrated when we use networking to connect computers and transfer data between them. 

### Timeline
Thursday 1/2: Start work on the logistics of the game, such as the database of paragraphs and functions for randomly selecting passages, typing inputs, and displaying progress of typing.

Sunday 1/5: Start work on user interface and finish functions for calculating statistics. 

Tuesday 1/6: Typing processes, including calculating statistics, should be finished. Begin integrating user interface with these processes and shared memory and hopefully networking. 

Friday 1/10: Work with the shared file (source file of passage) should be about done. If work on networking hasn’t started, start.

Monday 1/13: Multiple computers should be able to race simultaneously. Work out kinks in shared memory to make sure racing can occur in real time.

Wednesday 1/15: Project should be done, last-minute debugging and adding addition features if possible

