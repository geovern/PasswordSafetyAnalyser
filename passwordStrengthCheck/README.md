# _Password Strength Checker_


This project is a CLI program written in C. You input a password and it calculates strength/safety with various metrics (length, special characters, etc.) and Shannon Entropy. It also checks if it is in a [list of common passwords](https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/Pwdb_top-10000000.txt) and provides a bruteforce time estimation using John the Ripper.


## Features

- Strength calculation using (casing, length and special charactes)
- Password randomness measured using [Shannon Entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) 
- Bruteforce time estimation using John the Ripper

## To-Do
 - Shannon Entropy using Map
 - Hydra Implementation
 - Possible HaveIBeenPwd API implementation
 - ANSI Colored Output
 - Git LFS for large password file

Written on Dillinger
