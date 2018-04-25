#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>

long long findNextPrime(long long n);   //given a number n, find the next prime number above n
bool isPrime(long long n);        //given a number n, determine if it is prime
bool isPermutablePrime(long long n);
std::vector<long long> firstPPrimes(int n);

std::map<int, bool> checkedPrimes;
std::map<int, bool> checkedPermutablePrimes;


//given a number n, find the next closest prime number above n
long long findNextPrime(long long n) {
  long long nextPrime = n;
  bool found = false;

  if (nextPrime == 1) {
    return 2;
  }

  if (nextPrime % 2 == 0) {
    nextPrime++;
  } else {
    nextPrime += 2;
  }
  //loop continuously until isPrime returns true for a number above n
  while (!found) {
      if (isPrime(nextPrime)) {
	found = true;
      } else {

	nextPrime += 2;
      }
    }

  return nextPrime;
}

bool isPrime(long long number) {

    if (number == 2 || number == 3)
        return true;

    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }

    long long divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {

      if (number % (divisor - 1) == 0) {
	return false;
      }

      if (number % (divisor + 1) == 0) {
            return false;
      }
      divisor += 6;

    }

    return true;

}

long long nextPossible(long long prime) {
  int num;

  std::string digits = std::to_string(prime);
  bool changed = false;
  if (prime > 9) {
    for (char& d : digits) {
      if (changed) {
	d = '0';
      }

      num = (int)d - '0';

      if (num % 2 == 0) {
	d += 1;
	num += 1;
	changed = true;
      }

      if (num == 5) {
	d += 2;
	changed = true;
      }


    }
  }

  return findNextPrime(std::stoll(digits) - 1);
}

std::vector<long long> firstPPrimes(int n) {
  std::vector<long long> permutablePrimes;
  long long prime = 2;
  bool isPPrime;
  bool test;
  int j = 0;

  long long nextPos;

  for (int i = 0; i < n;) {

    nextPos = nextPossible(prime);
    while (prime != nextPos) {
      prime = nextPossible(prime);
      nextPos = nextPossible(nextPos);
    }

    j++;
    if (j % 10000 == 0) {
      std::cout << prime << std::endl;
    }
    if (checkedPermutablePrimes.count(prime) > 0) {
      test = checkedPermutablePrimes[prime];
    } else {
      test = isPermutablePrime(prime);
      checkedPermutablePrimes.insert(std::pair<int, bool> (prime, test));
      }

    if (test) {
      permutablePrimes.push_back(prime);
      i++;
    }

    prime = findNextPrime(prime);
  }

  return permutablePrimes;
}

bool isPermutablePrime(long long n) {
  //  std::vector<int> digits;
  std::string digits = std::to_string(n);

  int num;
  if (digits.length() > 1) {
    for (char& d : digits) {
      num = (int)d - '0';
      if (num != 1 && num != 3 && num != 7 && num!= 9) {
	return false;
      }
    }
  }

  // digits will be in reverse order, but doesn't matter
  // while (n > 0) {
  //   digits.push_back(n % 10);
  //   n /= 10;
  // }
  std::sort(digits.begin(),digits.end());

  bool isPPrime = true;
  long long p;

  bool test;
  do {
    // p = 0;
    // for (int d : digits) {
    //   p += d;
    //   p *= 10;
    // }
    // p /= 10;

    p = stol(digits);

    if (checkedPrimes.count(p) > 0) {
      test = checkedPrimes[p];
    } else {
      test = isPrime(p);
      checkedPrimes.insert(std::pair<int, bool> (p, test));
    }
    if (!test) {
      isPPrime = false;
    }
  } while (std::next_permutation(digits.begin(), digits.end()) && isPPrime);
  if (isPPrime) {
    return true;
  }

  return false;
}

int main(int argc, char* argv[]) {
  std::cout << "Choose an option (0 - first n pprimes, 1 - check if pprime): ";
  int o;
  std::cin >> o;
  if (o == 0) {
    std::cout << "Get first n permutable primes: ";
    int n;
    std::cin >> n;

    std::vector<long long> permPrimes = firstPPrimes(n);
    for (long long p : permPrimes) {
      std::cout << p << std::endl;
    }

  } else {
    std::cout << "Prime to check if permutable next possible: ";
    long long n;
    std::cin >> n;


    std::cout << nextPossible(n) << std::endl;
  }

}
