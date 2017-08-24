/*
 Thought process behind this approach:
 
 After thinking about it, I realized that this task can be broken down into a few steps.  Each time a '/' character appears, I should treat the chunk just before that as a discrete unit.  That is, if the string in question is office/julie/1233/turtle, I should use '/' as a flag and look at "office" as one section, "julie" as another, etc.
 
 So what I do is take both strings, see which one is longer, and create two identical "NULL" strings of that length.  For each loop, I go through and fill that NULL string with characters until the '/' flag pops up.  At that point, I compare the two strings.  If they are identical, I consider that chunk "confirmed", clear the NULL strings back to NULL, and move on to the next chunk.
 
 But there are situations that can trigger the end of the loop.  If the chunks aren't identical, I then check to see if there was a '+' flag or a '#' flag.  If the '+' flag shows up, I consider them to be identical.  If the '#' flag shows up, and everything up until that point has been confirmed as identical, I end the loop and return "true".  However, if they're just not identical and neither the '+' or '#' flags showed up, I terminate the loop with a "false".
 
 This function is comprised mainly of one giant "while" loop:  "while nothing triggers an immediate end, keep looping though and comparing".  The basic until of this while loop are the "chunks".  It loops through to get a chunk from the topic (i.e. everything up until the next '/'), and does the same for the pattern.  Once it has both, it compares them.  If everything matches (or if there are flags that imply a match), it loops again.  The default return value is 'true', so if everything keeps matching, the function will just return true. However, there are situations that trigger a false return: if the chunks don't match, the default switches to 'false', so unless something like a '+' flag override the false and switch the default back to true, the loop will terminate end return false.
 
 There are a lot of different ints in here.  Since the strings could be different lengths (because '+' and '#' take up much less room than most full words), so I had to keep track of most things seperately.  Topic and Pattern loops have their own counters, resets, etc.
 
 */

#include <iostream>
using namespace std;

bool checkTopic (string topic, string pattern)  //function for checking to see if pattern and topic match
{
    //list of variables and initializations
    
    bool checkBool = true; //bool for returning
    bool loopBool = true;  //keeps loop going.  If something triggers a 'false' loopBool, loop will end
    int topicLength = topic.length();  //int for length of topic string
    int patternLength = pattern.length();   //int for length of pattern string
    int topicCounter = 0;  //keeps track of times through each individual topic loop
    int patternCounter = 0;  //keeps track of times through pattern loop
    bool flagBoolTopic = true;  //flags for when the '/' character is hit...
    bool flagBoolPattern = true;  //...which triggers a string comparison
    int topicOverallCounter = 0;  //keeps track of total times through the loop, and therefore position in the string
    int patternOverallCounter = 0;  //same for pattern
    int topicResetCounter = 0;  //this resets each time through, so that I'm always filling in a string from the zeo position
    int patternResetCounter = 0;  //same for pattern
    int topicSpace = 0;  //keeps track of position in the topic string. Initializes at the beginning of each loop through (i.e. after each comparison)....
    int patternSpace = 0; //...so that when it fills in a string, it starts where it last left off
    string topicCheck;  //holds topic string
    string patternCheck;  //holds pattern string
    int topLength;  //keeps track of the length of the longer string
    bool plusBool = false;  //check to see if a + is found
    bool hashBool = false;  //check to see if a # is found
    
    
    /*
     This section essentially gives me one int to work with, which will be the length of the longer of the two strings, and sets both 'holder' strings to that length, and my "topLength" int to that length.
     */
    
    
    if (patternLength > topicLength)
    {
        topicCheck = pattern;   //sets this 'holder' string to appropriate length
        patternCheck = pattern;  //sets this h'holder' string to appropriate length
        topLength = patternLength;
    }
    
    else if (patternLength == topicLength)
    {
        topicCheck = topic;   //sets this 'holder' string to appropriate length
        patternCheck = pattern;  //sets this h'holder' string to appropriate length
        topLength = patternLength;
    }
    else
    {
        topicCheck = topic;   //sets this 'holder' string to appropriate length
        patternCheck = topic;  //sets this h'holder' string to appropriate length
        topLength = topicLength;
    }
    
    
    
    while (loopBool == true)  //keeps loop going until something triggers a false loopBool (i.e. when the function should end: if there is a hash, or if the input ends)
    {
        
        
        topicSpace = topicOverallCounter;  //at the very beginning of each time through, set the 'space' int to the counter.  This ensures that there is a record of where to start after each comparison
        patternSpace = patternOverallCounter;  //same for pattern.
        
        
        
        /*
         These next two loops iterate through the holder strings and set all the spaces to NULL
         */
        
        for (int i = 0; i < topLength; i++)
        {
            topicCheck[i] = NULL;
        }
        
        for (int i = 0; i < topLength; i++)
        {
            patternCheck[i] = NULL;
        }
        
        //both topicCheck and patternCheck should be comprised entirely of NULL characters at this point.

        
        
        while (flagBoolTopic == true && topicOverallCounter < topicLength+1)  //interates through topic
        {
            char currentT = topic[topicOverallCounter]; //current topic char, sets to 'next' string position
            
                if (currentT == '+')  //checks to see if it's a +
                {
                    plusBool = true;  //and sets this bool
                }
            
            if (currentT == '#')  //check for a #
            {
                hashBool = true;  //and triggers this bool
            }
            
            
                if (currentT == '/' or topicOverallCounter == topicLength)  //using '/' as a flag:  feeding everything prior to this flag into a string
                {
                    for (int i = topicSpace; i < topicOverallCounter; i++)  //if the flag comes up, this puts all topic characters from the last "chunk" into topicCheck string
                    {
                        topicCheck[topicResetCounter] = topic[i];  //topicCheck starts at zero, but topic picks up where it left off
                        topicResetCounter++;  //and resetCounter adds to keep things moving
                    }
                    
                    flagBoolTopic = false;  //and then this switches, to alert that no more loop is needd right now and it's time for a comparison
                    
                }
            
            topicCounter ++;  //these counter keep track of how many loops have happened in this chunk, and
            topicOverallCounter++;  //how many loops overall.
            
        }
        
     /* 
    This loop is the same as for topic, but with its own independent counters.  This is because the topic chunk may be any number of characters, but this may only be one: '+' or '#'.  So pattern and topic have seperate trackers, but essentially do the same thing:  Start where it left off last time, and feed everything up until the next '/' (or the end) into a string for comparison.
      
      */
        
         while (flagBoolPattern == true && patternOverallCounter < patternLength+1)  //interates through pattern
         {
             char currentP = pattern[patternOverallCounter]; //current pattern char
             
                if (currentP == '+') //checks for flags
                {
                    plusBool = true;
                }
             
                if (currentP == '#')  //checks for flags
                {
                 hashBool = true;
                }
             
                if (currentP == '/' or patternOverallCounter == patternLength)  //using '/' as a flag:  feeding everything prior to this flag into a string
                {
                    for (int i = patternSpace; i < patternOverallCounter; i++)
                    {
                        patternCheck[patternResetCounter] = pattern[i];  //sets patternCheck string
                        patternResetCounter++;
                    }
         
                    flagBoolPattern = false;  //ends loop once chunk has been obtained
         
                }
         
             patternCounter ++;  //and has its own seperate loop trackers, that are used for the same purposes.
             patternOverallCounter++;
         
         }
        
        
        
        
        /*
         At this point, there should be two new strings:  topicCheck and patternCheck, and they will be comprised of the characters up until the next '/' character in the string (depending on where in the string they are currently). They will either be identical, in which case nothing has gone wrong YET, or different, in which case the loop may as well just end--UNLESS they are different because of the '+' or '#' flags.  This next loop will check these things.
         */
        
        
        while (flagBoolTopic == false or flagBoolPattern == false)  //if neither is false, then no '/' character was hit
        {
            if (patternCheck != topicCheck)  //this compares the two strings
            {
                loopBool = false;  //if they're not identical, the default is to end the loop with 'false'
                checkBool = false;  //and return false
                
                
                if (hashBool == true)  //but if a '#' flag shows up....
                {
                    loopBool = false;  //the loop can end with true.
                    checkBool = true;  //because if it got to this point, everything before now is identical
                }
                
                if (plusBool == true)  //and if there's a '+' flag, the program keeps going
                {
                    loopBool = true; //because there may be more to check
                    checkBool = true;  //but it switches the return bool back to a 'true' default
                    plusBool = false;  //and then switches the plus marker back for next time
                }
                
            }
            
            
            flagBoolPattern = true;  //resets bool for next loop
            flagBoolTopic = true;  //resets bool for next loop
            patternCounter = 0;  //resets these back to zero
            topicCounter = 0;
            
            
        }
        

        if ((topicOverallCounter >= topicLength) && (patternOverallCounter >= patternLength))
        {
            loopBool = false;  //this triggers the loop ending once there is no more data
        }
        
        topicResetCounter = 0;
        patternResetCounter = 0;
        topicCounter = 0;  //and these loops basically just reset everything once each loop.
        patternCounter = 0;
    }
    
    
    return checkBool;  //returns "answer"
}




