# ByteType
By Vivian Huynh (4), Rachel Leong (10), Steve Wang (10)

### Description
  We are attempting to create a type-racing game, modeled after the game NitroType which you can find and play at nitrotype.com. To play, up to 4 players will join a game. The “race host” has the option to start when everyone is ready by pressing a button. After a short delay, users will type a paragraph of text selected randomly from a database as fast, and accurately as they can before the other players finish. Each player (not including bots) is given a boost that players can use once per game to skip a word. Statistics like words per minute and accuracy as well as positions will be displayed in real time. 

### User Interface
  Users will be able to log onto separate computers and sync up in order to start a race. When players connect, their names will appear on the screen for all players connected and the “race host” who created the race will have the option to start. Before the race officially starts, a short delay is given to prepare everyone to get ready. During the race, players will have to type a paragraph of text displayed at the bottom of the screen as quickly and accurately as possible. While typing, there will be an indicator showing what the player has already typed. If the player makes a mistake, the indicator will stay in place until the player types the correct character. Players can also see the positions of all racers with a progress bar and who is currently in first place. A words per minute statistic (number of characters typed divided by 5 divided by the total time spent typing) and accuracy percentage are calculated for each player and those individual values are shown and updated to each player during the course of the race. Players can also skip a word by hitting the Enter key and using a boost to skip the current word. 
  
During the race, players will be able to see everyone’s progress on a progress bar. The race will end when the last person finishes typing. There will be a words per minute statistic and an accuracy percentage are calculated and displayed for everybody at the end of each race and those that finish before others have will need to wait for everyone to finish before seeing all statistics. When players finish racing, they are given the options to race again or quit.

### Topics
  We will incorporate networking, signals, files, processes, and pipes. Networks will be used to communicate statistics and real-time positions between players on different computers. Signals will be used to stop and exit the game. Text files will store a selection of paragraphs to be randomly chosen for players to type. Multiple child processes will be used to calculate statistics as the race is going on. Pipes will be used to transfer information about real time progress from child processes to parent as the race is going on.

### Work Break-Down

### Data Structures
We will use arrays of strings to provide the paragraphs typed during the game, which each string being a separate character to allow for easy iteration of user inputs for the game.

### Timeline
1/2 - start work on the project upon approval. Start work on the logistics of the game, such as the database of paragraphs and the typing inputs.

1/6 - Start implementing the basic shell prompts and inputs to set up a network connection and continue working on logistics.

1/10 - debug everything completed so far and continue work on the game. 

1/15 - have everything completed to allow two days for final debugging.
