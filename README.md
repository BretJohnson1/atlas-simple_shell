# The Simple Shell Project

Now the question

## What is a Simple Shell? And more importantly what is *OUR* Simple Shell?

A simple shell "simply" is a way for a user to interact with the UNIX system and and execute commands.

Usually a terminal thats pre-installed comes with a shell, but as that one was created, We can create one too and so we __HAVE__.

# What our Simply Shell is capable of

As of now our Shell...

* Prompts the user
	The shell will initalize itself replicating paths and enviroments.
	If it fails it will free the memory of the input and flush out the nonsense, returning a "$" ready for another input.

* Executes (Things)
	Our shell can execute alot of the basic commands but also execute and executable file we may want to execute.
	The shell is also capable of executing files from _Outside_ its active state with out prompting the user.
	This means we can quickly view things from inside the child process or from out.

* Handling input
	The shell has State of the Scribblings *String Parsing* techonology and can very simply parse a string,
	find spaces or commas and seperate them to effectively find tokens (arguments) to act on.

*