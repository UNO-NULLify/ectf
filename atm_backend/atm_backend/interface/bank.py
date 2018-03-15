"""Backend of ATM interface for xmlrpc"""

import logging
import sys
import socket
import requests
import json
import binascii


class Bank:
    """Interface for communicating with the bank

    Args:
        address (str): IP address of bank
        port (int): Port to connect to
    """

    def __init__(self, address='172.17.0.2', port="1337"):
        self.ip_address = 'https://' + str(address) + ':' + str(port)

    def check_balance(self, card_id, encrypted_response, pin):
        """Requests the balance of the account associated with the card_id

        Args:
            card_id (str): UUID of the ATM card to look up

        Returns:
            str: Balance of account on success
            bool: False on failure
        """
        logging.info('check_balance: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {
                        'card_id': str(card_id),
                        'encrypted_response': str(encrypted_response),
                        'pin':str(pin)
                       }

        response = requests.post(self.ip_address + '/balance', headers=headers, data=json.dumps(data_to_send),verify=False)

        if response.status_code == 403:
            return False
        elif response.status_code == 200:
             return int(str(response.json()['OK']))
        else:
            return False

    def withdraw(self, atm_id, card_id, encrypted_response, pin, amount):
        logging.info('withdraw: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {
                        'atm_id': str(atm_id),
                        'card_id': str(card_id),
                        'encrypted_response': str(encrypted_response),
                        'pin':str(pin),
                        'num_bills': str(amount)
                       }

        response = requests.post(self.ip_address + '/withdraw', headers=headers, data=json.dumps(data_to_send),verify=False)

        if response.status_code == 403:
            return False
        elif response.status_code == 200:
            return binascii.unhexlify(response.json()['OK'])
        else:
            return False

    def change_pin(self, card_id, encrypted_response, pin, new_pin):
        logging.info('change pin: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {
                        'card_id': str(card_id),
                        'encrypted_response': str(encrypted_response),
                        'pin':str(pin),
                        'new_pin': str(new_pin)
                       }
        response = requests.post(self.ip_address + '/change_pin', headers=headers, data=json.dumps(data_to_send),verify=False)
        if response.status_code == 403:
            return False
        elif response.status_code == 200:
            return True
        else:
            return False

    def get_challenge(self, card_id):
        logging.info('getting challenge: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id}
        response = requests.post(self.ip_address + '/get_challenge', headers=headers, data=json.dumps(data_to_send),verify=False)
        if response.status_code == 403:
            return False
        elif response.status_code == 200:
            return str(response.json()['OK'])
        else:
            return False

    def provision_card(self, card_id, pin, key):
        logging.info('provisioning_card: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {
                        'card_id': str(card_id),
                        'new_pin': str(pin),
                        'key': str(key)
                       }
        response = requests.post(self.ip_address + '/initalize_card', headers=headers, data=json.dumps(data_to_send),verify=False)
        if response.status_code == 403:
            return False
        elif response.status_code == 200:
            return True
        else:
            return False

    def provision_atm(self, atm_id, key, num_bills):
        logging.info('provisioning_card: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {
                        'atm_id': str(atm_id),
                        'key': str(key),
                        'num_bills' : str(num_bills)
                       }
        response = requests.post(self.ip_address + '/initalize_atm', headers=headers, data=json.dumps(data_to_send),verify=False)
        if response.status_code == 403:
            return False
        elif response.status_code == 200:
            return True
        else:
            return False