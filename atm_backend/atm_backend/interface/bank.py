"""Backend of ATM interface for xmlrpc"""

import logging
import sys
import socket
import requests
import json


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
        print card_id
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id,
                        'encrypted_response': encrypted_response,
                        'pin':pin
                       }

        response = requests.post(self.ip_address + 'balance', headers=headers, data=json.dumps(data_to_send))

        if response.status_code == 403:
            return 'Transaction could not be verified.'
        else:
            return response.json()['balance']
        return False

    def withdraw(self, card_id, encrypted_response, pin, amount):
        logging.info('withdraw: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id,
                        'signed_message': encrypted_response,
                        'pin':pin,
                        'amount': amount
                       }

        response = requests.post(self.ip_address + 'withdraw', headers=headers, data=json.dumps(data_to_send))

        if response.status_code == 403:
            return 'Transaction could not be verified.'
        else:
            return response.json()['OK']
        return False

    def change_pin(self, card_id, encrypted_response, pin, new_pin):
        logging.info('change pin: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id,
                        'encrypted_response': encrypted_response,
                        'pin':pin,
                        'new_pin': new_pin
                       }
        response = requests.post(self.ip_address + 'change_pin', headers=headers, data=json.dumps(data_to_send))
        if response.status_code == 403:
            return 'Transaction could not be verified.'
        else:
            return True

    def get_challenge(self, card_id):
        logging.info('getting challenge: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {'card_id': card_id}
        response = requests.post(self.ip_address + 'get_challenge', headers=headers, data=json.dumps(data_to_send))
        if response.status_code == 403:
            return 'Transaction could not be verified.'
        else:
            return response.json()['OK']

    def provision_card(self, card_id, pin, key):
        print card_id
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
        else:
            return True

    def provision_atm(self, atm_id, key, num_bills):
        logging.info('provisioning_card: Sending request to Bank')
        headers = {'content-type': 'application/json'}
        data_to_send = {
                        'atm_id': atm_id,
                        'key': key,
                        'num_bills' : num_bills
                       }
        response = requests.post(self.ip_address + '/initalize_atm', headers=headers, data=json.dumps(data_to_send))
        if response.status_code == 403:
            return False
        else:
            return True
