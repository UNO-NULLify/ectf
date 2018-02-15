""" DB
This module implements an interface to the bank_server database.
It uses a mutex because both the bank_interface and admin_interface
need access to database. (sqlite3 does not gurantee concurrent operations)"""

import sqlite3
import os

class DB(object):
    """Implements a Database interface for the bank server and admin interface"""
    def __init__(self, db_mutex=None, db_init=None, db_path=None):
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
        return self.modify("UPDATE cards SET balance = (?) WHERE \
                                    card_id = (?);", (balance, card_id,))

    def get_balance(self, card_id):
        """get balance of account: card_id

        Returns:
            (string or None): Returns balance on Success. None otherwise.
        """
        self.cur.execute("SELECT balance FROM cards WHERE card_id = (?);", (card_id,))
        result = self.cur.fetchone()
        if result is None:
            return None
        return result[0]

    def get_atm(self, atm_id):
        """get atm_id of atm: atm_id
        this is an obviously dumb function but maybe it can be expanded...

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        self.cur.execute("SELECT atm_id FROM atms WHERE atm_id = (?);", (atm_id,))
        result = self.cur.fetchone()
        if result is None:
            return None
        return result[0]

    def get_atm_num_bills(self, atm_id):
        """get number of bills in atm: atm_id

        Returns:
            (string or None): Returns atm_id on Success. None otherwise.
        """
        self.cur.execute("SELECT num_bills FROM atms WHERE atm_id = (?);", (atm_id,))
        result = self.cur.fetchone()
        if result is None:
            return None
        return result[0]

    def set_atm_num_bills(self, atm_id, num_bills):
        """set number of bills in atm: atm_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        return self.modify("UPDATE atms SET num_bills = (?) WHERE \
                                    atm_id = (?);", (num_bills, atm_id,))

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
            'card_id' : card_id,
            'balance' : amount
        }
        return self.users.insert_one(new_account).acknowledged

    def admin_create_atm(self, atm_id):
        """create atm with atm_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        new_atm = {
            'atm_id' : atm_id
        }
        return self.atm.insert_one(new_atm).ackknowledged

    def admin_get_balance(self, account_name):
        """get balance of account: card_id

        Returns:
            (string or None): Returns balance on Success. None otherwise.
        """
        account = self.users.find_one({'account_name':account_name})
        if account is None:
            return False
        else:
            return account['balance']

    @lock_db
    def admin_set_balance(self, account_name, balance):
        """set balance of account: card_id

        Returns:
            (bool): Returns True on Success. False otherwise.
        """
        self.users.update_one({'name':'test2'},{"$set": {'balance': 87654321}}).acknowledged
