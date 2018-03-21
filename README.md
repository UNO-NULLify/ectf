# NULLify eCTF 2018 Documentation
  As a general approach, we modified the insecure example rather then starting from scratch. Details on changes to each component are below.

  The high-level flow of a typical transaction is the following:
  ```
  - a transaction is initiated on the atm_interface (XMLRPC)
  - the users card_id retrieved from the card and sent to the Bank by the atm (https/json)
    - The bank generates a 32 byte challenge for the card to "sign"
    - the mongoDB document for that account is updated with the challenge, and an expire time for the challenge (5 seconds)
    - the bank sends back the challenge
  - the card is sent the challenge by the atm
    - the card uses its unique AES_KEY to encrypt the challenge
    - the card sends the encrypted bytes back to the atm
  - the encrypted response, pin and other necessary transaction data is sent to the Bank (https/json)
  - The bank verifies the encrypted response and pin, and completes the transaction if is valid.
    - An encrypted response is valid if it:
      - is given within 5 seconds of when the challenge was requested.
      - The bank can use the saved AES_KEY to decrypt the encrypted_challenge and verify it is the same as the unencrypted challenge stored in the accounts mongoDB document.
```

## HSM and Bank Card Changes
1. Both the HSM and the Bank use static hardware values and SuperFastHash to generate a 32 byte AES key. This is stored on the bank at provision time.
2. Every time a transaction is initiated, the card receives a challenge, and "signs" it with its AES key. The bank verifies this since the AES_KEY is on the bank as well.
3. Whenever a withdraw is initiated, the bank will send a 64 byte encrypted message. This message is encrypted with the HSMs AES_KEY. The format of this message is {first_bill_to_dispense},{last_bill_to_dispense}\x00 + random bytes.
The HSM will ensure each 16 byte block is different, and that the first n bytes of the message are the same and follow this format before proceeding to allow a transaction to occur. Additionally, in order to work correctly, the first bill to dispense must match what is saved on the HSM as the next bill to dispense.


## ATM Changes

##### The provision process for the ATM/HSM has changed.
  1. A uuid is sent to an HSM and stored. (hsm.py)
  2. The card loads bills from the bill file. (hsm.py)
  3. The card returns its unqiue AES_KEY. (hsm.py)
  4. The AES_KEY and number of bills are sent to the bank server and stored. (new function in bank.py)

##### The provision process for bank cards has changed.

  1. A uuid is sent to the card and stored.
  2. the card returns its unique AES_KEY
  3. The unique AES_KEY and pin for the account is sent to the bank and stored. (new function in bank.py)

##### Challenge Capabilities
  1. A function was added to bank.py to request a 32 byte alphanumeric challenge from the bank for a given card_id.
  2. A function was added on card.py to request that a challenge be encrypted and return the result

##### Withdraws
  1. The function to withdraw bills from the HSM now accepts a 64 byte message that the HSM will use to decrypt and send the appropriate bills.

## Bank Server



### Database
- Instead of using a sqlite database, we used mongoDB. There is no particular reason for this other then flexibility of documents, and my previous experience with mongoDB and lack thereof with sqlite

- There are two types of documents in the database, each having its own collection.

#### Account Collection
- An account is initialized with the following format:
```
new_account = {
    'account_name' : account_name,
    'card_id' : self.hash_card(card_id),
    'balance' : amount,
    'AES_KEY' : None,
    'pin' : None,
    'chall' : None,
    'time' : None
}
```


###### Fields provided/generated at creation
 - account_name: the plaintext account_name provided by an admin when the account is created
 - card_id: The card_id, which is hashed using SHA256
 - balance: The plaintext balance of an account

###### Fields generated at provision time
 - AES_KEY: a key generated on the PSOC during each request
 - pin: The pin salted with the plaintext card_id and hashed using argon2

###### Fields always updated when an request is initiated
 - chall: a 32 byte alphanumeric string
 - time: the time a the current chall will expire

###### Fields updated on successful withdraw
 - balance: The plaintext balance of an account

###### Fields updated on successful change pin
 - pin: The pin salted with the plaintext card_id and hashed using argon2



 #### ATM Fields

- An ATM is initialized with the following format
```
new_atm = {
       'atm_id' : atm_id,
       'num_bills' : 0,
       'num_dispensed_bills' : 0,
       'AES_KEY' : None
   }
```

###### Fields provided at creation
 - atm_id: The atm_id (hsm_id) in plaintext

###### Fields generated at provision time
 - AES_KEY: a key generated on the PSOC during each withdraw request
 - num_bills: The number of bills remaining on the HSM

####### Fields changed when a withdraw request is made
 - num_dispensed_bills: The number of bills the hsm has dispensed so far.
 - num_bills: The number of bills remaining on the HSM
