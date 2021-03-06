""" DB
This module implements an interface to the bank_server database.
It uses a mutex because both the bank_interface and admin_interface
need access to database. (sqlite3 does not gurantee concurrent operations)"""
from pymongo import MongoClient
from passlib.hash import argon2
from passlib.hash import sha256_crypt
import datetime
import string
import random
from Crypto.Cipher import AES

class DB(object):
    """Implements a Database interface for the bank server and admin interface"""
    def __init__(self):
        super(DB, self).__init__()
        self.client = MongoClient()
        self.db = self.client['bank_server']
        self.atms =  self.db['atms']
        self.users = self.db['users']

    ############################
    # BANK INTERFACE FUNCTIONS #
    ############################

    def verify_challenge(self, challenge, encrypted_response, AES_KEY, time):
        """verify the response to a challenge from a card

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        if datetime.datetime.now() > time:
            return False
        key = str(bytearray.fromhex(AES_KEY))
        cipher = AES.new(key, AES.MODE_ECB, '')
        decrypted_response = cipher.decrypt(str(bytearray.fromhex(encrypted_response)))
        return challenge == decrypted_response

    def set_balance(self, card_id, balance):
        """set balance of account

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.users.update_one({'card_id': self.hash_card(card_id)}, {"$set": {'balance': balance}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def set_pin(self, card_id, new_pin):
        """set the pin for account: card_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.users.update_one({'card_id': self.hash_card(card_id)}, {"$set": {'pin': self.hash_pin(card_id, new_pin)}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def get_atm(self, atm_id):
        """get atm_id of atm
        this is an obviously dumb function but maybe it can be expanded...

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        atm = self.atms.find_one({'atm_id': atm_id})
        if atm is None:
            return None
        else:
            return atm

    def get_account(self, card_id):
        """get account with card_id

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        account = self.users.find_one({'card_id':self.hash_card(card_id)})
        if account is None:
            return None
        else:
            return account

    def get_atm_num_bills(self, atm_id):
        """get number of bills in atm

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        atm = self.atms.find_one({'atm_id': atm_id})
        if atm is None:
            return None
        return atm['num_bills']

    def set_atm_num_bills(self, atm_id, num_bills):
        """set number of bills in atm

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.atms.update_one({'atm_id':atm_id},{"$set": {'num_bills': num_bills}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def set_atm_num_dispensed_bills(self, atm_id, num_bills):
        """set number of dispensed bills in atm

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.atms.update_one({'atm_id':atm_id},{"$set": {'num_dispensed_bills': num_bills}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def initialize_atm(self, key, num_bills, atm_id):
        """initalize a card by settings its AES_KEY and num_bills

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.atms.update_one({'atm_id':atm_id},{"$set": {'AES_KEY': key, 'num_bills':num_bills}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def hash_card(self, card_id):
        """create a hash of input card_id

        Returns:
            (string): Returns hashed string.
        """ 
        hash = sha256_crypt.using(salt_size=0,rounds=53500).hash(str(card_id))
        return hash[-86:]

    def hash_pin(self, card_id, pin):
        """create a hash of input pin

        Returns:
            (string): Returns hashed string.
        """
        hash = argon2.using(salt=bytes(card_id),digest_size=64,rounds=50).hash(str(pin))
        return hash[-86:]

    def verify_pin(self, pin, card_id, account):
        """verifies if pin matches database

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        if pin is None:
            return False
        elif account is None:
            return False
        elif account['pin'] == None or account['pin'] == '':
            return False
        return argon2.using(salt=bytes(card_id),digest_size=64,rounds=50).hash(str(pin))[-86:] == account['pin']

    def get_challenge(self, card_id):
        """creates a random challenge for a card id

        Returns:
            (str,bool): Returns 32 charecter alphanumeric challenges on Success. False otherwise.
        """

        chall = ''.join(random.SystemRandom().choice(string.ascii_letters + string.digits) for _ in range(32))
        updated = self.users.update_one({'card_id': self.hash_card(card_id)},{"$set": {'chall': chall, 'time': datetime.datetime.now() + datetime.timedelta(seconds=5)}})
        if updated.acknowledged and updated.raw_result['updatedExisting']:
            return chall
        else:
            return False

    def initialize_card(self, card_id, key, new_pin):
        """initializes a card by setting its pin and AES_KEY

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.users.update_one({'card_id': self.hash_card(card_id)},{"$set": {'AES_KEY': key,'pin': self.hash_pin(card_id, new_pin) }})
        return updated.acknowledged and updated.raw_result['updatedExisting']


    #############################
    # ADMIN INTERFACE FUNCTIONS #
    #############################

    def admin_create_account(self, account_name, card_id, amount):
        """create account with account_name, card_id, and amount

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        new_account = {
            'account_name' : account_name,
            'card_id' : self.hash_card(card_id),
            'balance' : amount,
            'AES_KEY' : None,
            'pin' : None,
            'chall' : None,
            'time' : None
        }
        return self.users.insert_one(new_account).acknowledged

    def admin_create_atm(self, atm_id):
        """create atm with atm_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        new_atm = {
            'atm_id' : atm_id,
            'num_bills' : 0,
            'num_dispensed_bills' : 0,
            'AES_KEY' : None
        }
        return self.atms.insert_one(new_atm).acknowledged

    def admin_get_balance(self, account_name):
        """get balance of account: account_name

        Returns:
            (string or None): Returns balance on Success. None otherwise.
        """
        account = self.users.find_one({'account_name':account_name})
        if account is None:
            return False
        else:
            return account['balance']

    def admin_set_balance(self, account_name, balance):
        """set balance of account: account_name

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.users.update_one({'account_name':account_name},{"$set": {'balance': balance}})
        return updated.acknowledged and updated.raw_result['updatedExisting']