int main() {

    //TEST A: should return TRUE
    
    string a = "al/bx/to/penny/green/elephant/yellow";
    string b = "al/+/to/+/green/#";
    
    bool testBoolA = checkTopic(a,b);
    
    
    if (testBoolA == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }
    
    
    
    //TEST B: should return FALSE
    
    string c = "al/bx/to/penny/green/elephant";
    string d = "al/+/to/+/green";
    
    bool testBoolB = checkTopic(c,d);
    
    
    if (testBoolB == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }
    
    
    //TEST C: should return FALSE
    
    string e = "al/";
    string f = "al/+/to/+/green";
    
    bool testBoolC = checkTopic(e,f);
    
    
    if (testBoolC == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }

    
    //TEST D: should return TRUE
    
    string g = "al/julie/to/quadratic/green/";
    string h = "al/+/to/+/green";  //the lack of '/' at the end doesn't affect things
    
    bool testBoolD = checkTopic(g,h);
    
    
    if (testBoolD == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }

    
    //TEST E: should return TRUE
    
    string i = "al/julie/to/quadratic/green/knapsack/elephant";
    string j = "al/+/#";
    
    bool testBoolE = checkTopic(i,j);
    
    
    if (testBoolE == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }

    
    
    //TEST F: should return FALSE
    
    string k = "al/bx/to/penny/green/elephant";
    string l = "al/bx/to/ponny/green/elephant";  //"penny" is misspelled
    
    bool testBoolF = checkTopic(k,l);
    
    
    if (testBoolF == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }

    
    //TEST G: should return TRUE
    
    string m = "candykettlezebra";  //check without any flags being hit
    string n = "candykettlezebra";
    
    bool testBoolG = checkTopic(m,n);
    
    
    if (testBoolG == true)
    {
        cout << "True!" << endl;
    }
    else
    {
        cout << "False!" << endl;
    }

    
    return 0;
}
