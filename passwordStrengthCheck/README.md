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

Password Strength is calculad by adding 1 point to it for every metric, the metrics being:
<br>
- Contains at least 8 characters
- Contains lower case letters
- Contains high case letters
- Contains numbers
- Contains special symbols

So the minimum strength seen is 1 and the maximum is 5.


<h3>Entropy</h3>

<h4>Password Entropy</h4>

blah blah, sources and code snippets

```math
E = L \times \log_2(R)
E: \text{Password Entropy (in bits)} \\
L: \text{Length of the password (number of characters)} \\
R: \text{Size of the character set (number of unique possible characters)} \\
\log_2: \text{Base-2 logarithm (used to express entropy in bits)}
```

<h4>Shannon Entropy</h4>

Shannon Entropy measures uncertainty per symbol based on actual character frequency, calculated using the following formula:

```math
H(X) = - \sum_{i=1}^{n} P(x_i) \log_2 P(x_i)
H(X): \text{Shannon Entropy of the random variable } X \\
P(x_i): \text{Probability of the } i\text{-th outcome } x_i \\
n: \text{Number of possible outcomes} \\
```

The above code snippets are a simplified example of the entropy calculations. In reality both entropies are calculated in the same function and returned as a std::pair<double, double>.

## To-Do

 - John the Ripper time estimation
 - Do dictionary attack simulation with JtR or Hydra instead of my own implementation
 - Possible HaveIBeenPwd API implementation
 - Git LFS for large password file
 - Cmake(what does the build even do) or how to curl project from github

Written on Dillinger
