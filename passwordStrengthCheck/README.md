# Password Strength Checker
## _utilizing Shannon Entropy, common password checks_
## _and Bruteforce time estimation using Hydra_


>This project is a CLI program written in C. You input a password and it calculates strength/safety with various metrics (length, special characters, etc.) and Shannon Entropy. It also checks if it is in a [list of common passwords](https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/Pwdb_top-10000000.txt) and provides a bruteforce time estimation using Hydra.


## Features

- Strength calculation using (casing, length and special charactes)
- Password randomness measured using [Shannon Entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) 
- Bruteforce time estimation using [Hydra](https://www.kali.org/tools/hydra/)

## To-Do
 - Shannon Entropy using Map
 - Hydra Implementation
 - Possible HaveIBeenPwd API implementation
 - ANSI Colored Output
