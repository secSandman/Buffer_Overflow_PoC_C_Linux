# Buffer_Overflow_PoC_C_Linux

This tutorial started as a simple attempt to take notes and follow my curiosity on C programming, Assembly and Buffer Overflows work. Don’t take anything here as gospel because the content was written by a high-school drop-out without any formal computer science background. If you find something wildly wrong then let me know. From what I can tell, overall this work is directionally accurate.  The PoC and much of the content is compiled and inspired from various CTFs, Online Videos, UPENN, Renseller, Blackhat presentations, exploit researchers on exploit-db and more.  

This entire paper looks at security from the perspective of someone who needs to learn from the ground up. All the tutorials and blogs on Buffer Overflows either show a basic “Input data here” C program or use well known vendor products. There little mention on the C programming language or the memory protections within. There is little mention of the pain of taking pre-compiled binaries that you did not write and attempting of fuzz it, reverse engineer it and understand it before throwing your garbage at the program. 

Most tutorials dive straight into intimidating debuggers GUIs without starting in a simple GDB screen never forcing the user to think about what they need to see. All the blogs, tutorials and training tells you to disable modern memory and stack protections without explaining the critically of them and the difficulty of developing a successful exploit in the modern world. And there is little interdisciplinary mention of implementing the protective and detective technology that relates to the buffer overflow.  

All this leaves the technology new-comer wildly unprepared or the least blissfully ignorant, including myself. In the unlikely chance that someone starting their career stumbles upon this paper online, I hope you find that it is historically as useless as the papers and tutorials that came before it. I hope it inspires you to learn more and build upon and correct it. There is no money involved here, no corporate sponsorship, no edu homework or anything like that. Just someone who loves learning who wrote it all down.  

If your foolish or bored enough to go any further, what will you find? 

Basics of C Socket programming <br /> 
C Socket program code w/ Inline comments on how to write a Socket program in C <br />
Basic fuzzer development in Python <br />
Basic of reverse engineering pre-compiled Binaries found online with NSA GHIDRA <br />
Basics of using GBD and EDB debuggers <br />
Intro material on x86 Assembly and Memory <br />
Crashing the Stack (Buffer Overflow PoC) <br />
Static Analysis of Insecure Functions in C <br />
Basics on the Mitigations to Buffer Overflows <br />
Basics on Bypassing Buffer Overflow Mitigations <br />
Basics on Detecting Buffer Overflows and Post exploit activity <br /> 

