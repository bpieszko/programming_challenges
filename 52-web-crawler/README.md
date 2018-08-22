# Web-crawler

## Email-crawler
### Details
Web-crawler type to collect email addresses.
### Compile
```
g++-7 --std=c++17 -o email_crawler email_crawler.cpp
```
### Using
```
./email_crawler [url] [depth]
eg.:
./email_crawler www.panoramafirm.pl/szukaj?k=notariusz 2
```

## Phone-crawler
Web-crawler type to collect phone addresses.
**IMPORTANT** - weak phone number regex.
### Compile
```
g++-7 --std=c++17 -o phone_crawler phone_crawler.cpp
```
### Using
```
./phone_crawler [url] [depth]
eg.:
./phone_crawler www.panoramafirm.pl/szukaj?k=notariusz 2
```