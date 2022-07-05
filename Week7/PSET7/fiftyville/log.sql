-- Keep a log of any SQL queries you execute as you solve the mystery.

--check out all the tables
.tables
.schema

--check the crime scene report of july 28,2021 on Humphrey Street
SELECT *
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = "Humphrey Street";
--Clue 0: id = 295 , description: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.Three witnesses both their transcript mentions the bakery

--check the interviews of this crime
SELECT *
  from interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND transcript
  LIKE "%thief%";

--Clue 1: 10:15am-10:25, the thief left the bakery parking lot in a car, might check the footage.
--check people left the parking lot at 10:15am-10:25am
SELECT name
  FROM people
 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute > 15
           AND minute <= 25
           AND activity = "exit")
 ORDER BY names;
-- people who left parking lot
-- | Vanessa |
-- | Barry   |
-- | Iman    |
-- | Sofia   |
-- | Luca    |
-- | Diana   |
-- | Kelsey  |
-- | Bruce   |

--Clue 2: The thief withdrawing some money eariler that morning. someone was recognized.
--check the atm_transactions in the eariler moring in july 28, 2021
SELECT name
  FROM people, bank_accounts
 WHERE people.id = bank_accounts.person_id
   AND account_number IN
       (SELECT account_number
          FROM atm_transactions
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND atm_location = "Leggett Street"
           AND transaction_type = "withdraw")
 ORDER BY name;
-- people who withdrawed money in Leggett Street ATM left
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Luca    |

--Clue 3: planning to take the earliest flight out of Fiftyville in july 29, 2021.Accomplice bought the ticket.
--check who bought the eariest flight ticket out of fiftyville

SELECT name
  FROM people
 WHERE passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id IN
               (SELECT id
                  FROM flights
                 WHERE year = 2021
                   AND month = 7
                   AND day = 29
                   AND origin_airport_id IN
                       (SELECT id
                          FROM airports
                         WHERE city = "Fiftyville")
                 ORDER BY hour
                 LIMIT 1))
 ORDER BY name;
-- people who bought the first flight out of Fiftyville left
-- | Bruce   |
-- | Luca    |

--Clue 4: 10:15am or later,The thief called someone for less than a minute
--check phone_calls

SELECT name
  FROM people
 WHERE phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration < 60)
 ORDER BY name;
-- people who called someone for less than a minute
-- | Bruce   | That's the thief!!!!

--get the imformation of Bruce
SELECT *
  FROM people
 WHERE name = "Bruce";

 --id:686048 name:Bruce phone_number: (367) 555-5533 passport_number: 5773159633 license_plate: 94KL13X

-- get The city the thief ESCAPED TO
SELECT city
  FROM airports
 WHERE id IN
       (SELECT destination_airport_id
          FROM flights
         WHERE year = 2021
           AND month = 7
           AND day = 29
           AND id IN
                (SELECT flight_id
                   FROM passengers
                  WHERE passport_number = 5773159633));

-- New York City

-- get the accomplice
SELECT name
  FROM people
  WHERE phone_number IN
        (SELECT receiver
           FROM phone_calls
          WHERE caller = "(367) 555-5533"
            AND year = 2021
            AND month = 7
            AND day = 28
            AND duration < 60)

-- Robin