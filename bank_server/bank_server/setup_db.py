from pymongo import MongoClient
client = MongoClient()
db = client['bank_server']
atms = db['atm']
users = db['user']
test = {'test': 1}
print (atms.insert_one(test))