""" DB
This module implements an interface to the bank_server database.
It uses a mutex because both the bank_interface and admin_interface
need access to database. (sqlite3 does not gurantee concurrent operations)"""
from pymongo import MongoClient
from passlib import argon2

class DB(object):
    """Implements a Database interface for the bank server and admin interface"""
    def __init__(self):
        super(DB, self).__init__()
        self.client = MongoClient()
        self.db = self.client['bank_server']
        self.atms =  self.db['atm']
        self.users = self.db['users']

    ############################
    # BANK INTERFACE FUNCTIONS #
    ############################

    def set_balance(self, card_id, balance):
        """set balance of account: card_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.users.update_one({'card_id': self.hash(card_id)}, {"$set": {'balance': balance}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def get_balance(self, card_id):
        """get balance of account: card_id

        Returns:
            (string or None): Returns balance on Success. None otherwise.
        """
        account = self.users.find_one({'card_id':self.hash(card_id)})
        if account is None:
            return False
        else:
            return account['balance']

    def set_pin(self, card_id, new_pin):
        updated = self.users.update_one({'card_id': self.hash(card_id)}, {"$set": {'pin': self.hash(new_pin)}})
        return updated.acknowledged and updated.raw_result['updatedExisting']


    def empty_pin(self, card_id):
        """Checks if account has a pin. 
        (DOES NOT CHECK IF ACCOUNT IS NONE)

        Returns:
            (bool): Returns True if pin is empty. False otherwise.
        """
        account = self.get_account(card_id)
        if(account['pin'] is None or account['pin'] == ''):
            return True
        else:
            False

    def get_atm(self, atm_id):
        """get atm_id of atm: atm_id
        this is an obviously dumb function but maybe it can be expanded...

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        atm = self.atms.find_one({'atm_id': atm_id})
        if atm is None:
            return None
        else:
            return atm['atm_id']

    def get_account(self, card_id):
        """get card_id of account: card_id
        this is an obviously dumb function but maybe it can be expanded...

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        account = self.users.find_one({'card_id':self.hash(card_id)})
        if account is None:
            return None
        else:
            return account

    def get_atm_num_bills(self, atm_id):
        """get number of bills in atm: atm_id

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        atm = self.atms.find_one({'atm_id': atm_id})
        if atm is None:
            return None
        return atm['num_bills']

    def set_atm_num_bills(self, atm_id, num_bills):
        """set number of bills in atm: atm_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        updated = self.atms.update_one({'atm_id':atm_id},{"$set": {'num_bills': num_bills}})
        return updated.acknowledged and updated.raw_result['updatedExisting']

    def hash(self, string):
        """create a hash of input string (card_id or pin)

        Returns:
            (string): Returns hashed string.
        """
        return argon2.using(rounds=100000).hash(str(string))

    def verify_pin(self, pin, card_id):
        """verifies if pin matches database

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        account = self.get_account(card_id)
        if pin is None:
            return False
        elif account is None:
            return False
        elif self.empty_pin(card_id):
            return False
        else:
            db_pin = account['pin']
        return argon2.verify(pin, db_pin)

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
            'card_id' : self.hash(card_id),
            'balance' : amount,
            'pin': None
        }
        return self.users.insert_one(new_account).acknowledged

    def admin_create_atm(self, atm_id):
        """create atm with atm_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        new_atm = {
            'atm_id' : atm_id,
            'bills' : []
        }
        return self.atm.insert_one(new_atm).ackknowledged

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
