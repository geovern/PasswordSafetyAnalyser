# _Password Safety Analyser_

> Input a password and learn about its strength, unpredictability 
> and security against Dictionary and Bruteforce attacks.

---

## Features:

- Strength calculation using casing, length and special symbols as metrics
- Unpredictability for human generated passwords measured using [Shannon Entropy](https://en.wikipedia.org/wiki/Entropy_(information_theory)) 
- [Password Entropy](https://www.pleacher.com/mp/mlessons/algebra/entropy.html) for randomly generated passwords
- Test against Dictionary attacks using a [list of 10M common passwords](https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/Pwdb_top-10000000.txt)
- Bruteforce time estimation (1 Billion guesses/sec)


## Deep Dive:

### Strength Calculation:

Password Strength is calculated by adding 1 point to it for every metric, the metrics being:
<br>    
- Contains at least 8 characters
- Contains lower case letters
- Contains upper case letters
- Contains numbers
- Contains special symbols

So the minimum strength seen is 1 and the maximum is 5. This could be seen more as a vast simplification of Password entropy than an actual metric of password strength.


### Entropy:


#### Password Entropy

Password Entropy measures the _total uncertainty in the whole password_, assuming a random choice from a known set. It is calculated with the following formula:

```math
E = L \times \log_2(R)
```

$$E$$: Password Entropy (in bits)     
$$L$$: Number of characters in password    
$$R$$: Possible range of character types in your password    
$$\log_2$$: logarithm used to express entropy in bits    

For example: 

 - Input: Hello
 - Range = 52 -> all lower and upper case characters
 - Length = 5

```math
E = 5 \times \log_2(52) = 28.5 bits
```

The following blog post from [Proton](https://proton.me/blog/what-is-password-entropy) was used as reference for the password safety standards of password entropy included in the code.

## 

#### Shannon Entropy

Shannon Entropy measures _uncertainty per symbol_ based on actual character frequency, calculated using the following formula:

```math
H(X) = - \sum_{i=1}^{n} P(x_i) \log_2 P(x_i)
```

$$H(X)$$: Shannon Entropy of password X (in bits)    
$$P(x_i)$$: Probability occurrence of character $$x_i$$ in X     
$$n$$: Number of unique characters    
$$\log_2$$: logarithm used to express entropy in bits    

I will not be providing an example of the Shannon Entropy calculation since it would take too long to calculate the probabilities of all password characters and sum them up by hand. But this is a code snippet of how it is calculated:

```cpp
double entropy(const char* input) {
    std::string s(input);
    std::unordered_map<char, int> freq;

    for (char c : s)
        freq[c]++;

    double sEntropy = 0.0;
    int len = s.size();
    for (const auto& p : freq) {
        double f = (double)p.second / len;
        sEntropy -= f * (log2(f));
    }

    return sEntropy * len; // multiplying with length to get entropy in bits
}
```

<br>    

The above code snippet is a simplified example of the Shannon entropy calculation. In reality both entropies are calculated in the same function and returned as a std::pair.        

The following document from [RFC editor](https://www.rfc-editor.org/rfc/rfc4086) served as reference for the password safety standards of shannon entropy included in the code. Shannon entropy is not widely used in password security estimations and research is limited, so no true standard of security exists.    


Entropy, in general, can not provide a standard of password security due to [Moore's Law](https://en.wikipedia.org/wiki/Moore%27s_law) (2/3 bits would have to be added every year to maintain password security standards, [RFC4086](https://www.rfc-editor.org/rfc/rfc4086#section-8.2.1)) and the varying resistance to cracking attacks shown between passwords of the same (Shannon)entropy value presented in this [blog](https://reusablesec.blogspot.com/2010/10/ccs-paper-part-2-password-entropy.html).
<br>

Disclaimer: Not all references provided are peer-reviewed or academically "valid". This is just a side project, not to be used as an actual tool for determining password security.

### Bruteforce Time Estimation

The BTE was made using the following equation:    

```math
\text{Estimated Time (seconds)} = \frac{\text{Combinations}}{\text{Guesses Per Second}}, \text{where}
```
<br> 

```math
\text{Combinations} = (\text{Character type range})^{(\text{Password Length})}
```


```cpp
    int length = strlen(input); //length of password
	long double totalGuesses = pow(range, length); // combinations
	double guessesPerSec = 1e9; // assuming 1B guesses/sec
	long double seconds = totalGuesses / guessesPerSec; //estimated time
    
    (...)
```   

## To-Do

 - Cmake
 - Docker for dependency installation
 - Do dictionary attack simulation with JtR or Hydra instead of my own implementation, using fork,exec,pipe
 - Possible HaveIBeenPwd API implementation
 - Suggest stronger passphrase alternatives if a password is weak(a -> @, E -> 3, maybe use $random bash cmd and fork/exec to get random additions to the code if no nums are used)


