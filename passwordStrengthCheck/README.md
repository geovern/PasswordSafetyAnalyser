# _Password Strength Checker_


This project is a CLI program written in C++(started it in C). You input a password and it calculates strength/safety with various metrics (length, special characters, etc.), Shannon and Password Entropy. It also checks if it is in a list of common passwords and provides a bruteforce time estimation using John the Ripper.

---

## Features:

- Strength calculation using casing, length and special symbols as metrics
- Unpredictability for human generated passwords measured using [Shannon Entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) 
- [Password Entropy](https://www.pleacher.com/mp/mlessons/algebra/entropy.html) for randomly generated passwords
- Test against Dictionary attacks using a [list of 10M common passwords](https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/Pwdb_top-10000000.txt)
- Bruteforce time estimation using John the Ripper

## Deep Dive:

<h3>Strength Calculation</h3>
<br />
Password Strength is calculad by adding 1 point to it for every metric, the metrics being:
- Contains at least 8 characters
- Contains lower case letters
- Contains high case letters
- Contains numbers
- Contains special symbols

So the minimum strength seen is 1 and the maximum is 5.

<br />

___

<h4>Entropy</h4>

<h5>Password Entropy</h5>

blah blah, sources and code snippets

<h5>Shannon Entropy</h5>

Shannon Entropy measures uncertainty per symbol based on actual character frequency, calculated using the following formula:

https://wikimedia.org/api/rest_v1/media/math/render/svg/ff26f81edc1f4bb204793a52b2430c77f6633203

## To-Do

 - John the Ripper time estimation
 - Do dictionary attack simulation with JtR or Hydra instead of my own implementation
 - Possible HaveIBeenPwd API implementation
 - Git LFS for large password file
 - Cmake(what does the build even do) or how to curl project from github

Written on Dillinger
