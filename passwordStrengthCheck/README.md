# _Password Strength Checker_


This project is a CLI program written in C++(started it in C). You input a password and it calculates strength/safety with various metrics (length, special characters, etc.) and Shannon Entropy. It also checks if it is in a [list of common passwords](https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/Pwdb_top-10000000.txt) and provides a bruteforce time estimation using John the Ripper.


## Features:

- Strength calculation using (casing, length and special charactes)
- Unpredictability for human generated passwords measured using [Shannon Entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) 
- [Password Entropy](https://www.pleacher.com/mp/mlessons/algebra/entropy.html) for randomly generated passwords
- Bruteforce time estimation using John the Ripper

## Deep Dive:

<h3>Strength Calculation</h3>
Password Strength is calculad by adding 1 point to it for every metric, the metrics being:
- Contains at least 8 characters
- Contains lower case letters
- Contains high case letters
- Contains numbers
- Contains special symbols

So the minimum strength seen is 1 and the maximum is 5.

<br />

<h3>Entropy</h3>


## To-Do

 - John the Ripper time estimation
 - Do dictionary attack simulation with JtR or Hydra instead of my own implementation
 - Possible HaveIBeenPwd API implementation
 - Git LFS for large password file
 - Cmake(what does the build even do) or how to curl project from github

Written on Dillinger
