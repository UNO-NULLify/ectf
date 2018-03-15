# NULLify eCTF 2018 Documentation
  As a general approach, we modified the insecure example rather then starting from scratch. Details on each component are below.


## ATM
  - The general structure of our ATM is similar to the provided example. The major changes are discussed below.
  ##### bank.py
  - Instead of using XMLRPC, we use the requests module to make post requests to our bank applicable
  - We added three additional requests to the bank.py
    - get_challenge
        - requests a challenge for a particular bank card from the Bank
    - initialize_card
        - sends the necessary info to the bank to provision a card
    - initialize_hsm
        - sends the necessary info to the bank to provsion a atm/hsm

    ##### hsm.py
      - Provision process was changed
          - a uuid is sent and stored on the cards
          - the card returns its unqiue AES_KEY
          - The card loads bills from the bill file
      - the withdraw function was changed
          - it now only sends a encrypted 64 byte message that when decrypted, tells the hsm what to dispense

    #### card.py
      - Almost all major functions were changed/removed.
      - Provision process has changed
        - a uuid is sent and stored on the cards
        - the card returns its unique AES_KEY
      - A function was added to have the card encrypt a challenge with an AES_KEY and return the result

    #### atm.py
      - No significant flow changes have added.
      - For each possible operation, the atm facilitates retrieving a challenge from the bank, sending it to the card, getting a response from the card, and sending the response to the correct bank function (allow with the pin, card_id, and any operation specific data)



## Bank Server

### How requests are handled

- Instead of using XMLRPC, we are using a REST-like json interface.
- The server listens only for https requests
- When a request is made, it is checked to ensure all needed fields are present
- If all fields are present, the applicable account/atm will be retrieved, and the values will be checked to ensure they are appropriate and correct.
- ###### Each request must successfully pass the challenge/response  test
  - When a request is made, the atm first notifies the bank requesting a challenge
  - The bank updates the profiles document with a new challenge and timestamp
  - A card must encrypt that unique challenge with its AES_KEY and send it back to the Bank
  - If a card takes too long to respond (3 seconds), the challenge is invalidated
  - The bank also has the cards AES_KEY so if it can verify it was encrypted correctly.

- If all the above are correct/succeed , the request finishes.

### Database
- Instead of using a sqlite database, we used mongoDB. There is no particular reason for this other then flexibility of documents, and my previous experience with mongoDB and lack thereof with sqlite

- There are two types of documents in the database, each having its own collection.

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

#### Account Fields

###### Fields provided/generated at creation
 - account_name: the plaintext account_name provided by an admin when the account is created
 - card_id: The card_id, which is hashed using SHA256
 - balance: The plaintext balance of an account

###### Fields generated at provision time
 - AES_KEY: a key generated on the PSOC during each request
 - pin: The pin salted with the plaintext card_id and hashed using argon2

###### Fields changed when an initial request is made
 - chall: a 32 byte alphanumeric string
 - time: the time a the current chall will expire
 - balance (if applicable)


- An ATM is initialized with the following format
```
new_atm = {
       'atm_id' : atm_id,
       'num_bills' : 0,
       'num_dispensed_bills' : 0,
       'AES_KEY' : None
   }
```
#### ATM Fields
###### Fields provided at creation
 - atm_id: The atm_id (hsm_id) in plaintext

###### Fields generated at provision time
 - AES_KEY: a key generated on the PSOC during each withdraw request
 - num_bills: The number of bills loaded onto the HSM

 ####### Fields changed when a request is made
 - num_dispensed_bills: The number of bills the hsm has dispensed so far.
 - num_bills: Any withdrawn bills will be subtracted
